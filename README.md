# fastq_manipulation

---
I will store any NGS manipulation scripts in this repository.

remove_reads.py and filterReads are both tools for filtering fastq files with unwanted read IDs. 

usage: ./remove_reads.py \<fastqFile\> \<idFile\>    
usage:  ./filterReads \<fastqFile\> \<idFile\>    

* \<fastqFile\> can be any four line fastq sequencing files
	* line 1: id
	* line 2: sequence
	* line 3:  + / +id
	* line 4: quality scores
* \<idFile\> sotres one id per line.


Benchmarking:
For a Fastq file with 8720139 reads, id file with 4477244 ids:


	$ time ./filterReads fastqFile  idFile | grep -c '^@'
	## 4242895
	## ./filterReads fastqFile
	## 18.07s user
	## 1.89s system
	## 99% cpu
	## 20.154 total

	$ time ./remove_reads.py fastqFile  idFile | grep -c '^@'
	## 4242895
	## ./remove_reads.py fastqFile
	## 62.37s user
	## 2.81s system
	## 99% cpu
	## 1:05.44 total

Major difference, filterReads.c hashed id list instead of fastq file when comparing to remove_reads.py
