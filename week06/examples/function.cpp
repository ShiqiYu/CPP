#include <iostream>
#include <float.h>

struct Matrix
{
    int rows;
    int cols;
    float * pData;
};

float matrix_max(struct Matrix mat)
{
    float max = FLT_MIN;
    //find max value of mat
    for(int r = 0; r < mat.rows; r++)
        for (int c = 0; c < mat.cols; c++)
        {
            float val = mat.pData[ r * mat.cols + c];
            max = ( max > val ? max : val);
        }
    return max;
}

Matrix * create_matrix(int rows, int cols)
{
    Matrix * p = new Matrix{rows, cols};
    p->pData = new float[p->rows * p->cols]{1.f, 2.f, 3.f};
    //you should check if the memory is allocated successfully
    return p;
}

bool matrix_add(const Matrix & matA, const Matrix & matB, Matrix & matC)
{
    // check the dimensions of the three matrices
    // re-create matC if needed
    // do: matC = matA + matB
    // return true if everything is right
    return true;
}

int main()
{
    using namespace std;

    Matrix matA = {3,4};
    matA.pData = new float[matA.rows * matA.cols]{1.f, 2.f, 3.f};

    Matrix matB = {4,8};
    matB.pData = new float[matB.rows * matB.cols]{10.f, 20.f, 30.f};

    Matrix matC = {4, 2};
    matC.pData = new float[matC.rows * matC.cols]{100.f, 200.f, 300.f};

    // some operations on the matrices

    float maxa = matrix_max(matA);
    float maxb = matrix_max(matB);
    float maxc = matrix_max(matC);

    cout << "max(matA) = " << maxa << endl;
    cout << "max(matB) = " << maxb << endl;
    cout << "max(matC) = " << maxc << endl;


    delete [] matA.pData;
    delete [] matB.pData;
    delete [] matC.pData;

    return 0;
}
