#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str = "Hello, SUSTech!";
    for(int i = 0; i <= str.length(); i++) //no bound check
        cout << i << ": " << str[i] << endl;

    return 0;
}