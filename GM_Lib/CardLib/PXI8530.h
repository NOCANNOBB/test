#ifndef _CI_PXI8530_DEVICE_
#define _CI_PXI8530_DEVICE_

#include "windows.h"

#pragma once
//////////////////////////////////////////////////////////////////////////
// 同步422时钟输出模式定义
#define PXI8530_SYNC422_CLK_Continue	(0)		// 连续时钟输出模式
#define PXI8530_SYNC422_CLK_Discontinue	(1)		// 间歇时钟输出模式
// 同步422通道定义
#define PXI8530_SYNC422_CH0				(0)		// 同步422通道0
//////////////////////////////////////////////////////////////////////////
// 传输模式定义
#define PXI8530_TRANSF_MODE_DMA			(0)		// DMA传输模式
#define PXI8530_TRANSF_MODE_PRO			(1)		// 程序传输模式
//////////////////////////////////////////////////////////////////////////
// 波特率定义
#define PXI8530_RATE_4800				(0)
#define PXI8530_RATE_9600				(1)
#define PXI8530_RATE_19200				(2)
#define PXI8530_RATE_38400				(3)
#define PXI8530_RATE_57600				(4)
#define PXI8530_RATE_115200				(5)
// 校验位定义
#define PXI8530_PARITY_NONE				(0)		// 没有校验
#define PXI8530_PARITY_EVEN				(1)		// 偶校验
#define PXI8530_PARITY_ODD				(2)		// 奇校验
//////////////////////////////////////////////////////////////////////////
#define PXI8530_ENDAT_MODE_SOFT			(0)		// 软件触发
#define PXI8530_ENDAT_MODE_CYCLE		(1)		// 周期读取80uS
#define PXI8530_ENDAT_MODE_CIRCLE		(2)		// 圈同步触发
#define PXI8530_ENDAT_MODE_FRAME		(3)		// 帧同步触发
//////////////////////////////////////////////////////////////////////////
// 错误信息
#define PXI8530_Failed(error)				((error)<0)
#define PXI8530_NoError						(0)
#define PXI8530_WarningTimeOut				(-20019)
//////////////////////////////////////////////////////////////////////////
// Device function
#ifdef __cplusplus
extern "C" {
#endif
	LONG __stdcall PXI8530_DeviceOpen(						// open PXI8530 device
								ULONG DeviceNum,			// device logic ID
								HANDLE* pDrvHandle);		// return card object handle

	LONG __stdcall PXI8530_DeviceClose(						// close PXI8530 device 
								HANDLE devHandle);			// card object handle

	LONG __stdcall PXI8530_GetDeviceCount(					// get card count
								ULONG* devCount);			// return card count
		
	LONG __stdcall PXI8530_GetDevicePhyID(					// get card physical id
								HANDLE devHandle,			// card object handle
								ULONG* Physical);			// return card physical id

	LONG __stdcall PXI8530_GetDevicePXISolt(				// 获得设备所在槽位
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// 同步422 发送部分
	LONG __stdcall PXI8530_SYNC422_SendInitChan(			// 发送通道初始化
								HANDLE devHandle, 			//
								ULONG chanNum,				// 发送通道号,参考同步422通道定义
								ULONG frameLen,				// 发送帧长，如果设置为0，发送数据时使能管脚一直有效到《发送停止》函数使用
								double rate,				// 设置发送频率 1K ~500K,单位Hz
								ULONG perChanGetSamples);	// 发送内部缓冲区

	LONG __stdcall PXI8530_SYNC422_SendCfgTrigExtern(		// 配置外部帧圈同步出发模式
								HANDLE devHandle, 
								ULONG chanNum);				// 同步发送通道

	LONG __stdcall PXI8530_SYNC422_SendTrigFrame(			// 外触发 帧同步信号发送包
								HANDLE	devHandle, 
								ULONG	chanNum,			// 同步发送通道
								BYTE	writeArray[],
								ULONG	arraySize);			// 发送长度,  这里需要是80字节的帧包

	LONG __stdcall PXI8530_SYNC422_SendTrigCircle(			// 外触发 圈同步信号发送包
								HANDLE	devHandle, 
								ULONG	chanNum,			// 同步发送通道
								BYTE	writeArray[],
								ULONG	arraySize);			// 发送长度,  这里需要是2*80字节的圈包

	LONG __stdcall PXI8530_SYNC422_SendStart(				// 同步422 发送开始
								HANDLE devHandle,
								ULONG chanNum,				// 通道号,参考同步422通道定义
								ULONG clkMode);				// 时钟输出模式，参考 同步422时钟输出模式定义

	LONG __stdcall PXI8530_SYNC422_SendStop(				// 同步422 发送停止
								HANDLE devHandle,
								ULONG chanNum);				// 通道号,参考同步422通道定义

	LONG __stdcall PXI8530_SYNC422_Send(					// 发送
								HANDLE	devHandle, 
								ULONG	chanNum,			// 通道号,参考同步422通道定义
								ULONG	numSampsPer,		// 输出点数
								ULONG	loopNum,			// 输出次数, 0为无限输出
								BYTE	writeArray[],		// 输出缓冲区, 直接写电压值(V)	
								ULONG	arraySize,			// 缓冲区大小，这里注意，缓冲区不能小于numSampsPer，如果小于则只输出arraySize个点，并且返回错误
								double	timeout);			// 超时时间(单位：秒)

	LONG __stdcall PXI8530_SYNC422_GetSendLen(				// 返回写数据长度
								HANDLE	devHandle,
								ULONG	chanNum,			// 通道号,参考同步422通道定义
								UINT64* pRetWriteLen);		// 返回写数据长度，单位:字节

	LONG __stdcall PXI8530_SYNC422_GetSendErrorSts(			// 返回错误状态
								HANDLE	devHandle,
								ULONG chanNum,				// 通道范围(0, 1)
								ULONG* sendBreakpointCount);// 发送断点错误计数

	LONG __stdcall PXI8530_SYNC422_SendWaitDoneEvent(		// 等待AO输出结束消息，如果用单次模式则，可以等到结束消息
								HANDLE	devHandle,
								ULONG chanNum,				// 通道范围(0, 1)
								double  timeout);			// 超时时间,以秒为单位,最小分辨0.001, -1是一直等待

	// 这条函数必须在PXI8530_SYNC422_SendInitChan以前调用。否则无效
	LONG __stdcall PXI8530_SYNC422_SetSendTransferMode(		// 发送传输方式设定，
								HANDLE	devHandle,
								ULONG	chanNum,			// 通道范围(0, 1)
								ULONG	mode);				// 传输模式，参考 传输模式定义
	//////////////////////////////////////////////////////////////////////////
	// 同步422 接收部分
	LONG __stdcall PXI8530_SYNC422_RecvInitChan(			// 接收通道初始化
								HANDLE devHandle, 			//
								ULONG chanNum,				// 通道号,参考同步422通道定义
								ULONG perChanGetSamples);	// 接收内部缓冲区

	LONG __stdcall PXI8530_SYNC422_RecvStart(				// 同步422 接收开始
								HANDLE devHandle,
								ULONG chanNum);				// 通道号,参考同步422通道定义

	LONG __stdcall PXI8530_SYNC422_RecvStop(				// 同步422 接收停止
								HANDLE devHandle,
								ULONG chanNum);				// 通道号,参考同步422通道定义

	LONG __stdcall PXI8530_SYNC422_Recv(					// 接收
								HANDLE devHandle,			// device object handle
								ULONG chanNum,				// 通道号,参考同步422通道定义
								ULONG readLen,				// 读取数据长度
								ULONG* retLen,				// 反馈数据长度
								BYTE readArray[],			// 接收原始AI数据的用户缓冲区
								ULONG arraySize,			// 缓冲区大小
								double timeOut);			// 超时时间,以秒为单位,最小分辨0.001, -1是一直等待

	LONG __stdcall PXI8530_SYNC422_GetRecvErrorSts(				// 返回错误状态
								HANDLE	devHandle,
								ULONG chanNum,				// 通道范围(0, 1)
								ULONG* recvOverflow);		// 接收溢出计数


	// 这条函数必须在PXI8530_SYNC422_RecvInitChan以前调用。否则无效
	LONG __stdcall PXI8530_SYNC422_SetRecvTransferMode(		// 发送传输方式设定，
								HANDLE	devHandle,
								ULONG	chanNum,			// 通道范围(0, 1)
								ULONG	mode);				// 传输模式，参考 传输模式定义
	//////////////////////////////////////////////////////////////////////////
	// 编码器控制
	LONG __stdcall PXI8530_EnDat_InitChan(					// 初始化通道
								HANDLE	devHandle,
								ULONG	readMode,			// 模式
								ULONG perChanGetSamples);	// 接收内部缓冲区

	LONG __stdcall PXI8530_EnDat_Start(						// 开始读取 软件触发可以不适用这条函数
								HANDLE	devHandle);

	LONG __stdcall PXI8530_EnDat_Stop(						// 停止读取 软件触发可以不适用这条函数
								HANDLE	devHandle);

	LONG __stdcall PXI8530_EnDat_Read(						// 读取数据
								HANDLE	devHandle,
								ULONG	readLen,				// 读取数据长度
								ULONG*	retLen,				// 反馈数据长度
								ULONG	readArray[],		// 编码器数组
								__int64 timeCode[],			// 时间码数组
								double timeOut);			// 超时时间
	//////////////////////////////////////////////////////////////////////////
	// 设置 脉冲输出功能1
	LONG __stdcall PXI8530_PulseOut_Cfg(					// 脉冲输出配置
								HANDLE	devHandle,
								double	circleWidth,		// 圈脉冲宽度设置 单位mS 步进0.1 参考 50~150, 范围 0.1~6553.5
								double	circleCycle,		// 圈脉冲周期设置 单位mS 步进0.1 参考 500~3000, 范围 0.1~6553.5
								double	frameWidth,			// 帧同步宽度设置 单位mS 步进0.01 参考 0.25~1.5, 范围 0.01~2.55
								double	frameCycle,			// 帧同步周期设置 单位mS 最小0.01 参考 1~3, 范围 0.01~5.12
								double	frameDelayCircle,	// 帧输出相对于圈信号延时设置 单位mS 最小0.1 参考 50~600, 范围 0.1~819.2
								ULONG	unit1BeingPos,		// 第一组 起始位置 0 ~ 1023
								ULONG	unit1EndPos,		// 第一组 结束位置 0 ~ 1023
								ULONG	unit2BeingPos,		// 第二组 起始位置 0 ~ 1023
								ULONG	unit2EndPos,		// 第二组 结束位置 0 ~ 1023
								ULONG	unit3BeingPos,		// 第三组 起始位置 0 ~ 1023
								ULONG	unit3EndPos,		// 第三组 结束位置 0 ~ 1023
								ULONG	unit4BeingPos,		// 第四组 起始位置 0 ~ 1023
								ULONG	unit4EndPos,		// 第四组 结束位置 0 ~ 1023
								ULONG	unit5BeingPos,		// 第五组 起始位置 0 ~ 1023
								ULONG	unit5EndPos,		// 第五组 结束位置 0 ~ 1023
								ULONG	unit6BeingPos,		// 第六组 起始位置 0 ~ 1023
								ULONG	unit6EndPos,		// 第六组 结束位置 0 ~ 1023
								ULONG	unit7BeingPos,		// 第七组 起始位置 0 ~ 1023
								ULONG	unit7EndPos);		// 第七组 结束位置 0 ~ 1023

	LONG __stdcall PXI8530_PulseOut_Start(					// 脉冲输出配置
								HANDLE	devHandle);

	LONG __stdcall PXI8530_PulseOut_Stop(					// 脉冲输出配置
								HANDLE	devHandle);

	LONG __stdcall PXI8530_PulseOut_GetCount(				// 获得帧圈计数值
								HANDLE	devHandle,
								ULONG*	pCircleCnt,			// 返回圈同步计数值
								ULONG*	pFrameCnt);			// 返回帧同步计数值

	// 设置 脉冲输出功能2
	LONG __stdcall PXI8530_Pulse2OutCfg(
								HANDLE	devHandle,
								double	circleCycle,		// 圈脉冲周期设置 单位mS 0.01 范围 0.01~42949672.95
								double	frameCycle,			// 帧同步周期设置 单位mS 0.01 范围 0.01~655.35
								double	frameWidth,			// 帧同步宽度设置 单位mS 0.01 范围 0.01~655.35
								double	frameDelayCircle);	// 帧圈延时设置

	LONG __stdcall PXI8530_Pulse2Out_Start(					// 脉冲输出配置
								HANDLE	devHandle);

	LONG __stdcall PXI8530_Pulse2Out_Stop(					// 脉冲输出配置
								HANDLE	devHandle);

	LONG __stdcall PXI8530_PulseOut_MainTrig(					
								HANDLE	devHandle,
								BOOL		bOut);
	// 设置PPS信号的主备使能
	LONG __stdcall PXI8530_SetPPSMainOrViceEnable(			// PPS信号的主备使能
								HANDLE devHandle,
								BOOL chan0En,
								BOOL chan1En);
	//////////////////////////////////////////////////////////////////////////
	// 异步422通信
	LONG __stdcall PXI8530_ASYNC422_InitChan(				// 初始化
								HANDLE devHandle,
								ULONG  chanNum,
								ULONG rateIndex,			// 波特率,参考波特率定义
								ULONG parityBit);			// 校验位,参考校验位定义

	LONG __stdcall PXI8530_ASYNC422_Start(					// 422开始接收发送
								HANDLE devHandle,
								ULONG  chanNum);

	LONG __stdcall PXI8530_ASYNC422_Stop(					// 422停止接收发送
								HANDLE devHandle,
								ULONG  chanNum);

	LONG __stdcall PXI8530_ASYNC422_ClearFIFO(
								HANDLE devHandle,
								ULONG  chanNum,
								BOOL	bTxFifoClear,		// TRUE清除发送FIFO
								BOOL	bRxFifoClear);		// TRUE清除接收FIFO

	LONG __stdcall PXI8530_ASYNC422_Read(
								HANDLE devHandle,
								ULONG  chanNum,
								BYTE	readArray[],		// 读取数组
								ULONG	readLen,			// 读取长度
								ULONG*	retLen,				// 实际返回长度
								double	timeOut);			// 超时时间 单位:秒

	LONG __stdcall PXI8530_ASYNC422_Write(
								HANDLE devHandle,
								ULONG  chanNum,
								BYTE	writeArray[],		// 写数组
								ULONG	writeLen);			// 写长度

	LONG __stdcall PXI8530_ASYNC422_SetReadTransferMode(	// 异步422读数传输方式设定，
								HANDLE	devHandle,
								ULONG	chanNum,			// 通道范围(0, 1)
								ULONG	mode);				// 传输模式，参考 传输模式定义
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8530_MEAS_Frame_SetTime(				// 设置测量帧同步s时间
								HANDLE	devHandle,
								ULONG	timeData);			// 时间值

	LONG __stdcall PXI8530_MEAS_Circle_SetTime(				// 设置测量帧同步s时间
								HANDLE	devHandle,
								ULONG	timeData);			// 时间值

	LONG __stdcall PXI8530_MEAS_Start(				// 开始读取帧同步测量数值
								HANDLE	devHandle);

	LONG __stdcall PXI8530_MEAS_Stop(				// 停止读取帧同步测量数值
								HANDLE	devHandle);

	LONG __stdcall PXI8530_MEAS_Read(				// 读取帧同步测量数值
								HANDLE	devHandle,
								__int64	readArray[],		// 读取数组
								ULONG	readLen,			// 读取长度
								ULONG*	retLen,				// 实际返回长度
								double	timeOut);			// 超时时间 单位:秒



	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8530_ReSignal_Init(					// 复位信号 初始化 清除所有通道计数器值
								HANDLE	devHandle);

	LONG __stdcall PXI8530_ReSignal_GetPulseWidth(			// 复位信号 获得复位信号脉冲宽度
								HANDLE	devHandle,
								ULONG	chanNum,
								ULONG*	retReSinalCount,		// 返回复位次数
								ULONG*	retPulseWidth);			// 脉冲宽度
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8530_GetErrorString(					// get error string
								LONG errorCode,				// error code
								char errorString[],			// return error info string 
								ULONG bufferSize);			// errorString buffer size
	//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#ifndef _PXI8530_DLL
	#ifndef _WIN64
		#pragma comment(lib, "PXI8530.lib")
	#else
		#pragma comment(lib, "PXI8530_64.lib")
	#endif
#endif

#endif // _CI_PXI8530_DEVICE_

