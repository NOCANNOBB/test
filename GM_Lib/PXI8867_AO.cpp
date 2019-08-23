// PCI6860DCOut.cpp: implementation of the CPCI6860DCOut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WRFileINI.h"
#include "PXI8867_AO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPXI8867_AO::CPXI8867_AO():m_logFile(EXCARD_LOGNAME)
{
	m_pIErrLog = NULL;

	m_pIErrLog = NULL;

	PDEV_AO psDevAO;

	for (ULONG cardNum=0; cardNum<PXI8867_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];
		psDevAO->cardLgcID = cardNum;

		InitHandle(psDevAO ->hDev);
	}

	InitHandle(m_hMutex);
}

CPXI8867_AO::~CPXI8867_AO()
{
	Release();
}

BOOL CPXI8867_AO::Create(void)
{
	m_hMutex = CreateMutex(NULL, FALSE, MUTEX_IDADC_1);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		_WriteLog("已经创建，不可以重复创建");
		return FALSE;
	}
	ULONG ulCount;

	PXI8867_GetDeviceCount(&ulCount);

	if (ulCount < PXI8867_CARD_COUNT)
	{
		_WriteLog("没有足够板卡，只有%d", ulCount);

		return FALSE;
	}

	try
	{
		PDEV_AO			psDevAO;

		for (ULONG cardNum=0; cardNum<PXI8867_CARD_COUNT; cardNum++)
		{
			psDevAO = &m_sDevAO[cardNum];

			if (_IsErrChk(PXI8867_DeviceOpen(cardNum, &psDevAO->hDev), cardNum)) throw "error";
			PXI8867_GetDevicePXISlot(psDevAO->hDev, &psDevAO->cardSlotID);
		}

		std::sort(m_sDevAO, m_sDevAO+PXI8867_CARD_COUNT, CPXI8867_AO::_CompareLess);

		m_bCreateSuccess = TRUE;
	}
	catch (char* )
	{
		Release();

		return FALSE;
	}

	return TRUE;
}

BOOL CPXI8867_AO::Release(void)
{
	if (!m_bCreateSuccess) return TRUE;

	DelEvent(m_hMutex);

	Stop(0);
	PDEV_AO			psDevAO;

	for (ULONG cardNum=0; cardNum<PXI8867_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];

		if (!IsHandleInvalid(psDevAO->hDev))
		{
			PXI8867_DeviceClose(psDevAO->hDev);
			InitHandle(psDevAO->hDev);
		}
	}

	m_bCreateSuccess	= FALSE;
	return TRUE;
}

BOOL CPXI8867_AO::LoadParam(void)
{
	_IsWarningRet("LoadParam");
	return TRUE;
}

BOOL CPXI8867_AO::Init(void)
{
	_IsWarningRet("Init");
	PDEV_AO			psDevAO;

	for (ULONG cardNum=0; cardNum<PXI8867_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];

		for (ULONG ch=0; ch<PXI8867_CH_COUNT; ch++)
		{
			if (_IsErrChk(PXI8867_AO_InitChan(psDevAO->hDev, ch, PXI8867_VAL_MIN, PXI8867_VAL_MAX), psDevAO->cardSlotID)) return FALSE;
		}
	}

	return TRUE;
}

int CPXI8867_AO::GetChCount(void)
{
	return PXI8867_CH_COUNT * PXI8867_CARD_COUNT;
}

BOOL CPXI8867_AO::Start(ULONG)
{
	_IsWarningRet("Start");
	return TRUE;
}

BOOL CPXI8867_AO::Stop(ULONG)
{
	_IsWarningRet("Stop");

	return TRUE;
}

BOOL CPXI8867_AO::WriteDC(ULONG ulChan, double dfVolt)
{
	_IsWarningRet("WriteDC");

	if (ulChan >= (ULONG)GetChCount())
	{
		_WriteLog("WriteDC 通道超限(%d):%d", GetChCount(), ulChan);
		return FALSE;
	}
	if ((dfVolt>PXI8867_VAL_MAX) || (dfVolt<PXI8867_VAL_MIN))
	{
		_WriteLog("WriteDC 输出超限(范围%.0f~%.0f) 当前%.3f", PXI8867_VAL_MIN, PXI8867_VAL_MAX, dfVolt);
		dfVolt = LIMIT_NUM(dfVolt, PXI8867_VAL_MIN, PXI8867_VAL_MAX);
	}

	// 获得卡号
	ULONG cardNum = ulChan / PXI8867_CH_COUNT;
	// 获得卡对应的通道号
	ULONG cardChan = ulChan % PXI8867_CH_COUNT;

	PDEV_AO	psDevAO = &m_sDevAO[cardNum];


	PXI8867_AO_Write(psDevAO->hDev, cardChan, dfVolt);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOL CPXI8867_AO::_IsErrChk(LONG err, ULONG ulCard)
{
	if (PXI8867_Failed(err))
	{
		char errString[128]; 
		PXI8867_GetErrorString(err, errString, 128); 

		_WriteLog("[Dev-%d] %s", ulCard, errString);
		return TRUE;
	}

	return FALSE;
}

void CPXI8867_AO::_WriteLog(LPCSTR lpszInfo, ...)
{
	char strText[1024];
	char strWriteText[2048];
	va_list va;

	va_start(va, lpszInfo);
	::_vstprintf(strText, lpszInfo, va);
	va_end(va);

	sprintf(strWriteText, "[PXI8867] %s", strText);

	if (m_pIErrLog)
	{
		m_pIErrLog->WriteLog(strWriteText);
	}
	else 
	{
		m_logFile.WriteInfo(strWriteText);
	}
}

// 由小到大排序
bool CPXI8867_AO::_CompareLess(CPXI8867_AO::DEV_AO& __left, CPXI8867_AO::DEV_AO& __right)
{
	return (__left.cardSlotID < __right.cardSlotID);
}