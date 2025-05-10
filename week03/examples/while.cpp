#include <iostream>
using namespace std;
int main()
{
    int num = 10;
    while(num > 0) // when num gets 0 loop will break
    {
        cout << "num = " << num << endl;
        num--;
    }
    // num gets 0 and priting it out of while loop
    cout<<"num = "<<num;
    // num = 10;
    // do 
    // {
    //     cout << "num = " << num << endl;
    //     num--;
    // }while (num > 0);

    // num = 10;
    // while (num > 0)
    // {
    //     if (num == 5)
    //         break;
    //     cout << "num = " << num << endl;
    //     num--;
    // }
    return 0;
} 