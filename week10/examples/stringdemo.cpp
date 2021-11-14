#include <iostream>
#include <string>

int main()
{
    std::string s("Hello ");
    s += "C";
    s.operator+=(" and CPP!");

    std::cout << s << std::endl;
    return 0;
}