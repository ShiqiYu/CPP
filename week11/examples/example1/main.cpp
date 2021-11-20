#include <iostream>
#include "mystring.hpp"

using namespace std;

// Why memory leak and memory double free?
int main()
{
    MyString str1(10, "Shenzhen");
    cout << "str1: " << str1 << endl;

    MyString str2 = str1; 
    cout << "str2: " << str2 << endl;

    MyString str3;
    cout << "str3: " << str3 << endl;
    str3 = str1;
    cout << "str3:" << str3 << endl;

    return 0;
}