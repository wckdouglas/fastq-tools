#include <zlib.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include "kseq.h"
#include "khash.h"
#include <string>

using namespace std;

KSEQ_INIT(gzFile, gzread)
KHASH_SET_INIT_STR(s)

int printSeq(string id, string sequence, string qual, string comment)
{
	//print
	cout << "@" << id << '\t' << comment << endl;
	cout << sequence << endl;
	cout << '+' << endl;
	cout << qual << endl; 
	return 0;
}

int filterSequence(const char *fqFile, int mode, kh_s_t *h)
{
	cerr << "Reading fastq file: "<< fqFile << endl;
	//declare variable
	gzFile fp;
	kseq_t *seq;
	int flag = 0, seqCount = 0 ;

	//open fastq file
	fp = gzopen(fqFile,"r"); // open fastq file for kseq parsing 
	seq = kseq_init(fp);

	//================================================================
	// filter id
	while (kseq_read(seq) >= 0)
	{
		//define sequencing read elements
		string id(seq -> name.s);
		string comment(seq -> comment.s);
		string qual(seq -> qual.s);
		string sequence(seq -> seq.s);
		int hashPos = kh_get(s, h, id.c_str());

		//perform extraction
		if (mode == 1 && hashPos == kh_end(h))
		{
			// print out seqeunce in fastq format
			printSeq(id,sequence,qual,comment); 
			seqCount ++;
		}
		else if (mode == 0 && hashPos < kh_end(h))
		{
			// print out seqeunce in fastq format
			printSeq(id,sequence,qual,comment); 
			seqCount ++;
		}
	}
	cerr << "Written " << seqCount << " sequences from " << fqFile << endl;
	kseq_destroy(seq);
	gzclose(fp);
	return 0;
}

int indexing(string idFile, kh_s_t *hashTable)
{
	int ret;
	cerr << "Hashing ID file: " << idFile  << endl;
	ifstream idfile(idFile);
	for (string line; getline(idfile,line);)
	{
		kh_put(s, hashTable, strdup(line.c_str()), &ret);
	}
	return 0;
}

int usage()
{
	cerr << "usage: filterFastq -i <id file> -q <fastq file> [-v]" << endl;
	cerr << endl;
	cerr << "-q" << "      <fastq file>" << endl; 
	cerr << "-i" << "      <idFile>" << endl;
	cerr << "-v" << "      inverted match (same as grep -v)" << endl;
	return 0;
}

// main function
int main(int argc, char **argv)
{
	string  idFile;	
	char * fqFile;
	int mode = 0;
	int c;

	if (argc == 1)
	{
		usage();
		return 1;
	}
	
	opterr = 0;
	// print usage if not enough argumnets
	while ((c = getopt(argc, argv, "vq:i:")) != -1)
	{
		switch (c)
		{
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
				usage();
				return 1;
			default:
				abort();
		}
    }
	//hasing table
	khash_t(s) *hashTable;
	khint_t k;
	hashTable = kh_init(s);
	indexing(idFile,hashTable);

	// create hashing table
	filterSequence(fqFile, mode, hashTable);
	kh_destroy(s,hashTable);
	return 0;
}

