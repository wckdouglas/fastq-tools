CC=gcc
Cpp=g++
MKDIR=mkdir -p
CFLAGS=-lz
CPPFlags=-lgzstream -lz -Wall
ZipFlags=-lstdc++
INCLUDE=-I include

all: binary filterFastq

binary:
	$(MKDIR)  bin

filterFastq: 
	$(CC) src/filterFastq.c -o bin/filterFastqC  $(CFLAGS) $(INCLUDE)
	$(Cpp) src/filterFastq.cpp -o bin/filterFastq  $(CFLAGS) $(INCLUDE)

fastqSize: 
	$(Cpp) src/fastqSize.cpp -o bin/fastqSize  $(CPPFlags) $(INCLUDE)

splitFastq:
	$(Cpp) src/splitReads.cpp -o bin/splitFastq $(CPPFlags) $(ZipFlags) $(INCLUDE)

sam2fastq:
	$(Cpp) src/sam2fastq.cpp -o bin/sam2fastq $(INCLUDE)
