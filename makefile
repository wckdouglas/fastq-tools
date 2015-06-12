CC=gcc
Cpp=g++
MKDIR=mkdir -p
CFLAGS=-lz
CPPFlags=-lgzstream -lz -Wall
INCLUDE=-l include

all: binary filterFastq fastqSize

binary:
	$(MKDIR)  bin

filterFastq: 
	$(CC) src/filterFastq.c -o bin/filterFastq  $(CFLAGS) $(INCLUDE)
	$(Cpp) src/filterFastq.cpp -o bin/filterFastqCPP  $(CFLAGS) $(INCLUDE)

fastqSize: 
	$(Cpp) src/fastqSize.cpp -o bin/fastqSize  $(CPPFlags)

