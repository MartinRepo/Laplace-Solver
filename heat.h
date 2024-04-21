#ifndef LAPLACE_SOLVER_HEAT_H
#define LAPLACE_SOLVER_HEAT_H

void update_temperatures(double **curr_t, double **next_t, int N);
void set_radiator(double **t, int N, double temp);
double *get_final_temperatures(int N, int maxIter, double *radTemps, int numTemps);

#endif //LAPLACE_SOLVER_HEAT_H
