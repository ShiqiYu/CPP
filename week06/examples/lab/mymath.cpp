#include <iostream>
#include "mymath.h"

float arraySum(const float *array, size_t size)
{
    if(array == NULL)
    {
        std::cerr << "NULL pointer!" << std::endl;
        return 0.0f;
    }
    float sum = 0.0f;
    for(size_t i = 0; i < size; i++)
        sum += array[i];
    return sum;
}
