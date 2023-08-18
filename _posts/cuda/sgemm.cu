#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#define BLOCK_WIDTH 16
using namespace std;


__global__ void MatrixMulKernel(int m, int n, int k, float *A,float  *B, float *C)
{
	int Row=blockIdx.y*blockDim.y+threadIdx.y;
	int Col=blockIdx.x*blockDim.x+threadIdx.x;

	if((Row<m) && (Col<k))
	{
		float cur =0.0;
		for(int i=0;i<n;++i)
		     cur += A[Row*n+i]*B[Col+i*k];
		C[Row*k+Col]= cur;
	}
}


__global__ void MatrixMulKernel(int m, int n, int k, float *A,float  *B, float *C)
{
	 //申请共享内存，存在于每个block中
	__shared__ float ds_A[BLOCK_WIDTH][BLOCK_WIDTH];
	__shared__ float ds_B[BLOCK_WIDTH][BLOCK_WIDTH];
	//简化坐标记法,出现下面6个表示的地方就是并行的地方。
	int bx = blockIdx.x, by = blockIdx.y;
	int tx = threadIdx.x, ty = threadIdx.y;
	//确定结果矩阵中的行和列
	int Row = by * BLOCK_WIDTH + ty;
	int Col = bx * BLOCK_WIDTH + tx;
	float val = 0;

 	//循环读入A,B瓦片，计算结果矩阵，分阶段进行计算
	for (int t=0; t < (n-1) / BLOCK_WIDTH + 1; ++t)
	{
		//将A,B矩阵瓦片化的结果放入shared memory中，每个线程加载相应于C元素的A/B矩阵元素
		if (Row < m && t * BLOCK_WIDTH + tx < n)
		    ds_A[tx][ty] = A[Row * n + t*BLOCK_WIDTH+tx];
		else
			ds_A[tx][ty] = 0.0;

		if (t * BLOCK_WIDTH + ty < n && Col < k)
            ds_B[tx][ty] = B[(t*BLOCK_WIDTH + ty) * k + Col];
		else
			ds_B[tx][ty] = 0.0;

		__syncthreads();
		for (int i = 0; i < BLOCK_WIDTH; ++i)
            val += ds_A[i][ty] * ds_B[tx][i];

		__syncthreads();
 		if(Row < m && Col < k)
			C[Row*k+Col]=val;
	}
}


int main()
{
    float A[6] = { 11.4, 24, 33.5,   45, 55 ,32.4 }; //2×3的矩阵
	float B[12] = {12,43,22.4, 31.3,  12,324,23,12,  44.4,23.4,65.3,73};//3×4的矩阵
    float C[8] = { 0 }; //2×4的结果矩阵
	int m=2,n=3,k=4;

	int size = sizeof(float);
	float *d_a;
	float *d_b;
	float *d_c;
	cudaMalloc((void**)&d_a,m*n*size);
	cudaMalloc((void**)&d_b,n*k*size);
	cudaMalloc((void**)&d_c,m*k*size);

	cudaMemcpy(d_a, A, size*6, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, B, size*12, cudaMemcpyHostToDevice);
	cudaMemcpy(d_c, C, size*8, cudaMemcpyHostToDevice);

    dim3 dimBlock(BLOCK_WIDTH,BLOCK_WIDTH,1);
	dim3 dimGrid((k-1)/BLOCK_WIDTH+1,(m-1)/BLOCK_WIDTH+1,1);

	MatrixMulKernel<<<dimGrid,dimBlock>>>(m,n,k,d_a,d_b,d_c);

	cudaMemcpy(C, d_c, size*8, cudaMemcpyDeviceToHost);

    for (int i=0;i<8;i++)
	{
		cout<<C[i]<<endl;
	}

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

    return 0;
}
