#include <iostream>
#include <string>
#include <ctype.h>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 1)
	{
		printf("The name of the file is missing!\n");
		return 1;
	}
    ifstream file(argv[1]);

    string str;
    string arr[7];
    int i = 0;
    while(file >> str)
    {
        for (int g = 0, len = str.size(); g < len; g++)
        {
            if (ispunct(str[g]))
            {
                str.erase(g--, 1);
                len = str.size();
            }
        }
        if(str.size() >= 10)
        {
            arr[i] = str;
            i++;
        }
    }
    for(int j = 0; j < 7; j++)
    {
        transform(arr[j].begin(), arr[j].end(), arr[j].begin(), ::toupper);
        cout << arr[j] << endl;
    }
    file.close();
    return 0;
}