#include <iostream>
using namespace std;

int main()
{
    int num  = 10;
    if (num < 5)
        cout << "The number is less than 5. " << endl;
    
    if (num == 5 )
    {
        cout << "The number is 5." << endl;
    }
    else
    {
        cout << "The number is not 5." << endl;
    }

    if (num < 5)
        cout << "The number is less than 5." << endl;
    else if (num > 10)
        cout << "The number is greater than 10." << endl;
    else
        cout << "The number is in range [5, 10]." << endl;

    if(num < 20)
    if(num < 5)
    cout << "The number is less than 5" << endl;
    else
    cout << "Where I'm?" << endl;

    int * p = new int[1024];
    if (p)
        cout << "Memory has been allocated." << endl;

    return 0;
}