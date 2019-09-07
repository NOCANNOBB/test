#ifndef _CI_PXI6435D_DEVICE_
#define _CI_PXI6435D_DEVICE_

#include "windows.h"

#pragma once
//////////////////////////////////////////////////////////////////////////
// 边沿定义
#define PXI6435D_Val_Falling	(0)		// 下降沿
#define PXI6435D_Val_Rising		(1)		// 上升沿


//////////////////////////////////////////////////////////////////////////
// 通道总数
#define PXI6435D_CI_CHAN_TOTAL				(8)
//////////////////////////////////////////////////////////////////////////
// 错误信息
#define PXI6435D_Failed(error)				((error)<0)
#define PXI6435D_NoError						(0)
#define PXI6435D_WarningTimeOut				(-20019)
//////////////////////////////////////////////////////////////////////////
// Device function
#ifdef __cplusplus
extern "C" {
#endif
	LONG __stdcall PXI6435D_DeviceOpen(						// open PXI6435D device
								ULONG DeviceNum,			// device logic ID
								HANDLE* pDrvHandle);		// return card object handle

	LONG __stdcall PXI6435D_DeviceClose(						// close PXI6435D device 
								HANDLE devHandle);			// card object handle

	LONG __stdcall PXI6435D_GetDeviceCount(					// get card count
								ULONG* devCount);			// return card count		

	LONG __stdcall PXI6435D_GetDevicePhyID(					// get card physical id
								HANDLE devHandle,			// card object handle
								ULONG* Physical);			// return card physical id
	
	LONG __stdcall PXI6435D_GetDevicePXISlot(				// 获得设备所在槽位
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI6435D_CNT_InFreqChan(					// 频率测量
								HANDLE devHandle,			// card object handle
								ULONG	chan,				// 计数器通道 范围0~1
								double	minVal,				// 测量的最小值,单位 秒
								double	maxVal,				// 测量的最大值,单位 秒
								ULONG	edge,				// 测量边沿
								double	measTime);			// 测量时间，单位秒

	LONG __stdcall PXI6435D_CNT_Start(						// 计数器开始 计数/输出
								HANDLE devHandle,			// card object handle
								ULONG chan);				// 计数器通道 范围0~1

	LONG __stdcall PXI6435D_CNT_Stop(						// 计数器停止 计数/输出
								HANDLE devHandle,			// card object handle
								ULONG chan);				// 计数器通道 范围0~1

	LONG __stdcall PXI6435D_CNT_ReadF64(
								HANDLE devHandle,			// card object handle
								ULONG chan,					// 计数器通道 范围0~1
								double* frequency,			// 反馈值 反馈频率
								double* dutyCycle,			// 反馈值 脉冲高电平时间除以脉冲周期
								double timeOut);			// 超时时间 单位秒
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI6435D_GetErrorString(					// get error string
								LONG errorCode,				// error code
								char errorString[],			// return error info string 
								ULONG bufferSize);			// errorString buffer size
	//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#ifndef _PXI6435D_DLL
	#ifndef _WIN64
		#pragma comment(lib, "PXI6435D.lib")
	#else
		#pragma comment(lib, "PXI6435D_64.lib")
	#endif
#endif

#endif // _CI_PXI6435D_DEVICE_
