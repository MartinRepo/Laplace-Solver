#!/bin/bash -l

# Specify the current working directory as the location for executables/files
#This is the default setting.
#SBATCH -D ./

# Export the current environment to the compute node (all modules that are loaded)
# This is the default setting.
#SBATCH --export=ALL

# Specific course queue, exclusive use (for timings), max 1 min wallclock time.
#SBATCH -p course
#SBATCH --exclusive
#SBATCH -t 10


echo '---Running ./heat-omp-gcc---'
#export OMP_NUM_THREADS=1
#time ./heat-omp-gcc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_gcc_256_1024_4096.dat
#export OMP_NUM_THREADS=2
#time ./heat-omp-gcc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_gcc_256_1024_4096.dat
#export OMP_NUM_THREADS=4
#time ./heat-omp-gcc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_gcc_256_1024_4096.dat
#export OMP_NUM_THREADS=8
#time ./heat-omp-gcc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_gcc_256_1024_4096.dat
#export OMP_NUM_THREADS=16
#time ./heat-omp-gcc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_gcc_256_1024_4096.dat
#export OMP_NUM_THREADS=32
time ./heat-omp-gcc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_gcc_256_1024_4096.dat
time ./heat-omp-icc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_icc_256_1024_4096.dat
time mpirun -np 4 ./heat-complete-gcc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_mpicc_256_1024_4096.dat
time mpirun -np 4 ./heat-complete-icc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_mpiicc_256_1024_4096.dat
echo '---Ending ./heat-omp-gcc----'