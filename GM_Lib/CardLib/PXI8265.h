#ifndef _CI_PXI8265_DEVICE_
#define _CI_PXI8265_DEVICE_

#include "windows.h"

#pragma once
//////////////////////////////////////////////////////////////////////////
// �ɼ�/���ģʽ
//ʹ�ú��� PXI8265_AI_CfgTiming, PXI8265_AO_CfgTiming
#define PXI8265_FiniteSamps 		(0)		// ����ģʽ
#define PXI8265_ContSamps			(1)		// ����ģʽ

// AI_InitChan ����ʹ�ö���
// AI����
#define PXI8265_AI_B_10_V			(0)		// -10V ~ +10V
#define PXI8265_AI_B_5_V			(1)		// -5V ~ +5V
#define PXI8265_AI_B_1_V			(2)		// -1V ~ +1V
#define PXI8265_AI_B_0_2_V			(3)		// -0.2V ~ +0.2V

// AI�ӵ�ģʽ
#define PXI8265_AI_RSE				(0)		// ����
#define PXI8265_AI_DIFF				(1)		// ˫��
#define PXI8265_AI_NRSE				(2)		// �޲ο�����

// AI���ģʽ
#define PXI8265_AI_GroupByChannel	(0)		// ��ͨ�������� 
#define PXI8265_AI_GroupByScanNum	(1)		// ���ղ���˳����
//-----------------------------------------------------------------------------
// AO ��ض���,ͨ������2
// AO ֹͣģʽ
#define PXI8265_AO_Stop_Immediately		(0)	// ֱ��ֹͣ
#define PXI8265_AO_Stop_Completebatch	(1)	// �������ֹͣ ǰ���ǲ�ִ��DeviceClose����

#define PXI8265_AO_CH0				(0)		// AOͨ��0
#define PXI8265_AO_CH1				(1)		// AOͨ��1
//-----------------------------------------------------------------------------
// ʱ��Դѡ��
#define PXI8265_SRCCLK_Default		(0)		// Ĭ��ʱ��Դ�����ѡ��Ĭ��ʱ��Դ����������ʹ���Լ��ă�ʱ��
#define PXI8265_SRCCLK_Extern		(1)		// ��ʱ������
#define PXI8265_SRCCLK_PXICLK10M	(2)		// PXI����10Mʱ��
//-----------------------------------------------------------------------------
// ����������
// ������
#define PXI8265_TRIGEdge_Falling	(0)		// �½���
#define PXI8265_TRIGEdge_Rising		(1)		// ������

// ������ƽ
#define PXI8265_TRIGLevel_Low		(0)		// �͵�ƽ
#define PXI8265_TRIGLevel_High		(1)		// �ߵ�ƽ

