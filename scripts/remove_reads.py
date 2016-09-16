#!/usr/bin/env python

from Bio.SeqIO.QualityIO import FastqGeneralIterator
import sys

if len(sys.argv) != 3:
    sys.exit('\nusage: python remove_reads.py fastqFile idFile \n\
              \nThis is a prgram to remove records from id list output is a fastq file \
              \n      1. sequence file needs to be fastq \
              \n      2. idfile is one id per line text file (without "@" sign in front of the id )\n')


# read mapped ID
index = {line.strip():1  for line in open(sys.argv[2],'r')}
sys.stderr.write ('Indexed!\n')


# print sequences
count = 0
for id, seq, qual in FastqGeneralIterator(open(sys.argv[1])):
	try: 
		a = index[id.split(' ')[0]]
		pass
	except KeyError:
		print "@%s\n%s\n+\n%s" %(id,seq,qual)


