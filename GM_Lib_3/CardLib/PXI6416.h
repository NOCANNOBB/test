#ifndef _CI_PXI6416_DEVICE_
#define _CI_PXI6416_DEVICE_

#include "windows.h"

#pragma once
//////////////////////////////////////////////////////////////////////////
// ������Ϣ
#define PXI6416_Failed(error)				((error)<0)
#define PXI6416_NoError						(0)
#define PXI6416_WarningTimeOut				(-20019)
//////////////////////////////////////////////////////////////////////////
// Device function
#ifdef __cplusplus
extern "C" {
#endif
	LONG __stdcall PXI6416_DeviceOpen(						// open PXI6416 device
								ULONG DeviceNum,			// device logic ID
								HANDLE* pDrvHandle);		// return card object handle

	LONG __stdcall PXI6416_DeviceClose(						// close PXI6416 device 
								HANDLE devHandle);			// card object handle

	LONG __stdcall PXI6416_GetDeviceCount(					// get card count
								ULONG* devCount);			// return card count
		
	LONG __stdcall PXI6416_GetDevicePhyID(					// get card physical id
								HANDLE devHandle,			// card object handle
								ULONG* Physical);			// return card physical id

	LONG __stdcall PXI6416_GetDevicePXISolt(				// ����豸���ڲ�λ
								HANDLE devHandle,
								ULONG* pxiSlotNum);
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI6416_DO_Write(						// ��ȡ���������
								HANDLE devHandle,			// card object handle
								BYTE writeArray[64],		// ����������������
								ULONG arraySize);			// �������С ���������64ͨ��

	LONG __stdcall PXI6416_DO_Read(							// ��ȡ���������״̬
								HANDLE devHandle,			// card object handle
								BYTE readArray[64],			// ����������������
								ULONG arraySize);			// �������С ���������64ͨ��
	//////////////////////////////////////////////////////////////////////////
	LONG __stdcall PXI6416_GetErrorString(					// get error string
								LONG errorCode,				// error code
								char errorString[],			// return error info string 
								ULONG bufferSize);			// errorString buffer size
	//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#ifndef _PXI6416_DLL
	#ifndef _WIN64
		#pragma comment(lib, "PXI6416.lib")
	#else
		#pragma comment(lib, "PXI6416_64.lib")
	#endif
#endif

#endif // _CI_PXI6416_DEVICE_

