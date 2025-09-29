#include <hls_stream.h>
#include <ap_int.h>

// 定义常量
#define MATRIX_SIZE 8
#define VECTOR_SIZE 64
typedef ap_int<16> data_t;

// 基础矩阵乘法 - 未优化版本
void matrix_multiply_basic(
    data_t A[MATRIX_SIZE][MATRIX_SIZE],
    data_t B[MATRIX_SIZE][MATRIX_SIZE],
    data_t C[MATRIX_SIZE][MATRIX_SIZE]) 
{
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            data_t sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

// 使用完全分区的矩阵乘法
void matrix_multiply_partition(
    data_t A[MATRIX_SIZE][MATRIX_SIZE],
    data_t B[MATRIX_SIZE][MATRIX_SIZE],
    data_t C[MATRIX_SIZE][MATRIX_SIZE]) 
{
    // 对矩阵A按第二维完全分区，实现并行访问
    #pragma HLS ARRAY_PARTITION variable=A dim=2 complete
    // 对矩阵B按第一维完全分区
    #pragma HLS ARRAY_PARTITION variable=B dim=1 complete
    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            #pragma HLS PIPELINE II=1
            data_t sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

// 使用循环分区的矩阵乘法
void matrix_multiply_cyclic(
    data_t A[MATRIX_SIZE][MATRIX_SIZE],
    data_t B[MATRIX_SIZE][MATRIX_SIZE],
    data_t C[MATRIX_SIZE][MATRIX_SIZE]) 
{
    // 对矩阵A按第二维循环分区，factor=2
    #pragma HLS ARRAY_PARTITION variable=A dim=2 cyclic factor=2
    // 对矩阵B按第一维循环分区，factor=2
    #pragma HLS ARRAY_PARTITION variable=B dim=1 cyclic factor=2
    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            #pragma HLS PIPELINE II=1
            data_t sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

// 使用数组重构的矩阵乘法
void matrix_multiply_reshape(
    data_t A[MATRIX_SIZE][MATRIX_SIZE],
    data_t B[MATRIX_SIZE][MATRIX_SIZE],
    data_t C[MATRIX_SIZE][MATRIX_SIZE]) 
{
    // 对矩阵A按第二维完全重构
    #pragma HLS ARRAY_RESHAPE variable=A dim=2 complete
    // 对矩阵B按第一维完全重构
    #pragma HLS ARRAY_RESHAPE variable=B dim=1 complete
    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            #pragma HLS PIPELINE II=1
            data_t sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

