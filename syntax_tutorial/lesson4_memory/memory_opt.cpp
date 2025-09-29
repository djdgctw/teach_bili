#include <hls_stream.h>
#include <ap_int.h>

#define BUFFER_SIZE 4096
#define BLOCK_SIZE 512
typedef ap_int<16> data_t;

// 基础缓存实现 - 使用BRAM
void cache_basic(
    data_t input[BUFFER_SIZE],
    data_t output[BUFFER_SIZE])
{
    data_t buffer[BUFFER_SIZE];
    
    // 读取数据到缓存
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = input[i];
    }
    
    // 处理数据
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = buffer[i] * 2;
    }
    
    // 写回结果
    for (int i = 0; i < BUFFER_SIZE; i++) {
        output[i] = buffer[i];
    }
}

// URAM优化版本
void cache_uram(
    data_t input[BUFFER_SIZE],
    data_t output[BUFFER_SIZE])
{
    data_t buffer[BUFFER_SIZE];
    #pragma HLS bind_storage variable=buffer type=RAM_2P impl=URAM
    
    // 读取数据到URAM缓存
    for (int i = 0; i < BUFFER_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        buffer[i] = input[i];
    }
    
    // 处理数据
    for (int i = 0; i < BUFFER_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        buffer[i] = buffer[i] * 2;
    }
    
    // 写回结果
    for (int i = 0; i < BUFFER_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        output[i] = buffer[i];
    }
}

// 双缓冲优化版本
void cache_double_buffer(
    data_t input[BUFFER_SIZE],
    data_t output[BUFFER_SIZE])
{
    data_t buffer_a[BLOCK_SIZE];
    data_t buffer_b[BLOCK_SIZE];
    #pragma HLS ARRAY_PARTITION variable=buffer_a complete
    #pragma HLS ARRAY_PARTITION variable=buffer_b complete
    
    // 使用双缓冲进行流水线处理
    for (int block = 0; block < BUFFER_SIZE/BLOCK_SIZE; block++) {
        // 当前处理块的基址
        int base = block * BLOCK_SIZE;
        
        // 使用buffer_a处理当前块
        for (int i = 0; i < BLOCK_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            buffer_a[i] = input[base + i];
            buffer_a[i] = buffer_a[i] * 2;
            output[base + i] = buffer_a[i];
        }
        
        // 使用buffer_b预加载下一块
        if (block < BUFFER_SIZE/BLOCK_SIZE - 1) {
            int next_base = (block + 1) * BLOCK_SIZE;
            for (int i = 0; i < BLOCK_SIZE; i++) {
                #pragma HLS PIPELINE II=1
                buffer_b[i] = input[next_base + i];
            }
        }
        
        // 交换缓冲区
        data_t temp[BLOCK_SIZE];
        #pragma HLS ARRAY_PARTITION variable=temp complete
        for (int i = 0; i < BLOCK_SIZE; i++) {
            #pragma HLS UNROLL
            temp[i] = buffer_a[i];
            buffer_a[i] = buffer_b[i];
            buffer_b[i] = temp[i];
        }
    }
}

// 使用不同存储器类型的混合优化版本
void cache_hybrid(
    data_t input[BUFFER_SIZE],
    data_t output[BUFFER_SIZE])
{
    // 大容量缓存使用URAM
    data_t main_buffer[BUFFER_SIZE];
    #pragma HLS bind_storage variable=main_buffer type=RAM_2P impl=URAM
    
    // 小容量工作缓存使用BRAM
    data_t work_buffer[BLOCK_SIZE];
    #pragma HLS ARRAY_PARTITION variable=work_buffer cyclic factor=4
    
    // 分块加载和处理
    for (int block = 0; block < BUFFER_SIZE/BLOCK_SIZE; block++) {
        int base = block * BLOCK_SIZE;
        
        // 加载数据到主缓存
        for (int i = 0; i < BLOCK_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            main_buffer[base + i] = input[base + i];
        }
        
        // 处理数据块
        for (int i = 0; i < BLOCK_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            work_buffer[i] = main_buffer[base + i];
            work_buffer[i] = work_buffer[i] * 2;
            main_buffer[base + i] = work_buffer[i];
        }
        
        // 写回结果
        for (int i = 0; i < BLOCK_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            output[base + i] = main_buffer[base + i];
        }
    }
}

