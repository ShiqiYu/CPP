#include <iostream>
int main()
{
    auto a = 10;
    a = 20.5;
    a += 10.5;
    std::cout << a << std::endl; //30
    auto b = 10.0;
    b = 20.5;
    b += a;
    std::cout << b << std::endl; //50.5
    return 0;
}