#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
    int a, b;
    double c, d, f, g;
    char h;
    a = 19.99 + 21.99;
    b = (int)19.99 + 21.99;
    c = 23 / 3;
    d = 23 / 3.0;
    f = 23 / 3.0e4;
    g = 23 / 3.0e5;
    h = 'b' - 32; 
    
    // complete code here
    cout << h << endl;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << fixed << setprecision(5) << d << endl;
    cout << scientific << setprecision(5) << g << endl;
    cout << fixed << setprecision(9) << f << endl;
    return 0;
}