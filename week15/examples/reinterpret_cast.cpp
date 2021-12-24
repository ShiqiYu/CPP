#include <iostream>
using namespace std;

int main()
{
    int i = 18;
    float * p1 = reinterpret_cast<float *>(i); // static_cast will fail
    int * p2 = reinterpret_cast<int*>(p1);

    printf("p1=%p\n", p1);
    printf("p2=%p\n", p2);

    return 0;
}
