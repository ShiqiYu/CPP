#include <iostream>
using namespace std;

void increase(const int * pn)
{
    int * pi;
    pi = const_cast<int *>(pn);
    (*pi)++; // undefined behavior
}


int main()
{
    int value1 = 100;
    const int value2 = 200;
    cout << "value1 = " << value1 << endl;
    cout << "value2 = " << value2 << endl;
    
    int * pv1 = const_cast<int *>(&value1);
    int * pv2 = const_cast<int *>(&value2);

    (*pv1)++;
    (*pv2)++;

    cout << "value1 = " << value1 << endl;
    cout << "value2 = " << value2 << endl;
    
    int v2 = const_cast<int&>(value2);
    v2++;
    cout << "value2 = " << value2 << endl;

    // cout << "*pv2 = " << (*pv2) << endl;
    // cout << "v2 = " << v2 << endl;

    return 0;
}
