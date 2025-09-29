#include <hls_stream.h>
#include <ap_int.h>

#define DATA_SIZE 1024
#define BLOCK_SIZE 256
typedef ap_int<16> data_t;

// 基础处理流程 - 无优化版本
void process_data_basic(
    data_t in_data[DATA_SIZE],
    data_t out_data[DATA_SIZE])
{
    data_t temp[DATA_SIZE];
    
    // 第一阶段：数据预处理
    for (int i = 0; i < DATA_SIZE; i++) {
        temp[i] = in_data[i] * 2;
    }
    
    // 第二阶段：数据过滤
    for (int i = 0; i < DATA_SIZE; i++) {
        if (temp[i] > 1000) {
            temp[i] = 1000;
        }
    }
    
    // 第三阶段：数据输出
    for (int i = 0; i < DATA_SIZE; i++) {
        out_data[i] = temp[i] + 100;
    }
}

// 使用dataflow优化的处理流程
void process_stage1(
    data_t in_data[DATA_SIZE],
    hls::stream<data_t>& stream1)
{
    #pragma HLS INLINE off
    for (int i = 0; i < DATA_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        stream1.write(in_data[i] * 2);
    }
}

void process_stage2(
    hls::stream<data_t>& stream1,
    hls::stream<data_t>& stream2)
{
    #pragma HLS INLINE off
    for (int i = 0; i < DATA_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        data_t temp = stream1.read();
        if (temp > 1000) {
            temp = 1000;
        }
        stream2.write(temp);
    }
}

void process_stage3(
    hls::stream<data_t>& stream2,
    data_t out_data[DATA_SIZE])
{
    #pragma HLS INLINE off
    for (int i = 0; i < DATA_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        out_data[i] = stream2.read() + 100;
    }
}

void process_data_dataflow(
    data_t in_data[DATA_SIZE],
    data_t out_data[DATA_SIZE])
{
    #pragma HLS DATAFLOW
    hls::stream<data_t> stream1;
    #pragma HLS STREAM variable=stream1 depth=32
    hls::stream<data_t> stream2;
    #pragma HLS STREAM variable=stream2 depth=32
    
    process_stage1(in_data, stream1);
    process_stage2(stream1, stream2);
    process_stage3(stream2, out_data);
}

