#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double *get_final_temperatures(int N, int maxIter, double *radTemps, int numTemps) {
    // allocate memory in advance
    double *results = (double *)malloc(numTemps * sizeof(double));
    #pragma omp parallel for
    for (int temp = 0; temp < numTemps; temp++) {
        double ***t = (double ***)malloc(2 * sizeof(double **));
        for (int k = 0; k < 2; k++) {
            t[k] = (double **)malloc(N * sizeof(double *));
            for (int i = 0; i < N; i++) {
                t[k][i] = (double *)malloc(N * sizeof(double));
                for (int j = 0; j < N; j++) {
                    t[k][i][j] = 10.0;
                }
            }
        }
        // set radiator on the wall
        int start = floor((N-1) * 0.3);
        int end = ceil((N-1) * 0.7);
        for (int k = 0; k < 2; k++) {
            for (int j = start; j <= end; j++) {
                t[k][j][N-1] = radTemps[temp];
            }
        }

        int curr = 0;
        int next = 1;
        int column = N-2;
        // start iteration...
        for (int iter = 0; iter < maxIter; iter++) {
            if (iter >= N-3) {
                for (int i = 1; i < N-1; i++) {
                    for (int j = 1; j < N-1; j++) {
                        double newTemp = (t[curr][i - 1][j] + t[curr][i][j - 1] + t[curr][i + 1][j] + t[curr][i][j + 1]) * 0.25;
                        t[next][i][j] = newTemp;
                    }
                }
            } else {
                for(int col = column; col < N-1; col++) {
                    for(int row = 1; row < N-1; row++) {
                        double newTemp = (t[curr][row - 1][col] + t[curr][row][col - 1] + t[curr][row + 1][col] + t[curr][row][col + 1]) * 0.25;
                        t[next][row][col] = newTemp;
                    }
                }
                column--;
            }
            int temp_idx = curr;
            curr = next;
            next = temp_idx;
        }
        // store result
        int pointx = floor((N - 1) * 0.5);
        int pointy = floor((N - 1) * 0.5);
        results[temp] = t[curr][pointx][pointy];
        // free memory
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < N; i++) {
                free(t[k][i]);
            }
            free(t[k]);
        }
        free(t);
    }
    return results;
}