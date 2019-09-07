#ifndef _CI_PXI6860_DEVICE_
#define _CI_PXI6860_DEVICE_

#include "windows.h"

#pragma once
//------------------------------------------------------------------------
// AO 相关定义,通道个数2
// AO 停止模式
#define PXI6860_AO_CH0				(0)		// AO通道0
#define PXI6860_AO_CH1				(1)		// AO通道1
#define PXI6860_AO_CH11				(11)	// AO通道11
//////////////////////////////////////////////////////////////////////////
// 错误信息
#define PXI6860_Failed(error)				((error)<0)
#define PXI6860_NoError						(0)
#define PXI6860_WarningTimeOut				(-20019)
//////////////////////////////////////////////////////////////////////////
// Device function
#ifdef __cplusplus
extern "C" {
#endif
	LONG __stdcall PXI6860_DeviceOpen(						// open PXI6860 device
								ULONG DeviceNum,			// device logic ID
								HANDLE* pDrvHandle);		// return card object handle

	LONG __stdcall PXI6860_DeviceClose(						// close PXI6860 device 
								HANDLE devHandle);			// card object handle

	LONG __stdcall PXI6860_GetDeviceCount(					// get card count
								ULONG* devCount);			// return card count
		
	LONG __stdcall PXI6860_GetDevicePhyID(					// get card physical id
								HANDLE devHandle,			// card object handle
								ULONG* Physical);			// return card physical id

	LONG __stdcall PXI6860_GetDevicePXISlot(				// 获得设备所在槽位
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// AO 函数
	LONG __stdcall PXI6860_AO_InitChan(						// 初始化通道设置
								HANDLE devHandle, 			//
								ULONG chanNum,				// 通道范围(0, 1)
								double minVal,				// 输出最小值
								double maxVal);				// 输出最大值

    LONG __stdcall PXI6860_AO_Write(
								HANDLE devHandle, 
								ULONG chanNum,				// 通道范围(0, 1)
								double writeVal);           // 输出缓冲区, 直接写电压值(V)	
	//------------------------------------------------------------------------
	// 校准函数
	LONG __stdcall PXI6860_AO_CalEn(				       // 校准函数
								HANDLE devHandle,
                                BOOL  bEn);                 // TRUE使能校准, FALSE 停止校准

    LONG __stdcall PXI6860_AO_Cal_Reset(					// 校准值复位
								HANDLE devHandle,			// 设备句柄
								ULONG chan);				// 通道号

    LONG __stdcall PXI6860_AO_Cal_WriteVal(
                                HANDLE devHandle,
								ULONG chanNum,				// 通道号
                                double valK,				// K值
                                double valB);				// B值

    LONG __stdcall PXI6860_AO_Cal_CalcWriteVal(				// 计算并写入校准值
								HANDLE devHandle,			// 设备句柄
								ULONG chanNum,				// 通道号
								double arrayCur[],			// 采集值
								double arrayTarget[],		// 目标值
								ULONG arraySize);			// 数组大小

	LONG __stdcall PXI6860_AO_Cal_WriteEEP(			    	// 写入EEP
								HANDLE devHandle);			// 设备句柄
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI6860_GetErrorString(					// get error string
								LONG errorCode,				// error code
								char errorString[],			// return error info string 
								ULONG bufferSize);			// errorString buffer size
	//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#ifndef _PXI6860_DLL
	#ifndef _WIN64
		#pragma comment(lib, "PXI6860.lib")
	#else
		#pragma comment(lib, "PXI6860_64.lib")
	#endif
#endif

#endif // _CI_PXI6860_DEVICE_

