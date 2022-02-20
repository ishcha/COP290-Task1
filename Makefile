# Usage
# make
# make clean

CC = g++
CFLAGS = -g -Wall
LIBS = -lm
MKLROOT = /opt/intel/compilers_and_libraries_2018.2.199/linux/mkl
MKLFLAGS = -fopenmp -m64 -I${MKLROOT}/include -Wl,--no-as-needed -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl

SRCS = main.cpp activation.cpp fullyconnected.cpp pooling.cpp probability.cpp helper.cpp fc_pthread.cpp fc_mkl.cpp
OBJS = $(SRCS:.cpp=.o)
FILE = yourcode.out

all:$(FILE)
$(FILE): $(OBJS)
	$(CC) $(CFLAGS) -o $(FILE) $(OBJS) -pthread $(MKLFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

activation.o: activation.cpp
	$(CC) $(CFLAGS) -c activation.cpp

fullyconnected.o: fullyconnected.cpp
	$(CC) $(CFLAGS) -c fullyconnected.cpp

helper.o: helper.cpp
	$(CC) $(CFLAGS) -c helper.cpp

probability.o: probability.cpp
	$(CC) $(CFLAGS) -c probability.cpp

pooling.o: pooling.cpp
	$(CC) $(CFLAGS) -c pooling.cpp

fc_pthread.o: fc_pthread.cpp
	$(CC) $(CFLAGS) -c fc_pthread.cpp -pthread

fc_mkl.o:fc_mkl.cpp
	$(CC) $(CFLAGS) -c fc_mkl.cpp $(MKLFLAGS)

clean:
	rm $(FILE) $(OBJS)