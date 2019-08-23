#ifndef _CI_PXI8510_DEVICE_
#define _CI_PXI8510_DEVICE_

#include "windows.h"

#pragma once
//////////////////////////////////////////////////////////////////////////
// 同步422时钟输出模式定义
#define PXI8510_LVDS_CLK_Continue	(0)		// 连续时钟输出模式
#define PXI8510_LVDS_CLK_Discontinue	(1)		// 间歇时钟输出模式
// 同步422通道定义
#define PXI8510_LVDS_CH0				(0)		// 同步422通道0
//////////////////////////////////////////////////////////////////////////
// 传输模式定义
#define PXI8510_TRANSF_MODE_DMA			(0)		// DMA传输模式
#define PXI8510_TRANSF_MODE_PRO			(1)		// 程序传输模式
//////////////////////////////////////////////////////////////////////////
#define PXI8510_SEND_LVDS_CH_MAX		(2)		// 发送2通道
#define PXI8510_SEND_RECV_CH_MAX		(4)		// 接收4通道
//////////////////////////////////////////////////////////////////////////
// 错误信息
#define PXI8510_Failed(error)				((error)<0)
#define PXI8510_NoError						(0)
#define PXI8510_WarningTimeOut				(-20019)
//////////////////////////////////////////////////////////////////////////
// Device function
#ifdef __cplusplus
extern "C" {
#endif
	LONG __stdcall PXI8510_DeviceOpen(						// open PXI8510 device
								ULONG DeviceNum,			// device logic ID
								HANDLE* pDrvHandle);		// return card object handle

	LONG __stdcall PXI8510_DeviceClose(						// close PXI8510 device 
								HANDLE devHandle);			// card object handle

	LONG __stdcall PXI8510_GetDeviceCount(					// get card count
								ULONG* devCount);			// return card count
		
	LONG __stdcall PXI8510_GetDevicePhyID(					// get card physical id
								HANDLE devHandle,			// card object handle
								ULONG* Physical);			// return card physical id

	LONG __stdcall PXI8510_GetDevicePXISolt(				// 获得设备所在槽位
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// 同步422 发送部分
	LONG __stdcall PXI8510_LVDS_SendInitChan(				// 发送通道初始化
								HANDLE devHandle, 			//
								ULONG chanNum,				// 发送通道号,参考同步422通道定义
								ULONG frameLen,				// 发送帧长，如果设置为0，发送数据时使能管脚一直有效到《发送停止》函数使用
								double rate,				// 设置发送频率 1K ~500K,单位Hz
								ULONG perChanGetSamples);	// 发送内部缓冲区
	//---------------------------------------------------------------------------
	// 用于触发使用的输出
	LONG __stdcall PXI8510_LVDS_SendCfgTrigExtern(		// 配置外部帧圈同步出发模式
								HANDLE devHandle, 
								ULONG chanNum);				// 同步发送通道
	//---------------------------------------------------------------
	// 帧圈数据
	LONG __stdcall PXI8510_LVDS_SendTrigFrame(			// 外触发 帧同步信号发送包
								HANDLE	devHandle, 
								ULONG	chanNum,			// 同步发送通道
								BYTE	writeArray[],
								ULONG	arraySize);			// 发送长度,  这里需要是80字节的帧包

	LONG __stdcall PXI8510_LVDS_SendTrigCircle(			// 外触发 圈同步信号发送包
								HANDLE	devHandle, 
								ULONG	chanNum,			// 同步发送通道
								BYTE	writeArray[],
								ULONG	arraySize);			// 发送长度,  这里需要是2*80字节的圈包
	//---------------------------------------------------------------
	LONG __stdcall PXI8510_LVDS_SendCfgTrgiExtern2(
								HANDLE devHandle, 
								ULONG chanNum);				// 同步发送通道

	LONG __stdcall PXI8510_LVDS_SendInitNum2(				// 初始值和增量值设定
								HANDLE	devHandle, 
								ULONG	chanNum,			// 同步发送通道
								ULONG	initNum,			// 初始值 注意这里只有14Bit有效
								ULONG	incNum,				// 增量值(递增步长)14Bit有效
								ULONG   intTimer);			// 间隔时钟	

	LONG __stdcall PXI8510_LVDS_SetRowsAndImageElement(		// LVDS总行数设置和像元
								HANDLE  devHandle,			
								ULONG   rows,				// 总行数
								ULONG   imageElement);		// 像元数
	//---------------------------------------------------------------
	LONG __stdcall PXI8510_PulseIn_GetCount(				// 获得帧圈计数值
								HANDLE	devHandle,
								ULONG*	pCircleCnt,			// 返回圈同步计数值
								ULONG*	pFrameCnt);			// 返回帧同步计数值

	LONG __stdcall PXI8510_PulseIn_ClearCount(				// 清除帧圈计数值
								HANDLE	devHandle);			//
	//---------------------------------------------------------------------------
	LONG __stdcall PXI8510_LVDS_SendStart(					// 同步422 发送开始
								HANDLE devHandle,
								ULONG chanNum,				// 通道号,参考同步422通道定义
								ULONG clkMode);				// 时钟输出模式，参考 同步422时钟输出模式定义

	LONG __stdcall PXI8510_LVDS_SendStop(					// 同步422 发送停止
								HANDLE devHandle,
								ULONG chanNum);				// 通道号,参考同步422通道定义

	LONG __stdcall PXI8510_LVDS_Send(						// 发送
								HANDLE	devHandle, 
								ULONG	chanNum,			// 通道号,参考同步422通道定义
								ULONG	numSampsPer,		// 输出点数
								ULONG	loopNum,			// 输出次数, 0为无限输出
								BYTE	writeArray[],		// 输出缓冲区, 直接写电压值(V)	
								ULONG	arraySize,			// 缓冲区大小，这里注意，缓冲区不能小于numSampsPer，如果小于则只输出arraySize个点，并且返回错误
								double	timeout);			// 超时时间(单位：秒)

	LONG __stdcall PXI8510_LVDS_GetSendLen(					// 返回写数据长度
								HANDLE	devHandle,
								ULONG	chanNum,			// 通道号,参考同步422通道定义
								UINT64* pRetWriteLen);		// 返回写数据长度，单位:字节

	LONG __stdcall PXI8510_LVDS_GetSendErrorSts(			// 返回错误状态
								HANDLE	devHandle,
								ULONG chanNum,				// 通道范围(0, 1)
								ULONG* sendBreakpointCount);// 发送断点错误计数

	LONG __stdcall PXI8510_LVDS_SendWaitDoneEvent(			// 等待AO输出结束消息，如果用单次模式则，可以等到结束消息
								HANDLE	devHandle,
								ULONG chanNum,				// 通道范围(0, 1)
								double  timeout);			// 超时时间,以秒为单位,最小分辨0.001, -1是一直等待

	// 这条函数必须在PXI8510_LVDS_SendInitChan以前调用。否则无效
	LONG __stdcall PXI8510_LVDS_SetSendTransferMode(		// 发送传输方式设定，
								HANDLE	devHandle,
								ULONG	chanNum,			// 通道范围(0, 1)
								ULONG	mode);				// 传输模式，参考 传输模式定义
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// 同步422 接收部分
	LONG __stdcall PXI8510_LVDS_RecvInitChan(				// 接收通道初始化
								HANDLE devHandle, 			//
								ULONG chanNum,				// 通道号,参考同步422通道定义
								ULONG perChanGetSamples);	// 接收内部缓冲区

	LONG __stdcall PXI8510_LVDS_RecvStart(					// 同步422 接收开始
								HANDLE devHandle,
								ULONG chanNum);				// 通道号,参考同步422通道定义

	LONG __stdcall PXI8510_LVDS_RecvStop(					// 同步422 接收停止
								HANDLE devHandle,
								ULONG chanNum);				// 通道号,参考同步422通道定义

	LONG __stdcall PXI8510_LVDS_Recv(						// 接收
								HANDLE devHandle,			// device object handle
								ULONG chanNum,				// 通道号,参考同步422通道定义
								ULONG readLen,				// 读取数据长度
								ULONG* retLen,				// 反馈数据长度
								BYTE readArray[],			// 接收原始AI数据的用户缓冲区
								ULONG arraySize,			// 缓冲区大小
								double timeOut);			// 超时时间,以秒为单位,最小分辨0.001, -1是一直等待

	LONG __stdcall PXI8510_LVDS_GetRecvErrorSts(			// 返回错误状态
								HANDLE	devHandle,
								ULONG chanNum,				// 通道范围(0, 1)
								ULONG* recvOverflow);		// 接收溢出计数


	// 这条函数必须在PXI8510_LVDS_RecvInitChan以前调用。否则无效
	LONG __stdcall PXI8510_LVDS_SetRecvTransferMode(		// 发送传输方式设定，
								HANDLE	devHandle,
								ULONG	chanNum,			// 通道范围(0, 1)
								ULONG	mode);				// 传输模式，参考 传输模式定义
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8510_GetErrorString(					// get error string
								LONG errorCode,				// error code
								char errorString[],			// return error info string 
								ULONG bufferSize);			// errorString buffer size
	//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#ifndef _PXI8510_DLL
	#ifndef _WIN64
		#pragma comment(lib, "PXI8510.lib")
	#else
		#pragma comment(lib, "PXI8510_64.lib")
	#endif
#endif

#endif // _CI_PXI8510_DEVICE_

