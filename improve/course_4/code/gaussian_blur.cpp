#include "gaussian_blur.h"

void gaussian_blur(const ap_uint<8> *input, ap_uint<8> *output, int rows, int cols) {
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem0 depth=4096
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem1 depth=4096
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=rows bundle=control
#pragma HLS INTERFACE s_axilite port=cols bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    // 5x5 Gaussian kernel (σ ≈ 1.0)
    const int gaussian_kernel[5][5] = {
        {1,  4,  6,  4, 1},
        {4, 16, 24, 16, 4},
        {6, 24, 36, 24, 6},
        {4, 16, 24, 16, 4},
        {1,  4,  6,  4, 1}
    };
    const int kernel_sum = 256;  // Sum of all kernel values
    
    // Apply Gaussian blur to inner pixels
    for (int i = 2; i < rows - 2; i++) {
        for (int j = 2; j < cols - 2; j++) {
#pragma HLS PIPELINE
            int sum = 0;
            
            // Apply 5x5 Gaussian kernel
            for (int ki = -2; ki <= 2; ki++) {
                for (int kj = -2; kj <= 2; kj++) {
                    ap_uint<8> pixel = input[(i + ki) * cols + (j + kj)];
                    sum += gaussian_kernel[ki + 2][kj + 2] * pixel;
                }
            }
            
            // Normalize by kernel sum
            output[i * cols + j] = sum / kernel_sum;
        }
    }
    
    // Handle border pixels - copy original values
    // Top and bottom borders (2 rows each)
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < cols; j++) {
            output[i * cols + j] = input[i * cols + j];  // top border
            output[(rows - 1 - i) * cols + j] = input[(rows - 1 - i) * cols + j];  // bottom border
        }
    }
    
    // Left and right borders (2 columns each)
    for (int i = 2; i < rows - 2; i++) {
        for (int j = 0; j < 2; j++) {
            output[i * cols + j] = input[i * cols + j];  // left border
            output[i * cols + (cols - 1 - j)] = input[i * cols + (cols - 1 - j)];  // right border
        }
    }
} 