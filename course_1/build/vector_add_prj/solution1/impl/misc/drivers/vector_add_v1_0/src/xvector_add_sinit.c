// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xvector_add.h"

extern XVector_add_Config XVector_add_ConfigTable[];

XVector_add_Config *XVector_add_LookupConfig(u16 DeviceId) {
	XVector_add_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XVECTOR_ADD_NUM_INSTANCES; Index++) {
		if (XVector_add_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XVector_add_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XVector_add_Initialize(XVector_add *InstancePtr, u16 DeviceId) {
	XVector_add_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XVector_add_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XVector_add_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

