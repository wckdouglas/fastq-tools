CC=gcc
CFLAGS=-lz

filterReads: filterReads.c  khash.h  kseq.h
	$(CC) $(CFLAGS) filterReads.c -o filterReads

