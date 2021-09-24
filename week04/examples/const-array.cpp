#include <iostream>
using namespace std;

//float array_sum(const float *values, size_t length)
//float array_sum(const float values[4], size_t length)
float array_sum(const float values[], size_t length)
{
    float sum = 0.0f;
    for (int i = 0; i < length; i++)
    {
        sum += values[i];
        //values[i] = 0; //error
    }
    return sum;
}

int main()
{
    // const float PI = 3.1415926f;
    // PI += 1.f; // error
    // const float values[4] = {1.1f, 2.2f, 3.3f, 4.4f};
    // values[0] = 1.0f; // error

    float values[4] = {1.1f, 2.2f, 3.3f, 4.4f};
    float sum = array_sum(values, 4);

    cout << "sum = " << sum << endl;
    return 0;
}