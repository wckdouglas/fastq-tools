CC=gcc

filterReads: filterReads.c  khash.h  kseq.h
	$(CC) -lz filterReads.c -o filterReads

