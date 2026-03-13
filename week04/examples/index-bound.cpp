#include <iostream>
using namespace std;
int main()
{
    int num_array[5]; 

    for(int idx = -1; idx <= 5; idx++) //out of bounds <- -1 index does not exits and 5 also->
        num_array[idx] = idx * idx;

    for(int idx = -1; idx <= 5; idx++) //out of bounds
        cout << "num_array[" << idx << "] = " << num_array[idx] << endl;

    return 0;
}