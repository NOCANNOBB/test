#ifndef _CI_PXI8867_DEVICE_
#define _CI_PXI8867_DEVICE_

#include "windows.h"

#pragma once
//------------------------------------------------------------------------
// AO ��ض���,ͨ������2
// AO ֹͣģʽ
#define PXI8867_AO_CH0				(0)		// AOͨ��0
#define PXI8867_AO_CH1				(1)		// AOͨ��1
#define PXI8867_AO_CH11				(11)	// AOͨ��11
//////////////////////////////////////////////////////////////////////////
// ������Ϣ
#define PXI8867_Failed(error)				((error)<0)
#define PXI8867_NoError						(0)
#define PXI8867_WarningTimeOut				(-20019)
//////////////////////////////////////////////////////////////////////////
// Device function
#ifdef __cplusplus
extern "C" {
#endif
	LONG __stdcall PXI8867_DeviceOpen(						// open PXI8867 device
								ULONG DeviceNum,			// device logic ID
								HANDLE* pDrvHandle);		// return card object handle

	LONG __stdcall PXI8867_DeviceClose(						// close PXI8867 device 
								HANDLE devHandle);			// card object handle

	LONG __stdcall PXI8867_GetDeviceCount(					// get card count
								ULONG* devCount);			// return card count
		
	LONG __stdcall PXI8867_GetDevicePhyID(					// get card physical id
								HANDLE devHandle,			// card object handle
								ULONG* Physical);			// return card physical id

	LONG __stdcall PXI8867_GetDevicePXISlot(				// ����豸���ڲ�λ
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// AO ����
	LONG __stdcall PXI8867_AO_InitChan(						// ��ʼ��ͨ������
								HANDLE devHandle, 			//
								ULONG chanNum,				// ͨ����Χ(0, 1)
								double minVal,				// �����Сֵ
								double maxVal);				// ������ֵ

    LONG __stdcall PXI8867_AO_Write(
								HANDLE devHandle, 
								ULONG chanNum,				// ͨ����Χ(0, 1)
								double writeVal);           // ���������, ֱ��д��ѹֵ(V)	
	//------------------------------------------------------------------------
	// У׼����
	LONG __stdcall PXI8867_AO_CalEn(				       // У׼����
								HANDLE devHandle,
                                BOOL  bEn);                 // TRUEʹ��У׼, FALSE ֹͣУ׼

    LONG __stdcall PXI8867_AO_Cal_Reset(					// У׼ֵ��λ
								HANDLE devHandle,			// �豸���
								ULONG chan);				// ͨ����

    LONG __stdcall PXI8867_AO_Cal_WriteVal(
                                HANDLE devHandle,
								ULONG chanNum,				// ͨ����
                                double valK,				// Kֵ
                                double valB);				// Bֵ

    LONG __stdcall PXI8867_AO_Cal_CalcWriteVal(				// ���㲢д��У׼ֵ
								HANDLE devHandle,			// �豸���
								ULONG chanNum,				// ͨ����
								double arrayCur[],			// �ɼ�ֵ
								double arrayTarget[],		// Ŀ��ֵ
								ULONG arraySize);			// �����С

	LONG __stdcall PXI8867_AO_Cal_WriteEEP(			    	// д��EEP
								HANDLE devHandle);			// �豸���
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8867_GetErrorString(					// get error string
								LONG errorCode,				// error code
								char errorString[],			// return error info string 
								ULONG bufferSize);			// errorString buffer size
	//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#ifndef _PXI8867_DLL
	#ifndef _WIN64
		#pragma comment(lib, "PXI8867.lib")
	#else
		#pragma comment(lib, "PXI8867_64.lib")
	#endif
#endif

#endif // _CI_PXI8867_DEVICE_

