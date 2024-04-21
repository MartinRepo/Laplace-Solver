#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void update_temperatures(double **curr_t, double **next_t, int N) {
#pragma omp parallel for default(none) shared(next_t, curr_t, N) collapse(2)
    for (int i = 1; i < N-1; i++) {
        for (int j = 1; j < N - 1; j++) {
            next_t[i][j] = (curr_t[i - 1][j] + curr_t[i + 1][j] + curr_t[i][j - 1] + curr_t[i][j + 1]) / 4.0;
        }
    }
}


void set_radiator(double **t, int N, double temp) {
    int start = floor((N-1) * 0.3);
    int end = ceil((N-1) * 0.7);
    for (int j = start; j <= end; j++) {
        t[N-1][j] = temp;
    }
}

double *get_final_temperatures(int N, int maxIter, double *radTemps, int numTemps) {
    double *results = (double*)malloc(numTemps * sizeof(double));
    double **curr_t = (double **)malloc(N * sizeof(double *));
    double **next_t = (double **)malloc(N * sizeof(double *));

    for (int i = 0; i < N; i++) {
        curr_t[i] = (double *)malloc(N * sizeof(double));
        next_t[i] = (double *)malloc(N * sizeof(double));
        for (int j = 0; j < N; j++) {
            curr_t[i][j] = 20.0; // Initial temperature of the room
        }
    }

    int pointx = floor((N - 1) * 0.5);
    int pointy = floor((N - 1) * 0.5);

    for (int temp = 0; temp < numTemps; temp++) {
        set_radiator(curr_t, N, radTemps[temp]);

        for (int iter = 0; iter < maxIter; iter++) {
            update_temperatures(curr_t, next_t, N);
            // Swap pointers for next iteration
            double **temp_ptr = curr_t;
            curr_t = next_t;
            next_t = temp_ptr;
        }
        results[temp] = curr_t[pointx][pointy];
    }

    for (int i = 0; i < N; i++) {
        free(curr_t[i]);
        free(next_t[i]);
    }
    free(curr_t);
    free(next_t);

    return results;
}
