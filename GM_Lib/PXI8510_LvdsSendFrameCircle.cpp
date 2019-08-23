#include "stdafx.h"
#include "PXI8510_LvdsSendFrameCircle.h"
#include "PXI8510.h"

CPXI8510_LvdsSendFrameCircleData::CPXI8510_LvdsSendFrameCircleData()
{
	m_logFile.SetFileName(EXCARD_LOGNAME);

	m_iAdd		= 0;
	m_hDevice	= INVALID_HANDLE_VALUE;
	m_pLogInfo	= NULL;
	m_bStart	= FALSE;

	for (ULONG i=0; i<(ULONG)GetChCount(); i++)
	{
		m_sParam[i].rate = 1E+6;
	}
}

CPXI8510_LvdsSendFrameCircleData::~CPXI8510_LvdsSendFrameCircleData()
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}

	TRACE("CPXI8510_LvdsSendFrameCircleData quit!\n");
}

BOOL CPXI8510_LvdsSendFrameCircleData::Create(void)
{
	return TRUE;
}

BOOL CPXI8510_LvdsSendFrameCircleData::Release(void)
{
	return TRUE;	
}

BOOL CPXI8510_LvdsSendFrameCircleData::LoadParam(void)
{
	CWRFileINI fileINI(GM_LIB_INI);

	CString strKey;
	CString strTmp;

	for (ULONG i=0; i<(ULONG)GetChCount(); i++)
	{
		strKey.Format(_T("LVDS_Param_%d"), i);

		fileINI.ReadString(strKey, _T("rate"), _T("1000000"), strTmp.GetBuffer(255), 255);
		strTmp.ReleaseBuffer();
		m_sParam[i].rate = _tcstod(strTmp, NULL);

		fileINI.WriteString(strKey, _T("rate"), strTmp.GetBuffer(0));
	}

	return TRUE;
}

BOOL CPXI8510_LvdsSendFrameCircleData::Init(void)
{
	_IsWarningRet("Init");

	PXI8510_LVDS_SetRowsAndImageElement(m_hDevice, 380, 512);

	for (ULONG chan=0; chan<(ULONG)GetChCount(); chan++)
	{
		PXI8510_LVDS_SendInitChan(m_hDevice, chan, 80, m_sParam[chan].rate, 100000);
		PXI8510_LVDS_SendCfgTrigExtern(m_hDevice, chan);
	}

	return TRUE;
}

int CPXI8510_LvdsSendFrameCircleData::GetChCount(void)
{
	return (SEND_CH_MAX);
}

BOOL CPXI8510_LvdsSendFrameCircleData::Start(ULONG ulChan)
{
	_IsWarningRet("Start");

	if (ulChan>=(ULONG)GetChCount()) return FALSE;

	LONG result;

	result = PXI8510_LVDS_SendInitChan(m_hDevice, ulChan, 80, m_sParam[ulChan].rate, 100000);
	result = PXI8510_LVDS_SendCfgTrigExtern(m_hDevice, ulChan);

	if (m_vcFrame.size() != 0)
	{
		result = PXI8510_LVDS_SendTrigFrame(m_hDevice, ulChan, &m_vcFrame[0], m_vcFrame.size());
		//		_WriteLog("frameLen:%d, %d", m_vcFrame.size(), result);
	}

	if (m_vcCircle.size() != 0)
	{
		PXI8510_LVDS_SendTrigCircle(m_hDevice, ulChan, &m_vcCircle[0], m_vcCircle.size());
		//		_WriteLog("Circle:%d, %d", m_vcCircle.size(), result);
	}

	result = PXI8510_LVDS_SendStart(m_hDevice, ulChan, PXI8510_LVDS_CLK_Continue);

	CString strErr;

	if (__IsErr(result, strErr))
	{ // ´íÎó
		_WriteLog(_T("LVDS Send  Start ´íÎó:%s"), strErr);
		return FALSE;
	}

	m_bStart = TRUE;
	
	return TRUE;
}

BOOL CPXI8510_LvdsSendFrameCircleData::Stop(ULONG ulChan)
{
	_IsWarningRet("Stop");

	LONG result = PXI8510_LVDS_SendStop(m_hDevice, ulChan);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ´íÎó
		_WriteLog(_T("LVDS Send Stop ´íÎó:%s"), strErr);
		return FALSE;
	}

	m_bStart = FALSE;

	return TRUE;
}

// ·¢ËÍÈ¦Ð­Òé 160×Ö½Ú
BOOL CPXI8510_LvdsSendFrameCircleData::SendCircle(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen)
{
	_IsWarningRet("SendCircle");

	LONG result = PXI8510_LVDS_SendTrigCircle(m_hDevice, 0, byWriteBuff, ulWriteLen);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ´íÎó
		_WriteLog(_T("SendTrigCircle ´íÎó:%s"), strErr);
		return FALSE;
	}

	m_vcCircle.resize(ulWriteLen);
	memcpy(&m_vcCircle[0], byWriteBuff, ulWriteLen);

	return TRUE;
}
// ·¢ËÍÖ¡Ð­Òé 80×Ö½Ú
BOOL CPXI8510_LvdsSendFrameCircleData::SendFrame(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen)
{
	_IsWarningRet("SendFrame");

	LONG result = PXI8510_LVDS_SendTrigFrame(m_hDevice, 0, byWriteBuff, ulWriteLen);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ´íÎó
		_WriteLog(_T("SendTrigFrame ´íÎó:%s"), strErr);
		return FALSE;
	}

	m_vcFrame.resize(ulWriteLen);
	memcpy(&m_vcFrame[0], byWriteBuff, ulWriteLen);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
void CPXI8510_LvdsSendFrameCircleData::_WriteLog(LPCSTR lpszInfo, ...)
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

BOOL CPXI8510_LvdsSendFrameCircleData::__IsErr(LONG result, CString& strRetErr)
{
	if (PXI8510_Failed(result))
	{
		char szText[256];
		PXI8510_GetErrorString(result, szText, 256);

		strRetErr = szText;
		
		return TRUE;
	}

	return FALSE;
}