#include "threshold.h"

void threshold(const ap_uint<8> *input, ap_uint<8> *output, int size, ap_uint<8> thresh_val) {
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem0 depth=4096
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem1 depth=4096
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=size bundle=control
#pragma HLS INTERFACE s_axilite port=thresh_val bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    // Apply threshold to each pixel
    for (int i = 0; i < size; i++) {
#pragma HLS PIPELINE
        if (input[i] > thresh_val) {
            output[i] = 255;  // White
        } else {
            output[i] = 0;    // Black
        }
    }
} 