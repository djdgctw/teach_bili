set SynModuleInfo {
  {SRCNAME sobel_edge_Pipeline_VITIS_LOOP_17_2 MODELNAME sobel_edge_Pipeline_VITIS_LOOP_17_2 RTLNAME sobel_edge_sobel_edge_Pipeline_VITIS_LOOP_17_2
    SUBMODULES {
      {MODELNAME sobel_edge_flow_control_loop_pipe_sequential_init RTLNAME sobel_edge_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME sobel_edge_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME sobel_edge_Pipeline_VITIS_LOOP_37_5 MODELNAME sobel_edge_Pipeline_VITIS_LOOP_37_5 RTLNAME sobel_edge_sobel_edge_Pipeline_VITIS_LOOP_37_5}
  {SRCNAME sobel_edge_Pipeline_VITIS_LOOP_41_6 MODELNAME sobel_edge_Pipeline_VITIS_LOOP_41_6 RTLNAME sobel_edge_sobel_edge_Pipeline_VITIS_LOOP_41_6}
  {SRCNAME sobel_edge MODELNAME sobel_edge RTLNAME sobel_edge IS_TOP 1
    SUBMODULES {
      {MODELNAME sobel_edge_mul_31ns_32s_63_2_1 RTLNAME sobel_edge_mul_31ns_32s_63_2_1 BINDTYPE op TYPE mul IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME sobel_edge_mul_32s_32s_32_2_1 RTLNAME sobel_edge_mul_32s_32s_32_2_1 BINDTYPE op TYPE mul IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME sobel_edge_gmem0_m_axi RTLNAME sobel_edge_gmem0_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME sobel_edge_gmem1_m_axi RTLNAME sobel_edge_gmem1_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME sobel_edge_control_s_axi RTLNAME sobel_edge_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
