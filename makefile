CC=gcc
CFLAGS=-lz

all: filterReads extractSeq

filterReads: 
	$(CC) $(CFLAGS) -o filterReads filterReads.c  

extractSeq: 
	$(CC) $(CFLAGS) -o extractSeq extractSeq.c 

