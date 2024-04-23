#include <stdio.h>
#include <stdlib.h>
#include "file-reader.h"
#include "heat.h"

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
    write_to_output_file(outputFileName, finalTemperatures, radNum);
    free(radTemps);
    free(finalTemperatures);
    return 0;
}