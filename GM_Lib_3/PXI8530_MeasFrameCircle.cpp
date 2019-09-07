#include "stdafx.h"
#include "PXI8530_MeasFrameCircle.h"
#include "PXI8530.h"

CPXI8530_MeasFrameCircle::CPXI8530_MeasFrameCircle()
{
	for (ULONG i=0; i<CARD_COUNT; i++)
	{
		m_hDevice[i] = INVALID_HANDLE_VALUE;
		m_bStart[i] = FALSE;
	}

	m_iAdd = 0;
	m_logFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
}

CPXI8530_MeasFrameCircle::~CPXI8530_MeasFrameCircle()
{
	for (ULONG i=0; i<CARD_COUNT; i++)
	{
		if (m_hDevice[i] != INVALID_HANDLE_VALUE)
		{
			Release();
			m_hDevice[i] = INVALID_HANDLE_VALUE;
		}
	}
}

BOOL CPXI8530_MeasFrameCircle::Create(void)
{
	return TRUE;
}

BOOL CPXI8530_MeasFrameCircle::Release(void)
{
	Stop();
	return TRUE;	
}

BOOL CPXI8530_MeasFrameCircle::LoadParam(void)
{
	return TRUE;
}

BOOL CPXI8530_MeasFrameCircle::Init(void)
{
	_IsWarningRet("Init");
	return TRUE;
}

int CPXI8530_MeasFrameCircle::GetChCount(void)
{
	return (1);
}

BOOL CPXI8530_MeasFrameCircle::Start(ULONG ulChan)
{
	_IsWarningRet("Start");

	LONG result = PXI8530_MEAS_Start(m_hDevice[ulChan]);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ´íÎó
		_WriteLog(_T("MEAS_Frame Start ´íÎó:%s"), strErr);
		return FALSE;
	}

	m_bStart[ulChan] = TRUE;

	return TRUE;
}

BOOL CPXI8530_MeasFrameCircle::Stop(ULONG ulChan)
{
	if (!m_bStart[ulChan]) return TRUE;
	_IsWarningRet("Stop");

	LONG result = PXI8530_MEAS_Stop(m_hDevice[ulChan]);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ´íÎó
		_WriteLog(_T("MEAS_Frame Stop ´íÎó:%s"), strErr);
		return FALSE;
	}

	m_bStart[ulChan] = FALSE;

	return TRUE;
}

BOOL CPXI8530_MeasFrameCircle::SetCircleTime(ULONG timeData)
{
	_IsWarningRet("SetCircleTime");

	for (ULONG i=0; i<CARD_COUNT; i++)
	{
		if (m_hDevice[i] != INVALID_HANDLE_VALUE)
		{
			PXI8530_MEAS_Circle_SetTime(m_hDevice[i], timeData);
		}
	}
	return TRUE;
}

BOOL CPXI8530_MeasFrameCircle::SetFrameTime(ULONG timeData)
{
	_IsWarningRet("SetFrameTime");

	for (ULONG i=0; i<CARD_COUNT; i++)
	{
		if (m_hDevice[i] != INVALID_HANDLE_VALUE)
		{
			PXI8530_MEAS_Frame_SetTime(m_hDevice[i], timeData);
		}
	}
	return TRUE;
}

BOOL CPXI8530_MeasFrameCircle::Read(
					   ULONG  ulChan,			// Í¨µÀºÅ
					   __int64	readArray[],	// ¶ÁÈ¡Êý×é
					   ULONG&	cbSize,			// ¶ÁÈ¡³¤¶È
					   double timeOut)
{
	_IsWarningRet("FrameRead");
	ULONG ulReadLen = cbSize;
	ULONG ulRetLen = 0;

	LONG result = PXI8530_MEAS_Read(m_hDevice[ulChan], readArray, ulReadLen, &ulRetLen, timeOut);
	CString strErr;

	cbSize = ulRetLen;

	if (result == PXI8530_WarningTimeOut) return TRUE;

	if (__IsErr(result, strErr))
	{ // ´íÎó
		_WriteLog(_T("Recv ´íÎó:%s"), strErr);
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void CPXI8530_MeasFrameCircle::_WriteLog(LPCSTR lpszInfo, ...)
{
	char strText[1024];
	char strWriteText[2048];
	va_list va;

	va_start(va, lpszInfo);
	::_vstprintf(strText, lpszInfo, va);
	va_end(va);

	sprintf(strWriteText, "[PXI8530 422 Recv] %s", strText);

	if (m_pLogInfo)
	{
		m_pLogInfo->WriteLog(strWriteText);
	}
	else 
	{
		m_logFile.WriteInfo(strWriteText);
	}
}

BOOL CPXI8530_MeasFrameCircle::__IsErr(LONG result, CString& strRetErr)
{
	if (PXI8530_Failed(result))
	{
		char szText[256];
		PXI8530_GetErrorString(result, szText, 256);

		strRetErr = szText;

		return TRUE;
	}

	return FALSE;
}