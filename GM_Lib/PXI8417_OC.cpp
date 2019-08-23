#include "StdAfx.h"
#include "PXI8417.h"
#include "PXI8417_OC.h"

CPXI8417_OC::CPXI8417_OC(void)
{
	m_hDevice = INVALID_HANDLE_VALUE;
	m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;

}

CPXI8417_OC::~CPXI8417_OC(void)
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL CPXI8417_OC::_WriteLog(LPCSTR lpszInfo, ...)
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

BOOL CPXI8417_OC::Create()
{
	return TRUE;
}

BOOL CPXI8417_OC::Release()
{
	return TRUE;
}

BOOL CPXI8417_OC::LoadParam()
{
	return TRUE;
}

BOOL CPXI8417_OC::Init()
{

	return TRUE;
}

BOOL CPXI8417_OC::Start(ULONG ulChan)
{

	return TRUE;
}

BOOL CPXI8417_OC::Stop(ULONG ulChan)
{
	return TRUE;
}

int CPXI8417_OC::GetChCount()
{
	return PXI8417_MAX_CHAN_OC;
}

BOOL CPXI8417_OC::SetOC(ULONG ulChan, double pulseWidthMS)
{
	if (ulChan >= PXI8417_MAX_CHAN_OC) return FALSE;

	ULONG ulPulseWidth = (ULONG)(pulseWidthMS * 1E+3);

	ULONG result = PXI8417_OC_OutputPulseWidth(m_hDevice, ulChan, ulPulseWidth);

	if (result != PXI8417_NoError)
	{
		_WriteLog("PXI2514_SetDeviceOCPulseWidth Error!");
		return FALSE;
	}

	return TRUE;
}
