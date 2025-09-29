set SynModuleInfo {
  {SRCNAME rgb2gray_Pipeline_VITIS_LOOP_10_1 MODELNAME rgb2gray_Pipeline_VITIS_LOOP_10_1 RTLNAME rgb2gray_rgb2gray_Pipeline_VITIS_LOOP_10_1
    SUBMODULES {
      {MODELNAME rgb2gray_mul_41ns_43ns_56_5_1 RTLNAME rgb2gray_mul_41ns_43ns_56_5_1 BINDTYPE op TYPE mul IMPL dsp LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME rgb2gray_mac_muladd_8ns_6ns_40ns_41_4_1 RTLNAME rgb2gray_mac_muladd_8ns_6ns_40ns_41_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1 RTLNAME rgb2gray_mac_muladd_8ns_4ns_41ns_41_4_1 BINDTYPE op TYPE all IMPL dsp48 LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME rgb2gray_flow_control_loop_pipe_sequential_init RTLNAME rgb2gray_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME rgb2gray_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME rgb2gray MODELNAME rgb2gray RTLNAME rgb2gray IS_TOP 1
    SUBMODULES {
      {MODELNAME rgb2gray_gmem0_m_axi RTLNAME rgb2gray_gmem0_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME rgb2gray_gmem1_m_axi RTLNAME rgb2gray_gmem1_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME rgb2gray_control_s_axi RTLNAME rgb2gray_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
