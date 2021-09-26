#include <iostream>
using namespace std;

typedef int myint;
typedef unsigned char vec3b[3];
typedef struct _rgb_struct{ // name _rgb_struct can be omit
    unsigned char r;
    unsigned char g;
    unsigned char b;
}  rgb_struct;

int main()
{
    myint num = 32;

    // the following two lines are identical
    //unsigned char color[3] = {255, 0, 255};
    vec3b color = {255, 0, 255}; 
    cout << hex;
    cout << "R=" << +color[0] << ", ";
    cout << "G=" << +color[1] << ", ";
    cout << "B=" << +color[2] << endl;

    rgb_struct rgb = {0, 255, 128};
    cout << "R=" << +rgb.r << ", ";
    cout << "G=" << +rgb.g << ", ";
    cout << "B=" << +rgb.b << endl;

    cout << sizeof(rgb.r) << endl;
    cout << sizeof(+rgb.r) << endl; //why 4?

    return 0;
}