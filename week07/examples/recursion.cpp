#include <iostream>
using namespace std;

void div2(double val);

int main()
{
    div2(1024.); // call the recursive function
    return 0;
}

void div2(double val)
{

    cout << "Entering val = " << val << endl;
    if (val > 1.0)
        div2( val / 2); // function calls itself
    else
        cout << "--------------------------" << endl;
    
    cout << "Leaving  val = " << val << endl;
}
