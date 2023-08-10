#include <stdio.h>

const int N = 1024;

__global__ void matrixMultiply(float* A, float* B, float* C, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
    if (i < n && j < n) {
        float sum = 0.0f;
        for (int k = 0; k < n; k++) {
            sum += A[i * n + k] * B[k * n + j];
        }
        C[i * n + j] = sum;
    }
}


int main() {
    float *hA, *hB, *hC;
    float *dA, *dB, *dC;
    int size = N * N * sizeof(float);

    // 分配内存并初始化矩阵
    hA = (float*)malloc(size);
    hB = (float*)malloc(size);
    hC = (float*)malloc(size);
    for (int i = 0; i < N * N; i++) {
        hA[i] = 1.0f;
        hB[i] = 2.0f;
    }

    // 在GPU上分配内存
    cudaMalloc(&dA, size);
    cudaMalloc(&dB, size);
    cudaMalloc(&dC, size);

    // 将矩阵数据从主机(CPU)内存拷贝到GPU全局内存
    cudaMemcpy(dA, hA, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dB, hB, size, cudaMemcpyHostToDevice);

    // 设置块(Block)和线程(Thread)的数量
    dim3 blockSize(16, 16);
    dim3 gridSize((N + blockSize.x - 1) / blockSize.x, (N + blockSize.y - 1) / blockSize.y);

    // 调用CUDA内核函数计算矩阵乘法
    matrixMultiply<<<gridSize, blockSize>>>(dA, dB, dC, N);

    // 将计算结果从GPU全局内存拷贝回主机(CPU)内存
    cudaMemcpy(hC, dC, size, cudaMemcpyDeviceToHost);

    // 验证计算结果
    for (int i = 0; i < N * N; i++) {
        if (hC[i] != 2.0f * N) {
            printf("Error: incorrect result\n");
            break;
        }
    }
    printf("Success: correct result\n");

    // 释放内存
    free(hA);
    free(hB);
    free(hC);
    cudaFree(dA);
    cudaFree(dB);
    cudaFree(dC);

    return 0;
}
