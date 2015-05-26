#include <iostream>
#include <stdlib.h>
#include <glob.h>
#include <string>
#include <fstream>

using namespace std;

int readFile(const char *filename)
{
	int i = 0;
	ifstream fastqfile(filename);
	for (string line; getline(fastqfile, line);)
	{
		i ++;
	}
	cout << filename << "\t" << i/4 << endl;
	return i;
}

int main(int argc, char *argv[])
{
	const char *filepath = argv[1];
	string pattern = argv[2];
	glob_t globbuf;
	int err = glob(pattern.c_str(), 0, NULL, &globbuf);
	cout << err << endl;
	if(err == 0)
	{
		for (size_t i = 0; i < globbuf.gl_pathc; i++)
		{
			readFile(globbuf.gl_pathv[i]);
		}
		globfree(&globbuf);
	}
}
