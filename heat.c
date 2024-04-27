#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <sys/time.h>

double *get_final_temperatures(int N, int maxIter, double *radTemps, int numTemps) {
    double *results = (double *)malloc(numTemps * sizeof(double));
    double ***t = (double ***)malloc(2 * sizeof(double **));

    int pointx = floor((N - 1) * 0.5);
    int pointy = floor((N - 1) * 0.5);

    for (int k = 0; k < 2; k++) {
        t[k] = (double **)malloc(N * sizeof(double *));
        for (int i = 0; i < N; i++) {
            t[k][i] = (double *)malloc(N * sizeof(double));
        }
    }
    struct timeval startTime, endTime;
    long seconds, useconds;
    double total_time;
    for (int temp = 0; temp < numTemps; temp++) {
        gettimeofday(&startTime, NULL);
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    t[k][i][j] = 10.0;
                }
            }
        }
        int start = floor((N-1) * 0.3);
        int end = ceil((N-1) * 0.7);
        for (int k = 0; k < 2; k++) {
            for (int j = start; j <= end; j++) {
                t[k][j][N-1] = radTemps[temp];
            }
        }
        int curr = 0;
        int next = 1;

        for (int iter = 0; iter < maxIter; iter++) {
            #pragma omp parallel for default(none) shared(t, curr, next, N) collapse(2)
            for (int i = 1; i < N-1; i++) {
                for (int j = 1; j < N-1; j++) {
                    t[next][i][j] = (t[curr][i - 1][j] + t[curr][i + 1][j] + t[curr][i][j - 1] + t[curr][i][j + 1]) / 4.0;
                }
            }
            int temp_idx = curr;
            curr = next;
            next = temp_idx;
        }
        results[temp] = t[curr][pointx][pointy];
        gettimeofday(&endTime, NULL);
        seconds  = endTime.tv_sec  - startTime.tv_sec;
        useconds = endTime.tv_usec - startTime.tv_usec;
        total_time = seconds + useconds/1000000.0;

        printf("Loop took %f seconds to execute.\n", total_time);
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
