#include <iostream> //file name: lab3_p4_3.cpp
#define EPSILON 1e-10

using namespace std;
int main()
{
    cout << fixed;
    float f1 = 1.0f;
    cout << "f1 = " << f1 << endl;
    float a = 0.1f;
    float f2 = a + a + a + a + a + a + a + a + a + a;
    cout << "f2 = " << f2 << endl;
    if ((f1-f2) < EPSILON) // TIPS: Modify the code here
        cout << "f1 == f2" << endl;
    else
        cout << "f1 != f2" << endl;
    return 0;
}