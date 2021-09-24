#include <iostream>
using namespace std;

// You must tell the function the bound of an array,
// otherwise, elements cannot be accessed
// if the array is a variable-length one, it may be difficult to know the bound
void init_2d_array(float mat[][4], //error, arrays of unknown bound
                    size_t rows, size_t cols)
{
    for (int r = 0; r < rows; r++)
        for(int c = 0; c < cols; c++)
            mat[r][c] =  r * c;
}

int main()
{
    int mat1[2][3] = {{11,12,13}, {14,15,16}};

    int rows = 5;
    int cols = 4;
    //float mat2[rows][cols]; //uninitialized array
    float mat2[rows][4]; //uninitialized array

    //init_2d_array(mat2, rows, cols);

    for (int r = 0; r < rows; r++)
        for(int c = 0; c < cols; c++)
            mat2[r][c] =  r * c;


    for (int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
            cout << mat2[r][c] << " ";
        cout << endl;
    }
    return 0;
}