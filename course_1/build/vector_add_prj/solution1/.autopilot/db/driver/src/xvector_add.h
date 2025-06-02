// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XVECTOR_ADD_H
#define XVECTOR_ADD_H

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
#include "xvector_add_hw.h"

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
} XVector_add_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XVector_add;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XVector_add_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XVector_add_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XVector_add_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XVector_add_ReadReg(BaseAddress, RegOffset) \
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
int XVector_add_Initialize(XVector_add *InstancePtr, u16 DeviceId);
XVector_add_Config* XVector_add_LookupConfig(u16 DeviceId);
int XVector_add_CfgInitialize(XVector_add *InstancePtr, XVector_add_Config *ConfigPtr);
#else
int XVector_add_Initialize(XVector_add *InstancePtr, const char* InstanceName);
int XVector_add_Release(XVector_add *InstancePtr);
#endif

void XVector_add_Start(XVector_add *InstancePtr);
u32 XVector_add_IsDone(XVector_add *InstancePtr);
u32 XVector_add_IsIdle(XVector_add *InstancePtr);
u32 XVector_add_IsReady(XVector_add *InstancePtr);
void XVector_add_EnableAutoRestart(XVector_add *InstancePtr);
void XVector_add_DisableAutoRestart(XVector_add *InstancePtr);

void XVector_add_Set_a(XVector_add *InstancePtr, u64 Data);
u64 XVector_add_Get_a(XVector_add *InstancePtr);
void XVector_add_Set_c(XVector_add *InstancePtr, u64 Data);
u64 XVector_add_Get_c(XVector_add *InstancePtr);
void XVector_add_Set_size(XVector_add *InstancePtr, u32 Data);
u32 XVector_add_Get_size(XVector_add *InstancePtr);

void XVector_add_InterruptGlobalEnable(XVector_add *InstancePtr);
void XVector_add_InterruptGlobalDisable(XVector_add *InstancePtr);
void XVector_add_InterruptEnable(XVector_add *InstancePtr, u32 Mask);
void XVector_add_InterruptDisable(XVector_add *InstancePtr, u32 Mask);
void XVector_add_InterruptClear(XVector_add *InstancePtr, u32 Mask);
u32 XVector_add_InterruptGetEnabled(XVector_add *InstancePtr);
u32 XVector_add_InterruptGetStatus(XVector_add *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
