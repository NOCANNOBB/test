#ifndef _CI_PXI8510_DEVICE_
#define _CI_PXI8510_DEVICE_

#include "windows.h"

#pragma once
//////////////////////////////////////////////////////////////////////////
// ͬ��422ʱ�����ģʽ����
#define PXI8510_LVDS_CLK_Continue	(0)		// ����ʱ�����ģʽ
#define PXI8510_LVDS_CLK_Discontinue	(1)		// ��Ъʱ�����ģʽ
// ͬ��422ͨ������
#define PXI8510_LVDS_CH0				(0)		// ͬ��422ͨ��0
//////////////////////////////////////////////////////////////////////////
// ����ģʽ����
#define PXI8510_TRANSF_MODE_DMA			(0)		// DMA����ģʽ
#define PXI8510_TRANSF_MODE_PRO			(1)		// ������ģʽ
//////////////////////////////////////////////////////////////////////////
#define PXI8510_SEND_LVDS_CH_MAX		(2)		// ����2ͨ��
#define PXI8510_SEND_RECV_CH_MAX		(4)		// ����4ͨ��
//////////////////////////////////////////////////////////////////////////
// ������Ϣ
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

	LONG __stdcall PXI8510_GetDevicePXISolt(				// ����豸���ڲ�λ
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// ͬ��422 ���Ͳ���
	LONG __stdcall PXI8510_LVDS_SendInitChan(				// ����ͨ����ʼ��
								HANDLE devHandle, 			//
								ULONG chanNum,				// ����ͨ����,�ο�ͬ��422ͨ������
								ULONG frameLen,				// ����֡�����������Ϊ0����������ʱʹ�ܹܽ�һֱ��Ч��������ֹͣ������ʹ��
								double rate,				// ���÷���Ƶ�� 1K ~500K,��λHz
								ULONG perChanGetSamples);	// �����ڲ�������
	//---------------------------------------------------------------------------
	// ���ڴ���ʹ�õ����
	LONG __stdcall PXI8510_LVDS_SendCfgTrigExtern(		// �����ⲿ֡Ȧͬ������ģʽ
								HANDLE devHandle, 
								ULONG chanNum);				// ͬ������ͨ��
	//---------------------------------------------------------------
	// ֡Ȧ����
	LONG __stdcall PXI8510_LVDS_SendTrigFrame(			// �ⴥ�� ֡ͬ���źŷ��Ͱ�
								HANDLE	devHandle, 
								ULONG	chanNum,			// ͬ������ͨ��
								BYTE	writeArray[],
								ULONG	arraySize);			// ���ͳ���,  ������Ҫ��80�ֽڵ�֡��

	LONG __stdcall PXI8510_LVDS_SendTrigCircle(			// �ⴥ�� Ȧͬ���źŷ��Ͱ�
								HANDLE	devHandle, 
								ULONG	chanNum,			// ͬ������ͨ��
								BYTE	writeArray[],
								ULONG	arraySize);			// ���ͳ���,  ������Ҫ��2*80�ֽڵ�Ȧ��
	//---------------------------------------------------------------
	LONG __stdcall PXI8510_LVDS_SendCfgTrgiExtern2(
								HANDLE devHandle, 
								ULONG chanNum);				// ͬ������ͨ��

	LONG __stdcall PXI8510_LVDS_SendInitNum2(				// ��ʼֵ������ֵ�趨
								HANDLE	devHandle, 
								ULONG	chanNum,			// ͬ������ͨ��
								ULONG	initNum,			// ��ʼֵ ע������ֻ��14Bit��Ч
								ULONG	incNum,				// ����ֵ(��������)14Bit��Ч
								ULONG   intTimer);			// ���ʱ��	

	LONG __stdcall PXI8510_LVDS_SetRowsAndImageElement(		// LVDS���������ú���Ԫ
								HANDLE  devHandle,			
								ULONG   rows,				// ������
								ULONG   imageElement);		// ��Ԫ��
	//---------------------------------------------------------------
	LONG __stdcall PXI8510_PulseIn_GetCount(				// ���֡Ȧ����ֵ
								HANDLE	devHandle,
								ULONG*	pCircleCnt,			// ����Ȧͬ������ֵ
								ULONG*	pFrameCnt);			// ����֡ͬ������ֵ

	LONG __stdcall PXI8510_PulseIn_ClearCount(				// ���֡Ȧ����ֵ
								HANDLE	devHandle);			//
	//---------------------------------------------------------------------------
	LONG __stdcall PXI8510_LVDS_SendStart(					// ͬ��422 ���Ϳ�ʼ
								HANDLE devHandle,
								ULONG chanNum,				// ͨ����,�ο�ͬ��422ͨ������
								ULONG clkMode);				// ʱ�����ģʽ���ο� ͬ��422ʱ�����ģʽ����

	LONG __stdcall PXI8510_LVDS_SendStop(					// ͬ��422 ����ֹͣ
								HANDLE devHandle,
								ULONG chanNum);				// ͨ����,�ο�ͬ��422ͨ������

	LONG __stdcall PXI8510_LVDS_Send(						// ����
								HANDLE	devHandle, 
								ULONG	chanNum,			// ͨ����,�ο�ͬ��422ͨ������
								ULONG	numSampsPer,		// �������
								ULONG	loopNum,			// �������, 0Ϊ�������
								BYTE	writeArray[],		// ���������, ֱ��д��ѹֵ(V)	
								ULONG	arraySize,			// ��������С������ע�⣬����������С��numSampsPer�����С����ֻ���arraySize���㣬���ҷ��ش���
								double	timeout);			// ��ʱʱ��(��λ����)

	LONG __stdcall PXI8510_LVDS_GetSendLen(					// ����д���ݳ���
								HANDLE	devHandle,
								ULONG	chanNum,			// ͨ����,�ο�ͬ��422ͨ������
								UINT64* pRetWriteLen);		// ����д���ݳ��ȣ���λ:�ֽ�

	LONG __stdcall PXI8510_LVDS_GetSendErrorSts(			// ���ش���״̬
								HANDLE	devHandle,
								ULONG chanNum,				// ͨ����Χ(0, 1)
								ULONG* sendBreakpointCount);// ���Ͷϵ�������

	LONG __stdcall PXI8510_LVDS_SendWaitDoneEvent(			// �ȴ�AO���������Ϣ������õ���ģʽ�򣬿��Եȵ�������Ϣ
								HANDLE	devHandle,
								ULONG chanNum,				// ͨ����Χ(0, 1)
								double  timeout);			// ��ʱʱ��,����Ϊ��λ,��С�ֱ�0.001, -1��һֱ�ȴ�

	// ��������������PXI8510_LVDS_SendInitChan��ǰ���á�������Ч
	LONG __stdcall PXI8510_LVDS_SetSendTransferMode(		// ���ʹ��䷽ʽ�趨��
								HANDLE	devHandle,
								ULONG	chanNum,			// ͨ����Χ(0, 1)
								ULONG	mode);				// ����ģʽ���ο� ����ģʽ����
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// ͬ��422 ���ղ���
	LONG __stdcall PXI8510_LVDS_RecvInitChan(				// ����ͨ����ʼ��
								HANDLE devHandle, 			//
								ULONG chanNum,				// ͨ����,�ο�ͬ��422ͨ������
								ULONG perChanGetSamples);	// �����ڲ�������

	LONG __stdcall PXI8510_LVDS_RecvStart(					// ͬ��422 ���տ�ʼ
								HANDLE devHandle,
								ULONG chanNum);				// ͨ����,�ο�ͬ��422ͨ������

	LONG __stdcall PXI8510_LVDS_RecvStop(					// ͬ��422 ����ֹͣ
								HANDLE devHandle,
								ULONG chanNum);				// ͨ����,�ο�ͬ��422ͨ������

	LONG __stdcall PXI8510_LVDS_Recv(						// ����
								HANDLE devHandle,			// device object handle
								ULONG chanNum,				// ͨ����,�ο�ͬ��422ͨ������
								ULONG readLen,				// ��ȡ���ݳ���
								ULONG* retLen,				// �������ݳ���
								BYTE readArray[],			// ����ԭʼAI���ݵ��û�������
								ULONG arraySize,			// ��������С
								double timeOut);			// ��ʱʱ��,����Ϊ��λ,��С�ֱ�0.001, -1��һֱ�ȴ�

	LONG __stdcall PXI8510_LVDS_GetRecvErrorSts(			// ���ش���״̬
								HANDLE	devHandle,
								ULONG chanNum,				// ͨ����Χ(0, 1)
								ULONG* recvOverflow);		// �����������


	// ��������������PXI8510_LVDS_RecvInitChan��ǰ���á�������Ч
	LONG __stdcall PXI8510_LVDS_SetRecvTransferMode(		// ���ʹ��䷽ʽ�趨��
								HANDLE	devHandle,
								ULONG	chanNum,			// ͨ����Χ(0, 1)
								ULONG	mode);				// ����ģʽ���ο� ����ģʽ����
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

