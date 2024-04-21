#ifndef LAPLACE_SOLVER_FILE_READER_H
#define LAPLACE_SOLVER_FILE_READER_H

void read_dims(char *filename);
void read_array(char *filename, int numOfValues);
void write_to_output_file(char *filename, double *output, int numOfValues);

#endif //LAPLACE_SOLVER_FILE_READER_H
