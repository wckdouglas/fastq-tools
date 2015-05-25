#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;


int main(int argc, char *argv[])
{
	const char *filename = argv[1];
	ifstream fastqfile(filename);
	int i;
	for (string line; getline(fastqfile, line);)
	{
		i ++;
	}
	cout << filename << "\t" << i/4 << endl;
	return 0;
}
