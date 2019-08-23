#ifndef _CI_PXI8530_DEVICE_
#define _CI_PXI8530_DEVICE_

#include "windows.h"

#pragma once
//////////////////////////////////////////////////////////////////////////
// ͬ��422ʱ�����ģʽ����
#define PXI8530_SYNC422_CLK_Continue	(0)		// ����ʱ�����ģʽ
#define PXI8530_SYNC422_CLK_Discontinue	(1)		// ��Ъʱ�����ģʽ
// ͬ��422ͨ������
#define PXI8530_SYNC422_CH0				(0)		// ͬ��422ͨ��0
//////////////////////////////////////////////////////////////////////////
// ����ģʽ����
#define PXI8530_TRANSF_MODE_DMA			(0)		// DMA����ģʽ
#define PXI8530_TRANSF_MODE_PRO			(1)		// ������ģʽ
//////////////////////////////////////////////////////////////////////////
// �����ʶ���
#define PXI8530_RATE_4800				(0)
#define PXI8530_RATE_9600				(1)
#define PXI8530_RATE_19200				(2)
#define PXI8530_RATE_38400				(3)
#define PXI8530_RATE_57600				(4)
#define PXI8530_RATE_115200				(5)
// У��λ����
#define PXI8530_PARITY_NONE				(0)		// û��У��
#define PXI8530_PARITY_EVEN				(1)		// żУ��
#define PXI8530_PARITY_ODD				(2)		// ��У��
//////////////////////////////////////////////////////////////////////////
#define PXI8530_ENDAT_MODE_SOFT			(0)		// �������
#define PXI8530_ENDAT_MODE_CYCLE		(1)		// ���ڶ�ȡ80uS
#define PXI8530_ENDAT_MODE_CIRCLE		(2)		// Ȧͬ������
#define PXI8530_ENDAT_MODE_FRAME		(3)		// ֡ͬ������
//////////////////////////////////////////////////////////////////////////
// ������Ϣ
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

	LONG __stdcall PXI8530_GetDevicePXISolt(				// ����豸���ڲ�λ
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// ͬ��422 ���Ͳ���
	LONG __stdcall PXI8530_SYNC422_SendInitChan(			// ����ͨ����ʼ��
								HANDLE devHandle, 			//
								ULONG chanNum,				// ����ͨ����,�ο�ͬ��422ͨ������
								ULONG frameLen,				// ����֡�����������Ϊ0����������ʱʹ�ܹܽ�һֱ��Ч��������ֹͣ������ʹ��
								double rate,				// ���÷���Ƶ�� 1K ~500K,��λHz
								ULONG perChanGetSamples);	// �����ڲ�������

	LONG __stdcall PXI8530_SYNC422_SendCfgTrigExtern(		// �����ⲿ֡Ȧͬ������ģʽ
								HANDLE devHandle, 
								ULONG chanNum);				// ͬ������ͨ��

	LONG __stdcall PXI8530_SYNC422_SendTrigFrame(			// �ⴥ�� ֡ͬ���źŷ��Ͱ�
								HANDLE	devHandle, 
								ULONG	chanNum,			// ͬ������ͨ��
								BYTE	writeArray[],
								ULONG	arraySize);			// ���ͳ���,  ������Ҫ��80�ֽڵ�֡��

	LONG __stdcall PXI8530_SYNC422_SendTrigCircle(			// �ⴥ�� Ȧͬ���źŷ��Ͱ�
								HANDLE	devHandle, 
								ULONG	chanNum,			// ͬ������ͨ��
								BYTE	writeArray[],
								ULONG	arraySize);			// ���ͳ���,  ������Ҫ��2*80�ֽڵ�Ȧ��

	LONG __stdcall PXI8530_SYNC422_SendStart(				// ͬ��422 ���Ϳ�ʼ
								HANDLE devHandle,
								ULONG chanNum,				// ͨ����,�ο�ͬ��422ͨ������
								ULONG clkMode);				// ʱ�����ģʽ���ο� ͬ��422ʱ�����ģʽ����

	LONG __stdcall PXI8530_SYNC422_SendStop(				// ͬ��422 ����ֹͣ
								HANDLE devHandle,
								ULONG chanNum);				// ͨ����,�ο�ͬ��422ͨ������

	LONG __stdcall PXI8530_SYNC422_Send(					// ����
								HANDLE	devHandle, 
								ULONG	chanNum,			// ͨ����,�ο�ͬ��422ͨ������
								ULONG	numSampsPer,		// �������
								ULONG	loopNum,			// �������, 0Ϊ�������
								BYTE	writeArray[],		// ���������, ֱ��д��ѹֵ(V)	
								ULONG	arraySize,			// ��������С������ע�⣬����������С��numSampsPer�����С����ֻ���arraySize���㣬���ҷ��ش���
								double	timeout);			// ��ʱʱ��(��λ����)

	LONG __stdcall PXI8530_SYNC422_GetSendLen(				// ����д���ݳ���
								HANDLE	devHandle,
								ULONG	chanNum,			// ͨ����,�ο�ͬ��422ͨ������
								UINT64* pRetWriteLen);		// ����д���ݳ��ȣ���λ:�ֽ�

	LONG __stdcall PXI8530_SYNC422_GetSendErrorSts(			// ���ش���״̬
								HANDLE	devHandle,
								ULONG chanNum,				// ͨ����Χ(0, 1)
								ULONG* sendBreakpointCount);// ���Ͷϵ�������

	LONG __stdcall PXI8530_SYNC422_SendWaitDoneEvent(		// �ȴ�AO���������Ϣ������õ���ģʽ�򣬿��Եȵ�������Ϣ
								HANDLE	devHandle,
								ULONG chanNum,				// ͨ����Χ(0, 1)
								double  timeout);			// ��ʱʱ��,����Ϊ��λ,��С�ֱ�0.001, -1��һֱ�ȴ�

	// ��������������PXI8530_SYNC422_SendInitChan��ǰ���á�������Ч
	LONG __stdcall PXI8530_SYNC422_SetSendTransferMode(		// ���ʹ��䷽ʽ�趨��
								HANDLE	devHandle,
								ULONG	chanNum,			// ͨ����Χ(0, 1)
								ULONG	mode);				// ����ģʽ���ο� ����ģʽ����
	//////////////////////////////////////////////////////////////////////////
	// ͬ��422 ���ղ���
	LONG __stdcall PXI8530_SYNC422_RecvInitChan(			// ����ͨ����ʼ��
								HANDLE devHandle, 			//
								ULONG chanNum,				// ͨ����,�ο�ͬ��422ͨ������
								ULONG perChanGetSamples);	// �����ڲ�������

	LONG __stdcall PXI8530_SYNC422_RecvStart(				// ͬ��422 ���տ�ʼ
								HANDLE devHandle,
								ULONG chanNum);				// ͨ����,�ο�ͬ��422ͨ������

	LONG __stdcall PXI8530_SYNC422_RecvStop(				// ͬ��422 ����ֹͣ
								HANDLE devHandle,
								ULONG chanNum);				// ͨ����,�ο�ͬ��422ͨ������

	LONG __stdcall PXI8530_SYNC422_Recv(					// ����
								HANDLE devHandle,			// device object handle
								ULONG chanNum,				// ͨ����,�ο�ͬ��422ͨ������
								ULONG readLen,				// ��ȡ���ݳ���
								ULONG* retLen,				// �������ݳ���
								BYTE readArray[],			// ����ԭʼAI���ݵ��û�������
								ULONG arraySize,			// ��������С
								double timeOut);			// ��ʱʱ��,����Ϊ��λ,��С�ֱ�0.001, -1��һֱ�ȴ�

	LONG __stdcall PXI8530_SYNC422_GetRecvErrorSts(				// ���ش���״̬
								HANDLE	devHandle,
								ULONG chanNum,				// ͨ����Χ(0, 1)
								ULONG* recvOverflow);		// �����������


	// ��������������PXI8530_SYNC422_RecvInitChan��ǰ���á�������Ч
	LONG __stdcall PXI8530_SYNC422_SetRecvTransferMode(		// ���ʹ��䷽ʽ�趨��
								HANDLE	devHandle,
								ULONG	chanNum,			// ͨ����Χ(0, 1)
								ULONG	mode);				// ����ģʽ���ο� ����ģʽ����
	//////////////////////////////////////////////////////////////////////////
	// ����������
	LONG __stdcall PXI8530_EnDat_InitChan(					// ��ʼ��ͨ��
								HANDLE	devHandle,
								ULONG	readMode,			// ģʽ
								ULONG perChanGetSamples);	// �����ڲ�������

	LONG __stdcall PXI8530_EnDat_Start(						// ��ʼ��ȡ ����������Բ�������������
								HANDLE	devHandle);

	LONG __stdcall PXI8530_EnDat_Stop(						// ֹͣ��ȡ ����������Բ�������������
								HANDLE	devHandle);

	LONG __stdcall PXI8530_EnDat_Read(						// ��ȡ����
								HANDLE	devHandle,
								ULONG	readLen,				// ��ȡ���ݳ���
								ULONG*	retLen,				// �������ݳ���
								ULONG	readArray[],		// ����������
								__int64 timeCode[],			// ʱ��������
								double timeOut);			// ��ʱʱ��
	//////////////////////////////////////////////////////////////////////////
	// ���� �����������1
	LONG __stdcall PXI8530_PulseOut_Cfg(					// �����������
								HANDLE	devHandle,
								double	circleWidth,		// Ȧ���������� ��λmS ����0.1 �ο� 50~150, ��Χ 0.1~6553.5
								double	circleCycle,		// Ȧ������������ ��λmS ����0.1 �ο� 500~3000, ��Χ 0.1~6553.5
								double	frameWidth,			// ֡ͬ��������� ��λmS ����0.01 �ο� 0.25~1.5, ��Χ 0.01~2.55
								double	frameCycle,			// ֡ͬ���������� ��λmS ��С0.01 �ο� 1~3, ��Χ 0.01~5.12
								double	frameDelayCircle,	// ֡��������Ȧ�ź���ʱ���� ��λmS ��С0.1 �ο� 50~600, ��Χ 0.1~819.2
								ULONG	unit1BeingPos,		// ��һ�� ��ʼλ�� 0 ~ 1023
								ULONG	unit1EndPos,		// ��һ�� ����λ�� 0 ~ 1023
								ULONG	unit2BeingPos,		// �ڶ��� ��ʼλ�� 0 ~ 1023
								ULONG	unit2EndPos,		// �ڶ��� ����λ�� 0 ~ 1023
								ULONG	unit3BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
								ULONG	unit3EndPos,		// ������ ����λ�� 0 ~ 1023
								ULONG	unit4BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
								ULONG	unit4EndPos,		// ������ ����λ�� 0 ~ 1023
								ULONG	unit5BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
								ULONG	unit5EndPos,		// ������ ����λ�� 0 ~ 1023
								ULONG	unit6BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
								ULONG	unit6EndPos,		// ������ ����λ�� 0 ~ 1023
								ULONG	unit7BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
								ULONG	unit7EndPos);		// ������ ����λ�� 0 ~ 1023

	LONG __stdcall PXI8530_PulseOut_Start(					// �����������
								HANDLE	devHandle);

	LONG __stdcall PXI8530_PulseOut_Stop(					// �����������
								HANDLE	devHandle);

	LONG __stdcall PXI8530_PulseOut_GetCount(				// ���֡Ȧ����ֵ
								HANDLE	devHandle,
								ULONG*	pCircleCnt,			// ����Ȧͬ������ֵ
								ULONG*	pFrameCnt);			// ����֡ͬ������ֵ

	// ���� �����������2
	LONG __stdcall PXI8530_Pulse2OutCfg(
								HANDLE	devHandle,
								double	circleCycle,		// Ȧ������������ ��λmS 0.01 ��Χ 0.01~42949672.95
								double	frameCycle,			// ֡ͬ���������� ��λmS 0.01 ��Χ 0.01~655.35
								double	frameWidth,			// ֡ͬ��������� ��λmS 0.01 ��Χ 0.01~655.35
								double	frameDelayCircle);	// ֡Ȧ��ʱ����

	LONG __stdcall PXI8530_Pulse2Out_Start(					// �����������
								HANDLE	devHandle);

	LONG __stdcall PXI8530_Pulse2Out_Stop(					// �����������
								HANDLE	devHandle);

	LONG __stdcall PXI8530_PulseOut_MainTrig(					
								HANDLE	devHandle,
								BOOL		bOut);
	// ����PPS�źŵ�����ʹ��
	LONG __stdcall PXI8530_SetPPSMainOrViceEnable(			// PPS�źŵ�����ʹ��
								HANDLE devHandle,
								BOOL chan0En,
								BOOL chan1En);
	//////////////////////////////////////////////////////////////////////////
	// �첽422ͨ��
	LONG __stdcall PXI8530_ASYNC422_InitChan(				// ��ʼ��
								HANDLE devHandle,
								ULONG  chanNum,
								ULONG rateIndex,			// ������,�ο������ʶ���
								ULONG parityBit);			// У��λ,�ο�У��λ����

	LONG __stdcall PXI8530_ASYNC422_Start(					// 422��ʼ���շ���
								HANDLE devHandle,
								ULONG  chanNum);

	LONG __stdcall PXI8530_ASYNC422_Stop(					// 422ֹͣ���շ���
								HANDLE devHandle,
								ULONG  chanNum);

	LONG __stdcall PXI8530_ASYNC422_ClearFIFO(
								HANDLE devHandle,
								ULONG  chanNum,
								BOOL	bTxFifoClear,		// TRUE�������FIFO
								BOOL	bRxFifoClear);		// TRUE�������FIFO

	LONG __stdcall PXI8530_ASYNC422_Read(
								HANDLE devHandle,
								ULONG  chanNum,
								BYTE	readArray[],		// ��ȡ����
								ULONG	readLen,			// ��ȡ����
								ULONG*	retLen,				// ʵ�ʷ��س���
								double	timeOut);			// ��ʱʱ�� ��λ:��

	LONG __stdcall PXI8530_ASYNC422_Write(
								HANDLE devHandle,
								ULONG  chanNum,
								BYTE	writeArray[],		// д����
								ULONG	writeLen);			// д����

	LONG __stdcall PXI8530_ASYNC422_SetReadTransferMode(	// �첽422�������䷽ʽ�趨��
								HANDLE	devHandle,
								ULONG	chanNum,			// ͨ����Χ(0, 1)
								ULONG	mode);				// ����ģʽ���ο� ����ģʽ����
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8530_MEAS_Frame_SetTime(				// ���ò���֡ͬ��sʱ��
								HANDLE	devHandle,
								ULONG	timeData);			// ʱ��ֵ

	LONG __stdcall PXI8530_MEAS_Circle_SetTime(				// ���ò���֡ͬ��sʱ��
								HANDLE	devHandle,
								ULONG	timeData);			// ʱ��ֵ

	LONG __stdcall PXI8530_MEAS_Start(				// ��ʼ��ȡ֡ͬ��������ֵ
								HANDLE	devHandle);

	LONG __stdcall PXI8530_MEAS_Stop(				// ֹͣ��ȡ֡ͬ��������ֵ
								HANDLE	devHandle);

	LONG __stdcall PXI8530_MEAS_Read(				// ��ȡ֡ͬ��������ֵ
								HANDLE	devHandle,
								__int64	readArray[],		// ��ȡ����
								ULONG	readLen,			// ��ȡ����
								ULONG*	retLen,				// ʵ�ʷ��س���
								double	timeOut);			// ��ʱʱ�� ��λ:��



	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8530_ReSignal_Init(					// ��λ�ź� ��ʼ�� �������ͨ��������ֵ
								HANDLE	devHandle);

	LONG __stdcall PXI8530_ReSignal_GetPulseWidth(			// ��λ�ź� ��ø�λ�ź�������
								HANDLE	devHandle,
								ULONG	chanNum,
								ULONG*	retReSinalCount,		// ���ظ�λ����
								ULONG*	retPulseWidth);			// ������
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

