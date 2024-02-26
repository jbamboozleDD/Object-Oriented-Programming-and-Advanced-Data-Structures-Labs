#include <iostream>
#include <iomanip> 
#include <string>
using namespace std;

int main()
{
    string str;
    cin >> str;
    int len = str.size();
    for(int i = 0; i < 4; i++)
    {
        cout << setw((2 + 2*i));
        for(int j = len - 1 ; j >= 0; j--)
        {
            cout << str[j];
        }
        cout << setw((22 + 2*(i+1)));
        cout << str << "\n";
    }
    cout << setw(9);
    for(int k = len - 1 ; k >= 0; k--)
    {
        cout << str[k];
    }
    cout  << "\n";

    return 0;
}