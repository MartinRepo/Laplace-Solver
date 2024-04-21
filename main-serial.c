#include <stdio.h>
#include "file-reader.c"
#include "heat.c"

void printArray(double* array, int length) {
    for (int i = 0; i < length; i++) {
        printf("%.2f ", array[i]);
    }
}

int main() {
    printf("main-serial.c\n");
    int radNum = read_dims("COMP328_CA_DATA_FILES/input_10.dat");
    printf("here is output %d\n", radNum);
    double* radTemps = read_array("COMP328_CA_DATA_FILES/input_10.dat", radNum);
    printArray(radTemps, radNum);
    int N = 10;
    int maxIter = 1000;
    double *finalTemperatures = get_final_temperatures(N, maxIter, radTemps, radNum);

    printf("Final temperatures at the center of the room for different radiator temperatures:\n");
    for (int i = 0; i < radNum; i++) {
        printf("Radiator Temp: %.2f, Center Temp: %.2f\n", radTemps[i], finalTemperatures[i]);
    }

    free(finalTemperatures);
    return 0;
}