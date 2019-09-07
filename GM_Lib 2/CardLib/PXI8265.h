#ifndef _CI_PXI8265_DEVICE_
#define _CI_PXI8265_DEVICE_

#include "windows.h"

#pragma once
//////////////////////////////////////////////////////////////////////////
// 采集/输出模式
//使用函数 PXI8265_AI_CfgTiming, PXI8265_AO_CfgTiming
#define PXI8265_FiniteSamps 		(0)		// 单次模式
#define PXI8265_ContSamps			(1)		// 连续模式

// AI_InitChan 函数使用定义
// AI量程
#define PXI8265_AI_B_10_V			(0)		// -10V ~ +10V
#define PXI8265_AI_B_5_V			(1)		// -5V ~ +5V
#define PXI8265_AI_B_1_V			(2)		// -1V ~ +1V
#define PXI8265_AI_B_0_2_V			(3)		// -0.2V ~ +0.2V

// AI接地模式
#define PXI8265_AI_RSE				(0)		// 单端
#define PXI8265_AI_DIFF				(1)		// 双端
#define PXI8265_AI_NRSE				(2)		// 无参考单端

// AI填充模式
#define PXI8265_AI_GroupByChannel	(0)		// 按通道分组存放 
#define PXI8265_AI_GroupByScanNum	(1)		// 按照采样顺序存放
//-----------------------------------------------------------------------------
// AO 相关定义,通道个数2
// AO 停止模式
#define PXI8265_AO_Stop_Immediately		(0)	// 直接停止
#define PXI8265_AO_Stop_Completebatch	(1)	// 本批完成停止 前提是不执行DeviceClose函数

#define PXI8265_AO_CH0				(0)		// AO通道0
#define PXI8265_AO_CH1				(1)		// AO通道1
//-----------------------------------------------------------------------------
// 时钟源选择
#define PXI8265_SRCCLK_Default		(0)		// 默认时钟源，如果选择默认时钟源，各个功能使用自己的內时钟
#define PXI8265_SRCCLK_Extern		(1)		// 外时钟输入
#define PXI8265_SRCCLK_PXICLK10M	(2)		// PXI背板10M时钟
//-----------------------------------------------------------------------------
// 数字量触发
// 触发沿
#define PXI8265_TRIGEdge_Falling	(0)		// 下降沿
#define PXI8265_TRIGEdge_Rising		(1)		// 上升沿

// 触发电平
#define PXI8265_TRIGLevel_Low		(0)		// 低电平
#define PXI8265_TRIGLevel_High		(1)		// 高电平

