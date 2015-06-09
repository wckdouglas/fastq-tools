#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

using namespace std;

typedef vector<string> stringList;
typedef map<string, int> idIdx;

class seqRecord
{
	public:
		string id;
		string idLine;
		string sequence;
		string quality;
};


//split function to split line with desired deliminator
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


int readID(char *idFile, idIdx &seqIdx)
{
	ifstream idfile(idFile);
	string id;
	for (string line; std::getline(idfile,line);)
	{
		stringList names;
		split(line,' ',names);
		id = names[0];
		seqIdx[id] = 0;
	}
	return 0;
}

int readFq(char *fqFile, idIdx seqIdx, int mode)
{
	ifstream fqfile(fqFile);
	int lineNo = 0;
	seqRecord seq;
	string id;
	for (string line; std::getline(fqfile,line);)
	{
		lineNo ++ ;
		if (lineNo == 1)
		{
			stringList idLine;
			split(line,' ',idLine);
			id = idLine[0];
			seq.id = id.substr(1,id.length()-1);
			seq.idLine = line;
		}
		else if (lineNo == 2)
		{
			seq.sequence = line;
		}
		else if (lineNo == 4)
		{
			seq.quality = line;
			if (seqIdx.find(seq.id) == seqIdx.end() && mode == 1)
			{
				cout << seq.idLine << "\n" << seq.sequence << "\n";
				cout << "+\n" << seq.quality << endl;
			}
			else if (seqIdx.find(seq.id) != seqIdx.end() && mode == 0)
			{
				cout << seq.idLine << "\n" << seq.sequence << "\n";
				cout << "+\n" << seq.quality << endl;
			}
			lineNo = 0;
			seqRecord seq;
		}
	}
	return 0;
}

int usage()
{
	cerr << "usage: filterFastq -q <fastqFile> -i <idFile> [-v]" << endl;
	cerr << "[options]" << endl;
	cerr << "-q" << "              <fastq file>" << endl;
	cerr << "-i" << "              <idFile>"  << endl;
	cerr << "-v" << "              inverted match (same as grep -v))"<< endl;
	return 0;
}

// main function
int main(int argc, char ** argv)
{
	char *fqFile, *idFile;	
	int mode = 0;
	int c;
	if (argc == 1)
	{
		usage();
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

	// pass variable to fnuction
	idIdx seqIdx;
	readID(idFile, seqIdx);
	readFq(fqFile, seqIdx, mode);
	return 0;
}

