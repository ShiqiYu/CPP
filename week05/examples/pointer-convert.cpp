#include <iostream>
using namespace std;

int main()
{
    int * pi = new int[2]();
    unsigned char * pc = (unsigned char*)pi;
    pc[1] = 1;
    pc[5] = 2;
    cout << "pi[0] = " << pi[0] << endl;
    cout << "pi[1] = " << pi[1] << endl;

    delete []pi;
    //delete []pc; 
    return 0;
}