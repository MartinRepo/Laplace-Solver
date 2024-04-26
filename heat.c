#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void update_temperatures(double ***t, int curr, int next, int N) {
#pragma omp parallel for default(none) shared(t, curr, next, N) collapse(2)
    for (int i = 1; i < N-1; i++) {
        for (int j = 1; j < N-1; j++) {
            t[next][i][j] = (t[curr][i - 1][j] + t[curr][i + 1][j] + t[curr][i][j - 1] + t[curr][i][j + 1]) / 4.0;
        }
    }
}

void set_radiator(double **t1, double **t2, int N, double temp) {
    int start = floor((N-1) * 0.3);
    int end = ceil((N-1) * 0.7);
    for (int j = start; j <= end; j++) {
        t1[j][N-1] = temp;
        t2[j][N-1] = temp;
    }
}

double *get_final_temperatures(int N, int maxIter, double *radTemps, int numTemps) {
    double *results = (double *)malloc(numTemps * sizeof(double));
    double ***t = (double ***)malloc(2 * sizeof(double **));

    int pointx = floor((N - 1) * 0.5);
    int pointy = floor((N - 1) * 0.5);

    for (int temp = 0; temp < numTemps; temp++) {
        for (int k = 0; k < 2; k++) {
            t[k] = (double **)malloc(N * sizeof(double *));
            for (int i = 0; i < N; i++) {
                t[k][i] = (double *)malloc(N * sizeof(double));
                for (int j = 0; j < N; j++) {
                    t[k][i][j] = 10.0;
                }
            }
        }
        set_radiator(t[0], t[1], N, radTemps[temp]); // Assume the initial radiator setup is done in t[0]
        int curr = 0;
        int next = 1;

        for (int iter = 0; iter < maxIter; iter++) {
            update_temperatures(t, curr, next, N);
            // Swap indices for next iteration
            int temp_idx = curr;
            curr = next;
            next = temp_idx;
        }
        results[temp] = t[curr][pointx][pointy];
    }

    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < N; i++) {
            free(t[k][i]);
        }
        free(t[k]);
    }
    free(t);

    return results;
}
