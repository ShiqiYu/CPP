#include <iostream>
using namespace std;

struct Student1{
    int id;
    bool male;
    char label;
    float height;
};

struct Student2{
    int id;
    bool male;
    float height;
    char label;
};

int main()
{
    cout << "Size of Student1: " << sizeof(Student1) << endl;
    cout << "Size of Student2: " << sizeof(Student2) << endl;
    return 0;
}