#ifndef _CI_PXI8417_DEVICE_
#define _CI_PXI8417_DEVICE_

#include "windows.h"

#pragma once
// �ɼ�/���ģʽ
//ʹ�ú��� PXI8417_AI_CfgTiming, PXI8417_AO_CfgTiming
#define PXI8417_FiniteSamps 		(0)		// ����ģʽ
#define PXI8417_ContSamps			(1)		// ����ģʽ

// AI_InitChan ����ʹ�ö���
// AI����
#define PXI8417_AI_B_10_V			(0)		// -10V ~ +10V
#define PXI8417_AI_B_5_V			(1)		// -5V ~ +5V

// AI�ӵ�ģʽ
#define PXI8417_AI_RSE				(0)		// ����
#define PXI8417_AI_DIFF				(1)		// ˫��
#define PXI8417_AI_NRSE				(2)		// �޲ο�����

// AI���ģʽ
#define PXI8417_AI_GroupByChannel	(0)		// ��ͨ�������� 
#define PXI8417_AI_GroupByScanNum	(1)		// ���ղ���˳����
// ʱ��Դѡ��
#define PXI8417_SRCCLK_Default		(0)		// Ĭ��ʱ��Դ�����ѡ��Ĭ��ʱ��Դ����������ʹ���Լ��ă�ʱ��
#define PXI8417_SRCCLK_Extern		(1)		// ��ʱ������
#define PXI8417_SRCCLK_PXICLK10M	(2)		// PXI����10Mʱ��
//-----------------------------------------------------------------------------
// ����������
// ������
#define PXI8417_TRIGEdge_Falling	(0)		// �½���
#define PXI8417_TRIGEdge_Rising		(1)		// ������

// ������ƽ
#define PXI8417_TRIGLevel_Low		(0)		// �͵�ƽ
#define PXI8417_TRIGLevel_High		(1)		// �ߵ�ƽ

