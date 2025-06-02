#ifndef VECTOR_ADD_H
#define VECTOR_ADD_H

#include <ap_int.h>

void vector_add(const ap_uint<32> *a,
                ap_uint<32> *c,
                int size);
#endif // VECTOR_ADD_H 