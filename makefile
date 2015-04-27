CC=gcc
filterReads: filterReads.c  khash.h  kseq.h
	gcc -lz filterReads.c -o filterReads

