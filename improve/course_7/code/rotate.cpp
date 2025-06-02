#include "rotate.h"

void rotate_90(const ap_uint<8> *input, ap_uint<8> *output, int rows, int cols) {
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem0 depth=4096
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem1 depth=4096
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=rows bundle=control
#pragma HLS INTERFACE s_axilite port=cols bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    // Rotate 90 degrees clockwise: (x,y) -> (y, rows-1-x)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
#pragma HLS PIPELINE
            int input_idx = i * cols + j;
            int output_idx = j * rows + (rows - 1 - i);
            output[output_idx] = input[input_idx];
        }
    }
} 