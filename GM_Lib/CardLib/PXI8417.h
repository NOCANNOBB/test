#ifndef _CI_PXI8417_DEVICE_
#define _CI_PXI8417_DEVICE_

#include "windows.h"

#pragma once
// 采集/输出模式
//使用函数 PXI8417_AI_CfgTiming, PXI8417_AO_CfgTiming
#define PXI8417_FiniteSamps 		(0)		// 单次模式
#define PXI8417_ContSamps			(1)		// 连续模式

// AI_InitChan 函数使用定义
// AI量程
#define PXI8417_AI_B_10_V			(0)		// -10V ~ +10V
#define PXI8417_AI_B_5_V			(1)		// -5V ~ +5V

// AI接地模式
#define PXI8417_AI_RSE				(0)		// 单端
#define PXI8417_AI_DIFF				(1)		// 双端
#define PXI8417_AI_NRSE				(2)		// 无参考单端

// AI填充模式
#define PXI8417_AI_GroupByChannel	(0)		// 按通道分组存放 
#define PXI8417_AI_GroupByScanNum	(1)		// 按照采样顺序存放
// 时钟源选择
#define PXI8417_SRCCLK_Default		(0)		// 默认时钟源，如果选择默认时钟源，各个功能使用自己的內时钟
#define PXI8417_SRCCLK_Extern		(1)		// 外时钟输入
#define PXI8417_SRCCLK_PXICLK10M	(2)		// PXI背板10M时钟
//-----------------------------------------------------------------------------
// 数字量触发
// 触发沿
#define PXI8417_TRIGEdge_Falling	(0)		// 下降沿
#define PXI8417_TRIGEdge_Rising		(1)		// 上升沿

// 触发电平
#define PXI8417_TRIGLevel_Low		(0)		// 低电平
#define PXI8417_TRIGLevel_High		(1)		// 高电平

