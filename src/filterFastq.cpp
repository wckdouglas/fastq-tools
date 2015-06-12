#include <zlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unordered_set>



using namespace std;
typedef unordered_set< string > idSet;
typedef vector<string> stringList;

stringList &split(const string &s, char delim, stringList &result) 
{
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) 
        {
                result.push_back(item);
        }
        return result;
}

int printSeq(string id, string sequence, string qual, string comment)
{
	//print
	cout << "@" << id << '\t' << comment << '\n';
	cout << sequence << '\n';
	cout << '+' << '\n';
	cout << qual << '\n'; 
	return 0;
}


int checkPass (string id, string sequence, string comment , string qual, idSet &ids, int mode, int &seqCount)
{
	//perform extraction
	if (mode == 1 &&  ids.find(id) == ids.end())
	{
		// print out seqeunce in fastq format
		printSeq(id,sequence,qual,comment); 
		seqCount ++;
	}
	else if (mode == 0 && ids.find(id) != ids.end())
	{
		// print out seqeunce in fastq format
		printSeq(id,sequence,qual,comment); 
		seqCount ++;
	}
	return 0;
}

int filterSequence(string fqFile, int mode, idSet &ids)
{
	//declare variable
	int seqCount = 0, seqNo = 0, hashPos, lineno = 0;
	string id, comment, qual, sequence;

	//open fastq file
	cerr << "Reading fastq file: "<< fqFile << endl;

	//================================================================
	// filter id
	ifstream fastq(fqFile);
	for (string line; getline(fastq,line);)
	{
		lineno ++;
		if (lineno == 1)
		{
			stringList blocks;
			split(line,' ',blocks);
			id = blocks[0].substr(1,blocks[0].length());
			comment = blocks[1];
		}
		else if (lineno == 2)
		{
			sequence = line;
		}
		else if (lineno == 4)
		{
			qual = line;
			checkPass(id, sequence, comment, qual, ids, mode, seqCount);
			seqNo ++;
			lineno = 0;
		}

	}
	cerr << "Written " << seqCount << " reads from ";
	cerr << fqFile << " with " << seqNo << " reads"<< endl;
	return 0;
}

int hashing(string idFile, idSet &ids)
{
	int ret;
	cerr << "Hashing ID file: " << idFile  << endl;
	ifstream id(idFile);
	for (string line; getline(id,line);)
	{
		ids.insert(line);
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
	string idFile;	
	string fqFile;
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
	idSet ids;
	// create hashing table
	hashing(idFile, ids);
	filterSequence(fqFile, mode, ids);
	return 0;
}

