#include <stdio.h>

__global__ void add(const float * input1, const float * input2, float * output, size_t len)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if(i < len)
    {
        printf("(%d, %d) working for element %d\n", blockDim.x, threadIdx.x, i);
        output[i] = input1[i] + input2[i];
    }
    else
    {
        printf("(%d, %d) skipped element %d\n", blockDim.x, threadIdx.x, i);
    }

}

int main()
{
    cudaError_t ecode = cudaSuccess;
    const size_t len = 8;
    float vec1[len]{0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f};
    float vec2[len]{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};
    float vec3[len]{};

    float * cudaVec1 = NULL;
    float * cudaVec2 = NULL;
    float * cudaVec3 = NULL;


    if (cudaMalloc (&cudaVec1, sizeof(float) * len) != cudaSuccess
        || cudaMalloc (&cudaVec2, sizeof(float) * len) != cudaSuccess
        || cudaMalloc (&cudaVec3, sizeof(float) * len) != cudaSuccess)
    {
        fprintf(stderr, "Allocate device memory failed.\n");
        return -1;
    }
    cudaMemcpy(cudaVec1, vec1, sizeof(float)*len, cudaMemcpyHostToDevice);
    cudaMemcpy(cudaVec2, vec2, sizeof(float)*len, cudaMemcpyHostToDevice);
    add<<<2,2>>>(cudaVec1, cudaVec2, cudaVec3, len);
    if ((ecode = cudaGetLastError()) != cudaSuccess) // check 
    {
        fprintf(stderr, "CUDA Error: %s\n", cudaGetErrorString(ecode));
        return false;
    }
    cudaMemcpy(vec3, cudaVec3, sizeof(float)*len, cudaMemcpyDeviceToHost);  
    cudaDeviceSynchronize();

    for(size_t i = 0; i < len; i++)
        printf("vec3[%zu] = %.1f\n", i, vec3[i]);

    return 0;
}