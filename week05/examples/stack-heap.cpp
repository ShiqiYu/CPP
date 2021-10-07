#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    
    cout << &a << endl;
    cout << &b << endl;
    cout << &c << endl;

    int * p1 = (int*) malloc (4);
    int * p2 = (int*) malloc (4);
    int * p3 = (int*) malloc (4);

    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;

    free(p1);
    free(p2);
    free(p3);

    return 0;
}
