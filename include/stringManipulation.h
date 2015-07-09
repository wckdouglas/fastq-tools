#include <string>
#include <vector>
#include <sstream>

using namespace std;

typedef vector<string> stringList;
typedef vector<int> numList;

//split function to split line with desired deliminator
stringList split(const string &s, char delim) 
{
	stringList result; 
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) 
    {
        result.push_back(item);
    }
    return result;
}

// separate number and string
int regexSeparate(string tag, numList &numberslists, stringList &letterlists)
{
    int i, current = 0, size = tag.length();
    string letters = "";
    char c;
    for ( i = 0; i < size; i ++)
    {
        c = tag.at(i);
        if (isdigit(c))
        {
            current = current * 10 + (c-'0');
            letters = "";
            if (i == size-1)
            {
                numberslists.push_back(current);
                letterlists.push_back("N");
            }
        }
        else
        {
            numberslists.push_back(current);
            letters = letters + string(1,c);
            letterlists.push_back(letters);
            current = 0;
        }
    }
    return 0;
}
