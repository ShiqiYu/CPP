#include <iostream>
using namespace std;

int foo(const char * p)
{
    // the value that p points to cannot be changed
    // play a trick?
    char * p2 = p; //syntax error
    //...
    return 0;
}

int main()
{
    int num = 1;
    int another = 2;
    
    //You cannot change the value that p1 points to through p1
    const int * p1 = &num;
    *p1 = 3; //error
    num = 3; //okay

    //You cannot change value of p2 (address)
    int * const p2 = &num;
    *p2 = 3; //okay
    p2 = &another; //error

    //You can change neither
    const int* const p3 = &num;
    *p3 = 3; //error
    p3 = &another; // error

    return 0;
}