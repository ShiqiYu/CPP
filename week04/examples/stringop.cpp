#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char str1[] = "Hello, \0CPP";
    char str2[] = "SUSTech";
    char result[128];

    for(int i = 0; i < 16; i++)
        cout << i << ":" << +str1[i] << "(" << str1[i] << ")" << endl;

    strcpy(result, str1);
    cout << "Result = " <<  result << endl;
    strcat(result, str2);
    cout << "Result = " <<  result << endl;

    cout << "strcmp() = " << strcmp(str1, str2) << endl;

    //strcat(str1, str2); //danger operation!
    //cout << "str1 = " << str1 << endl;
}