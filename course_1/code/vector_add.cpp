#include "vector_add.h"

void vector_add(const ap_uint<32> *a,
                ap_uint<32> *c,
                int size) {
#pragma HLS INTERFACE m_axi port=a offset=slave bundle=gmem0 depth=256
#pragma HLS INTERFACE m_axi port=c offset=slave bundle=gmem1 depth=256
#pragma HLS INTERFACE s_axilite port=a bundle=control
#pragma HLS INTERFACE s_axilite port=c bundle=control
#pragma HLS INTERFACE s_axilite port=size bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    for (int i = 0; i < size; i++) {
    #pragma HLS PIPELINE
        c[i] = a[i] - 1;
    }
} 