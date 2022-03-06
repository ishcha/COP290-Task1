# Usage
# make all
# make clean

CC = g++
CFLAGS = -g -Wall
# MKL_BLAS_PATH = /opt/intel/compilers_and_libraries_2018.2.199/linux/mkl
MKLFLAGS = -fopenmp -m64 -I${MKL_BLAS_PATH}/include -Wl,--no-as-needed -L${MKL_BLAS_PATH}/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl
LIBPATH = $(shell pwd)

SRCS = audioAPI.cpp activation.cpp probability.cpp fc_mkl.cpp
OBJS = $(SRCS:.cpp=.o)
FILE = yourcode.out

all:$(FILE) # here the yourcode executable is made 

$(FILE): main.cpp libaudioAPI.so
	$(CC) -L/$(LIBPATH) $(CFLAGS) -o $(FILE) main.cpp -laudioAPI $(MKLFLAGS)

libaudioAPI.so: $(OBJS)
	$(CC) $(CFLAGS) -shared -o libaudioAPI.so $(OBJS) $(MKLFLAGS)

audioAPI.o: audioAPI.cpp audioAPI.h utility.h constants.h # audioAPI.o binary created
	$(CC) $(CFLAGS) -c -Werror -fpic audioAPI.cpp

activation.o: activation.cpp utility.h # OK: just compile activation.cpp having relu
	$(CC) $(CFLAGS) -c activation.cpp

probability.o: probability.cpp utility.h # OK: just compile probability.cpp having softmax
	$(CC) $(CFLAGS) -c probability.cpp

fc_mkl.o:fc_mkl.cpp utility.h # OK: just compile fc_mkl.cpp with MKLFLAGS
	$(CC) $(CFLAGS) -c fc_mkl.cpp $(MKLFLAGS)

clean:
	rm $(FILE) $(OBJS) *.so