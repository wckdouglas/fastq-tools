CC=gcc
CPP=g++
MKDIR=mkdir -p
GZLIB_FLAG=-L./lib -lgzstream -lz
CPP_FLAGS=-lstdc++ $(GZLIB_FLAG)
INCLUDE=-I./include 

all: binary filterFastq splitFastq sam2fastq

binary:
	$(MKDIR)  bin

filterFastq: 
	$(CC) src/filterFastq.c -o bin/filterFastqC  $(GZLIB_FLAG) $(INCLUDE)
	$(CPP) src/filterFastq.cpp -o bin/filterFastq  $(CPP_FLAGS) $(INCLUDE)

fastqSize: 
	$(CPP) src/fastqSize.cpp -o bin/fastqSize  $(CPPFlags) $(INCLUDE)

splitFastq:
	$(CPP) src/splitReads.cpp -o bin/splitFastq $(CPPFlags) $(GZLIB_FLAG) $(INCLUDE) 

sam2fastq:
	$(CPP) src/sam2fastq.cpp -o bin/sam2fastq $(INCLUDE) $(GZLIB_FLAG)
