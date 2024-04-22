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
#SBATCH -t 1


echo '---Running ./heat-omp-gcc---'

time ./heat-omp-gcc 10 20 ./COMP328_CA_DATA_FILES/input_10.dat ./COMP328_CA_DATA_FILES/outputDemo_10_10_20_.dat

echo '---Ending ./heat-omp-gcc----'