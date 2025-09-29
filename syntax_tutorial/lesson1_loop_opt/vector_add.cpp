#include <hls_stream.h>
#include <ap_int.h>

// 基本向量加法示例 - 未优化版本
void vector_add_basic(int A[1024], int B[1024], int C[1024]) {
    for (int i = 0; i < 1024; i++) {
        C[i] = A[i] + B[i];
    }
}

// 循环展开示例 - factor=2
void vector_add_unroll(int A[1024], int B[1024], int C[1024]) {
    #pragma HLS array_partition variable=A cyclic factor=2
    #pragma HLS array_partition variable=B cyclic factor=2
    #pragma HLS array_partition variable=C cyclic factor=2
    
    for (int i = 0; i < 1024; i++) {
        #pragma HLS UNROLL factor=2
        C[i] = A[i] + B[i];
    }
}

// 循环流水线示例
void vector_add_pipeline(int A[1024], int B[1024], int C[1024]) {
    #pragma HLS array_partition variable=A cyclic factor=8
    #pragma HLS array_partition variable=B cyclic factor=8
    #pragma HLS array_partition variable=C cyclic factor=8
    
    #pragma HLS PIPELINE II
    for (int i = 0; i < 1024; i++) {
        C[i] = A[i] + B[i];
    }
}


