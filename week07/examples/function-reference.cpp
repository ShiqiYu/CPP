#include <iostream>
#include <cmath>
using namespace std;

float norm_l1(float x, float y); //declaration
float norm_l2(float x, float y); //declaration
float (&norm_ref)(float x, float y) = norm_l1; //norm_ref is a function reference

int main()
{
    cout << "L1 norm of (-3, 4) = " << norm_ref(-3, 4) << endl;
    return 0;
}

float norm_l1(float x, float y)
{
    return fabs(x) + fabs(y);
}

float norm_l2(float x, float y)
{
    return sqrt(x * x + y * y);
}