// 数字触发源
#define PXI8265_DIGTRIG_Extern  	(0)		// 外触发管脚
#define PXI8265_DIGTRIG_PXITrig_0	(1)		// PXI背板Trigger0
#define PXI8265_DIGTRIG_PXITrig_1	(2)		// PXI背板Trigger1
#define PXI8265_DIGTRIG_PXITrig_2	(3)		// PXI背板Trigger2
#define PXI8265_DIGTRIG_PXITrig_3	(4)		// PXI背板Trigger3
#define PXI8265_DIGTRIG_PXITrig_4	(5)		// PXI背板Trigger4
#define PXI8265_DIGTRIG_PXITrig_5	(6)		// PXI背板Trigger5
#define PXI8265_DIGTRIG_PXITrig_6	(7)		// PXI背板Trigger6
#define PXI8265_DIGTRIG_PXITrig_7	(8)		// PXI背板Trigger7
#define PXI8265_DIGTRIG_Int_AO0		(9)		// 用AO通道0的触发
#define PXI8265_DIGTRIG_Int_AO1		(10)	// 用AO通道1的触发
// 模拟触发源
#define PXI8265_ANLGTRIG_Extern		(0)		// 模拟量外触发管教
// 模拟触发斜率
#define PXI8265_TRIGSlope_Falling	(0)		// 下降
#define PXI8265_TRIGSlope_Rising	(1)		// 上升
//////////////////////////////////////////////////////////////////////////
// PXI Trigger定义
// PXI8265_SetPXITriggerLineOutput PXI8265_ResetPXITriggerLine 使用
#define PXI8265_PXITrig_Line_0		(0)		// PXI trigger Line 0
#define PXI8265_PXITrig_Line_1		(1)		// PXI trigger Line 1
#define PXI8265_PXITrig_Line_2		(2)		// PXI trigger Line 2
#define PXI8265_PXITrig_Line_3		(3)		// PXI trigger Line 3
#define PXI8265_PXITrig_Line_4		(4)		// PXI trigger Line 4
#define PXI8265_PXITrig_Line_5		(5)		// PXI trigger Line 5
#define PXI8265_PXITrig_Line_6		(6)		// PXI trigger Line 6
#define PXI8265_PXITrig_Line_7		(7)		// PXI trigger Line 7
// 被发送到PXI Trigger上的启动信号
#define PXI8265_StartSignal_AI		(0)		// AO0通道 启动信号输出
#define PXI8265_StartSignal_AO0		(1)		// AO0通道 启动信号输出
#define PXI8265_StartSignal_AO1		(2)		// AO1通道 启动信号输出
//////////////////////////////////////////////////////////////////////////
// DIO 通道定义,两组，每组4个开关量共计8个
#define PXI8265_DIO_LINE_0			(0)		// 开关量输入/输出 0 组
#define PXI8265_DIO_LINE_1			(1)		// 开关量输入/输出 1 组

// DIO 方向定义
#define PXI8265_DIO_INPORT			(0)		// 为输入方向
#define PXI8265_DIO_OUTPORT			(1)		// 为输出方向
//------------------------------------------------------------------
//***********************************************************
// CNT 模式定义
#define PXI8265_CNT_POSITIVE_0	(0)		// GATE高电平时计数，低电平时停止计数，计数时重新写入初值，按初值计数
										// 计数结束产生中断：写入初值开始计数时OUT开始为0，当计数到0时OUT为1

#define PXI8265_CNT_RISING_1	(1)		// GATE上边沿触发计数，计数中出现GATE上升沿重新装入初值计数
										// 可编程单拍脉冲：当写入初值时OUT为1，当开始计数时OUT为0，当计数到0时OUT再次为1

#define PXI8265_CNT_POSITIVE_2	(2)		// GATE高电平时计数，低电平时停止计数，计数时重新写入初值，按初值计数
										// 频率发生器：计数期间OUT为1，计数到0后输出一个周期的0，并重新装入计数值计数

#define PXI8265_CNT_POSITIVE_3	(3)		// GATE高电平时计数，低电平时停止计数，计数时重新写入初值，按初值计数
										// 方波发生器：计数期间OUT为1，计数到0后输出一个周期的0，并重新装入计数值计数

#define PXI8265_CNT_POSITIVE_4	(4)		// GATE高电平时计数，低电平时停止计数，计数时重新写入初值，按初值计数
										// 软件触发选通：写入初值OUT为1， 计数结束OUT输出一个周期低电平信号

#define PXI8265_CNT_RISING_5	(5)		// GATE上边沿触发计数，计数中出现GATE上升沿重新装入初值计数
										// 硬件触发选通：写入初值OUT为1， 计数结束OUT输出一个周期低电平信号
