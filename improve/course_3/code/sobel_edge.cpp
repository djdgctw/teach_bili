#include "sobel_edge.h"

void sobel_edge(const ap_uint<8> *input, ap_uint<8> *output, int rows, int cols) {
#pragma HLS INTERFACE m_axi port=input offset=slave bundle=gmem0 depth=4096
#pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem1 depth=4096
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE s_axilite port=output bundle=control
#pragma HLS INTERFACE s_axilite port=rows bundle=control
#pragma HLS INTERFACE s_axilite port=cols bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

    // Sobel kernels
    const int sobel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    const int sobel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
#pragma HLS PIPELINE
            int gx = 0, gy = 0;
            
            // Apply Sobel kernels
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    ap_uint<8> pixel = input[(i + ki) * cols + (j + kj)];
                    gx += sobel_x[ki + 1][kj + 1] * pixel;
                    gy += sobel_y[ki + 1][kj + 1] * pixel;
                }
            }
            
            // Calculate edge magnitude: |gx| + |gy|
            int magnitude = (gx < 0 ? -gx : gx) + (gy < 0 ? -gy : gy);
            output[i * cols + j] = (magnitude > 255) ? 255 : magnitude;
        }
    }
    
    // Set border pixels to 0
    for (int i = 0; i < rows; i++) {
        output[i * cols] = 0;  // left border
        output[i * cols + cols - 1] = 0;  // right border
    }
    for (int j = 0; j < cols; j++) {
        output[j] = 0;  // top border
        output[(rows - 1) * cols + j] = 0;  // bottom border
    }
} 