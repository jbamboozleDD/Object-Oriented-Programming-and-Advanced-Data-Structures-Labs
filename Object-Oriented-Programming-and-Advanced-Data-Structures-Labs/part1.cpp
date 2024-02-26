#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

int main()
{
    string str;
    int alp = 0;
    int nonalp = 0;
    getline(cin, str);
    int length = str.size();
    for(int i = 0; i < length; i++)
    {
        if( isalnum( str[i] ) )
            alp++;
        else if(!isblank(str[i]))
            nonalp++;
    }

    cout << str << " has " << alp << " alphanumeric characters and " << nonalp << " non-alphanumeric characters.\n";
    return 0;
}