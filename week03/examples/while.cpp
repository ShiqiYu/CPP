#include <iostream>
using namespace std;
int main()
{
    int num = 10;
    while(num > 0)
    {
        cout << "num = " << num << endl;
        num--;
    }

    num = 10;
    do
    {
        cout << "num = " << num << endl;
        num--;
    }while (num > 0);

    num = 10;
    while (num > 0)
    {
        cout << "num = " << num << endl;
        num--;
        if (num == 5)
            break;
    }
    return 0;
} 