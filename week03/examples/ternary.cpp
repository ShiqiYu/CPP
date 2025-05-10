#include <iostream>
using namespace std;

int main()
{
    // to understand ternary operator

    int a,b;
    cout<<"This code will help you to understand ternary operator better."<<endl;
    cout<<"Enter first number: ";
    cin>>a;
    cout<<"Enter second number: ";
    cin>>b;

    //ternary operator
    int max = a>b?a:b;
    cout<<"The greater number is: "<<max;
    return 0;
}