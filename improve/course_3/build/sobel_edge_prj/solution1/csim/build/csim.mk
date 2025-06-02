# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
# Tool Version Limit: 2019.12
# Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
# ==============================================================
CSIM_DESIGN = 1

__SIM_FPO__ = 1

__SIM_MATHHLS__ = 1

__SIM_FFT__ = 1

__SIM_FIR__ = 1

__SIM_DDS__ = 1

ObjDir = obj

HLS_SOURCES = ../../../../../code/main.cpp ../../../../../code/sobel_edge.cpp

override TARGET := csim.exe

AUTOPILOT_ROOT := /opt/Xilinx/Vitis_HLS/2022.2
AUTOPILOT_MACH := lnx64
ifdef AP_GCC_M32
  AUTOPILOT_MACH := Linux_x86
  IFLAG += -m32
endif
IFLAG += -fPIC
ifndef AP_GCC_PATH
  AP_GCC_PATH := /opt/Xilinx/Vitis_HLS/2022.2/tps/lnx64/gcc-8.3.0/bin
endif
AUTOPILOT_TOOL := ${AUTOPILOT_ROOT}/${AUTOPILOT_MACH}/tools
AP_CLANG_PATH := ${AUTOPILOT_TOOL}/clang-3.9/bin
AUTOPILOT_TECH := ${AUTOPILOT_ROOT}/common/technology


IFLAG += -I "${AUTOPILOT_ROOT}/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include/ap_sysc"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_FP_comp"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_comp"
IFLAG += -I "${AUTOPILOT_TOOL}/auto_cc/include"
IFLAG += -I "/usr/include/x86_64-linux-gnu"
IFLAG += -D__HLS_COSIM__

IFLAG += -D__HLS_CSIM__

IFLAG += -D__VITIS_HLS__

IFLAG += -D__SIM_FPO__

IFLAG += -D__SIM_FFT__

IFLAG += -D__SIM_FIR__

IFLAG += -D__SIM_DDS__

IFLAG += -D__DSP48E1__
IFLAG += -I/home/fyt/.conda/envs/opencv_env/include/opencv4 -std=c++14 -L/home/fyt/.conda/envs/opencv_env/lib -Wl,-rpath,/home/fyt/.conda/envs/opencv_env/lib -Wno-unknown-pragmas 
LFLAG += -L/home/fyt/.conda/envs/opencv_env/lib -Wl,-rpath,/home/fyt/.conda/envs/opencv_env/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs
IFLAG += -g
DFLAG += -D__xilinx_ip_top= -DAESL_TB
CCFLAG += -Werror=return-type
CCFLAG += -Wno-abi
TOOLCHAIN += 



include ./Makefile.rules

all: $(TARGET)



$(ObjDir)/main.o: ../../../../../code/main.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../code/main.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -I/home/fyt/.conda/envs/opencv_env/include/opencv4 -std=c++14 -L/home/fyt/.conda/envs/opencv_env/lib -Wl,-rpath,/home/fyt/.conda/envs/opencv_env/lib -Wno-unknown-pragmas -Wno-unknown-pragmas  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/main.d

$(ObjDir)/sobel_edge.o: ../../../../../code/sobel_edge.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../code/sobel_edge.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/sobel_edge.d
