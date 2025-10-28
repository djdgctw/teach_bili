#include "ap_int.h"

void led(ap_uint<4> key_t, ap_uint<4> &led){
    #pragma HLS INTERFACE ap_none port=key_t
    #pragma HLS INTERFACE ap_none port=led
    #pragma HLS INTERFACE ap_ctrl_none port=return
    led = key_t;
}
