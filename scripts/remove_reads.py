#!/usr/bin/env python

from Bio.SeqIO.QualityIO import FastqGeneralIterator
import sys


if len(sys.argv) != 3:
    sys.exit('\nusage: python remove_reads.py fastqFile idFile \n\
              \nThis is a prgram to remove records from id list output is a fastq file \
              \n      1. sequence file needs to be fastq \
              \n      2. idfile is one id per line text file (without "@" sign in front of the id )\n')

# set up fastq index
index = {id.split(' ')[0]:'@%s\n%s\n+\n%s' %(id,seq,qual) for id, seq, qual in FastqGeneralIterator(open(sys.argv[1]))}

# read mapped ID
mapped_id_list = [line.strip() for line in open(sys.argv[2],'r')]

# get unmapped IDs
ids = set(index.keys()) - set(mapped_id_list)
ids = list(ids)
ids.sort()

# print sequences
for id in ids:
    print index[id]

