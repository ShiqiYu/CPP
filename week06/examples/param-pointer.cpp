#include <iostream>
using namespace std;

int foo(int * p)
{
    (*p) += 10;
    return *p;
}

int main()
{
    int num1 = 20;
    int * p1 = &num1;
    int num2 = foo( p1 );
    cout << num1 << endl;
    cout << num2 << endl;
    
    return 0;
}
