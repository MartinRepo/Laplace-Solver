#include <stdlib.h>
#include <math.h>

double *get_final_temperatures(int N, int maxIter, double *radTemps, int numTemps){
    double *results = (double*)malloc(numTemps * sizeof(double));
    for(int temp = 0; temp < numTemps; temp++){
        int curr_t[N][N];
        int pointx = floor((N - 1)*0.5);
        int pointy = floor((N - 1)*0.5);
        double result = curr_t[pointx][pointy];
        results[temp] = result;
    }
    return results ;
}
