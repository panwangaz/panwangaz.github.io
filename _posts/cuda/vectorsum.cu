#include <stdio.h>

__global__ void vectorAddKernel(float* a, float* b, float* c, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
    {
        c[i] = a[i] + b[i];
    }
}

void vectorAdd(float* a, float* b, float* c, int n)
{
    int blockSize = 256;
    int numBlocks = (n + blockSize - 1) / blockSize;

    vectorAddKernel<<<numBlocks, blockSize>>>(a, b, c, n);
}

int main()
{
    int n = 1000000;

    float* a = new float[n];
    float* b = new float[n];
    float* c = new float[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = i;
        b[i] = i * 2;
    }

    vectorAdd(a, b, c, n);

    for (int i = 0; i < n; i++)
    {
        printf("%f\n", c[i]);
    }

    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}
