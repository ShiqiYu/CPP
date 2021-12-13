#include <iostream>
#include <cstdlib>
#include <cfloat>

float ratio(float a, float b)
{
    if (fabs(a + b) < FLT_EPSILON)
    {
        std::cerr << "The sum of the two arguments is close to zero." << std::endl;
        std::abort();
    }
    return (a - b) / (a + b);
    //return int(a - b) / int(a + b);// divided by zero behavior differently for int and float
}

int main()
{
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    std::cout << "Please input two numbers <q to quit>:";
    while (std::cin >> x >> y)
    {
        z = ratio(x,y);
        std::cout << "ratio(" << x << ", " << y<< ") = " << z << std::endl;
        std::cout << "Please input two numbers <q to quit>:";
    }
    std::cout << "Bye!" << std::endl;
    return 0;
}
