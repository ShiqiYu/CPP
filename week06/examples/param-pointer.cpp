#include <iostream>
using namespace std;

int foo1(int x)
{
    x += 10;
    return x;
}


int foo2(int * p)
{
    (*p) += 10;
    return *p;
}

int main()
{
    int num1 = 20;
    int num2 = foo1(num1);
    cout << "num1=" << num1 << endl;
    cout << "num2=" << num2 << endl;

    int * p = &num1;
    int num3 = foo2( p );
    cout << "num1=" << num1 << endl;
    cout << "*p=" << *p << endl;
    cout << "num3=" << num3 << endl;
    
    return 0;
}
