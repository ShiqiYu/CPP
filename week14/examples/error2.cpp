#include <iostream>
#include <cstdlib>
#include <cfloat>

bool ratio(float a, float b, float & c)
{
    if (fabs(a + b) < FLT_EPSILON)
    {
        std::cerr << "The sum of the two arguments is close to zero." << std::endl;
        return false;
    }
    c = (a - b) / (a + b);
    return true;
}

int main()
{
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    std::cout << "Please input two numbers <q to quit>:";
    while (std::cin >> x >> y)
    {
        bool ret = ratio(x, y, z);
        if(ret) 
            std::cout << "ratio(" << x << ", " << y<< ") = " << z << std::endl;
        else
            std::cerr << "ratio(" << x << ", " << y<< ") failed." << std::endl;

        std::cout << "Please input two numbers <q to quit>:";
    }
    std::cout << "Bye!" << std::endl;
    return 0;
}
