#include <iostream>
#include <float.h>

struct Matrix
{
    int rows;
    int cols;
    float * pData;
};

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

    float maxa = FLT_MIN;
    float maxb = FLT_MIN;
    float maxc = FLT_MIN;

    //find max value of matA
    for(int r = 0; r < matA.rows; r++)
        for (int c = 0; c < matA.cols; c++)
        {
            float val = matA.pData[ r * matA.cols + c];
            maxa = ( maxa > val ? maxa : val);
        }

    //find max value of matB
    for(int r = 0; r < matB.rows; r++)
        for (int c = 0; c < matB.cols; c++)
        {
            float val = matB.pData[ r * matB.cols + c];
            maxb = ( maxb > val ? maxb : val);
        }

    //find max value of matC
    for(int r = 0; r < matC.rows; r++)
        for (int c = 0; c < matC.cols; c++)
        {
            float val = matC.pData[ r * matC.cols + c];
            maxc = ( maxc > val ? maxc : val);
        }

    cout << "max(matA) = " << maxa << endl;
    cout << "max(matB) = " << maxb << endl;
    cout << "max(matC) = " << maxc << endl;


    delete [] matA.pData;
    delete [] matB.pData;
    delete [] matC.pData;

    return 0;
}