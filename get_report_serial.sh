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


echo '---Running ./heat-omp-icc---'
export OMP_NUM_THREADS=1
time ./heat-omp-icc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_icc_256_1024_4096.dat
export OMP_NUM_THREADS=4
time ./heat-omp-icc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_icc_256_1024_4096.dat
export OMP_NUM_THREADS=8
time ./heat-omp-icc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_icc_256_1024_4096.dat
export OMP_NUM_THREADS=16
time ./heat-omp-icc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_icc_256_1024_4096.dat
export OMP_NUM_THREADS=32
time ./heat-omp-icc 256 4096 ./COMP328_CA_DATA_FILES/input_1024.dat ./COMP328_CA_DATA_FILES/outputDemo_icc_256_1024_4096.dat
echo '---Ending ./heat-omp-icc----'