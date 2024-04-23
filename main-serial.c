#include <stdio.h>
#include <stdlib.h>
#include "file-reader.c"
#include "heat.c"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <N> <maxIter> <inputFileName> <outputFileName>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int maxIter = atoi(argv[2]);
    char *inputFileName = argv[3];
    char *outputFileName = argv[4];
    int radNum = read_dims(inputFileName);
    double* radTemps = read_array(inputFileName, radNum);
    double *finalTemperatures = get_final_temperatures(N, maxIter, radTemps, radNum);
    FILE *outfile = fopen(outputFileName, "w");
    if (!outfile) {
        fprintf(stderr, "Could not open %s for writing\n", outputFileName);
        return 1;
    }

    fprintf(outfile, "Final temperatures at the center of the room for different radiator temperatures:\n");
    for (int i = 0; i < radNum; i++) {
        fprintf(outfile, "Radiator Temp: %.2f, Center Temp: %.2f\n", radTemps[i], finalTemperatures[i]);
    }
    fclose(outfile);
    free(radTemps);
    free(finalTemperatures);
    return 0;
}