// ���ִ���Դ
#define PXI8265_DIGTRIG_Extern  	(0)		// �ⴥ���ܽ�
#define PXI8265_DIGTRIG_PXITrig_0	(1)		// PXI����Trigger0
#define PXI8265_DIGTRIG_PXITrig_1	(2)		// PXI����Trigger1
#define PXI8265_DIGTRIG_PXITrig_2	(3)		// PXI����Trigger2
#define PXI8265_DIGTRIG_PXITrig_3	(4)		// PXI����Trigger3
#define PXI8265_DIGTRIG_PXITrig_4	(5)		// PXI����Trigger4
#define PXI8265_DIGTRIG_PXITrig_5	(6)		// PXI����Trigger5
#define PXI8265_DIGTRIG_PXITrig_6	(7)		// PXI����Trigger6
#define PXI8265_DIGTRIG_PXITrig_7	(8)		// PXI����Trigger7
#define PXI8265_DIGTRIG_Int_AO0		(9)		// ��AOͨ��0�Ĵ���
#define PXI8265_DIGTRIG_Int_AO1		(10)	// ��AOͨ��1�Ĵ���
// ģ�ⴥ��Դ
#define PXI8265_ANLGTRIG_Extern		(0)		// ģ�����ⴥ���ܽ�
// ģ�ⴥ��б��
#define PXI8265_TRIGSlope_Falling	(0)		// �½�
#define PXI8265_TRIGSlope_Rising	(1)		// ����
//////////////////////////////////////////////////////////////////////////
// PXI Trigger����
// PXI8265_SetPXITriggerLineOutput PXI8265_ResetPXITriggerLine ʹ��
#define PXI8265_PXITrig_Line_0		(0)		// PXI trigger Line 0
#define PXI8265_PXITrig_Line_1		(1)		// PXI trigger Line 1
#define PXI8265_PXITrig_Line_2		(2)		// PXI trigger Line 2
#define PXI8265_PXITrig_Line_3		(3)		// PXI trigger Line 3
#define PXI8265_PXITrig_Line_4		(4)		// PXI trigger Line 4
#define PXI8265_PXITrig_Line_5		(5)		// PXI trigger Line 5
#define PXI8265_PXITrig_Line_6		(6)		// PXI trigger Line 6
#define PXI8265_PXITrig_Line_7		(7)		// PXI trigger Line 7
// �����͵�PXI Trigger�ϵ������ź�
#define PXI8265_StartSignal_AI		(0)		// AO0ͨ�� �����ź����
#define PXI8265_StartSignal_AO0		(1)		// AO0ͨ�� �����ź����
#define PXI8265_StartSignal_AO1		(2)		// AO1ͨ�� �����ź����
//////////////////////////////////////////////////////////////////////////
// DIO ͨ������,���飬ÿ��4������������8��
#define PXI8265_DIO_LINE_0			(0)		// ����������/��� 0 ��
#define PXI8265_DIO_LINE_1			(1)		// ����������/��� 1 ��

// DIO ������
#define PXI8265_DIO_INPORT			(0)		// Ϊ���뷽��
#define PXI8265_DIO_OUTPORT			(1)		// Ϊ�������
//------------------------------------------------------------------
//***********************************************************
// CNT ģʽ����
#define PXI8265_CNT_POSITIVE_0	(0)		// GATE�ߵ�ƽʱ�������͵�ƽʱֹͣ����������ʱ����д���ֵ������ֵ����
										// �������������жϣ�д���ֵ��ʼ����ʱOUT��ʼΪ0����������0ʱOUTΪ1

#define PXI8265_CNT_RISING_1	(1)		// GATE�ϱ��ش��������������г���GATE����������װ���ֵ����
										// �ɱ�̵������壺��д���ֵʱOUTΪ1������ʼ����ʱOUTΪ0����������0ʱOUT�ٴ�Ϊ1

#define PXI8265_CNT_POSITIVE_2	(2)		// GATE�ߵ�ƽʱ�������͵�ƽʱֹͣ����������ʱ����д���ֵ������ֵ����
										// Ƶ�ʷ������������ڼ�OUTΪ1��������0�����һ�����ڵ�0��������װ�����ֵ����

#define PXI8265_CNT_POSITIVE_3	(3)		// GATE�ߵ�ƽʱ�������͵�ƽʱֹͣ����������ʱ����д���ֵ������ֵ����
										// �����������������ڼ�OUTΪ1��������0�����һ�����ڵ�0��������װ�����ֵ����

#define PXI8265_CNT_POSITIVE_4	(4)		// GATE�ߵ�ƽʱ�������͵�ƽʱֹͣ����������ʱ����д���ֵ������ֵ����
										// �������ѡͨ��д���ֵOUTΪ1�� ��������OUT���һ�����ڵ͵�ƽ�ź�

#define PXI8265_CNT_RISING_5	(5)		// GATE�ϱ��ش��������������г���GATE����������װ���ֵ����
										// Ӳ������ѡͨ��д���ֵOUTΪ1�� ��������OUT���һ�����ڵ͵�ƽ�ź�
