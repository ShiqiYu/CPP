#include <stdio.h>
#include "matrix.h"

int main()
{
    Matrix * matA = createMat(2, 3);
    Matrix * matB = createMat(2, 3);
    Matrix * matC = createMat(2, 3);
    Matrix * matD = createMat(3, 2);
    Matrix * matNULL = NULL;

    //initialization
    //You should have your own method to do it
    matA->data[3] = 2.3f;
    matB->data[3] = 3.1f;

    if(! add(matA, matB, matC))
        fprintf(stderr, "Matrix addition failed.");
    else
    {
        //You can have a better method to show the results
        printf("result=%f\n", matC->data[3]);
    }

    //more tests
    add(matA, matB, matD);

    add(matNULL, matB, matC);

    return 0;
}