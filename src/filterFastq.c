#include <zlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "kseq.h"
#include "khash.h"

KSEQ_INIT(gzFile, gzread);
KHASH_SET_INIT_STR(s)
#define BUF_SIZE 2048

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

int writeSequence(char *idFile, char *fqFile, int mode){
	//function for write fastq//
	fprintf(stderr,"Reading file: %s\nFrom %s...\n" ,idFile,fqFile);
	
	//declare variable
	char buf[BUF_SIZE];
	gzFile fp;
	kseq_t *seq;
	int lineno = 0, ret, l, seqCount = 0 ,flag;
	char *id, *sequence, *qual, *comment=0;

	// hashing id file
	khash_t(s) *h;
	khint_t k;
	h = kh_init(s);
	fp = fopen(idFile, "rb"); 
	while (fgets(buf, BUF_SIZE, fp)){
		kh_put(s, h, strstrip(strdup(buf)), &ret);
	}
	fclose(fp);

	//open fastq file
	fp = gzopen(fqFile,"r"); // open fastq file for kseq parsing 
	seq = kseq_init(fp);

	//================================================================
	// filter id
	while ((l = kseq_read(seq)) >= 0)
	{
		id = seq -> name.s;
		comment = seq -> comment.s;
		qual = seq -> qual.s;
		sequence = seq -> seq.s;
		flag = kh_get(s, h, id);
		if (mode == 1 && flag == kh_end(h))
		{
			// print out seqeunce in fastq format
			printf("@%s\t%s\n%s\n+\n%s\n", id,comment,sequence,qual); 
			seqCount ++;
		}
		else if (mode == 0 && flag < kh_end(h)) 
		{
			// print out seqeunce in fastq format
			printf("@%s\t%s\n%s\n+\n%s\n", id,comment,sequence,qual); 
			seqCount ++;
		}
	}
	fprintf(stderr,"Written %i sequences from %s.\n",seqCount,fqFile);
	kh_destroy(s,h);
	return 0;
}

// main function
int main(int argc, char **argv){
	char *fqFile, *idFile;	
	int mode = 0;
	int c;

	if (argc == 1){
		fprintf(stderr,"usage: filterFastq [options]\n\n"
				"[options]\n"
				"\t-q\t<fastq file>\n" 
				"\t-i\t<idFile>\n" 
				"\t-v\tinverted match (same as grep -v)\n");
		return 1;
	}
	
	opterr = 0;
	// print usage if not enough argumnets
	while ((c = getopt(argc, argv, "vq:i:")) != -1){
		switch (c){
			case 'q':
				fqFile = optarg;
				break;
			case 'i':
				idFile = optarg;
				break;
			case 'v':
				mode = 1;
				break;
			case '?':
				if (optopt == 'q' || optopt == 'i'){
					fprintf(stderr,"usage: filterFastq [options]\n\n"
							"[options]\n"
							"\t-q\t<fastq file>\n" 
							"\t-i\t<idFile>\n"
							"\t-v\tinverted match (same as grep -v)\n");
				}
				else if (isprint (optopt)){
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				}
				else {
					fprintf(stderr,"usage: filterFastq [options]\n\n"
							"[options]\n"
							"\t-q\t<fastq file>\n" 
							"\t-i\t<idFile>\n" 
							"\t-v\tinverted match (same as grep -v)\n");
				}
				return 1;
			default:
				abort();
		}
    }

	// pass variable to fnuction
	writeSequence(idFile,fqFile,mode);
}

