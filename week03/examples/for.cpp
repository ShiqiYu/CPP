#include <iostream>
using namespace std;
int main()
{
    long long sum = 0;
    long num;
    cout<<"Enter any positive number: ";
    cin>>num;
    for(int i = 1; i <= num; i++)
    {
        sum += i;
    }
    cout << "sum of all numbers till "  <<num<<" is: "<< sum << endl;

    return 0;
}