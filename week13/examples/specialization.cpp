#include <iostream>
using namespace std;

// Class Template
template<typename T>
class MyVector
{
    size_t length;
    T * data;
  public:
    MyVector(size_t length): length(length)
    {
        data = new T[length * sizeof(T)]{};
    }
    ~MyVector()
    {
        delete [] data;
    }
    MyVector(const MyVector&) = delete;
    MyVector& operator=(const MyVector&) = delete;
    T getElement(size_t index);
    bool setElement(size_t index, T value);
};
template <typename T>
T MyVector<T>::getElement(size_t index)
{
    if (index >= this->length)
    {
        cerr << "getElement(): Indices are out of range" << endl;
        return 0;
    }
    return data[index];
}
template <typename T>
bool MyVector<T>::setElement(size_t index, T value)
{
    if (index >= this->length)
    {
        cerr << "setElement(): Indices are out of range" << endl;
        return false;
    }

    data[ index ] = value;
    return true;
}

template class MyVector<int>; // Explicitly instantiate template Mat<int>

// class specialization
template<>
class MyVector<bool>
{
    size_t length;
    unsigned char * data;
  public:
    MyVector(size_t length): length(length)
    {
        int num_bytes =  (length - 1) / 8 + 1;
        data = new unsigned char[num_bytes]{};
    }
    ~MyVector()
    {
        delete [] data;
    }
    MyVector(const MyVector&) = delete;
    MyVector& operator=(const MyVector&) = delete;
    bool getElement(size_t index);
    bool setElement(size_t index, bool value);
};
bool MyVector<bool>::getElement(size_t index)
{
    if (index >= this->length)
    {
        cerr << "getElement(): Indices are out of range" << endl;
        return 0;
    }
    size_t byte_id = index / 8;
    size_t bit_id = index % 8;
    unsigned char mask = (1 << bit_id);
    return bool(data[byte_id] & mask) ;
}
bool MyVector<bool>::setElement(size_t index, bool value)
{
    if (index >= this->length)
    {
        cerr << "setElement(): Indices are out of range" << endl;
        return false;
    }

    size_t byte_id = index / 8;
    size_t bit_id = index % 8;
    unsigned char mask = (1 << bit_id);

    if (value)
        data[byte_id] |= mask; 
    else 
        data[byte_id] &= ~mask;

    return true;
}

int main()
{
    MyVector<int> vec(16);
    vec.setElement(3, 256);
    cout << vec.getElement(3) << endl;
    
    MyVector<bool> boolvec(17);
    boolvec.setElement(15, false);
    boolvec.setElement(16, true);

    cout << boolvec.getElement(15) << endl;
    cout << boolvec.getElement(16) << endl;
    return 0;
}