// ���ִ���Դ
#define PXI8417_DIGTRIG_Extern  	(0)		// �ⴥ���ܽ�
#define PXI8417_DIGTRIG_PXITrig_0	(1)		// PXI����Trigger0
#define PXI8417_DIGTRIG_PXITrig_1	(2)		// PXI����Trigger1
#define PXI8417_DIGTRIG_PXITrig_2	(3)		// PXI����Trigger2
#define PXI8417_DIGTRIG_PXITrig_3	(4)		// PXI����Trigger3
#define PXI8417_DIGTRIG_PXITrig_4	(5)		// PXI����Trigger4
#define PXI8417_DIGTRIG_PXITrig_5	(6)		// PXI����Trigger5
#define PXI8417_DIGTRIG_PXITrig_6	(7)		// PXI����Trigger6
#define PXI8417_DIGTRIG_PXITrig_7	(8)		// PXI����Trigger7
#define PXI8417_DIGTRIG_Int_AO0		(9)		// ��AOͨ��0�Ĵ���
#define PXI8417_DIGTRIG_Int_AO1		(10)	// ��AOͨ��1�Ĵ���
// ģ�ⴥ��Դ
#define PXI8417_ANLGTRIG_Extern		(0)		// ģ�����ⴥ���ܽ�
// ģ�ⴥ��б��
#define PXI8417_TRIGSlope_Falling	(0)		// �½�
#define PXI8417_TRIGSlope_Rising	(1)		// ����
//////////////////////////////////////////////////////////////////////////
// PXI Trigger����
// PXI8417_SetPXITriggerLineOutput PXI8417_ResetPXITriggerLine ʹ��
#define PXI8417_PXITrig_Line_0		(0)		// PXI trigger Line 0
#define PXI8417_PXITrig_Line_1		(1)		// PXI trigger Line 1
#define PXI8417_PXITrig_Line_2		(2)		// PXI trigger Line 2
#define PXI8417_PXITrig_Line_3		(3)		// PXI trigger Line 3
#define PXI8417_PXITrig_Line_4		(4)		// PXI trigger Line 4
#define PXI8417_PXITrig_Line_5		(5)		// PXI trigger Line 5
#define PXI8417_PXITrig_Line_6		(6)		// PXI trigger Line 6
#define PXI8417_PXITrig_Line_7		(7)		// PXI trigger Line 7
// �����͵�PXI Trigger�ϵ������ź�
#define PXI8417_StartSignal_AI		(0)		// AO0ͨ�� �����ź����
#define PXI8417_StartSignal_AO0		(1)		// AO0ͨ�� �����ź����
#define PXI8417_StartSignal_AO1		(2)		// AO1ͨ�� �����ź����
//////////////////////////////////////////////////////////////////////////
#define PXI8417_1PPS_TYPE_GPS		(0)		// GPS������
#define PXI8417_1PPS_TYPE_SIM		(1)		// ģ��������
//////////////////////////////////////////////////////////////////////////
// ������Ϣ
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

	LONG __stdcall PXI8417_GetDevicePXISolt(				// ����豸���ڲ�λ
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// AI���ƺ����ӿڶ���
	LONG __stdcall PXI8417_AI_InitChan(						// ��ʼ��ͨ������
								HANDLE devHandle, 			//
								ULONG firstChan,			// ��ͨ�� ��Χ(0~15)
								ULONG lastChan,				// ĩͨ�� ��Χ(0~15) Ӧ >=firstChan
								ULONG range,				// ����
								ULONG terminalConfig);		// �ӵ�ģʽ �ο��ӵ�ģʽ����

	LONG __stdcall PXI8417_AI_CfgTiming(					// ���òɼ�Ƶ�ʼ�ʱ��ѡ��
								HANDLE devHandle,			// card object handle
								ULONG sourceClk,			// ʱ��Դ���ο�ʱ�Ӷ���
								double rate,				// ��ͨ������Ƶ��
								ULONG sampleMode,			// �ɼ�ģʽ �ο��ɼ�ģʽ����
								ULONG perChanGetSamples);	// �����ɼ�ģʽ��Ϊ�ɼ���������С������ ���βɼ�ģʽ��Ϊ�ɼ�����

	LONG __stdcall PXI8417_AI_Start(						// ��ʼAI�ɼ�
								HANDLE devHandle);

	LONG __stdcall PXI8417_AI_Stop(							// ��ʼAI�ɼ�
								HANDLE devHandle);

	LONG __stdcall PXI8417_AI_Read(							// ��ȡAI����
								HANDLE devHandle,			// device object handle
								ULONG numSampsPerChan,		// ��ȡ��AI��ͨ�������
								ULONG* sampsPerChanRead,	// ���ض�ȡ�ĵ�ͨ������
								LONG readArray[],			// ����ԭʼAI���ݵ��û�������
								ULONG arraySize,			// ��������С
								ULONG fillMode,				// ���ģʽ �ο���䶨��
								double timeOut);			// ��ʱʱ��,����Ϊ��λ,��С�ֱ�0.001, -1��һֱ�ȴ�
	
	// ����AI��������
	// ���ִ���
	LONG __stdcall PXI8417_AI_CfgDigEdgeTrig(				// �������ش���
								HANDLE devHandle,		
								ULONG triggerSource,	 	// ����Դ  �ο���������������
								ULONG triggerEdge,			// ������  �ο������ض���
								LONG reserve);				// ����

	LONG __stdcall PXI8417_AI_CfgDigAreaTrig(				// ��������ƽ��������
								HANDLE devHandle,		
								ULONG triggerSource,	 	// ����Դ  �ο���������������
								ULONG triggerLevel);		// ������ƽ �ο�������ƽ����

	
	LONG __stdcall PXI8417_AI_CfgAnlgEdgeTrig(				// ģ����б�ʴ���
								HANDLE devHandle,		
								ULONG triggerSource, 		// ģ�ⴥ��Դ���ο�ģ�ⴥ��Դ����
								ULONG triggerSlope,			// б�� �ο�ģ�ⴥ��б��
								double triggerLevelVolt,	// ��ƽ ��ѹֵ(V)����Χ 0~10 ��λ:��ѹ
								LONG reserve);				// ����

	LONG __stdcall PXI8417_AI_CfgAnlgAreaTrig(				// ģ��������������������㴥�������ɼ���������������ͣ�ɼ�
								HANDLE devHandle,		
								ULONG triggerSource, 		// ����Դ �ο�ģ�ⴥ��Դ����
								ULONG triggerLevel,			// ������ƽ �ο�ģ���������
								double triggerLevelVolt);	// ��ƽ ��ѹֵ(V)����Χ 0~10 ��λ:��ѹ

	LONG __stdcall PXI8417_AI_DisableTrig(					// ��ֹ����
								HANDLE devHandle);
	// ��У׼
	LONG __stdcall PXI8417_AI_SelfCalibration(				// ��У׼����
								HANDLE devHandle);

	// ת����ѹ
	LONG __stdcall PXI8417_AI_ConvLsbToVolt(				// �Ѳɼ���������ֵת�������̶�Ӧ�ĵ�ѹֵ����λ ����
								ULONG range,				// �ɼ����̣��ο� AI���̶���
								LONG lsbArray[],			// �ɼ�����ֵ����
								ULONG lsbArrSize,			// ��ֵ�����С
								double voltArray[],			// ת����ĵ�ѹ����
								ULONG voltArrSize,			// ��ѹ�����С
								ULONG* returnSize);			// ����ת����ѹ������ݳ���
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8417_1PPS_Init(						// ��ʼ��������,2��ͨ��ͬʱ����
								HANDLE	devHandle,
								ULONG	outSrc);			// ���Դѡ��, 0:GPS��1:ģ��

	LONG __stdcall PXI8417_1PPS_Read(						// �������������ݣ�ģ���GPS������ʹ�ã�ģ�⿪ʼ������2000/01/01
								HANDLE	devHandle,
								ULONG*	bIsValid,			// ʱ���Ƿ���Ч��GPS��δ��λʱΪ0����λ��1��ģ�ⳣ1
								ULONG*	dateHex,			// 16��������,����2017��01��20�գ�����ֵΪ0x200117, ģ�������2000��1��1�տ�ʼ
								ULONG*  timeHex);			// 16����ʱ��,����15:35:32,����ֵΪ153532,ע��GPS������ʱ��ΪUTCʱ�䣬ģ���00:00:00��ʼ��ʱ

	LONG __stdcall PXI8417_1PPS_GetPulseCount(				// ������ �������,ģ�����ʹ��
								HANDLE	devHandle,
								ULONG*	pulPulseCount);		// �������������ֵ

	LONG __stdcall PXI8417_1PPS_ClearPulseCount(			// ������������ֵ,ģ�������Ч
								HANDLE	devHandle);			//


	LONG __stdcall PXI8417_1PPS_Start(						// �����忪ʼ���
								HANDLE	devHandle,
								ULONG	chanNum);			// ������ͨ�� 0 ~ 1 (0xFFFF ȫ�����)

	LONG __stdcall PXI8417_1PPS_Stop(						// ������ֹͣ���
								HANDLE	devHandle,
								ULONG	chanNum);			// ������ͨ�� 0 ~ 1 (0xFFFF ȫ�����)


	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8417_IR_Start(						// ʹ�ܹ���������Ȳɼ�ͨ��
								HANDLE devHandle,			// �豸���	
								ULONG  chanNum);			// ͨ��ѡ��0��31��

	LONG __stdcall PXI8417_IR_Stop(							// ֹͣ����������Ȳɼ�ͨ��
								HANDLE devHandle,			// �豸���	
								ULONG  chanNum);			// ͨ��ѡ��0��31��

	LONG __stdcall PXI8417_IR_GetPulseWidth(				// ��ȡ�豸������
								HANDLE devHandle,			// �豸���
								LONG  chanNum,				// ͨ��ѡ��0��31)
								ULONG* retPulseWidth);		// �����ȣ���λuS ΢�룩

	LONG __stdcall PXI8417_IR_WaitInput(					// �ȴ�����
								HANDLE devHandle,			// �豸���	
								double  timeout,			// ��ʱʱ��,����Ϊ��λ,��С�ֱ�0.001, -1��һֱ�ȴ�
								ULONG* chanNumBit);			// ͨ�����ϣ���D31:D0�������31ͨ����0ͨ�����жϣ�
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8417_OC_OutputPulseWidth(				// ����OCָ������������
								HANDLE devHandle,			// �豸���
								ULONG  chanNum,				// ͨ����
								ULONG  pulseWidth);			// �����ȣ���λuS ΢�룩
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

