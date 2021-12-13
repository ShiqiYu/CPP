#include <iostream>
#include <cstdlib>
#include <cfloat>

float ratio(float a, float b) 
{
    if (a < 0)
        throw 1;
    if (b < 0)
        throw 2;
    if (fabs(a + b) < FLT_EPSILON)
        throw "The sum of the two arguments is close to zero.";

    return (a - b) / (a + b);
}

float ratio_wrapper(float a, float b)
{
    try{
        return ratio(a, b);
    }
    catch(int eid)
    {
        if (eid == 1)
            std::cerr << "Call ratio() failed: the 1st argument should be positive." << std::endl;
        else if (eid == 2)
            std::cerr << "Call ratio() failed: the 2nd argument should be positive." << std::endl;
        else
            std::cerr << "Call ratio() failed: unrecognized error code." << std::endl;
    }
    return 0;
}

int main()
{
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    std::cout << "Please input two numbers <q to quit>:";
    while (std::cin >> x >> y)
    {
        try{
            z = ratio_wrapper(x,y);
            std::cout << "ratio(" << x << ", " << y<< ") = " << z << std::endl;
        }
        catch(const char * msg)
        {
            std::cerr << "Call ratio() failed: " << msg << std::endl;
            std::cerr << "I give you another chance." << std::endl;
        }

        std::cout << "Please input two numbers <q to quit>:";
    }
    std::cout << "Bye!" << std::endl;
    return 0;
}
