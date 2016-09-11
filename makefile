CC=gcc
CPP=g++
MKDIR=mkdir -p
CFLAGS=-lz
CPP_FLAGS=-Wall  -lstdc++
INCLUDE=-I./include 
GZLIB_FLAG=-L./lib -lgzstream -lz 

all: binary filterFastq

binary:
	$(MKDIR)  bin

filterFastq: 
	$(CC) src/filterFastq.c -o bin/filterFastqC  $(CFLAGS) $(INCLUDE)
	$(CPP) src/filterFastq.cpp -o bin/filterFastq  $(CFLAGS) $(INCLUDE)

fastqSize: 
	$(CPP) src/fastqSize.cpp -o bin/fastqSize  $(CPPFlags) $(INCLUDE)

splitFastq:
	$(CPP) src/splitReads.cpp -o bin/splitFastq $(CPPFlags) $(ZipFlags) $(INCLUDE)

sam2fastq:
	$(CPP) src/sam2fastq.cpp -o bin/sam2fastq $(INCLUDE)
