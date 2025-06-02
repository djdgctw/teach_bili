#ifndef GAUSSIAN_BLUR_H
#define GAUSSIAN_BLUR_H

#include "ap_int.h"

void gaussian_blur(const ap_uint<8> *input, ap_uint<8> *output, int rows, int cols);

#endif 