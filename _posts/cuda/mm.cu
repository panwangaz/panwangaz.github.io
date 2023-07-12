#include<stdio.h>
#define N 10000, M 2000

__global__ void sgemm(const float* a, const float* b, float* c, int row, int col, int k) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;
    if (i < row && j < col) {
        float sum = 0.0f;
        for (int index = 0; index < k; index++) {
            sum += a[i * row + k] * B[k * index + j];
        }
        c[i * row + col] = sum;
    }
}

int main() {
    float *hA, *hB, *hC;
    float *dA, *dB, *dC;
    int size = N * N * sizeof(float);

    hA = malloc(size);
    hB = malloc(size);
    hC = malloc(size);
    for (int i = 0; i < N * N; i++) {
        hA[i] = 2.0f;
        hB[i] = 3.0f;
    }

    cudaMalloc(&dA, size);
    cudaMalloc(&dB, size);
    cudaMalloc(&dC, size);

    cudaMemcpy(dA, hA, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dB, hB, size, cudaMemcpyHostToDevice);

    dim3 blockSize(16, 16);
    dim3 gridSize((N + blockSize.x - 1) / blockSize.x, (N + blockSize.y - 1) / blockSize.y);

    sgemm<<<gridSize, blockSize>>>(dA, dB, dC, N, N, N);

    cudaMemcpy(hC, dC, size, cudaMemcpyDeviceToHost);

    for (int i = 0; i < N*N; i++) {
        if (hC[i] != 6.0f * N) {
            printf("Error: incorrect result\n");
            break;
        }
    }
    printf("Success: correct result\n");

    free(hA);
    free(hB);
    free(hC);
    cudaFree(dA);
    cudaFree(dB);
    cudaFree(dC);

    return 0;
}
