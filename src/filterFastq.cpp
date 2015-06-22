#include <zlib.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "kseq.h"
#include "khash.h"

using namespace std;
KSEQ_INIT(gzFile, gzread);
KHASH_SET_INIT_STR(s)

void printSeq(string id, string comment, 
				string sequence, string qual)
{
	cout << "@" << id << '\t' << comment << '\n';
	cout << sequence << "\n+\n" ;
	cout << qual << "\n"; 
}


void filterFastq(char *fqFile, int &seqCount, int mode, kh_s_t *h)
{
	// open fastq file for kseq parsing 
	int flag, l;
	char *id, *sequence, *qual, *comment=0;
	gzFile fq = gzopen(fqFile,"r"); 
	kseq_t *seq = kseq_init(fq);

	//================================================================
	// filter id
	while ((l = kseq_read(seq)) >= 0)
	{
		id = seq -> name.s;
		comment = seq -> comment.s;
		qual = seq -> qual.s;
		sequence = seq -> seq.s;
		flag = kh_get(s,h,id);
		if (mode == 1 &&  flag == kh_end(h))
		{
			// print out seqeunce in fastq format
			printSeq(id,comment,sequence,qual); 
			seqCount ++;
		}
		else if (mode == 0 && flag < kh_end(h)) 
		{
			// print out seqeunce in fastq format
			printSeq(id,comment,sequence,qual); 
			seqCount ++;
		}
	}
	gzclose(fq);
}

void getID(char *idFile, char *fqFile, int mode)
{
	//function for write fastq//
	cerr << "Reading file: " << idFile << endl;
	cerr << "From " << fqFile << "...." << endl;;
	
	//declare variable
	int seqCount = 0, idCount = 0;
	int ret;

	// hashing id file
	ifstream fp(idFile); 
	khash_t(s) *h = kh_init(s);
	for (string line; getline(fp,line);)
	{
		kh_put(s, h, strdup(line.c_str()), &ret);
		cerr << line.c_str() << '\t' << ret <<  endl;
		idCount ++;
	}
	cerr << "Read "<< idCount << " ids." << endl;
	filterFastq(fqFile, seqCount, mode, h);
	cerr << "Written " << seqCount << " sequences from "<< fqFile << endl;
	kh_destroy(s, h);
}

void usage(string programname)
{
	cerr << "usage: "<< programname << "[options]" << endl;
	cerr << "[options]" << endl;
	cerr << "-q    <fastq file>"  << endl;
	cerr << "-i    <idFile>"  << endl;
	cerr << "-v    inverted match (same as grep -v)" << endl;
}

// main function
int main(int argc, char **argv){
	std::cout.sync_with_stdio(false);
	std::cin.sync_with_stdio(false);
	char *fqFile, *idFile;	
	int mode = 0;
	int c;

	string programname = argv[0];
	if (argc == 1){
		usage(programname);
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
				}
				else if (isprint (optopt)){
					usage(programname);
				}
				else {
					usage(programname);
				}
				return 1;
			default:
				abort();
		}
    }

	// pass variable to fnuction
	getID(idFile,fqFile,mode);
	return 0;
}

