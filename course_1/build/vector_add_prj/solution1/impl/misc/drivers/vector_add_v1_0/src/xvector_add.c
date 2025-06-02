// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xvector_add.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XVector_add_CfgInitialize(XVector_add *InstancePtr, XVector_add_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XVector_add_Start(XVector_add *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_AP_CTRL) & 0x80;
    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XVector_add_IsDone(XVector_add *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XVector_add_IsIdle(XVector_add *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XVector_add_IsReady(XVector_add *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XVector_add_EnableAutoRestart(XVector_add *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XVector_add_DisableAutoRestart(XVector_add *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_AP_CTRL, 0);
}

void XVector_add_Set_a(XVector_add *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_A_DATA, (u32)(Data));
    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_A_DATA + 4, (u32)(Data >> 32));
}

u64 XVector_add_Get_a(XVector_add *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_A_DATA);
    Data += (u64)XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_A_DATA + 4) << 32;
    return Data;
}

void XVector_add_Set_c(XVector_add *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_C_DATA, (u32)(Data));
    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_C_DATA + 4, (u32)(Data >> 32));
}

u64 XVector_add_Get_c(XVector_add *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_C_DATA);
    Data += (u64)XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_C_DATA + 4) << 32;
    return Data;
}

void XVector_add_Set_size(XVector_add *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_SIZE_DATA, Data);
}

u32 XVector_add_Get_size(XVector_add *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_SIZE_DATA);
    return Data;
}

void XVector_add_InterruptGlobalEnable(XVector_add *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_GIE, 1);
}

void XVector_add_InterruptGlobalDisable(XVector_add *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_GIE, 0);
}

void XVector_add_InterruptEnable(XVector_add *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_IER);
    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_IER, Register | Mask);
}

void XVector_add_InterruptDisable(XVector_add *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_IER);
    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_IER, Register & (~Mask));
}

void XVector_add_InterruptClear(XVector_add *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVector_add_WriteReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_ISR, Mask);
}

u32 XVector_add_InterruptGetEnabled(XVector_add *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_IER);
}

u32 XVector_add_InterruptGetStatus(XVector_add *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XVector_add_ReadReg(InstancePtr->Control_BaseAddress, XVECTOR_ADD_CONTROL_ADDR_ISR);
}

