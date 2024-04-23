#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "file-reader.c"
#include "heat.c"

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (argc != 5) {
        if (world_rank == 0) {
            fprintf(stderr, "Usage: %s <N> <maxIter> <inputFileName> <outputFileName>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int N = atoi(argv[1]);
    int maxIter = atoi(argv[2]);
    char *inputFileName = argv[3];
    char *outputFileName = argv[4];

    int radNum;
    double *radTemps = NULL;
    double *subRadTemps;
    int *recvcounts, *displs;

    if (world_rank == 0) {
        radNum = read_dims(inputFileName);
        radTemps = read_array(inputFileName, radNum);
    }

    // Broadcast the number of radiator temperatures
    MPI_Bcast(&radNum, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Allocate memory for receive counts and displacements for each process
    recvcounts = (int *)malloc(world_size * sizeof(int));
    displs = (int *)malloc(world_size * sizeof(int));

    // Calculate the number of elements each process will handle
    int quotient = radNum / world_size;
    int remainder = radNum % world_size;

    for (int i = 0; i < world_size; i++) {
        recvcounts[i] = quotient + (i < remainder ? 1 : 0);
        displs[i] = (i > 0) ? (displs[i - 1] + recvcounts[i - 1]) : 0;
    }

    // Allocate memory for sub-array that will store the temperatures this process will handle
    subRadTemps = (double *)malloc(recvcounts[world_rank] * sizeof(double));

    // Scatter the radiator temperatures
    MPI_Scatterv(radTemps, recvcounts, displs, MPI_DOUBLE, subRadTemps, recvcounts[world_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Compute final temperatures for the subset of radiator temperatures
    double *subFinalTemperatures = get_final_temperatures(N, maxIter, subRadTemps, recvcounts[world_rank]);

    // Gather all final temperatures at root
    double *finalTemperatures = NULL;
    if (world_rank == 0) {
        finalTemperatures = (double *)malloc(radNum * sizeof(double));
    }

    // Gather the computed temperatures back to the root process
    MPI_Gatherv(subFinalTemperatures, recvcounts[world_rank], MPI_DOUBLE, finalTemperatures, recvcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        FILE *outfile = fopen(outputFileName, "w");
        if (!outfile) {
            fprintf(stderr, "Could not open %s for writing\n", outputFileName);
            free(radTemps);
            free(finalTemperatures);
            MPI_Finalize();
            return 1;
        }

        fprintf(outfile, "Final temperatures at the center of the room for different radiator temperatures:\n");
        for (int i = 0; i < radNum; i++) {
            fprintf(outfile, "Radiator Temp: %.2f, Center Temp: %.2f\n", radTemps[i], finalTemperatures[i]);
        }
        fclose(outfile);
        free(radTemps);
        free(finalTemperatures);
    }

    free(subRadTemps);
    free(subFinalTemperatures);
    free(recvcounts);
    free(displs);

    MPI_Finalize();
    return 0;
}
