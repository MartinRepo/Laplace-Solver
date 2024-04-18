# Compiler definitions
GCC = gcc -std=c11
ICC = icc -std=c11
MPICC = mpicc -std=c11
MPIICC = mpiicc -std=c11

# Common source files
COMMON_SRC = heat.c file-reader.c

# Executable names
GCC_SERIAL_EXE = heat-omp-gcc
GCC_COMPLETE_EXE = heat-complete-gcc
ICC_SERIAL_EXE = heat-omp-icc
ICC_COMPLETE_EXE = heat-complete-icc

# Compilation rules
all: gccserial gcccomplete iccserial icccomplete

gccserial: main-serial.c $(COMMON_SRC)
	$(GCC) -o $(GCC_SERIAL_EXE) main-serial.c $(COMMON_SRC)

gcccomplete: main-mpi.c $(COMMON_SRC)
	$(MPICC) -o $(GCC_COMPLETE_EXE) main-mpi.c $(COMMON_SRC)

iccserial: main-serial.c $(COMMON_SRC)
	$(ICC) -o $(ICC_SERIAL_EXE) main-serial.c $(COMMON_SRC)

icccomplete: main-mpi.c $(COMMON_SRC)
	$(MPIICC) -o $(ICC_COMPLETE_EXE) main-mpi.c $(COMMON_SRC)

# Clean rule
clean:
	rm -f $(GCC_SERIAL_EXE) $(GCC_COMPLETE_EXE) $(ICC_SERIAL_EXE) $(ICC_COMPLETE_EXE)
