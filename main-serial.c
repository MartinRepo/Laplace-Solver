#include <stdio.h>
#include <stdlib.h>

double *get_final_temperatures(int N, int maxIter, double *radTemps, int numTemps);
int read_dims(char *filename);
double *read_array(char *filename, int numOfValues);
void *write_to_output_file(char *filename, double *output, int numOfValues);

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