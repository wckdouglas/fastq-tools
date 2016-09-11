#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>
#include <cassert>
#include "stringManipulation.h"

using namespace std;

//print usage 
int usage(char *argv[])
{
    cerr << "usage: "<< argv[0] << " <sam file>|<stdin> " << endl;
    cerr << endl;
    cerr << "Takes in samFile:"<<endl;
    cerr << "samtools view <bamFile> | ";
    cerr << argv[0] << " - "<<endl;
	return 1;
}


//process lines
void printSeq(vector<string> columns, int &seqCount)
{
    string id, sequence, qual, chrom;
    chrom = columns[2];
    if (chrom == "*")
    {
        id = columns[0];
        sequence = columns[9];
        qual = columns[10];
        assert (sequence.length() == qual.length());
		printf("@%s\n%s\n+\n%s\n",id.c_str(),sequence.c_str(),qual.c_str());
        seqCount ++;
    }
}

void readFile(const char* filename, int &seqCount)
{
    ifstream myfile(filename);
    for (string line; getline(myfile, line);)
    {
        if (line[0] != '@') 
        {
            stringList columns = split(line,'\t');
            printSeq(columns, seqCount);
        }
    }
}

// if lines are read from stdin,
// this function takes in and open the file and 
// parse it line by line
void readStream(int &seqCount)
{
    for (string line; getline(cin, line);)
    {
        if (line[0] != '@') 
        {
            stringList columns = split(line,'\t');
            printSeq(columns, seqCount);
        }
    }
}


int main(int argc, char *argv[])
{
	ios::sync_with_stdio(false);
    // warnings
    if (argc != 2)
    {
        usage(argv);
		return 0;
    }

    // read lines
    int seqCount;
    if (strcmp(argv[1],"-") == 0)
    {
        readStream(seqCount);
    }
    else
    {
        const char* filename = argv[1];
        readFile(filename, seqCount);
    }
    cerr << "Written "<< seqCount <<" sequences." << endl;
    return 0;
}
