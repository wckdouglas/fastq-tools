CC=gcc
CPP=g++
MKDIR=mkdir -p
CFLAGS=-lz
CPP_FLAGS=-Wall # -lstdc++
INCLUDE=-I./include 
GZLIB_FLAG=-L./lib -lgzstream -lz 

all: binary filterFastq splitFastq sam2fastq

binary:
	$(MKDIR)  bin

filterFastq: 
	$(CC)  src/filterFastq.c -o bin/filterFastqC   $(INCLUDE) $(CFLAGS)
	$(CPP) src/filterFastq.cpp -o bin/filterFastq   $(INCLUDE) $(CFLAGS)

splitFastq:
	$(CPP) src/splitReads.cpp -o bin/splitFastq  $(INCLUDE) $(CPP_FLAGS) $(GZLIB_FLAG) 

sam2fastq:
	$(CPP) src/sam2fastq.cpp -o bin/sam2fastq $(INCLUDE)
