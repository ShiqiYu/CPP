#include <iostream>
using namespace std;

int main()
{
    int num = 0;
    int & num_ref = num;
    cout << "num = " << num << endl;

    num_ref = 10;
    cout << "num = " << num << endl;

    return 0;
}
