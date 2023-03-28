#include<iostream>
// main.cpp
#include <iostream>
#include "mymath.h"
int main()
{
    float arr1[8]{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};
    float * arr2 = NULL;

    float sum1 = arraySum(arr1, 8);
    float sum2 = arraySum(arr2, 8);

    std::cout << "The result1 is " << sum1 << std::endl;
    std::cout << "The result2 is " << sum2 << std::endl;

    return 0;
}