//////////////////////////////////////////////////////////////////////////
// ������Ϣ
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

	LONG __stdcall PXI8265_GetDevicePXISolt(				// ����豸���ڲ�λ
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// AI���ƺ����ӿڶ���
	LONG __stdcall PXI8265_AI_InitChan(						// ��ʼ��ͨ������
								HANDLE devHandle, 			//
								ULONG firstChan,			// ��ͨ�� ��Χ(0~15)
								ULONG lastChan,				// ĩͨ�� ��Χ(0~15) Ӧ >=firstChan
								ULONG range,				// ����
								ULONG terminalConfig);		// �ӵ�ģʽ �ο��ӵ�ģʽ����

	LONG __stdcall PXI8265_AI_CfgTiming(					// ���òɼ�Ƶ�ʼ�ʱ��ѡ��
								HANDLE devHandle,			// card object handle
								ULONG sourceClk,			// ʱ��Դ���ο�ʱ�Ӷ���
								double rate,				// ��ͨ������Ƶ��
								ULONG sampleMode,			// �ɼ�ģʽ �ο��ɼ�ģʽ����
								ULONG perChanGetSamples);	// �����ɼ�ģʽ��Ϊ�ɼ���������С������ ���βɼ�ģʽ��Ϊ�ɼ�����

	LONG __stdcall PXI8265_AI_Start(						// ��ʼAI�ɼ�
								HANDLE devHandle);

	LONG __stdcall PXI8265_AI_Stop(							// ��ʼAI�ɼ�
								HANDLE devHandle);

	LONG __stdcall PXI8265_AI_Read(							// ��ȡAI����
								HANDLE devHandle,			// device object handle
								ULONG numSampsPerChan,		// ��ȡ��AI��ͨ�������
								ULONG* sampsPerChanRead,	// ���ض�ȡ�ĵ�ͨ������
								LONG readArray[],			// ����ԭʼAI���ݵ��û�������
								ULONG arraySize,			// ��������С
								ULONG fillMode,				// ���ģʽ �ο���䶨��
								double timeOut);			// ��ʱʱ��,����Ϊ��λ,��С�ֱ�0.001, -1��һֱ�ȴ�
	
	// ����AI��������
	// ���ִ���
	LONG __stdcall PXI8265_AI_CfgDigEdgeTrig(				// �������ش���
								HANDLE devHandle,		
								ULONG triggerSource,	 	// ����Դ  �ο���������������
								ULONG triggerEdge,			// ������  �ο������ض���
								LONG reserve);				// ����

	LONG __stdcall PXI8265_AI_CfgDigAreaTrig(				// ��������ƽ��������
								HANDLE devHandle,		
								ULONG triggerSource,	 	// ����Դ  �ο���������������
								ULONG triggerLevel);		// ������ƽ �ο�������ƽ����

	
	LONG __stdcall PXI8265_AI_CfgAnlgEdgeTrig(				// ģ����б�ʴ���
								HANDLE devHandle,		
								ULONG triggerSource, 		// ģ�ⴥ��Դ���ο�ģ�ⴥ��Դ����
								ULONG triggerSlope,			// б�� �ο�ģ�ⴥ��б��
								double triggerLevelVolt,	// ��ƽ ��ѹֵ(V)����Χ 0~10 ��λ:��ѹ
								LONG reserve);				// ����

	LONG __stdcall PXI8265_AI_CfgAnlgAreaTrig(				// ģ��������������������㴥�������ɼ���������������ͣ�ɼ�
								HANDLE devHandle,		
								ULONG triggerSource, 		// ����Դ �ο�ģ�ⴥ��Դ����
								ULONG triggerLevel,			// ������ƽ �ο�ģ���������
								double triggerLevelVolt);	// ��ƽ ��ѹֵ(V)����Χ 0~10 ��λ:��ѹ

	LONG __stdcall PXI8265_AI_DisableTrig(					// ��ֹ����
								HANDLE devHandle);
	// ��У׼
	LONG __stdcall PXI8265_AI_SelfCalibration(				// ��У׼����
								HANDLE devHandle);

	// ת����ѹ
	LONG __stdcall PXI8265_AI_ConvLsbToVolt(				// �Ѳɼ���������ֵת�������̶�Ӧ�ĵ�ѹֵ����λ ����
								ULONG range,				// �ɼ����̣��ο� AI���̶���
								LONG lsbArray[],			// �ɼ�����ֵ����
								ULONG lsbArrSize,			// ��ֵ�����С
								double voltArray[],			// ת����ĵ�ѹ����
								ULONG voltArrSize,			// ��ѹ�����С
								ULONG* returnSize);			// ����ת����ѹ������ݳ���

	//////////////////////////////////////////////////////////////////////////
	// AO ����
	LONG __stdcall PXI8265_AO_InitChan(						// ��ʼ��ͨ������
								HANDLE devHandle, 			//
								ULONG chanNum,				// ͨ����Χ(0, 1)
								double minVal,				// �����Сֵ
								double maxVal);				// ������ֵ

	LONG __stdcall PXI8265_AO_CfgTiming(					// ���������Ƶ�ʼ�ʱ��ѡ��
								HANDLE devHandle,			// card object handle
								ULONG chanNum,				// ͨ����Χ(0, 1)
								ULONG sourceClk,			// ʱ��Դ���ο�ʱ�Ӷ���
								double rate,				// ����Ƶ��
								ULONG sampleMode,			// ���ģʽ �ο����ģʽ����
								ULONG perChanGetSamples);	// �������ģʽ��Ϊ�����������С������ �������ģʽ��Ϊ�������

	LONG __stdcall PXI8265_AO_Write(
								HANDLE devHandle, 
								ULONG chanNum,				// ͨ����Χ(0, 1)
								ULONG numSampsPer,			// �������
								BOOL autoStart,				// �Ƿ�������� true������� false�ȴ�start����,�������ֻ��û����Ƶ�ʺ���ʱ��Ч
								double writeArray[],		// ���������, ֱ��д��ѹֵ(V)	
								ULONG arraySize,			// ��������С������ע�⣬����������С��numSampsPer�����С����ֻ���arraySize���㣬���ҷ��ش���
								double timeout);			// ��ʱʱ��(��λ����)

	LONG __stdcall PXI8265_AO_Start(						// ��ʼAO���
								HANDLE devHandle,
								ULONG chanNum);				// ͨ����Χ(0, 1)

	LONG __stdcall PXI8265_AO_Stop(							// ֹͣAO���
								HANDLE devHandle,
								ULONG chanNum,				// ͨ����Χ(0, 1)
								ULONG stopMode);			// ֹͣģʽ ��AOֹͣģʽ����
	
	LONG __stdcall PXI8265_AO_RegisterEventDone(			// ע��������Ϣ
								HANDLE devHandle,			// card object handle
								ULONG chanNum,				// ͨ����Χ(0, 1)
								HANDLE eventDone);			// ������־,�����������,����д-1����

	LONG __stdcall PXI8265_AO_WaitDoneEvent(				// �ȴ�AO���������Ϣ������õ���ģʽ�򣬿��Եȵ�������Ϣ
								HANDLE	devHandle,
								ULONG chanNum,				// ͨ����Χ(0, 1)
								double  timeout);			// ��ʱʱ��,����Ϊ��λ,��С�ֱ�0.001, -1��һֱ�ȴ�

	// ����AO��������
	// ���ִ���
	LONG __stdcall PXI8265_AO_CfgDigEdgeTrig(				// �������ش���
								HANDLE devHandle,		
								ULONG  chanNum,				// ͨ����Χ(0, 1)
								ULONG triggerSource,	 	// ����Դ  �ο���������������
								ULONG triggerEdge,			// ������  �ο������ض���
								LONG reserve);				// ����

	LONG __stdcall PXI8265_AO_CfgDigAreaTrig(				// ��������ƽ��������
								HANDLE devHandle,		
								ULONG  chanNum,				// ͨ����Χ(0, 1)
								ULONG triggerSource,	 	// ����Դ  �ο���������������
								ULONG triggerLevel);		// ������ƽ �ο�������ƽ����

	LONG __stdcall PXI8265_AO_CfgAnlgEdgeTrig(				// ģ����б�ʴ���
								HANDLE devHandle,		
								ULONG  chanNum,				// ͨ����Χ(0, 1)
								ULONG triggerSource, 		// ģ�ⴥ��Դ���ο�ģ�ⴥ��Դ����
								ULONG triggerSlope,			// б�� �ο�ģ�ⴥ��б��
								double triggerLevelVolt,	// ��ƽ ��ѹֵ(V)����Χ 0~10 ��λ:��ѹ
								LONG reserve);				// ����

	LONG __stdcall PXI8265_AO_CfgAnlgAreaTrig(				// ģ��������������������㴥�������ɼ���������������ͣ�ɼ�
								HANDLE devHandle,		
								ULONG  chanNum,				// ͨ����Χ(0, 1)
								ULONG triggerSource, 		// ����Դ �ο�ģ�ⴥ��Դ����
								ULONG triggerLevel,			// ������ƽ �ο�ģ���������
								double triggerLevelVolt);	// ��ƽ ��ѹֵ(V)����Χ 0~10 ��λ:��ѹ

	LONG __stdcall PXI8265_AO_DisableTrig(					// ��ֹ����
								HANDLE devHandle,
								ULONG  chanNum);			// ͨ����Χ(0, 1)

	// ��У׼
	LONG __stdcall PXI8265_AO_SelfCalibration(				// ��У׼����
								HANDLE devHandle);
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8265_SetPXITriggerLineOutput(			// ���ô��������TriggerLine�ϣ����Ұ�TriggerLine����Ϊ���
								HANDLE devHandle,
								ULONG PxiTrigLine,			// PXI trigger��� �ο�PXI Trigger����
								ULONG xfunStartSignal);		// �����ź� �ο������͵�PXI Trigger�ϵ������ź�

	LONG __stdcall PXI8265_ResetPXITriggerLine(				// ��λ���������
								HANDLE devHandle,
								ULONG PxiTrigLine);			// PXI trigger��� �ο�PXI Trigger����
	//////////////////////////////////////////////////////////////////////////
	// �������������
	LONG __stdcall PXI8265_DIO_CfgDev(						// ����DIO
								HANDLE devHandle,
								ULONG lineGroupNum,			// ͨ����ѡ�� �ο�DIOͨ������
								ULONG portDir);				// ͨ���鷽��

	LONG __stdcall PXI8265_DIO_ReturnCfgDev(					// �ض�����DIO
								HANDLE devHandle,
								ULONG lineGroupNum,			// ͨ����ѡ�� �ο�DIOͨ������
								ULONG* portDir);			// �ض�ͨ���鷽��

	LONG __stdcall PXI8265_DIO_Write(						// д���������,���ͨ������ΪINPORT�ģ����ֵ��Ч
								HANDLE devHandle,			// card object handle
								ULONG lineGroupNum,			// ͨ����ѡ�� �ο�DIOͨ������
								BYTE writeArray[],			// д�������������
								ULONG arraySize);			// д�����С

	LONG __stdcall PXI8265_DIO_Read(						// ��ȡ����������,���ͨ������ΪOUTPORT�ģ��������״̬
								HANDLE devHandle,			// card object handle
								ULONG lineGroupNum,			// ͨ����ѡ�� �ο�DIOͨ������
								BYTE readArray[],			// ����������������
								ULONG arraySize);			// �������С
	//////////////////////////////////////////////////////////////////////////
	// ������
	LONG __stdcall PXI8265_CNT_CfgDev(						// ���ü�����
								HANDLE devHandle,			// card object handle
								ULONG chan,					// ������ͨ�� ��Χ0
								ULONG countMode,			// ����ģʽ���ο�CNT����
								ULONG initValue);			// ��������ʼֵ

	LONG __stdcall PXI8265_CNT_Read(
								HANDLE devHandle,			// card object handle
								ULONG  chan,				// ������ͨ�� ��Χ0
								ULONG* countValue);			// ���ؼ�������ǰֵ
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

