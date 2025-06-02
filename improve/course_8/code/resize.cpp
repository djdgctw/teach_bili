#include "resize.h"

void resize_half(const ap_uint<8> *input, ap_uint<8> *output, int rows, int cols) {
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem0 depth=4096
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem1 depth=4096
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=rows bundle=control
#pragma HLS INTERFACE s_axilite port=cols bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    int new_rows = rows / 2;
    int new_cols = cols / 2;
    
    // Simple downsampling: take every 2nd pixel
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
#pragma HLS PIPELINE
            int input_i = i * 2;
            int input_j = j * 2;
            int input_idx = input_i * cols + input_j;
            int output_idx = i * new_cols + j;
            output[output_idx] = input[input_idx];
        }
    }
} 