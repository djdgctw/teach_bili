// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xsobel_edge.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XSobel_edge_CfgInitialize(XSobel_edge *InstancePtr, XSobel_edge_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XSobel_edge_Start(XSobel_edge *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_AP_CTRL) & 0x80;
    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XSobel_edge_IsDone(XSobel_edge *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XSobel_edge_IsIdle(XSobel_edge *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XSobel_edge_IsReady(XSobel_edge *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XSobel_edge_EnableAutoRestart(XSobel_edge *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XSobel_edge_DisableAutoRestart(XSobel_edge *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_AP_CTRL, 0);
}

void XSobel_edge_Set_input_r(XSobel_edge *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_INPUT_R_DATA, (u32)(Data));
    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_INPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XSobel_edge_Get_input_r(XSobel_edge *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_INPUT_R_DATA);
    Data += (u64)XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_INPUT_R_DATA + 4) << 32;
    return Data;
}

void XSobel_edge_Set_output_r(XSobel_edge *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_OUTPUT_R_DATA, (u32)(Data));
    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_OUTPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XSobel_edge_Get_output_r(XSobel_edge *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_OUTPUT_R_DATA);
    Data += (u64)XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_OUTPUT_R_DATA + 4) << 32;
    return Data;
}

void XSobel_edge_Set_rows(XSobel_edge *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_ROWS_DATA, Data);
}

u32 XSobel_edge_Get_rows(XSobel_edge *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_ROWS_DATA);
    return Data;
}

void XSobel_edge_Set_cols(XSobel_edge *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_COLS_DATA, Data);
}

u32 XSobel_edge_Get_cols(XSobel_edge *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_COLS_DATA);
    return Data;
}

void XSobel_edge_InterruptGlobalEnable(XSobel_edge *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_GIE, 1);
}

void XSobel_edge_InterruptGlobalDisable(XSobel_edge *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_GIE, 0);
}

void XSobel_edge_InterruptEnable(XSobel_edge *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_IER);
    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_IER, Register | Mask);
}

void XSobel_edge_InterruptDisable(XSobel_edge *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_IER);
    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_IER, Register & (~Mask));
}

void XSobel_edge_InterruptClear(XSobel_edge *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_edge_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_ISR, Mask);
}

u32 XSobel_edge_InterruptGetEnabled(XSobel_edge *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_IER);
}

u32 XSobel_edge_InterruptGetStatus(XSobel_edge *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XSobel_edge_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_EDGE_CONTROL_ADDR_ISR);
}

