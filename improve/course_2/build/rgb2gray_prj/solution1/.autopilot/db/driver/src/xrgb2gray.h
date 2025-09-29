// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XRGB2GRAY_H
#define XRGB2GRAY_H

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
#include "xrgb2gray_hw.h"

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
} XRgb2gray_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XRgb2gray;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XRgb2gray_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XRgb2gray_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XRgb2gray_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XRgb2gray_ReadReg(BaseAddress, RegOffset) \
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
int XRgb2gray_Initialize(XRgb2gray *InstancePtr, u16 DeviceId);
XRgb2gray_Config* XRgb2gray_LookupConfig(u16 DeviceId);
int XRgb2gray_CfgInitialize(XRgb2gray *InstancePtr, XRgb2gray_Config *ConfigPtr);
#else
int XRgb2gray_Initialize(XRgb2gray *InstancePtr, const char* InstanceName);
int XRgb2gray_Release(XRgb2gray *InstancePtr);
#endif

void XRgb2gray_Start(XRgb2gray *InstancePtr);
u32 XRgb2gray_IsDone(XRgb2gray *InstancePtr);
u32 XRgb2gray_IsIdle(XRgb2gray *InstancePtr);
u32 XRgb2gray_IsReady(XRgb2gray *InstancePtr);
void XRgb2gray_EnableAutoRestart(XRgb2gray *InstancePtr);
void XRgb2gray_DisableAutoRestart(XRgb2gray *InstancePtr);

void XRgb2gray_Set_rgb(XRgb2gray *InstancePtr, u64 Data);
u64 XRgb2gray_Get_rgb(XRgb2gray *InstancePtr);
void XRgb2gray_Set_gray(XRgb2gray *InstancePtr, u64 Data);
u64 XRgb2gray_Get_gray(XRgb2gray *InstancePtr);
void XRgb2gray_Set_size(XRgb2gray *InstancePtr, u32 Data);
u32 XRgb2gray_Get_size(XRgb2gray *InstancePtr);

void XRgb2gray_InterruptGlobalEnable(XRgb2gray *InstancePtr);
void XRgb2gray_InterruptGlobalDisable(XRgb2gray *InstancePtr);
void XRgb2gray_InterruptEnable(XRgb2gray *InstancePtr, u32 Mask);
void XRgb2gray_InterruptDisable(XRgb2gray *InstancePtr, u32 Mask);
void XRgb2gray_InterruptClear(XRgb2gray *InstancePtr, u32 Mask);
u32 XRgb2gray_InterruptGetEnabled(XRgb2gray *InstancePtr);
u32 XRgb2gray_InterruptGetStatus(XRgb2gray *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
