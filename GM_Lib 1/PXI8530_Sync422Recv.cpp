#include "stdafx.h"
#include "PXI8530_Sync422Recv.h"
#include "PXI8530.h"

CPXI8530_Sync422Recv::CPXI8530_Sync422Recv()
{
	m_iAdd = 0;
	m_hDevice = INVALID_HANDLE_VALUE;
	m_logFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;

	m_bStart = FALSE;
}

CPXI8530_Sync422Recv::~CPXI8530_Sync422Recv()
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL CPXI8530_Sync422Recv::Create(void)
{
	return TRUE;
}

BOOL CPXI8530_Sync422Recv::Release(void)
{
	Stop();
	return TRUE;	
}

BOOL CPXI8530_Sync422Recv::LoadParam(void)
{
	return TRUE;
}

BOOL CPXI8530_Sync422Recv::Init(void)
{
	_IsWarningRet("Init");

	PXI8530_SYNC422_SetRecvTransferMode(m_hDevice, 0, PXI8530_TRANSF_MODE_DMA);
	PXI8530_SYNC422_RecvInitChan(m_hDevice, 0, 100000);

	return TRUE;
}

int CPXI8530_Sync422Recv::GetChCount(void)
{
	return (1);
}

BOOL CPXI8530_Sync422Recv::Start(ULONG ulChan)
{
	_IsWarningRet("Start");

	LONG result = PXI8530_SYNC422_RecvStart(m_hDevice, 0);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ´íÎó
		_WriteLog(_T("Sync422 Start ´íÎó:%s"), strErr);
		return FALSE;
	}

	m_bStart = TRUE;

	return TRUE;
}

BOOL CPXI8530_Sync422Recv::Stop(ULONG ulChan)
{
	if (!m_bStart) return TRUE;
	_IsWarningRet("Stop");

	LONG result = PXI8530_SYNC422_RecvStop(m_hDevice, 0);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ´íÎó
		_WriteLog(_T("Sync422 Stop ´íÎó:%s"), strErr);
		return FALSE;
	}

	m_bStart = FALSE;

	return TRUE;
}

BOOL CPXI8530_Sync422Recv::Recv(ULONG ulChan, BYTE byReadBuff[], ULONG& cbSize, double timeOut)
{
	ULONG ulReadLen = cbSize;
	ULONG ulRetLen = 0;
	cbSize = 0;
	

	_IsWarningRet("Recv");

	LONG result = PXI8530_SYNC422_Recv(m_hDevice, 0, ulReadLen, &ulRetLen, byReadBuff, cbSize, timeOut);
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
void CPXI8530_Sync422Recv::_WriteLog(LPCSTR lpszInfo, ...)
{
	char strText[1024];
	char strWriteText[2048];
	va_list va;

	va_start(va, lpszInfo);
	::_vstprintf(strText, lpszInfo, va);
	va_end(va);

	sprintf(strWriteText, "[PXI8265] %s", strText);

	if (m_pLogInfo)
	{
		m_pLogInfo->WriteLog(strWriteText);
	}
	else 
	{
		m_logFile.WriteInfo(strWriteText);
	}
}

BOOL CPXI8530_Sync422Recv::__IsErr(LONG result, CString& strRetErr)
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