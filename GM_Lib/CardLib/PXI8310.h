#ifndef _CI_PXI8310_DEVICE_
#define _CI_PXI8310_DEVICE_

#include "windows.h"

#pragma once
//------------------------------------------------------------------------
// 电阻通道定义 
#define PXI8310_OHM_CH0				(0)		// 电阻通道0
#define PXI8310_OHM_CH1				(1)		// 电阻通道1
#define PXI8310_OHM_CH2				(2)		// 电阻通道2
#define PXI8310_OHM_CH3				(3)		// 电阻通道3
//------------------------------------------------------------------------
// 最大阻值定义
#define PXI8310_OHM_VAL_MAX			(16665)	
//////////////////////////////////////////////////////////////////////////
// 错误信息
#define PXI8310_Failed(error)				((error)<0)
#define PXI8310_NoError						(0)
#define PXI8310_WarningTimeOut				(-20019)
//////////////////////////////////////////////////////////////////////////
// Device function
#ifdef __cplusplus
extern "C" {
#endif
	LONG __stdcall PXI8310_DeviceOpen(						// open PXI8310 device
								ULONG DeviceNum,			// device logic ID
								HANDLE* pDrvHandle);		// return card object handle

	LONG __stdcall PXI8310_DeviceClose(						// close PXI8310 device 
								HANDLE devHandle);			// card object handle

	LONG __stdcall PXI8310_GetDeviceCount(					// get card count
								ULONG* devCount);			// return card count
		
	LONG __stdcall PXI8310_GetDevicePhyID(					// get card physical id
								HANDLE devHandle,			// card object handle
								ULONG* Physical);			// return card physical id

	LONG __stdcall PXI8310_GetDevicePXISlot(				// 获得设备所在槽位
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// OHM 函数
	LONG __stdcall PXI8310_OHM_InitChan(					// 初始化通道设置
								HANDLE devHandle, 			//
								ULONG  chanNum,				// 通道 参考通道定义
								BOOL   bGroup);				// 是否分组,

	LONG __stdcall PXI8310_OHM_Write(						// 输出电阻
								HANDLE devHandle,
								ULONG  chanNum,				// 通道 参考通道定义
								double val);				// 电阻值 最小单位1欧, 电阻最大值参考 最大阻值定义

	// 扩展函数，如果是分组模式，可以用这个函数分别控制高/低8位 电阻输出值
	LONG __stdcall PXI8310_OHM_WriteEx(						// 输出电阻值，
								HANDLE devHandle,
								ULONG  chanNum,				// 通道 参考通道定义
								double lowVal,				// 低8位电阻值 0~165
								double highVal);			// 高8位电阻值 100~16500

	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8310_GetErrorString(					// get error string
								LONG errorCode,				// error code
								char errorString[],			// return error info string 
								ULONG bufferSize);			// errorString buffer size
	//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#ifndef _PXI8310_DLL
	#ifndef _WIN64
		#pragma comment(lib, "PXI8310.lib")
	#else
		#pragma comment(lib, "PXI8310_64.lib")
	#endif
#endif

#endif // _CI_PXI8310_DEVICE_

