CC=gcc
Cpp=g++
MKDIR=mkdir -p
CFLAGS=-lz
CPPFlags=-lgzstream -lz -Wall
INCLUDE=-I include

all: binary filterFastq fastqSize

binary:
	$(MKDIR)  bin

filterFastq: 
	$(CC) src/filterFastq.c -o bin/filterFastqC  $(CFLAGS) $(INCLUDE)
	$(Cpp) src/filterFastq.cpp -o bin/filterFastq  $(CFLAGS) $(INCLUDE)

fastqSize: 
	$(Cpp) src/fastqSize.cpp -o bin/fastqSize  $(CPPFlags)

