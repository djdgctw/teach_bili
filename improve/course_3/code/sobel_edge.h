#ifndef SOBEL_EDGE_H
#define SOBEL_EDGE_H

#include "ap_int.h"

void sobel_edge(const ap_uint<8> *input, ap_uint<8> *output, int rows, int cols);

#endif 