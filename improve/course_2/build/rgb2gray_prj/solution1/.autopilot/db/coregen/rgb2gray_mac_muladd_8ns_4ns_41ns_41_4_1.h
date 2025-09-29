// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1__HH__
#define __rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1__HH__
#include "rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1.h"

template<
    int ID,
    int NUM_STAGE,
    int din0_WIDTH,
    int din1_WIDTH,
    int din2_WIDTH,
    int dout_WIDTH>
SC_MODULE(rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1) {
    sc_core::sc_in_clk clk;
    sc_core::sc_in<sc_dt::sc_logic> reset;
    sc_core::sc_in<sc_dt::sc_logic> ce;
    sc_core::sc_in< sc_dt::sc_lv<din0_WIDTH> >   din0;
    sc_core::sc_in< sc_dt::sc_lv<din1_WIDTH> >   din1;
    sc_core::sc_in< sc_dt::sc_lv<din2_WIDTH> >   din2;
    sc_core::sc_out< sc_dt::sc_lv<dout_WIDTH> >   dout;



    rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1 rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1_U;

    SC_CTOR(rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1):  rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1_U ("rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1_U") {
        rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1_U.clk(clk);
        rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1_U.rst(reset);
        rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1_U.ce(ce);
        rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1_U.in0(din0);
        rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1_U.in1(din1);
        rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1_U.in2(din2);
        rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1_DSP48_1_U.dout(dout);

    }

};

#endif //
