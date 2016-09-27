#include <string.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "gzstream.h"
#include <sstream>
#include <stdlib.h>
#include <cstdlib>

using namespace std;
//get the id hash table and
//iterate over the fastq file
// determine which sequence to print out

string fixfilenum(int filenum)
{
	string out;
	ostringstream convert;
	if (filenum > 10)
	{
		convert << filenum;
		out = convert.str();
	}
	else
	{
		convert << filenum;
		out = "0" + convert.str();
	}
	return out;
}

//http://stackoverflow.com/questions/8520560/get-a-file-name-from-a-path
string base_name(string const & path)
{
  return path.substr(path.find_last_of("/\\") + 1);
}

//http://stackoverflow.com/questions/5077693/dirnamephp-similar-function-in-c
string dir_name(string source)
{
    source.erase(std::find(source.rbegin(), source.rend(), '/').base(), source.end());
    return source;
}


void splitFastq(char *fqFile, string filePrefix, int recordNum, int gz)
{
	// open fastq file for kseq parsing
	cerr << "From " << fqFile << "...." << endl;
	cerr << "Splitting " << recordNum << " records per file" << endl;
	int maxLine = recordNum * 4;
	int lineCount = 0, filenum = 1;
	string samplename = base_name(filePrefix);
	string filepath = dir_name(filePrefix);

	string suffix;
	string filename;
	igzstream in(fqFile);

	if (gz == 0)
	{
		suffix = ".fastq";
		ofstream outFile;
		for (string line; getline(in,line);)
		{
			if (lineCount == 0)
			{
				filename = filepath + fixfilenum(filenum) +  "-" + samplename  + suffix;
				outFile.open(filename.c_str());
				outFile << line << '\n';
			}
			else if (lineCount == maxLine)
			{
				outFile.close();
				cerr << "written " << filename << endl;
				lineCount = 0;
				filenum ++;
				filename = filepath + fixfilenum(filenum) +  "-" + samplename  + suffix;
				outFile.open(filename.c_str());
				outFile << line << '\n';
			}
			else
			{
				outFile << line << '\n';
			}
			lineCount ++;
		}
		outFile.close();
	}
	else
	{
		suffix = ".fastq.gz";
		ogzstream outFile;
		for (string line; getline(in,line);)
		{
			if (lineCount == 0)
			{
				filename = filepath + fixfilenum(filenum) +  "-" + samplename  + suffix;
				outFile.open(filename.c_str());
				outFile << line << '\n';
			}
			else if (lineCount == maxLine)
			{
				outFile.close();
				cerr << "written " << filename << endl;
				lineCount = 0;
				filenum ++;
				filename = filepath + fixfilenum(filenum) +  "-" + samplename  + suffix;
				outFile.open(filename.c_str());
				outFile << line << '\n';
			}
			else
			{
				outFile << line << '\n';
			}
			lineCount ++;
		}
		outFile.close();
	}

	cerr << "written " << filename << endl;
}

// print usage
void usage(string programname)
{
	cerr << "usage: "<< programname << " -i <fqfile> -n <# of record per file> -o <prefix> [-z]" << endl;
	cerr << "[options]" << endl;
	cerr << "-i    <fastq file>"  << endl;
	cerr << "-n    <number of record in each splitted file> default: 10000000"  << endl;
	cerr << "-o    <prefix>"  << endl;
	cerr << "-z    optional: gzip output"  << endl;
}

// main function
int main(int argc, char **argv){
	char *fqFile;
	int c, recordNum = 10000000;
	int gz = 0;

	string programname = argv[0];
	string filePrefix = "";
	if (argc == 1){
		usage(programname);
		return 1;
	}

	opterr = 0;
	// print usage if not enough argumnets
	while ((c = getopt(argc, argv, "i:n:o:z")) != -1){
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
			case 'z':
				gz = 1;
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
	if (filePrefix == "" || strcmp(fqFile,"") == 0)
	{
		usage(programname);
		return 1;
	}

	splitFastq(fqFile, filePrefix, recordNum, gz);
	return 0;
}
