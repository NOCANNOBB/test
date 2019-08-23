#include "stdafx.h"
#include "PXI8510_LvdsRecv.h"
#include "PXI8510.h"

CPXI8510_LvdsRecv::CPXI8510_LvdsRecv()
{
	m_iAdd = 0;
	m_hDevice = INVALID_HANDLE_VALUE;
	m_logFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
}

CPXI8510_LvdsRecv::~CPXI8510_LvdsRecv()
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL CPXI8510_LvdsRecv::Create(void)
{
	return TRUE;
}

BOOL CPXI8510_LvdsRecv::Release(void)
{
	return TRUE;	
}

BOOL CPXI8510_LvdsRecv::LoadParam(void)
{
	return TRUE;
}

BOOL CPXI8510_LvdsRecv::Init(void)
{
	_IsWarningRet("Init");

	for (ULONG chan=0; chan<(ULONG)GetChCount(); chan++)
	{
		PXI8510_LVDS_SetRecvTransferMode(m_hDevice, chan, PXI8510_TRANSF_MODE_DMA);
		PXI8510_LVDS_RecvInitChan(m_hDevice, chan, 2000000);
	}

	return TRUE;
}

int CPXI8510_LvdsRecv::GetChCount(void)
{
	return (PXI8510_RECV_CH_MAX);
}

BOOL CPXI8510_LvdsRecv::Start(ULONG ulChan)
{
	_IsWarningRet("Start");

	LONG result = PXI8510_LVDS_RecvStart(m_hDevice, ulChan);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // 错误
		_WriteLog(_T("LVDS Start 错误:%s"), strErr);
		return FALSE;
	}
	
	return TRUE;
}

BOOL CPXI8510_LvdsRecv::Stop(ULONG ulChan)
{
	_IsWarningRet("Stop");

	LONG result = PXI8510_LVDS_RecvStop(m_hDevice, ulChan);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // 错误
		_WriteLog(_T("LVDS Stop 错误:%s"), strErr);
		return FALSE;
	}

	return TRUE;

}

BOOL CPXI8510_LvdsRecv::Read(
					ULONG ulChan,
					BYTE pbyReadBuff[],
					ULONG& cbSize,		// 读取个数，如果超时，返回实际数量，如果缓冲区NULL，返回内部已读数据长度
					double dfTimeOut)	// 读取超时时间
{
	_IsWarningRet("Stop");

	ULONG ulRetLen = 0;
	LONG result = PXI8510_LVDS_Recv(m_hDevice, ulChan, cbSize, &ulRetLen, pbyReadBuff, cbSize, dfTimeOut);
	CString strErr;

	cbSize = ulRetLen;
	
	if (result == PXI8510_WarningTimeOut)
	{
		TRACE("time out\n");
		return TRUE;
	}

// 	if (__IsErr(result, strErr))
// 	{ // 错误
// 		_WriteLog(_T("LVDS Stop 错误:%s"), strErr);
// 		TRACE("LVDS Stop 错误:%s", strErr);
// 		return FALSE;
// 	}

	TRACE("read:%d, xx %d xxx\n", cbSize, ulRetLen);
	cbSize = ulRetLen;
	return TRUE;
}

void CPXI8510_LvdsRecv::_WriteLog(LPCSTR lpszInfo, ...)
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

BOOL CPXI8510_LvdsRecv::__IsErr(LONG result, CString& strRetErr)
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