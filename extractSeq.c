#include <zlib.h>
#include <stdio.h>
#include <string.h>
#include "kseq.h"
#include "khash.h"

#define BUF_SIZE 2048
KSEQ_INIT(gzFile, gzread);
KHASH_SET_INIT_STR(s)

char *strstrip(char *s) // function for striping lines
{
	size_t size;
	char *end;

	size = strlen(s);

	if (!size)
		return s;

	end = s + size - 1;
	while (end >= s && isspace(*end))
		end--;
	*(end + 1) = '\0';

	while (*s && isspace(*s))
		s++;

	return s;
}


int main(int argc , char *argv[]){

	//declare variable
	char buf[BUF_SIZE];
	gzFile fp;
	kseq_t *seq;
	int lineno = 0, flag = 0, ret,l;
	char *id, *sequence, *qual, *comment;
	khash_t(s) *h;
	khint_t k;

	// print usage if not enough argumnets
	if (argc != 3){
		fprintf(stderr,"Usage: %s <fastq file> <idFile>  >  <new fastq file>\n",argv[0]);
		return 1;
	}
	fprintf(stderr,"Reading id file: %s\nFrom %s....\n" ,argv[2],argv[1] );

	//idFile read and put in index
	h = kh_init(s);
	fp = fopen(argv[2], "rb"); 
	while (fgets(buf, BUF_SIZE, fp)){
		kh_put(s, h, strstrip(strdup(buf)), &ret);
	}
	fclose(fp);


	//open fastq file
	fp = gzopen(argv[1],"r"); // open fastq file for kseq parsing 
	seq = kseq_init(fp);

	// start reading sequecne
	while ((l = kseq_read(seq)) >= 0){
		id = seq -> name.s;
		comment = seq -> comment.s;
		qual = seq -> qual.s;
		sequence = seq -> seq.s;
		flag = (kh_get(s, h, id) < kh_end(h));
		if (flag==1){
			printf("@%s\t%s\n%s\n+\n%s\n", id,comment,sequence,qual); // print out seqeunce in fastq format
		}
	}
	kh_destroy(s,h);
}
