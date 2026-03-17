#include <stdio.h>

__global__ void mykernel()
{
    printf("Hello, CUDA. I'm Thread %d in Block %d. blockDim=%d.\n",
            threadIdx.x, blockIdx.x, blockDim.x);
}

int main()
{
    cudaError_t ecode = cudaSuccess;
    mykernel<<<2,2>>>();
    if ((ecode = cudaGetLastError()) != cudaSuccess) // check 
    {
        fprintf(stderr, "CUDA Error: %s\n", cudaGetErrorString(ecode));
        return false;
    }
    cudaDeviceSynchronize();
    
    return 0;
}