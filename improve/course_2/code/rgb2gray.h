#ifndef RGB2GRAY_H
#define RGB2GRAY_H

#include <ap_int.h>

void rgb2gray(const ap_uint<24> *rgb, ap_uint<8> *gray, int size);

#endif // RGB2GRAY_H 