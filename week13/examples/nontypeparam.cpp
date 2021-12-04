#include <iostream>
using namespace std;

// Class Template
template<typename T, size_t rows, size_t cols>
class Mat
{
    T data[rows][cols];
  public:
    Mat(){}
    Mat(const Mat&) = delete;
    Mat& operator=(const Mat&) = delete;
    T getElement(size_t r, size_t c);
    bool setElement(size_t r, size_t c, T value);
};
template<typename T, size_t rows, size_t cols>
T Mat<T, rows, cols>::getElement(size_t r, size_t c)
{
    if ( r >= rows || c >= cols)
    {
        cerr << "getElement(): indices are out of range" << endl;
        return 0;
    }
    return data[r][c];
}
template<typename T, size_t rows, size_t cols>
bool Mat<T, rows, cols>::setElement(size_t r, size_t c, T value)
{
    if ( r >= rows || c >= cols)
    {
        cerr << "setElement(): Indices are out of range" << endl;
        return false;
    }

    data[r][c] = value;
    return true;
}

template class Mat<int, 2, 2>; // Explicitly instantiate template Mat<int, 2, 2>
typedef Mat<int, 2, 2> Mat22i;

//template Mat<float, 3, 1> will be instantiate implicitly

int main()
{
    Mat22i mat;

    mat.setElement(2, 3, 256);
    cout << mat.getElement(2, 3) << endl;

    mat.setElement(1, 1, 256);
    cout << mat.getElement(1, 1) << endl;

    Mat<float, 3, 1> vec;
    vec.setElement(2, 0, 3.14159f);
    cout << vec.getElement(2, 0) << endl;

    return 0;
}