//////////////////////////////////////////////////////////////////////////
// 错误信息
#define PXI8265_Failed(error)				((error)<0)
#define PXI8265_NoError						(0)
#define PXI8265_WarningTimeOut				(-20019)
//////////////////////////////////////////////////////////////////////////
// Device function
#ifdef __cplusplus
extern "C" {
#endif
	LONG __stdcall PXI8265_DeviceOpen(						// open PXI8265 device
								ULONG DeviceNum,			// device logic ID
								HANDLE* pDrvHandle);		// return card object handle

	LONG __stdcall PXI8265_DeviceClose(						// close PXI8265 device 
								HANDLE devHandle);			// card object handle

	LONG __stdcall PXI8265_GetDeviceCount(					// get card count
								ULONG* devCount);			// return card count
		
	LONG __stdcall PXI8265_GetDevicePhyID(					// get card physical id
								HANDLE devHandle,			// card object handle
								ULONG* Physical);			// return card physical id

	LONG __stdcall PXI8265_GetDevicePXISolt(				// 获得设备所在槽位
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// AI控制函数接口定义
	LONG __stdcall PXI8265_AI_InitChan(						// 初始化通道设置
								HANDLE devHandle, 			//
								ULONG firstChan,			// 首通道 范围(0~15)
								ULONG lastChan,				// 末通道 范围(0~15) 应 >=firstChan
								ULONG range,				// 量程
								ULONG terminalConfig);		// 接地模式 参考接地模式定义

	LONG __stdcall PXI8265_AI_CfgTiming(					// 设置采集频率及时钟选择
								HANDLE devHandle,			// card object handle
								ULONG sourceClk,			// 时钟源，参考时钟定义
								double rate,				// 单通道采样频率
								ULONG sampleMode,			// 采集模式 参考采集模式定义
								ULONG perChanGetSamples);	// 连续采集模式下为采集缓冲区大小，或者 单次采集模式下为采集长度

	LONG __stdcall PXI8265_AI_Start(						// 开始AI采集
								HANDLE devHandle);

	LONG __stdcall PXI8265_AI_Stop(							// 开始AI采集
								HANDLE devHandle);

	LONG __stdcall PXI8265_AI_Read(							// 读取AI数据
								HANDLE devHandle,			// device object handle
								ULONG numSampsPerChan,		// 读取的AI单通道点个数
								ULONG* sampsPerChanRead,	// 返回读取的单通道个数
								LONG readArray[],			// 接收原始AI数据的用户缓冲区
								ULONG arraySize,			// 缓冲区大小
								ULONG fillMode,				// 填充模式 参考填充定义
								double timeOut);			// 超时时间,以秒为单位,最小分辨0.001, -1是一直等待
	
	// 设置AI触发部分
	// 数字触发
	LONG __stdcall PXI8265_AI_CfgDigEdgeTrig(				// 数字量沿触发
								HANDLE devHandle,		
								ULONG triggerSource,	 	// 触发源  参考数字量触发定义
								ULONG triggerEdge,			// 触发沿  参考触发沿定义
								LONG reserve);				// 保留

	LONG __stdcall PXI8265_AI_CfgDigAreaTrig(				// 数字量电平持续触发
								HANDLE devHandle,		
								ULONG triggerSource,	 	// 触发源  参考数字量触发定义
								ULONG triggerLevel);		// 触发电平 参考触发电平定义

	
	LONG __stdcall PXI8265_AI_CfgAnlgEdgeTrig(				// 模拟量斜率触发
								HANDLE devHandle,		
								ULONG triggerSource, 		// 模拟触发源，参考模拟触发源定义
								ULONG triggerSlope,			// 斜率 参考模拟触发斜率
								double triggerLevelVolt,	// 电平 电压值(V)，范围 0~10 单位:电压
								LONG reserve);				// 保留

	LONG __stdcall PXI8265_AI_CfgAnlgAreaTrig(				// 模拟量区域持续触发，满足触发条件采集，不满足条件暂停采集
								HANDLE devHandle,		
								ULONG triggerSource, 		// 触发源 参考模拟触发源定义
								ULONG triggerLevel,			// 触发电平 参考模拟持续定义
								double triggerLevelVolt);	// 电平 电压值(V)，范围 0~10 单位:电压

	LONG __stdcall PXI8265_AI_DisableTrig(					// 禁止触发
								HANDLE devHandle);
	// 自校准
	LONG __stdcall PXI8265_AI_SelfCalibration(				// 自校准函数
								HANDLE devHandle);

	// 转换电压
	LONG __stdcall PXI8265_AI_ConvLsbToVolt(				// 把采集过来的码值转换成量程对应的电压值，单位 伏特
								ULONG range,				// 采集量程，参考 AI量程定义
								LONG lsbArray[],			// 采集的码值数组
								ULONG lsbArrSize,			// 码值数组大小
								double voltArray[],			// 转换后的电压数组
								ULONG voltArrSize,			// 电压数组大小
								ULONG* returnSize);			// 返回转换电压后的数据长度

	//////////////////////////////////////////////////////////////////////////
	// AO 函数
	LONG __stdcall PXI8265_AO_InitChan(						// 初始化通道设置
								HANDLE devHandle, 			//
								ULONG chanNum,				// 通道范围(0, 1)
								double minVal,				// 输出最小值
								double maxVal);				// 输出最大值

	LONG __stdcall PXI8265_AO_CfgTiming(					// 设置输出点频率及时钟选择
								HANDLE devHandle,			// card object handle
								ULONG chanNum,				// 通道范围(0, 1)
								ULONG sourceClk,			// 时钟源，参考时钟定义
								double rate,				// 采样频率
								ULONG sampleMode,			// 输出模式 参考输出模式定义
								ULONG perChanGetSamples);	// 连续输出模式下为输出缓冲区大小，或者 单次输出模式下为输出长度

	LONG __stdcall PXI8265_AO_Write(
								HANDLE devHandle, 
								ULONG chanNum,				// 通道范围(0, 1)
								ULONG numSampsPer,			// 输出点数
								BOOL autoStart,				// 是否立即输出 true立即输出 false等待start函数,这个参数只在没设置频率函数时有效
								double writeArray[],		// 输出缓冲区, 直接写电压值(V)	
								ULONG arraySize,			// 缓冲区大小，这里注意，缓冲区不能小于numSampsPer，如果小于则只输出arraySize个点，并且返回错误
								double timeout);			// 超时时间(单位：秒)

	LONG __stdcall PXI8265_AO_Start(						// 开始AO输出
								HANDLE devHandle,
								ULONG chanNum);				// 通道范围(0, 1)

	LONG __stdcall PXI8265_AO_Stop(							// 停止AO输出
								HANDLE devHandle,
								ULONG chanNum,				// 通道范围(0, 1)
								ULONG stopMode);			// 停止模式 看AO停止模式定义
	
	LONG __stdcall PXI8265_AO_RegisterEventDone(			// 注册读完成消息
								HANDLE devHandle,			// card object handle
								ULONG chanNum,				// 通道范围(0, 1)
								HANDLE eventDone);			// 结束标志,如果不想设置,这里写-1即可

	LONG __stdcall PXI8265_AO_WaitDoneEvent(				// 等待AO输出结束消息，如果用单次模式则，可以等到结束消息
								HANDLE	devHandle,
								ULONG chanNum,				// 通道范围(0, 1)
								double  timeout);			// 超时时间,以秒为单位,最小分辨0.001, -1是一直等待

	// 设置AO触发部分
	// 数字触发
	LONG __stdcall PXI8265_AO_CfgDigEdgeTrig(				// 数字量沿触发
								HANDLE devHandle,		
								ULONG  chanNum,				// 通道范围(0, 1)
								ULONG triggerSource,	 	// 触发源  参考数字量触发定义
								ULONG triggerEdge,			// 触发沿  参考触发沿定义
								LONG reserve);				// 保留

	LONG __stdcall PXI8265_AO_CfgDigAreaTrig(				// 数字量电平持续触发
								HANDLE devHandle,		
								ULONG  chanNum,				// 通道范围(0, 1)
								ULONG triggerSource,	 	// 触发源  参考数字量触发定义
								ULONG triggerLevel);		// 触发电平 参考触发电平定义

	LONG __stdcall PXI8265_AO_CfgAnlgEdgeTrig(				// 模拟量斜率触发
								HANDLE devHandle,		
								ULONG  chanNum,				// 通道范围(0, 1)
								ULONG triggerSource, 		// 模拟触发源，参考模拟触发源定义
								ULONG triggerSlope,			// 斜率 参考模拟触发斜率
								double triggerLevelVolt,	// 电平 电压值(V)，范围 0~10 单位:电压
								LONG reserve);				// 保留

	LONG __stdcall PXI8265_AO_CfgAnlgAreaTrig(				// 模拟量区域持续触发，满足触发条件采集，不满足条件暂停采集
								HANDLE devHandle,		
								ULONG  chanNum,				// 通道范围(0, 1)
								ULONG triggerSource, 		// 触发源 参考模拟触发源定义
								ULONG triggerLevel,			// 触发电平 参考模拟持续定义
								double triggerLevelVolt);	// 电平 电压值(V)，范围 0~10 单位:电压

	LONG __stdcall PXI8265_AO_DisableTrig(					// 禁止触发
								HANDLE devHandle,
								ULONG  chanNum);			// 通道范围(0, 1)

	// 自校准
	LONG __stdcall PXI8265_AO_SelfCalibration(				// 自校准函数
								HANDLE devHandle);
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8265_SetPXITriggerLineOutput(			// 设置触发输出到TriggerLine上，并且把TriggerLine设置为输出
								HANDLE devHandle,
								ULONG PxiTrigLine,			// PXI trigger输出 参考PXI Trigger定义
								ULONG xfunStartSignal);		// 启动信号 参考被发送到PXI Trigger上的启动信号

	LONG __stdcall PXI8265_ResetPXITriggerLine(				// 复位触发输出线
								HANDLE devHandle,
								ULONG PxiTrigLine);			// PXI trigger输出 参考PXI Trigger定义
	//////////////////////////////////////////////////////////////////////////
	// 数字量输入输出
	LONG __stdcall PXI8265_DIO_CfgDev(						// 配置DIO
								HANDLE devHandle,
								ULONG lineGroupNum,			// 通道组选择 参考DIO通道定义
								ULONG portDir);				// 通道组方向

	LONG __stdcall PXI8265_DIO_ReturnCfgDev(					// 回读配置DIO
								HANDLE devHandle,
								ULONG lineGroupNum,			// 通道组选择 参考DIO通道定义
								ULONG* portDir);			// 回读通道组方向

	LONG __stdcall PXI8265_DIO_Write(						// 写数字量输出,如果通道方向为INPORT的，输出值无效
								HANDLE devHandle,			// card object handle
								ULONG lineGroupNum,			// 通道组选择 参考DIO通道定义
								BYTE writeArray[],			// 写数字量输出数组
								ULONG arraySize);			// 写数组大小

	LONG __stdcall PXI8265_DIO_Read(						// 读取数字量输入,如果通道方向为OUTPORT的，返回输出状态
								HANDLE devHandle,			// card object handle
								ULONG lineGroupNum,			// 通道组选择 参考DIO通道定义
								BYTE readArray[],			// 读数字量输入数组
								ULONG arraySize);			// 读数组大小
	//////////////////////////////////////////////////////////////////////////
	// 计数器
	LONG __stdcall PXI8265_CNT_CfgDev(						// 配置计数器
								HANDLE devHandle,			// card object handle
								ULONG chan,					// 计数器通道 范围0
								ULONG countMode,			// 工作模式，参考CNT定义
								ULONG initValue);			// 计数器初始值

	LONG __stdcall PXI8265_CNT_Read(
								HANDLE devHandle,			// card object handle
								ULONG  chan,				// 计数器通道 范围0
								ULONG* countValue);			// 返回计数器当前值
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8265_GetErrorString(					// get error string
								LONG errorCode,				// error code
								char errorString[],			// return error info string 
								ULONG bufferSize);			// errorString buffer size
	//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#ifndef _PXI8265_DLL
	#ifndef _WIN64
		#pragma comment(lib, "PXI8265.lib")
	#else
		#pragma comment(lib, "PXI8265_64.lib")
	#endif
#endif

#endif // _CI_PXI8265_DEVICE_

