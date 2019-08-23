#include "stdafx.h"
#include "PXI8417_Total.h"
#include "PXI8417.h"

CPXI8417_Total::CPXI8417_Total()
{
	m_iAdd = 0;
	m_hDevice = INVALID_HANDLE_VALUE;
	m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
}

CPXI8417_Total::~CPXI8417_Total()
{

	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		CPXI8417_IR::Release();
		CPXI8417_OC::Release();
		CPXI8417_1PPS::Release();
		CPXI8417_AI::Release();

		Release();

		CPXI8417_IR::SetHandle(INVALID_HANDLE_VALUE);
		CPXI8417_OC::SetHandle(INVALID_HANDLE_VALUE);
		CPXI8417_1PPS::SetHandle(INVALID_HANDLE_VALUE);
		CPXI8417_AI::SetHandle(INVALID_HANDLE_VALUE);

		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL CPXI8417_Total::Create()
{
	if (m_iAdd > 0) 
	{
		m_iAdd ++;
		return TRUE;
	}

	m_iAdd ++;

	PXI8417_DeviceOpen(0, &m_hDevice);

	if (m_hDevice == INVALID_HANDLE_VALUE)
	{
		m_iAdd--;
		_WriteLog("PXI8417_DeviceOpen Error!");
		return FALSE;
	}

	CPXI8417_IR::SetHandle(m_hDevice);
	CPXI8417_OC::SetHandle(m_hDevice);
	CPXI8417_1PPS::SetHandle(m_hDevice);
	CPXI8417_AI::SetHandle(m_hDevice);

	return TRUE;
}

BOOL CPXI8417_Total::Release()
{
	if (m_iAdd > 0)
	{
		m_iAdd --;
		return TRUE;
	}

	m_iAdd = 0;

	ULONG result = PXI8417_DeviceClose(m_hDevice);
	if (result != PXI8417_NoError)
	{
		_WriteLog("PXI8417_DeviceClose Error!");
		return FALSE;
	}

	return TRUE;
}

BOOL CPXI8417_Total::_WriteLog(LPCSTR lpszInfo, ...)
{
	char szText[1024];
	char szWriteText[2048];
	va_list va;
	va_start(va, lpszInfo);
	wvsprintfA(szText, lpszInfo, va);
	va_end(va);

	sprintf(szWriteText, "[AllRS] %s", szText);

	if (m_pLogInfo != NULL)
	{
		m_pLogInfo->WriteLog(szWriteText);
	}
	else 
	{
		m_LogFile.WriteInfo(szWriteText);
	}

	return TRUE;
}