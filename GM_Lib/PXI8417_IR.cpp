#include "StdAfx.h"
#include "PXI8417.h"
#include "PXI8417_IR.h"


CPXI8417_IR::CPXI8417_IR(void)
{
	m_hDevice = INVALID_HANDLE_VALUE;
	m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
	m_hThread = INVALID_HANDLE_VALUE;
	memset(m_sIrParam, 0x00, sizeof(IR_PARAM)*PXI8417_MAX_CHAN_IR);
}

CPXI8417_IR::~CPXI8417_IR(void)
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL CPXI8417_IR::_WriteLog(LPCSTR lpszInfo, ...)
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

BOOL CPXI8417_IR::Create()
{
	return TRUE;
}

BOOL CPXI8417_IR::Release()
{
	for (ULONG i=0; i<PXI8417_MAX_CHAN_IR; i++)
	{
		Stop(i);
	}

	return TRUE;
}

BOOL CPXI8417_IR::LoadParam()
{
	return TRUE;
}

BOOL CPXI8417_IR::Init()
{

	return TRUE;
}

BOOL CPXI8417_IR::Start(ULONG ulChan)
{
	if (m_hThread != INVALID_HANDLE_VALUE) return TRUE;
	ULONG result;
	m_crLock.Lock();

	for (int chan=0; chan<PXI8417_MAX_CHAN_IR; chan++)
	{
		result = PXI8417_IR_Start(m_hDevice, chan);
		if (result != PXI8417_NoError)
		{
			_WriteLog("IR ch %d初始化失败!", chan);
			m_crLock.Unlock();
			return FALSE;
		}
	}

	m_hThread = ExCreateThread(GetIntPulseWidthThread, this);
	Sleep(100);

	m_crLock.Unlock();

	return TRUE;
}

BOOL CPXI8417_IR::Stop(ULONG ulChan)
{
	if (m_hThread == INVALID_HANDLE_VALUE)	return TRUE;

	m_bRun = FALSE;
	ExReleaseThread(m_hThread, 1000);

	ULONG result;

	for (int chan=0; chan<PXI8417_MAX_CHAN_IR; chan++)
	{
		result = PXI8417_IR_Stop(m_hDevice , chan);
		if (result != PXI8417_NoError)
		{
			_WriteLog("通道%d关闭使能失败!", chan);
			return FALSE;
		}
	}

	return TRUE;
}

int CPXI8417_IR::GetChCount()
{
	return PXI8417_MAX_CHAN_IR;
}

BOOL CPXI8417_IR::GetIR(ULONG ulChan, PBOOL pbSts, double* pdfPulseWidth, PULONG pulCount)
{
	if (ulChan >= PXI8417_MAX_CHAN_IR) return FALSE;

	*pbSts = m_sIrParam[ulChan].bIntSts;

	if (m_sIrParam[ulChan].bIntSts)
	{
		*pdfPulseWidth = m_sIrParam[ulChan].dfPulseWidthMS;
		*pulCount = m_sIrParam[ulChan].ulIntCount;
	}

	return TRUE;
}

BOOL CPXI8417_IR::ClrIRSts(ULONG ulChan)
{
	if (ulChan >= PXI8417_MAX_CHAN_IR) return FALSE;

	m_sIrParam[ulChan].bIntSts = FALSE;
	return TRUE;
}

unsigned int __stdcall CPXI8417_IR::GetIntPulseWidthThread(PVOID pVoid)
{
	CPXI8417_IR* pThreadIR = (CPXI8417_IR*)pVoid;
	ULONG ulIntSrc = 0;
	LONG lIntCount = 0;		// 内部中断计数
	ULONG ulPulseWidth = 0; // 脉冲宽度

	pThreadIR->m_bRun = TRUE;

	while (pThreadIR->m_bRun)
	{
		for (int i=0; i<PXI8417_MAX_CHAN_IR; i++)
		{
			PXI8417_IR_GetPulseWidth(pThreadIR->m_hDevice, i, &ulPulseWidth);

			if (ulPulseWidth != 0)
			{
				pThreadIR->m_sIrParam[i].ulIntCount++;
				pThreadIR->m_sIrParam[i].dfPulseWidthMS = ((double)ulPulseWidth) * 1E-3;
				pThreadIR->m_sIrParam[i].bIntSts = TRUE;
			}
		}
		Sleep(1);
	}

	TRACE("%s\n", __FUNCDNAME__);
	return 1;
}