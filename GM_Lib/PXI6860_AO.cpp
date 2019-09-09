// PCI6860DCOut.cpp: implementation of the CPCI6860DCOut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PXI6860_AO.h"
#include "CardLib/PXI6860.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPXI6860_AO::CPXI6860_AO()
{
	//m_pIErrLog = NULL;

	//m_pIErrLog = NULL;

	m_hDevice = INVALID_HANDLE_VALUE;
	//m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
	m_hThread = INVALID_HANDLE_VALUE;
	m_bCreateSuccess	= FALSE;

	PDEV_AO psDevAO;

	for (ULONG cardNum=0; cardNum<PXI6860_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];
		psDevAO->cardLgcID = cardNum;

		InitHandle(psDevAO ->hDev);
	}

	InitHandle(m_hMutex);
}

CPXI6860_AO::~CPXI6860_AO()
{
	Release();
}




BOOL CPXI6860_AO::Create(void)
{
	m_hMutex = CreateMutex(NULL, FALSE, MUTEX_IAO);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		_WriteLog("已经创建，不可以重复创建");
		return FALSE;
	}
	ULONG ulCount;

	PXI6860_GetDeviceCount(&ulCount);

	if (ulCount < PXI6860_CARD_COUNT)
	{
		_WriteLog("没有足够板卡，只有%d", ulCount);

		return FALSE;
	}

	try
	{
		PDEV_AO			psDevAO;

		for (ULONG cardNum=0; cardNum<PXI6860_CARD_COUNT; cardNum++)
		{
			psDevAO = &m_sDevAO[cardNum];

			if (_IsErrChk(PXI6860_DeviceOpen(cardNum, &psDevAO->hDev), cardNum)) throw "error";
			PXI6860_GetDevicePXISlot(psDevAO->hDev, &psDevAO->cardSlotID);
		}

		std::sort(m_sDevAO, m_sDevAO+PXI6860_CARD_COUNT, CPXI6860_AO::_CompareLess);

		m_bCreateSuccess = TRUE;
	}
	catch (char* )
	{
		Release();

		return FALSE;
	}

	return TRUE;
}

BOOL CPXI6860_AO::Release(void)
{
	if (!m_bCreateSuccess) return TRUE;

	DelEvent(m_hMutex);

	Stop(0);
	PDEV_AO			psDevAO;

	for (ULONG cardNum=0; cardNum<PXI6860_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];

		if (!IsHandleInvalid(psDevAO->hDev))
		{
			PXI6860_DeviceClose(psDevAO->hDev);
			InitHandle(psDevAO->hDev);
		}
	}

	m_bCreateSuccess	= FALSE;
	return TRUE;
}

BOOL CPXI6860_AO::LoadParam(void)
{
	_IsWarningRet("LoadParam");
	return TRUE;
}

BOOL CPXI6860_AO::Init(void)
{
	_IsWarningRet("Init");
	PDEV_AO			psDevAO;

	for (ULONG cardNum=0; cardNum<PXI6860_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];

		for (ULONG ch=0; ch<PXI6416_MAX_CHAN_AO; ch++)
		{
			if (_IsErrChk(PXI6860_AO_InitChan(psDevAO->hDev, ch, PXI6860_VAL_MIN, PXI6860_VAL_MAX), psDevAO->cardSlotID)) return FALSE;
		}
	}

	return TRUE;
}

int CPXI6860_AO::GetChCount(void)
{
	return PXI6416_MAX_CHAN_AO * PXI6860_CARD_COUNT;
}

BOOL CPXI6860_AO::Start(ULONG)
{
	_IsWarningRet("Start");
	return TRUE;
}

BOOL CPXI6860_AO::Stop(ULONG)
{
	_IsWarningRet("Stop");

	return TRUE;
}

BOOL CPXI6860_AO::WriteAO(ULONG ulChan, double dfVolt)
{
	_IsWarningRet("WriteDC");

	if (ulChan >= (ULONG)GetChCount())
	{
		_WriteLog("WriteDC 通道超限(%d):%d", GetChCount(), ulChan);
		return FALSE;
	}
	if ((dfVolt>PXI6860_VAL_MAX) || (dfVolt<PXI6860_VAL_MIN))
	{
		_WriteLog("WriteDC 输出超限(范围%.0f~%.0f) 当前%.3f", PXI6860_VAL_MIN, PXI6860_VAL_MAX, dfVolt);
		dfVolt = LIMIT_NUM(dfVolt, PXI6860_VAL_MIN, PXI6860_VAL_MAX);
	}

	// 获得卡号
	ULONG cardNum = ulChan / PXI6416_MAX_CHAN_AO;
	// 获得卡对应的通道号
	ULONG cardChan = ulChan % PXI6416_MAX_CHAN_AO;

	PDEV_AO	psDevAO = &m_sDevAO[cardNum];


	LONG retValue = PXI6860_AO_Write(psDevAO->hDev, cardChan, dfVolt);
	BOOL ret = !_IsErrChk(retValue,cardNum);
	return ret;
}
//////////////////////////////////////////////////////////////////////////
BOOL CPXI6860_AO::_IsErrChk(LONG err, ULONG ulCard)
{
	if (PXI6860_Failed(err))
	{
		char errString[128]; 
		PXI6860_GetErrorString(err, errString, 128); 

		_WriteLog("[Dev-%d] %s", ulCard, errString);
		return TRUE;
	}

	return FALSE;
}

void CPXI6860_AO::_WriteLog(LPCSTR lpszInfo, ...)
{
	char strText[1024];
	char strWriteText[2048];
	va_list va;

	va_start(va, lpszInfo);
	::_vstprintf(strText, lpszInfo, va);
	va_end(va);

	sprintf(strWriteText, "[PXI8867] %s", strText);

	if (m_pLogInfo)
	{
		m_pLogInfo->WriteLog(strWriteText);
	}
	else 
	{
		m_LogFile.WriteLog(strWriteText);
	}

}

// 由小到大排序
bool CPXI6860_AO::_CompareLess(CPXI6860_AO::DEV_AO& __left, CPXI6860_AO::DEV_AO& __right)
{
	return (__left.cardSlotID < __right.cardSlotID);
}