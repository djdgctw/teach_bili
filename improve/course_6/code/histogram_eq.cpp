#include "histogram_eq.h"

void histogram_eq(const ap_uint<8> *input, ap_uint<8> *output, int size) {
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem0 depth=4096
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem1 depth=4096
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=size bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    // Step 1: Calculate histogram
    int histogram[256];
#pragma HLS ARRAY_PARTITION variable=histogram complete
    
    // Initialize histogram
    for (int i = 0; i < 256; i++) {
#pragma HLS PIPELINE
        histogram[i] = 0;
    }
    
    // Count pixels for each intensity level
    for (int i = 0; i < size; i++) {
#pragma HLS PIPELINE
        ap_uint<8> pixel_value = input[i];
        histogram[pixel_value]++;
    }
    
    // Step 2: Calculate cumulative distribution function (CDF)
    int cdf[256];
#pragma HLS ARRAY_PARTITION variable=cdf complete
    
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; i++) {
#pragma HLS PIPELINE
        cdf[i] = cdf[i-1] + histogram[i];
    }
    
    // Step 3: Generate mapping table
    ap_uint<8> map_table[256];
#pragma HLS ARRAY_PARTITION variable=map_table complete
    
    int cdf_min = cdf[0];
    for (int i = 0; i < 256; i++) {
#pragma HLS PIPELINE
        // Histogram equalization formula: 
        // new_value = (cdf[i] - cdf_min) * 255 / (size - cdf_min)
        int numerator = (cdf[i] - cdf_min) * 255;
        int denominator = size - cdf_min;
        
        if (denominator == 0) {
            map_table[i] = 0;
        } else {
            int mapped_value = numerator / denominator;
            map_table[i] = (mapped_value > 255) ? 255 : mapped_value;
        }
    }
    
    // Step 4: Apply mapping to output image
    for (int i = 0; i < size; i++) {
#pragma HLS PIPELINE
        ap_uint<8> pixel_value = input[i];
        output[i] = map_table[pixel_value];
    }
} 