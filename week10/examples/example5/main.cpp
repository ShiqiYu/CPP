#include <iostream>
#include "time.hpp"

using namespace std;

int main()
{
    MyTime t1(1, 59);
    MyTime t2 = t1++;
    MyTime t3 = ++t1;

    std::cout << "t1 is " << t1 << std::endl;
    std::cout << "t2 is " << t2 << std::endl;
    std::cout << "t3 is " << t3 << std::endl;

    return 0;

}

