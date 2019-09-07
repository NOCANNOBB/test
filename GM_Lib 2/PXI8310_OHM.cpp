#include "StdAfx.h"
#include "WRFileINI.h"
#include "PXI8310_OHM.h"

CPXI8310_OHM::CPXI8310_OHM()
{
	m_hDevice = INVALID_HANDLE_VALUE;
	m_logFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
}

CPXI8310_OHM::~CPXI8310_OHM()
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}

	TRACE("CPXI8310_OHM quit!\n");
}

BOOL CPXI8310_OHM::Create(void)
{
	m_hMutex = CreateMutex(NULL, FALSE, MUTEX_IOHM);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		_WriteLog("已经创建，不可以重复创建");
		return FALSE;
	}
	ULONG ulCount;

	PXI8310_GetDeviceCount(&ulCount);

	if (ulCount < PXI8310_CARD_COUNT)
	{
		_WriteLog("没有足够板卡，只有%d", ulCount);

		return FALSE;
	}

	try
	{
		if (_IsErrChk(PXI8310_DeviceOpen(0, &m_hDevice), 0)) throw "error";

		m_bCreateSuccess = TRUE;

		TRACE("PXI8310_DeviceOpen Success!\n");
	}
	catch (char* )
	{
		Release();

		return FALSE;
	}

	return TRUE;
}

BOOL CPXI8310_OHM::Release(void)
{
	if (!m_bCreateSuccess) return TRUE;

	DelEvent(m_hMutex);

	Stop(0);

	if (!IsHandleInvalid(m_hDevice))
	{
		PXI8310_DeviceClose(m_hDevice);
		InitHandle(m_hDevice);
	}

	m_bCreateSuccess = FALSE;
	
	return TRUE;	
}

BOOL CPXI8310_OHM::LoadParam(void)
{
	return TRUE;
}

BOOL CPXI8310_OHM::Init(void)
{
	_IsWarningRet("Init");

	for (ULONG chan=0; chan<(ULONG)GetChCount(); chan++)
	{
		PXI8310_OHM_InitChan(m_hDevice, chan, FALSE);
	}

	TRACE("PXI8310_OHM_InitChan Success!\n");
	return TRUE;
}

int CPXI8310_OHM::GetChCount(void)
{
	return (PXI8310_CARD_COUNT*PXI8310_OHM_CH_MAX);
}

BOOL CPXI8310_OHM::Start(ULONG ulChan)
{
	return TRUE;
}

BOOL CPXI8310_OHM::Stop(ULONG ulChan)
{
	return TRUE;
}

BOOL CPXI8310_OHM::OutputOHM(ULONG ulChan, double dfOHM)
{
	LONG result = PXI8310_OHM_Write(m_hDevice, ulChan, dfOHM);
	if (PXI8310_Failed(result))
	{
		return FALSE;
	}

	return TRUE;
}

void CPXI8310_OHM::_WriteLog(LPCSTR lpszInfo, ...)
{
	char strText[1024];
	char strWriteText[2048];
	va_list va;

	va_start(va, lpszInfo);
	::_vstprintf(strText, lpszInfo, va);
	va_end(va);

	sprintf(strWriteText, "[PXI8310] %s", strText);

	if (m_pLogInfo)
	{
		m_pLogInfo->WriteLog(strWriteText);
	}
	else 
	{
		m_logFile.WriteInfo(strWriteText);
	}
}

BOOL CPXI8310_OHM::_IsErrChk(LONG err, ULONG ulCard)
{
	if (PXI8310_Failed(err))
	{
		char errString[128]; 
		PXI8310_GetErrorString(err, errString, 128); 

		_WriteLog("[Dev-%d] %s", ulCard, errString);
		return TRUE;
	}

	return FALSE;
}