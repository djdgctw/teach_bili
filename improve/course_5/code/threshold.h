#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "ap_int.h"

void threshold(const ap_uint<8> *input, ap_uint<8> *output, int size, ap_uint<8> thresh_val);

#endif 