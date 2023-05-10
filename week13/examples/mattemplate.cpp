#include <iostream>
using namespace std;

// Class Template
template<typename T>
class Mat
{
    size_t rows;
    size_t cols;
    T * data;
  public:
    Mat(size_t rows, size_t cols): rows(rows), cols(cols)
    {
        data = new T[rows * cols]{};
    }
    ~Mat()
    {
        delete [] data;
    }
    Mat(const Mat&) = delete;
    Mat& operator=(const Mat&) = delete;
    T getElement(size_t r, size_t c);
    bool setElement(size_t r, size_t c, T value);
};
template <typename T>
T Mat<T>::getElement(size_t r, size_t c)
{
    if ( r >= this->rows || c >= this->cols)
    {
        cerr << "getElement(): Indices are out of range" << endl;
        return 0;
    }
    return data[ this->cols * r + c];
}
template <typename T>
bool Mat<T>::setElement(size_t r, size_t c, T value)
{
    if ( r >= this->rows || c >= this->cols)
    {
        cerr << "setElement(): Indices are out of range" << endl;
        return false;
    }

    data[ this->cols * r + c] = value;
    return true;
}

template class Mat<int>; // Explicitly instantiate template Mat<int>
//template Mat<float> and Mat<double> will be instantiate implicitly
int main()
{
    Mat<int> imat(3,4);
    imat.setElement(1, 2, 256);
    Mat<float> fmat(2,3);
    fmat.setElement(1, 2, 3.14159f);
    Mat<double> dmat(2,3);
    dmat.setElement(1, 2, 2.718281828);

    // Mat<float> fmat2(fmat); //error

    // Mat<float> fmat3(2,3);
    // fmat3 = fmat; //error

    cout << imat.getElement(1,2) << endl;
    cout << fmat.getElement(1,2) << endl;
    cout << dmat.getElement(1,2) << endl;
    
    return 0;
}