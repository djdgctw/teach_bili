// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xrgb2gray.h"

extern XRgb2gray_Config XRgb2gray_ConfigTable[];

XRgb2gray_Config *XRgb2gray_LookupConfig(u16 DeviceId) {
	XRgb2gray_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XRGB2GRAY_NUM_INSTANCES; Index++) {
		if (XRgb2gray_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XRgb2gray_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XRgb2gray_Initialize(XRgb2gray *InstancePtr, u16 DeviceId) {
	XRgb2gray_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XRgb2gray_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XRgb2gray_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

