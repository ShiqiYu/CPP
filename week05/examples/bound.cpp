#include <iostream>
using namespace std;

int main()
{
    int a;
    int num = 0;
    int * p = &num;

    p[-1] = 2; //out of bound
    p[0] = 3; //okay
    *(p+1) = 4; //out of bound

    cout << "num = " << num << endl;
    
    return 0;
}