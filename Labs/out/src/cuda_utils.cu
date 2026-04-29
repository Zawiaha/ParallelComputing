#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>


__global__ void columnMaxKernel(const double* matrix, double* result, 
                                 size_t rows, size_t cols) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (col < cols) {
        double max_val = -1e308; // примерно lowest
        for (size_t i = 0; i < rows; i++) {
            double val = matrix[i * cols + col];
            if (val > max_val) max_val = val;
        }
        result[col] = max_val;
    }
}

extern "C" void runCudaKernel(const double* h_matrix, double* h_result,
                               size_t rows, size_t cols) {
    double *d_matrix, *d_result;
    size_t matrix_size = rows * cols * sizeof(double);
    size_t result_size = cols * sizeof(double);
    
    // Выделяем память на GPU
    cudaMalloc(&d_matrix, matrix_size);
    cudaMalloc(&d_result, result_size);
    
    // Копируем данные на GPU
    cudaMemcpy(d_matrix, h_matrix, matrix_size, cudaMemcpyHostToDevice);
    
    // Запускаем ядро
    int threadsPerBlock = 256;
    int blocksPerGrid = (cols + threadsPerBlock - 1) / threadsPerBlock;
    
    columnMaxKernel<<<blocksPerGrid, threadsPerBlock>>>(d_matrix, d_result, rows, cols);
    
    // Копируем результат обратно
    cudaMemcpy(h_result, d_result, result_size, cudaMemcpyDeviceToHost);
    
    // Очищаем память
    cudaFree(d_matrix);
    cudaFree(d_result);
}