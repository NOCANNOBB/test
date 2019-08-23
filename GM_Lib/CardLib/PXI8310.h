#ifndef _CI_PXI8310_DEVICE_
#define _CI_PXI8310_DEVICE_

#include "windows.h"

#pragma once
//------------------------------------------------------------------------
// ����ͨ������ 
#define PXI8310_OHM_CH0				(0)		// ����ͨ��0
#define PXI8310_OHM_CH1				(1)		// ����ͨ��1
#define PXI8310_OHM_CH2				(2)		// ����ͨ��2
#define PXI8310_OHM_CH3				(3)		// ����ͨ��3
//------------------------------------------------------------------------
// �����ֵ����
#define PXI8310_OHM_VAL_MAX			(16665)	
//////////////////////////////////////////////////////////////////////////
// ������Ϣ
#define PXI8310_Failed(error)				((error)<0)
#define PXI8310_NoError						(0)
#define PXI8310_WarningTimeOut				(-20019)
//////////////////////////////////////////////////////////////////////////
// Device function
#ifdef __cplusplus
extern "C" {
#endif
	LONG __stdcall PXI8310_DeviceOpen(						// open PXI8310 device
								ULONG DeviceNum,			// device logic ID
								HANDLE* pDrvHandle);		// return card object handle

	LONG __stdcall PXI8310_DeviceClose(						// close PXI8310 device 
								HANDLE devHandle);			// card object handle

	LONG __stdcall PXI8310_GetDeviceCount(					// get card count
								ULONG* devCount);			// return card count
		
	LONG __stdcall PXI8310_GetDevicePhyID(					// get card physical id
								HANDLE devHandle,			// card object handle
								ULONG* Physical);			// return card physical id

	LONG __stdcall PXI8310_GetDevicePXISlot(				// ����豸���ڲ�λ
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	// OHM ����
	LONG __stdcall PXI8310_OHM_InitChan(					// ��ʼ��ͨ������
								HANDLE devHandle, 			//
								ULONG  chanNum,				// ͨ�� �ο�ͨ������
								BOOL   bGroup);				// �Ƿ����,

	LONG __stdcall PXI8310_OHM_Write(						// �������
								HANDLE devHandle,
								ULONG  chanNum,				// ͨ�� �ο�ͨ������
								double val);				// ����ֵ ��С��λ1ŷ, �������ֵ�ο� �����ֵ����

	// ��չ����������Ƿ���ģʽ����������������ֱ���Ƹ�/��8λ �������ֵ
	LONG __stdcall PXI8310_OHM_WriteEx(						// �������ֵ��
								HANDLE devHandle,
								ULONG  chanNum,				// ͨ�� �ο�ͨ������
								double lowVal,				// ��8λ����ֵ 0~165
								double highVal);			// ��8λ����ֵ 100~16500

	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI8310_GetErrorString(					// get error string
								LONG errorCode,				// error code
								char errorString[],			// return error info string 
								ULONG bufferSize);			// errorString buffer size
	//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#ifndef _PXI8310_DLL
	#ifndef _WIN64
		#pragma comment(lib, "PXI8310.lib")
	#else
		#pragma comment(lib, "PXI8310_64.lib")
	#endif
#endif

#endif // _CI_PXI8310_DEVICE_

