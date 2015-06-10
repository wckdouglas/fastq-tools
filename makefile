CC=gcc
Cpp=g++
MKDIR = mkdir 
CFLAGS=-lz
CPPFlags=-lgzstream -lz -Wall

.PHONY: binary



all: binary filterFastq fastqSize

binary:
	${MKDIR}  ./bin

filterFastq: 
	$(CC) filterFastq.c -o ./bin/filterFastq  $(CFLAGS)
	$(Cpp) filterFastq.cpp -o ./bin/filterFastqCPP  $(CFLAGS)

fastqSize: 
	$(Cpp) fastqSize.cpp -o ./bin/fastqSize  $(CPPFlags)

