CC=gcc
CFLAGS=-lz

filterReads: filterReads.c  khash.h  kseq.h
	$(CC) -lz filterReads.c -o filterReads
