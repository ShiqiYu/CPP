#include <iostream>
using namespace std;
int main()
{
    int n, fa;
    do
    {
        fa *= n;
        n++;
    } while (n <= 10);
    cout << "fa = " << fa << endl;
    return 0;
}