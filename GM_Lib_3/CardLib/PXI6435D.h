#ifndef _CI_PXI6435D_DEVICE_
#define _CI_PXI6435D_DEVICE_

#include "windows.h"

#pragma once
//////////////////////////////////////////////////////////////////////////
// ���ض���
#define PXI6435D_Val_Falling	(0)		// �½���
#define PXI6435D_Val_Rising		(1)		// ������


//////////////////////////////////////////////////////////////////////////
// ͨ������
#define PXI6435D_CI_CHAN_TOTAL				(8)
//////////////////////////////////////////////////////////////////////////
// ������Ϣ
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
	
	LONG __stdcall PXI6435D_GetDevicePXISlot(				// ����豸���ڲ�λ
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI6435D_CNT_InFreqChan(					// Ƶ�ʲ���
								HANDLE devHandle,			// card object handle
								ULONG	chan,				// ������ͨ�� ��Χ0~1
								double	minVal,				// ��������Сֵ,��λ ��
								double	maxVal,				// ���������ֵ,��λ ��
								ULONG	edge,				// ��������
								double	measTime);			// ����ʱ�䣬��λ��

	LONG __stdcall PXI6435D_CNT_Start(						// ��������ʼ ����/���
								HANDLE devHandle,			// card object handle
								ULONG chan);				// ������ͨ�� ��Χ0~1

	LONG __stdcall PXI6435D_CNT_Stop(						// ������ֹͣ ����/���
								HANDLE devHandle,			// card object handle
								ULONG chan);				// ������ͨ�� ��Χ0~1

	LONG __stdcall PXI6435D_CNT_ReadF64(
								HANDLE devHandle,			// card object handle
								ULONG chan,					// ������ͨ�� ��Χ0~1
								double* frequency,			// ����ֵ ����Ƶ��
								double* dutyCycle,			// ����ֵ ����ߵ�ƽʱ�������������
								double timeOut);			// ��ʱʱ�� ��λ��
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
