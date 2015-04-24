# fastq_manipulation

---
I will store any NGS manipulation scripts in this repository.

remove_reads.py and filterReads are both tools for filtering fastq files with unwanted read IDs. 

usage: ./remover_reads.py <fastqFile> <idFile>    
usage:  ./filterReads <fastqFile> <idFile>    

* <fastqFile> can be any four line fastq sequencing files
	* line 1: id
	* line 2: sequence
	* line 3:  + / +id
	* line 4: quality scores
* <idFile> sotres one id per line.
