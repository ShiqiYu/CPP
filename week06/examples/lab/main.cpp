#include<iostream>
using std::cout;
using std::endl;

int plus( int a, int b ) {
        return a + b;
}

int main() {
        int a = 1234567890;
        int b = 1234567890;
        int c = plus(a, b);
        cout<<"a + b = "<<c<<endl;
        return 0;
}
