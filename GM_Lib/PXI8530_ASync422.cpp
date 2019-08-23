#include "stdafx.h"
#include "PXI8530_ASync422.h"
#include "PXI8530.h"

CPXI8530_ASync422::CPXI8530_ASync422()
{
	for (ULONG i=0; i<CARD_COUNT; i++)
	{
		m_hDevice[i] = INVALID_HANDLE_VALUE;
	}

	m_logFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;

	for (int i=0; i<(int)GetChCount(); i++)
	{
		m_bArrStart[i] = FALSE;
	}
	
}

CPXI8530_ASync422::~CPXI8530_ASync422()
{
	for (ULONG i=0; i<CARD_COUNT; i++)
	{
		if (m_hDevice[i] != INVALID_HANDLE_VALUE)
		{
			Release();
			m_hDevice[i] = INVALID_HANDLE_VALUE;
		}
	}

	TRACE("CPXI8530_ASync422 quit!\n");
}

BOOL CPXI8530_ASync422::Create(void)
{
	return TRUE;
}

BOOL CPXI8530_ASync422::Release(void)
{
	Stop();
	return TRUE;	
}

BOOL CPXI8530_ASync422::LoadParam(void)
{
	CWRFileINI fileINI(GM_LIB_INI);
	CString strTmp, strKey;

	for (ULONG ch=0; ch<(ULONG)GetChCount(); ch++)
	{
		strKey.Format(_T("ASYNC422_CH%d_RATE"), ch);
		fileINI.ReadString("ASYNC422_CTRL", strKey, _T("1"), strTmp.GetBuffer(256), 256);
		strTmp.ReleaseBuffer();
		m_ulRateIndex[ch] = _tcstoul(strTmp, NULL, 10);

		strKey.Format(_T("ASYNC422_CH%d_PARITY"), ch);
		fileINI.ReadString("ASYNC422_CTRL", strKey, _T("0"), strTmp.GetBuffer(256), 256);
		strTmp.ReleaseBuffer();
		m_ulParityBit[ch] = _tcstoul(strTmp, NULL, 10);
	}

	return TRUE;
}

BOOL CPXI8530_ASync422::Init(void)
{
	_IsWarningRet("Init");

	return TRUE;
}

int CPXI8530_ASync422::GetChCount(void)
{
	return (CARD_COUNT*ASYNC422_CH_COUNT);
}

BOOL CPXI8530_ASync422::Start(ULONG ulChan)
{
	_IsWarningRet("Start");
	LONG result = 0;

	// 获得卡号
	ULONG cardNum = ulChan / ASYNC422_CH_COUNT;
	// 获得卡对应的通道号
	ULONG cardChan = ulChan % ASYNC422_CH_COUNT;

	result = PXI8530_ASYNC422_SetReadTransferMode(m_hDevice[cardNum], cardChan, PXI8530_TRANSF_MODE_DMA);
	result = PXI8530_ASYNC422_InitChan(m_hDevice[cardNum], cardChan, m_ulRateIndex[ulChan], m_ulParityBit[ulChan]);
	result = PXI8530_ASYNC422_Start(m_hDevice[cardNum], cardChan);

	CString strErr;

	if (__IsErr(result, strErr))
	{ // 错误
		_WriteLog(_T("ASync422 Start 错误:%s"), strErr);
		return FALSE;
	}

	m_bArrStart[ulChan] = TRUE;

	return TRUE;
}

BOOL CPXI8530_ASync422::Stop(ULONG ulChan)
{
	if (!m_bArrStart[ulChan]) return TRUE;
	_IsWarningRet("Stop");

	// 获得卡号
	ULONG cardNum = ulChan / ASYNC422_CH_COUNT;
	// 获得卡对应的通道号
	ULONG cardChan = ulChan % ASYNC422_CH_COUNT;

	LONG result = PXI8530_ASYNC422_Stop(m_hDevice[cardNum], cardChan);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // 错误
		_WriteLog(_T("ASync422 Stop 错误:%s"), strErr);
		return FALSE;
	}

	m_bArrStart[ulChan] = FALSE;
	return TRUE;
}

BOOL CPXI8530_ASync422::Write(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteSize)
{
	_IsWarningRet("Write");

	// 获得卡号
	ULONG cardNum = ulChan / ASYNC422_CH_COUNT;
	// 获得卡对应的通道号
	ULONG cardChan = ulChan % ASYNC422_CH_COUNT;

	if (m_hDevice[cardNum] != INVALID_HANDLE_VALUE)
	{
		LONG result = PXI8530_ASYNC422_Write(m_hDevice[cardNum], cardChan, byWriteBuff, ulWriteSize);

		CString strErr;

		if (result == PXI8530_WarningTimeOut) return TRUE;

		if (__IsErr(result, strErr))
		{ // 错误
			_WriteLog(_T("Write 错误:%s"), strErr);
			return FALSE;
		}
	}
	else
	{
		_WriteLog(_T("设备不在 chan%d"), ulChan);
		return FALSE;
	}

	return TRUE;
	
}

BOOL CPXI8530_ASync422::Read(ULONG ulChan, BYTE byReadBuff[], ULONG& cbSize, double timeOut)
{
	ULONG ulReadLen = cbSize;
	ULONG ulRetLen = 0;
	cbSize = 0;

	_IsWarningRet("Read");
	
	// 获得卡号
	ULONG cardNum = ulChan / ASYNC422_CH_COUNT;
	// 获得卡对应的通道号
	ULONG cardChan = ulChan % ASYNC422_CH_COUNT;

	if (m_hDevice[cardNum] != INVALID_HANDLE_VALUE)
	{
		LONG result = PXI8530_ASYNC422_Read(m_hDevice[cardNum], cardChan, byReadBuff, ulReadLen, &ulRetLen, timeOut);
		cbSize = ulRetLen;

		CString strErr;

		if (result == PXI8530_WarningTimeOut) return TRUE;

		if (__IsErr(result, strErr))
		{ // 错误
			_WriteLog(_T("Read 错误:%s"), strErr);
			return FALSE;
		}
	}
	else
	{
		_WriteLog(_T("设备不在 chan%d"), ulChan);
		return FALSE;
	}
	

	return TRUE;
	
}

//////////////////////////////////////////////////////////////////////////
void CPXI8530_ASync422::_WriteLog(LPCSTR lpszInfo, ...)
{
	char strText[1024];
	char strWriteText[2048];
	va_list va;

	va_start(va, lpszInfo);
	::_vstprintf(strText, lpszInfo, va);
	va_end(va);

	sprintf(strWriteText, "[PXI8530 ASync422] %s", strText);

	if (m_pLogInfo)
	{
		m_pLogInfo->WriteLog(strWriteText);
	}
	else 
	{
		m_logFile.WriteInfo(strWriteText);
	}
}

BOOL CPXI8530_ASync422::__IsErr(LONG result, CString& strRetErr)
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