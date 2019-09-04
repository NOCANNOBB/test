#include "stdafx.h"
#include "PXI8265_Total.h"


CPXI8265_Total::CPXI8265_Total(void)
{
	m_iAdd = 0;
	m_hDevice = INVALID_HANDLE_VALUE;
	
	m_pLogInfo = NULL;
}


CPXI8265_Total::~CPXI8265_Total(void)
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		CPXI8265_DO::Release();
		CPXI8265_AI::Release();
		CPXI8265_CNT::Release();
		CPXI8265_AO::Release();

		Release();

		CPXI8265_AO::SetHandle(INVALID_HANDLE_VALUE);
		CPXI8265_CNT::SetHandle(INVALID_HANDLE_VALUE);
		CPXI8265_AI::SetHandle(INVALID_HANDLE_VALUE);
		CPXI8265_DO::SetHandle(INVALID_HANDLE_VALUE);

		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL CPXI8265_Total::Create()
{
	if (m_iAdd > 0) 
	{
		m_iAdd ++;
		return TRUE;
	}

	m_iAdd ++;

	PXI8265_DeviceOpen(0, &m_hDevice);
	//m_hDevice = 0;
	if (m_hDevice == INVALID_HANDLE_VALUE)
	{
		m_iAdd--;
		_WriteLog("8265_Total_DeviceOpen Error!");
		return FALSE;
	}

	CPXI8265_AO::SetHandle(m_hDevice);
	CPXI8265_CNT::SetHandle(m_hDevice);
	CPXI8265_AI::SetHandle(m_hDevice);
	CPXI8265_DO::SetHandle(m_hDevice);

	return TRUE;
}

BOOL CPXI8265_Total::Release()
{
	if (m_iAdd > 0)
	{
		m_iAdd --;
		return TRUE;
	}

	m_iAdd = 0;

	ULONG result = PXI8265_DeviceClose(m_hDevice);
	if (result != PXI8265_NoError)
	{
		_WriteLog("PXI8265_DeviceClose Error!");
		return FALSE;
	}

	return TRUE;
}

BOOL CPXI8265_Total::_WriteLog(LPCSTR lpszInfo, ...)
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
		m_LogFile.WriteLog(szWriteText);
	}

	return TRUE;
}

