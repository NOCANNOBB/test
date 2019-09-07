#include "StdAfx.h"
#include "PXI8417.h"
#include "PXI8417_1PPS.h"

CPXI8417_1PPS::CPXI8417_1PPS(void)
{
	m_hDevice = INVALID_HANDLE_VALUE;
	m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
	ZeroMemory(m_chanInit, sizeof(m_chanInit));
}

CPXI8417_1PPS::~CPXI8417_1PPS(void)
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL CPXI8417_1PPS::_WriteLog(LPCSTR lpszInfo, ...)
{
	char szText[1024];
	char szWriteText[2048];
	va_list va;
	va_start(va, lpszInfo);
	wvsprintfA(szText, lpszInfo, va);
	va_end(va);

	sprintf(szWriteText, "[PXI8417] %s", szText);

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

BOOL CPXI8417_1PPS::Create()
{
	SelectOutSrc(IBase1PPS::SRC_SIM);
	return TRUE;
}

BOOL CPXI8417_1PPS::Release()
{
	for (ULONG i=0; i<(ULONG)GetChCount(); i++)
	{
		Stop(i);
	}

	return TRUE;
}

BOOL CPXI8417_1PPS::LoadParam()
{
	return TRUE;
}

BOOL CPXI8417_1PPS::Init()
{

	return TRUE;
}

BOOL CPXI8417_1PPS::Start(ULONG ulChan)
{
	_IsWarningRet("Start");
	if (ulChan >= (ULONG)GetChCount()) return FALSE;

	ULONG result = PXI8417_1PPS_Start(m_hDevice, ulChan);

	if (result != PXI8417_NoError)
	{
		_WriteLog("通道%d 输出失败!", ulChan);
		return FALSE;
	}

	m_chanInit[ulChan] = TRUE;

	return TRUE;
}

BOOL CPXI8417_1PPS::Stop(ULONG ulChan)
{
	_IsWarningRet("Stop");
	if (ulChan >= (ULONG)GetChCount()) return FALSE;
	if (!m_chanInit[ulChan]) return FALSE;

	m_chanInit[ulChan] = TRUE;

	ULONG result = PXI8417_1PPS_Stop(m_hDevice, ulChan);

	if (result != PXI8417_NoError)
	{
		_WriteLog("通道%d 停止失败!", ulChan);
		return FALSE;
	}

	return TRUE;
}

int CPXI8417_1PPS::GetChCount()
{
	return PXI8417_MAX_CHAN_1PPS;
}

// 获得秒脉冲值
BOOL CPXI8417_1PPS::GetPulseCount(ULONG* pulPulse)
{
	_IsWarningRet("GetPulseCount");
	if (pulPulse == NULL) return FALSE;

	LONG result = PXI8417_1PPS_GetPulseCount(m_hDevice, pulPulse);

	if (result != PXI8417_NoError)
	{
		_WriteLog("获得秒脉冲值!");
		return FALSE;
	}

	return TRUE;
}
// 秒脉冲复位，这时是时间值
BOOL CPXI8417_1PPS::Reset()
{
	_IsWarningRet("Reset");

	LONG result = PXI8417_1PPS_ClearPulseCount(m_hDevice);

	if (result != PXI8417_NoError)
	{
		_WriteLog("清除值错误");
		return FALSE;
	}
	return TRUE;
}

// 选择妙脉冲输出源
BOOL CPXI8417_1PPS::SelectOutSrc(ULONG outSrc)
{
	_IsWarningRet("SelectOutSrc");

	LONG result = PXI8417_1PPS_Init(m_hDevice, outSrc);

	if (result != PXI8417_NoError)
	{
		_WriteLog("选择输出源错误");
		return FALSE;
	}
	return TRUE;
}

// 读出时间
BOOL CPXI8417_1PPS::Read(
				  ULONG*	bIsValid,			// 时间是否有效，GPS在未定位时为0，定位后1，模拟常1
				  ULONG*	dateHex,			// 16进制日期,例如2017年01月20日，反馈值为0x200117, 模拟输出从2000年1月1日开始
				  ULONG*  timeHex)			// 16进制时间,例如15:35:32,反馈值为153532,注意GPS反馈的时间为UTC时间，模拟从00:00:00开始计时
{
	_IsWarningRet("Read");

	LONG result = PXI8417_1PPS_Read(m_hDevice, bIsValid, dateHex, timeHex);

	if (result != PXI8417_NoError)
	{
		_WriteLog("读出时间错误");
		return FALSE;
	}
	return TRUE;
}

BOOL CPXI8417_1PPS::__IsErr(LONG result, CString& strRetErr)
{
	if (PXI8417_Failed(result))
	{
		char szText[256];
		PXI8417_GetErrorString(result, szText, 256);

		strRetErr = szText;
		return TRUE;
	}

	return FALSE;
}