#include <iostream>
using namespace std;

int main()
{
    int a = 56789;
    int b = 56789;
    int c = a * b;
    cout << "c = " << c << endl;

    // unsigned int c1 = a * b; //danger operation
    // cout << "c1 = " << c1 << endl;
    return 0;
}
