# Compiler definitions
GCC = gcc -std=c99
ICC = icc -std=c99
MPICC = mpicc -std=c99
MPIICC = mpiicc -std=c99

# Common source files
COMMON_SRC = heat.c file-reader.c

# Executable names
GCC_SERIAL_EXE = heat-omp-gcc
GCC_COMPLETE_EXE = heat-complete-gcc
ICC_SERIAL_EXE = heat-omp-icc
ICC_COMPLETE_EXE = heat-complete-icc

# Compilation rules
all: loadCompilers gccserial gcccomplete iccserial icccomplete

gccserial: main-serial.c $(COMMON_SRC)
	$(GCC) -fopenmp main-serial.c $(COMMON_SRC) -o $(GCC_SERIAL_EXE) -lm

gcccomplete: main-mpi.c $(COMMON_SRC)
	$(MPICC) -fopenmp main-mpi.c $(COMMON_SRC) -o $(GCC_COMPLETE_EXE) -lm

iccserial: main-serial.c $(COMMON_SRC)
	$(ICC) -qopenmp main-serial.c $(COMMON_SRC) -o $(ICC_SERIAL_EXE) -lm

icccomplete: main-mpi.c $(COMMON_SRC)
	$(MPIICC) -qopenmp main-mpi.c $(COMMON_SRC) -o $(ICC_COMPLETE_EXE) -lm

# Clean rule
clean:
	rm -f $(GCC_SERIAL_EXE) $(GCC_COMPLETE_EXE) $(ICC_SERIAL_EXE) $(ICC_COMPLETE_EXE)
