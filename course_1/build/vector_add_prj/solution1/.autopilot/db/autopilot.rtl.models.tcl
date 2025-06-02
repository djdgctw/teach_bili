set SynModuleInfo {
  {SRCNAME vector_add_Pipeline_VITIS_LOOP_13_1 MODELNAME vector_add_Pipeline_VITIS_LOOP_13_1 RTLNAME vector_add_vector_add_Pipeline_VITIS_LOOP_13_1
    SUBMODULES {
      {MODELNAME vector_add_flow_control_loop_pipe_sequential_init RTLNAME vector_add_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME vector_add_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME vector_add MODELNAME vector_add RTLNAME vector_add IS_TOP 1
    SUBMODULES {
      {MODELNAME vector_add_gmem0_m_axi RTLNAME vector_add_gmem0_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME vector_add_gmem1_m_axi RTLNAME vector_add_gmem1_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME vector_add_control_s_axi RTLNAME vector_add_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
