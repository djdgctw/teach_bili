// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XSOBEL_EDGE_H
#define XSOBEL_EDGE_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xsobel_edge_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XSobel_edge_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XSobel_edge;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XSobel_edge_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XSobel_edge_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XSobel_edge_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XSobel_edge_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XSobel_edge_Initialize(XSobel_edge *InstancePtr, u16 DeviceId);
XSobel_edge_Config* XSobel_edge_LookupConfig(u16 DeviceId);
int XSobel_edge_CfgInitialize(XSobel_edge *InstancePtr, XSobel_edge_Config *ConfigPtr);
#else
int XSobel_edge_Initialize(XSobel_edge *InstancePtr, const char* InstanceName);
int XSobel_edge_Release(XSobel_edge *InstancePtr);
#endif

void XSobel_edge_Start(XSobel_edge *InstancePtr);
u32 XSobel_edge_IsDone(XSobel_edge *InstancePtr);
u32 XSobel_edge_IsIdle(XSobel_edge *InstancePtr);
u32 XSobel_edge_IsReady(XSobel_edge *InstancePtr);
void XSobel_edge_EnableAutoRestart(XSobel_edge *InstancePtr);
void XSobel_edge_DisableAutoRestart(XSobel_edge *InstancePtr);

void XSobel_edge_Set_input_r(XSobel_edge *InstancePtr, u64 Data);
u64 XSobel_edge_Get_input_r(XSobel_edge *InstancePtr);
void XSobel_edge_Set_output_r(XSobel_edge *InstancePtr, u64 Data);
u64 XSobel_edge_Get_output_r(XSobel_edge *InstancePtr);
void XSobel_edge_Set_rows(XSobel_edge *InstancePtr, u32 Data);
u32 XSobel_edge_Get_rows(XSobel_edge *InstancePtr);
void XSobel_edge_Set_cols(XSobel_edge *InstancePtr, u32 Data);
u32 XSobel_edge_Get_cols(XSobel_edge *InstancePtr);

void XSobel_edge_InterruptGlobalEnable(XSobel_edge *InstancePtr);
void XSobel_edge_InterruptGlobalDisable(XSobel_edge *InstancePtr);
void XSobel_edge_InterruptEnable(XSobel_edge *InstancePtr, u32 Mask);
void XSobel_edge_InterruptDisable(XSobel_edge *InstancePtr, u32 Mask);
void XSobel_edge_InterruptClear(XSobel_edge *InstancePtr, u32 Mask);
u32 XSobel_edge_InterruptGetEnabled(XSobel_edge *InstancePtr);
u32 XSobel_edge_InterruptGetStatus(XSobel_edge *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
