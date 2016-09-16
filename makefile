CC=gcc
Cpp=g++
MKDIR=mkdir -p
CFLAGS=-lz
CPPFlags=-lgzstream -lz -Wall -I./include -L./include
ZipFlags=-lstdc++
INCLUDE=-I include

all: binary filterFastq fastqSize splitFastq sam2fastq

binary:
	$(MKDIR)  bin

filterFastq: 
	$(CC) src/filterFastq.c -o bin/filterFastqC  $(CFLAGS) $(INCLUDE)
	$(Cpp) src/filterFastq.cpp -o bin/filterFastq  $(CFLAGS) $(INCLUDE)

fastqSize: 
	$(Cpp) src/fastqSize.cpp -o bin/fastqSize  $(CPPFlags)

splitFastq:
	$(Cpp) src/splitReads.cpp -o bin/splitFastq $(CPPFlags) $(ZipFlags)

sam2fastq:
	$(Cpp) src/sam2fastq.cpp -o bin/sam2fastq $(INCLUDE)
