#!/bin/env python

from __future__ import division
import fileinput
import time
import sys

start = time.time()
i = 0
for line in fileinput.input():
    if line[0] != '@':
        columns = line.split('\t')
        
        id = columns[0]
        chrom = columns[2]
        sequence = columns[9]
        qual = columns[10]
    
        assert len(sequence) == len(qual),'Wrong columns!!'
        
        if chrom == '*':
            i += 1
            print '@%s\n%s\n+\n%s' %(id,sequence,qual)
usedTime = time.time() -start
sys.stderr.write('Written %i sequences in %f min\n' %(i,usedTime/60))