// 数字触发源
#define PXI8417_DIGTRIG_Extern  	(0)		// 外触发管脚
#define PXI8417_DIGTRIG_PXITrig_0	(1)		// PXI背板Trigger0
#define PXI8417_DIGTRIG_PXITrig_1	(2)		// PXI背板Trigger1
#define PXI8417_DIGTRIG_PXITrig_2	(3)		// PXI背板Trigger2
#define PXI8417_DIGTRIG_PXITrig_3	(4)		// PXI背板Trigger3
#define PXI8417_DIGTRIG_PXITrig_4	(5)		// PXI背板Trigger4
#define PXI8417_DIGTRIG_PXITrig_5	(6)		// PXI背板Trigger5
#define PXI8417_DIGTRIG_PXITrig_6	(7)		// PXI背板Trigger6
#define PXI8417_DIGTRIG_PXITrig_7	(8)		// PXI背板Trigger7
#define PXI8417_DIGTRIG_Int_AO0		(9)		// 用AO通道0的触发
#define PXI8417_DIGTRIG_Int_AO1		(10)	// 用AO通道1的触发
// 模拟触发源
#define PXI8417_ANLGTRIG_Extern		(0)		// 模拟量外触发管教
// 模拟触发斜率
#define PXI8417_TRIGSlope_Falling	(0)		// 下降
#define PXI8417_TRIGSlope_Rising	(1)		// 上升
//////////////////////////////////////////////////////////////////////////
// PXI Trigger定义
// PXI8417_SetPXITriggerLineOutput PXI8417_ResetPXITriggerLine 使用
#define PXI8417_PXITrig_Line_0		(0)		// PXI trigger Line 0
#define PXI8417_PXITrig_Line_1		(1)		// PXI trigger Line 1
#define PXI8417_PXITrig_Line_2		(2)		// PXI trigger Line 2
#define PXI8417_PXITrig_Line_3		(3)		// PXI trigger Line 3
#define PXI8417_PXITrig_Line_4		(4)		// PXI trigger Line 4
#define PXI8417_PXITrig_Line_5		(5)		// PXI trigger Line 5
#define PXI8417_PXITrig_Line_6		(6)		// PXI trigger Line 6
#define PXI8417_PXITrig_Line_7		(7)		// PXI trigger Line 7
// 被发送到PXI Trigger上的启动信号
#define PXI8417_StartSignal_AI		(0)		// AO0通道 启动信号输出
#define PXI8417_StartSignal_AO0		(1)		// AO0通道 启动信号输出
#define PXI8417_StartSignal_AO1		(2)		// AO1通道 启动信号输出
//////////////////////////////////////////////////////////////////////////
#define PXI8417_1PPS_TYPE_GPS		(0)		// GPS秒脉冲
#define PXI8417_1PPS_TYPE_SIM		(1)		// 模拟秒脉冲
//////////////////////////////////////////////////////////////////////////
// 错误信息
#define PXI8417_Failed(error)				((error)<0)
#define PXI8417_NoError						(0)
#define PXI8417_WarningTimeOut				(-20019)
//////////////////////////////////////////////////////////////////////////
// Device function
#ifdef __cplusplus
extern "C" {
#endif
	LONG __stdcall PXI8417_DeviceOpen(						// open PXI8417 device
								ULONG DeviceNum,			// device logic ID
								HANDLE* pDrvHandle);		// return card object handle

	LONG __stdcall PXI8417_DeviceClose(						// close PXI8417 device 
								HANDLE devHandle);			// card object handle

	LONG __stdcall PXI8417_GetDeviceCount(					// get card count
								ULONG* devCount);			// return card count
		
	LONG __stdcall PXI8417_GetDevicePhyID(					// get card physical id
								HANDLE devHandle,			// card object handle
								ULONG* Physical);			// return card physical id

	LONG __stdcall PXI8417_GetDevicePXISolt(				// 获得设备所在槽位
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// AI控制函数接口定义
	LONG __stdcall PXI8417_AI_InitChan(						// 初始化通道设置
								HANDLE devHandle, 			//
								ULONG firstChan,			// 首通道 范围(0~15)
								ULONG lastChan,				// 末通道 范围(0~15) 应 >=firstChan
								ULONG range,				// 量程
								ULONG terminalConfig);		// 接地模式 参考接地模式定义

	LONG __stdcall PXI8417_AI_CfgTiming(					// 设置采集频率及时钟选择
								HANDLE devHandle,			// card object handle
								ULONG sourceClk,			// 时钟源，参考时钟定义
								double rate,				// 单通道采样频率
								ULONG sampleMode,			// 采集模式 参考采集模式定义
								ULONG perChanGetSamples);	// 连续采集模式下为采集缓冲区大小，或者 单次采集模式下为采集长度

	LONG __stdcall PXI8417_AI_Start(						// 开始AI采集
								HANDLE devHandle);

	LONG __stdcall PXI8417_AI_Stop(							// 开始AI采集
								HANDLE devHandle);

	LONG __stdcall PXI8417_AI_Read(							// 读取AI数据
								HANDLE devHandle,			// device object handle
								ULONG numSampsPerChan,		// 读取的AI单通道点个数
								ULONG* sampsPerChanRead,	// 返回读取的单通道个数
								LONG readArray[],			// 接收原始AI数据的用户缓冲区
								ULONG arraySize,			// 缓冲区大小
								ULONG fillMode,				// 填充模式 参考填充定义
								double timeOut);			// 超时时间,以秒为单位,最小分辨0.001, -1是一直等待
	
	// 设置AI触发部分
	// 数字触发
	LONG __stdcall PXI8417_AI_CfgDigEdgeTrig(				// 数字量沿触发
								HANDLE devHandle,		
								ULONG triggerSource,	 	// 触发源  参考数字量触发定义
								ULONG triggerEdge,			// 触发沿  参考触发沿定义
								LONG reserve);				// 保留

	LONG __stdcall PXI8417_AI_CfgDigAreaTrig(				// 数字量电平持续触发
								HANDLE devHandle,		
								ULONG triggerSource,	 	// 触发源  参考数字量触发定义
								ULONG triggerLevel);		// 触发电平 参考触发电平定义

	
	LONG __stdcall PXI8417_AI_CfgAnlgEdgeTrig(				// 模拟量斜率触发
								HANDLE devHandle,		
								ULONG triggerSource, 		// 模拟触发源，参考模拟触发源定义
								ULONG triggerSlope,			// 斜率 参考模拟触发斜率
								double triggerLevelVolt,	// 电平 电压值(V)，范围 0~10 单位:电压
								LONG reserve);				// 保留

	LONG __stdcall PXI8417_AI_CfgAnlgAreaTrig(				// 模拟量区域持续触发，满足触发条件采集，不满足条件暂停采集
								HANDLE devHandle,		
								ULONG triggerSource, 		// 触发源 参考模拟触发源定义
								ULONG triggerLevel,			// 触发电平 参考模拟持续定义
								double triggerLevelVolt);	// 电平 电压值(V)，范围 0~10 单位:电压

	LONG __stdcall PXI8417_AI_DisableTrig(					// 禁止触发
								HANDLE devHandle);
	// 自校准
	LONG __stdcall PXI8417_AI_SelfCalibration(				// 自校准函数
								HANDLE devHandle);

	// 转换电压
	LONG __stdcall PXI8417_AI_ConvLsbToVolt(				// 把采集过来的码值转换成量程对应的电压值，单位 伏特
								ULONG range,				// 采集量程，参考 AI量程定义
								LONG lsbArray[],			// 采集的码值数组
								ULONG lsbArrSize,			// 码值数组大小
								double voltArray[],			// 转换后的电压数组
								ULONG voltArrSize,			// 电压数组大小
								ULONG* returnSize);			// 返回转换电压后的数据长度
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8417_1PPS_Init(						// 初始化秒脉冲,2个通道同时配置
								HANDLE	devHandle,
								ULONG	outSrc);			// 输出源选择, 0:GPS，1:模拟

	LONG __stdcall PXI8417_1PPS_Read(						// 读入秒脉冲数据，模拟和GPS都可以使用，模拟开始日期是2000/01/01
								HANDLE	devHandle,
								ULONG*	bIsValid,			// 时间是否有效，GPS在未定位时为0，定位后1，模拟常1
								ULONG*	dateHex,			// 16进制日期,例如2017年01月20日，反馈值为0x200117, 模拟输出从2000年1月1日开始
								ULONG*  timeHex);			// 16进制时间,例如15:35:32,反馈值为153532,注意GPS反馈的时间为UTC时间，模拟从00:00:00开始计时

	LONG __stdcall PXI8417_1PPS_GetPulseCount(				// 秒脉冲 输出计数,模拟输出使用
								HANDLE	devHandle,
								ULONG*	pulPulseCount);		// 返回秒脉冲输出值

	LONG __stdcall PXI8417_1PPS_ClearPulseCount(			// 清除秒脉冲计数值,模拟输出有效
								HANDLE	devHandle);			//


	LONG __stdcall PXI8417_1PPS_Start(						// 秒脉冲开始输出
								HANDLE	devHandle,
								ULONG	chanNum);			// 秒脉冲通道 0 ~ 1 (0xFFFF 全部输出)

	LONG __stdcall PXI8417_1PPS_Stop(						// 秒脉冲停止输出
								HANDLE	devHandle,
								ULONG	chanNum);			// 秒脉冲通道 0 ~ 1 (0xFFFF 全部输出)


	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8417_IR_Start(						// 使能光隔离脉冲宽度采集通道
								HANDLE devHandle,			// 设备句柄	
								ULONG  chanNum);			// 通道选择（0—31）

	LONG __stdcall PXI8417_IR_Stop(							// 停止光隔离脉冲宽度采集通道
								HANDLE devHandle,			// 设备句柄	
								ULONG  chanNum);			// 通道选择（0—31）

	LONG __stdcall PXI8417_IR_GetPulseWidth(				// 获取设备脉冲宽度
								HANDLE devHandle,			// 设备句柄
								LONG  chanNum,				// 通道选择（0—31)
								ULONG* retPulseWidth);		// 脉冲宽度（单位uS 微秒）

	LONG __stdcall PXI8417_IR_WaitInput(					// 等待输入
								HANDLE devHandle,			// 设备句柄	
								double  timeout,			// 超时时间,以秒为单位,最小分辨0.001, -1是一直等待
								ULONG* chanNumBit);			// 通道集合，（D31:D0，代表第31通道到0通道的中断）
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8417_OC_OutputPulseWidth(				// 设置OC指令脉冲输出宽度
								HANDLE devHandle,			// 设备句柄
								ULONG  chanNum,				// 通道号
								ULONG  pulseWidth);			// 脉冲宽度（单位uS 微秒）
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8417_GetErrorString(					// get error string
								LONG errorCode,				// error code
								char errorString[],			// return error info string 
								ULONG bufferSize);			// errorString buffer size
	//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#ifndef _PXI8417_DLL
	#ifndef _WIN64
		#pragma comment(lib, "PXI8417.lib")
	#else
		#pragma comment(lib, "PXI8417_64.lib")
	#endif
#endif

#endif // _CI_PXI8417_DEVICE_

