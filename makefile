CC=gcc
CFLAGS=-lz

all: filterFastq

filterFastq: 
	$(CC) $(CFLAGS) -o filterFastq filterFastq.c  

#extractSeq: 
#	$(CC) $(CFLAGS) -o extractSeq extractSeq.c 

