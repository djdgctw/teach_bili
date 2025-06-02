// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xsobel_edge.h"

extern XSobel_edge_Config XSobel_edge_ConfigTable[];

XSobel_edge_Config *XSobel_edge_LookupConfig(u16 DeviceId) {
	XSobel_edge_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XSOBEL_EDGE_NUM_INSTANCES; Index++) {
		if (XSobel_edge_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XSobel_edge_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XSobel_edge_Initialize(XSobel_edge *InstancePtr, u16 DeviceId) {
	XSobel_edge_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XSobel_edge_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XSobel_edge_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

