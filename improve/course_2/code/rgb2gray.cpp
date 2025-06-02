#include "rgb2gray.h"

void rgb2gray(const ap_uint<24> *rgb, ap_uint<8> *gray, int size) {
#pragma HLS INTERFACE m_axi port=rgb offset=slave bundle=gmem0 depth=4096
#pragma HLS INTERFACE m_axi port=gray offset=slave bundle=gmem1 depth=4096
#pragma HLS INTERFACE s_axilite port=rgb bundle=control
#pragma HLS INTERFACE s_axilite port=gray bundle=control
#pragma HLS INTERFACE s_axilite port=size bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control
    for (int i = 0; i < size; i++) {
#pragma HLS PIPELINE
        ap_uint<8> r = rgb[i].range(23, 16);
        ap_uint<8> g = rgb[i].range(15, 8);
        ap_uint<8> b = rgb[i].range(7, 0);
        gray[i] = (r * 30 + g * 59 + b * 11) / 100;
    }
} 