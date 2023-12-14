__global__ void reduceSumKernel(float *input, float *output, int n)
{
    extern __shared__ float sdata[];

    int tid = threadIdx.x;
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    sdata[tid] = (i < n) ? input[i] : 0;
    __syncthreads();

    for (int s = blockDim.x / 2; s > 0; s >>= 1)
    {
        if (tid < s)
        {
            sdata[tid] += sdata[tid + s];
        }
        __syncthreads();
    }

    if (tid == 0)
    {
        output[blockIdx.x] = sdata[0];
    }
}


int main() {
    int n = 100000;
    float* input;
    input = (float*) malloc(n * sizeof(float));

    for (int i = 0; i < n; i++) {
        input[i] = 2.3f;
    }

    float *d_input, *d_output;

    cudaMalloc((void **)&d_input, n * sizeof(float));
    cudaMemcpy(d_input, input, n * sizeof(float), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    cudaMalloc((void **)&d_output, blocksPerGrid * sizeof(float));

    reduceSumKernel<<<blocksPerGrid, threadsPerBlock, threadsPerBlock * sizeof(float)>>>(d_input, d_output, n);

    float *output = (float *)malloc(blocksPerGrid * sizeof(float));
    cudaMemcpy(output, d_output, blocksPerGrid * sizeof(float), cudaMemcpyDeviceToHost);

    float result = 0;
    for (int i = 0; i < blocksPerGrid; i++)
    {
        result += output[i];
    }

    cudaFree(d_input);
    cudaFree(d_output);
    free(output);
    return 0;
}
