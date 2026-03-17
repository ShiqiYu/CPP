#include <iostream>
#include "mystring.hpp"

using namespace std;

int main()
{
    {
        MyString str1(10, "Shenzhen");
        cout << "str1: " << str1 << endl;

        MyString str2 = str1; // compilation error because of deleting copy constructor
        cout << "str2: " << str2 << endl;

        MyString str3;
        cout << "str3: " << str3 << endl;
        str3 = str1; // compilation error because of deleting copy assignment
        cout << "str3: " << str3 << endl;
    }
    cout << "end of main()" << endl;
    return 0;
}