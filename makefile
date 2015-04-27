CC=gcc
<<<<<<< HEAD

filterReads: filterReads.c  khash.h  kseq.h
	$(CC) -lz filterReads.c -o filterReads
=======
CFLAGS=-lz

filterReads: filterReads.c  khash.h  kseq.h
	$(CC) $(CFLAGS) filterReads.c -o filterReads
>>>>>>> 176182c6b9b1a65c5eff46ca64f1c500b66b641b

