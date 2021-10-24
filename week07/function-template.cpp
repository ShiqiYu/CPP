#include <iostream>
#include <typeinfo>
using namespace std;

template<typename T>
T sum(T x, T y)
{
    cout << "The input type is " << typeid(T).name() << endl;
    return x + y;
}

template double sum<double>(double, double); // instantiates sum<double>(double, double)
template char sum<>(char, char); // instantiates sum<char>(char, char), template argument deduced
template int sum(int, int); // instantiates sum<int>(int, int), template argument deduced

template<typename T>
T product(T x, T y)
{
    cout << "The input type is " << typeid(T).name() << endl;
    return x * y;
}



int main()
{
    //Explicit instantiated functions
    cout << "sum = " << sum(1, 2) << endl;
    cout << "sum = " << sum(1.1, 2.2) << endl;

    // Implicitly instantiates product<int>(int, int)
    cout << "product = " << product<int>(2.2f, 3.0f) << endl;
    // Implicitly instantiates product<float>(float, float)
    cout << "product = " << product(2.2f, 3.0f) << endl;

    return 0;
}