#include <string.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <gzstream.h>

using namespace std;
//get the id hash table and 
//iterate over the fastq file
// determine which sequence to print out

string fixfilenum(int filenum)
{
	string out;
	if (filenum > 10)
	{
		out = to_string(filenum);
	}
	else
	{
		out = "0" + to_string(filenum);
	}
	return out;
}


void splitFastq(char *fqFile, string filePrefix, int recordNum)
{
	// open fastq file for kseq parsing 
	cerr << "From " << fqFile << "...." << endl;
	cerr << "Splitting " << recordNum << " records per file" << endl;
	int maxLine = recordNum * 4; 
	int lineCount = 0, filenum = 0;
	string filename;
	igzstream in(fqFile);
	ofstream outFile;
	for (string line; getline(in,line);)
	{
		if (lineCount == 0)
		{			
			filename = filePrefix + "_" + fixfilenum(filenum) + ".fastq";
			outFile.open(filename);		
			outFile << line << '\n';
		}
		else if (lineCount == maxLine)
		{
			outFile.close();
			cerr << "written " << filename << endl;
			lineCount = 0;
			filenum ++;
			filename = filePrefix + "_" + fixfilenum(filenum) + ".fastq";
			outFile.open(filename);		
			outFile << line << '\n';
		}
		else 
		{
			outFile << line << '\n';
		}
		lineCount ++; 
	}
	outFile.close();
	cerr << "written " << filename << endl;
}

// print usage
void usage(string programname)
{
	cerr << "usage: "<< programname << " -i <fqfile> -n <# of record per file> -o <prefix>" << endl;
	cerr << "[options]" << endl;
	cerr << "-i    <fastq file>"  << endl;
	cerr << "-n    <number of record in each splitted file> default: 10000000"  << endl;
	cerr << "-o    <prefix>"  << endl;
}

// main function
int main(int argc, char **argv){
	char *fqFile;	
	int c, recordNum = 10000000;

	string programname = argv[0];
	string filePrefix;
	if (argc == 1){
		usage(programname);
		return 1;
	}
	
	opterr = 0;
	// print usage if not enough argumnets
	while ((c = getopt(argc, argv, "i:n:o:")) != -1){
		switch (c){
			case 'i':
				fqFile = optarg;
				break;
			case 'n':
				recordNum = atoi(optarg);
				break;
			case 'o':
				filePrefix = optarg;
				break;
			case '?':
				if (optopt == 'n' || optopt == 'i' || optopt== 'o'){
					cerr << "option n, i, p need arguments!" << endl;
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
	splitFastq(fqFile, filePrefix, recordNum);
	return 0;
}

