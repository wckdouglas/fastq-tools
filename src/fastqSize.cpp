#include <glob.h>
#include <iostream>
#include <fstream>
#include "gzstream.h"
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <libgen.h>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <libgen.h>

using namespace std;
typedef vector<string> stringList;
typedef pair <string, int> resultPairs;

bool comp(resultPairs x, resultPairs y){   
           return x.first < y.first; 
}


int usage(char *program){
    cout << "usage: " << program << " '$dir/*fastq'";
    cout << endl;
    cout << endl;
    abort();
    return 0;
}

//glob function to find all files in directory with same pattern
stringList globVector(const string& pattern){
    glob_t glob_result;
    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> files;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        files.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return files;
}

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

//function to count lines
int countLines(string filename){
    int lineNumber = 0;
    if (filename.substr(filename.length()-2)== "gz" ){
        igzstream fastqfile(filename.c_str());
        for (string line; getline(fastqfile,line);){
            lineNumber ++;
        }
    } else {
        ifstream fastqfile(filename.c_str());
        for (string line; getline(fastqfile,line);){
            lineNumber ++;
        }
    }
    return lineNumber;
}

//get basename and first character of sample name
char *getSampleName(string filename){ 
        stringList sampleName;
        string sample;
        sampleName = split(filename,'_',sampleName);
        sample = sampleName[0];
        char *samplename = new char[sample.length()+1];
        strcpy(samplename,sample.c_str());
        return(basename(samplename));
}

//get count for each file
vector<resultPairs> printOutPut(stringList filelist, int numOfFiles){
    string file;
    int i;
    vector<resultPairs> result(numOfFiles); 
    for (i = 0 ; i < numOfFiles; i++){
        file = filelist[i];
        result[i] = make_pair(getSampleName(file),countLines(file)/4);
    }
    return result;
}

// main function for printing out output
int main(int argc, char *argv[]){
    char *program  = argv[0];
    if (argc != 2){
        usage(program);
    }
    else{
        string pattern = argv[1];
        stringList files = globVector(pattern);
        int numOfFiles = files.size();
        vector<resultPairs> result = printOutPut(files,numOfFiles);
        sort(result.begin(),result.end(),comp);
        for (int i = 0 ; i < numOfFiles ; i++){
            cout << result[i].first << '\t';
            cout << result[i].second << endl;
        }
    }
    return 0;
}
