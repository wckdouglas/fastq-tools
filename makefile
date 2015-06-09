CC=gcc
Cpp=g++
CFLAGS=-lz
CPPFlags=-lgzstream -lz -Wall

all: filterFastq fastqSize

filterFastq: 
	$(CC) filterFastq.c -o filterFastqC  $(CFLAGS)
	$(Cpp) filterFastq.cpp -o filterFastqCPP  $(CFLAGS)

fastqSize: 
	$(Cpp) fastqSize.cpp -o fastqSize  $(CPPFlags)

