#include "stdafx.h"
#include "PXI8510_Total.h"
#include "PXI8510.h"

CPXI8510_Total::CPXI8510_Total()
{
	m_iAdd = 0;
	m_hDevice = INVALID_HANDLE_VALUE;
	m_logFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
}

CPXI8510_Total::~CPXI8510_Total()
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		CPXI8510_LvdsRecv::Release();
		CPXI8510_LvdsSendFrameCircleData::Release();
		Release();

		CPXI8510_LvdsRecv::SetHandle(INVALID_HANDLE_VALUE);
		CPXI8510_LvdsSendFrameCircleData::SetHandle(INVALID_HANDLE_VALUE);
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL CPXI8510_Total::Create(void)
{
	if (m_iAdd > 0) 
	{
		m_iAdd ++;
		return TRUE;
	}

	m_iAdd ++;

	ULONG result = PXI8510_DeviceOpen(0, &m_hDevice);

	if (result != PXI8510_NoError)
	{
		m_iAdd--;
		_WriteLog("PXI8510_DeviceOpen Error!");
		return FALSE;
	}

	CPXI8510_LvdsRecv::SetHandle(m_hDevice);
	CPXI8510_LvdsSendFrameCircleData::SetHandle(m_hDevice);

	return TRUE;
}

BOOL CPXI8510_Total::Release(void)
{
	if (m_iAdd > 0)
	{
		m_iAdd --;
		return TRUE;
	}

	m_iAdd = 0;

	ULONG result = PXI8510_DeviceClose(m_hDevice);

	if (result != PXI8510_NoError)
	{
		_WriteLog("PXI8510_DeviceClose Error!");
		return FALSE;
	}

	InitHandle(m_hDevice);

	return TRUE;	
}

void CPXI8510_Total::SetErrorLog(ILogInfo* log) 
{
	m_pLogInfo = log;
	CPXI8510_LvdsRecv::SetErrorLog(m_pLogInfo);
	CPXI8510_LvdsSendFrameCircleData::SetErrorLog(m_pLogInfo);
}

void CPXI8510_Total::_WriteLog(LPCSTR lpszInfo, ...)
{
	char strText[1024];
	char strWriteText[2048];
	va_list va;

	va_start(va, lpszInfo);
	::_vstprintf(strText, lpszInfo, va);
	va_end(va);

	sprintf(strWriteText, "[PXI8510] %s", strText);

	if (m_pLogInfo)
	{
		m_pLogInfo->WriteLog(strWriteText);
	}
	else 
	{
		m_logFile.WriteInfo(strWriteText);
	}
}
