#include <iostream>
using namespace std;
int *create_array(int size)
{
    int *arr = new int[size];
    for (int i = 0; i < size; i++)
        arr[i] = i * 10;
    return arr;
}
int main()
{
    int len = 16;
    int *ptr = create_array(len);
    for (int i = 0; i < len; i++)
        cout << ptr[i] << " ";
    cout << endl;
    delete[] ptr;
    return 0;
}