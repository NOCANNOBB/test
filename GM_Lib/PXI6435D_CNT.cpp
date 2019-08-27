#include "stdafx.h"
#include "PXI6435D_CNT.h"
#include "CardLib/PXI6435D.h"

PXI6435D_CNT::PXI6435D_CNT(void)
{
	m_hDevice = INVALID_HANDLE_VALUE;
	//m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
	m_hThread = INVALID_HANDLE_VALUE;
	m_bCreateSuccess	= FALSE;
	PDEV_CNT psDevAO;

	for (ULONG cardNum=0; cardNum<PXI6435D_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];
		psDevAO->cardLgcID = cardNum;

		InitHandle(psDevAO ->hDev);
	}

	InitHandle(m_hMutex);
}


PXI6435D_CNT::~PXI6435D_CNT(void)
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}



BOOL PXI6435D_CNT::_WriteLog(LPCSTR lpszInfo, ...)
{
	char szText[1024];
	char szWriteText[2048];
	va_list va;
	va_start(va, lpszInfo);
	wvsprintfA(szText, lpszInfo, va);
	va_end(va);

	sprintf(szWriteText, "[PXI6416] %s", szText);

	if (m_pLogInfo != NULL)
	{
		m_pLogInfo->WriteLog(szWriteText);
	}

	return TRUE;
}


BOOL PXI6435D_CNT::_IsErrChk(LONG err, ULONG ulCard)
{
	if (PXI6435D_Failed(err))
	{
		char errString[128]; 
		PXI6435D_GetErrorString(err, errString, 128); 
		_WriteLog("[Dev-%d] %s", ulCard, errString);
		return TRUE;
	}

	return FALSE;
}

BOOL PXI6435D_CNT::Create()
{
	m_hMutex = CreateMutex(NULL, FALSE, MUTEX_ICNT);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		_WriteLog("已经创建，不可以重复创建");
		return FALSE;
	}
	ULONG ulCount;

	PXI6435D_GetDeviceCount(&ulCount);

	if (ulCount < PXI6435D_CARD_COUNT)
	{
		_WriteLog("没有足够板卡，只有%d", ulCount);

		return FALSE;
	}
	try
	{
		PDEV_CNT		psDevAO;

		for (ULONG cardNum=0; cardNum<PXI6435D_CARD_COUNT; cardNum++)
		{
			psDevAO = &m_sDevAO[cardNum];

			if (_IsErrChk(PXI6435D_DeviceOpen(cardNum, &psDevAO->hDev), cardNum)) throw "error";
			PXI6435D_GetDevicePXISlot(psDevAO->hDev, &psDevAO->cardSlotID);
		}

		std::sort(m_sDevAO, m_sDevAO+PXI6435D_CARD_COUNT, CompareLess);

		m_bCreateSuccess = TRUE;
	}
	catch (char* )
	{
		Release();

		return FALSE;
	}

	return TRUE;
}

bool CompareLess(PXI6435D_CNT::DEV_CNT& __left, PXI6435D_CNT::DEV_CNT& __right)
{
	return (__left.cardSlotID < __right.cardSlotID);
}

BOOL PXI6435D_CNT::Release()
{
	if (!m_bCreateSuccess) return TRUE;

	DelEvent(m_hMutex);

	Stop(0);
	PDEV_CNT			psDevAO;

	for (ULONG cardNum=0; cardNum<PXI6435D_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];

		if (!IsHandleInvalid(psDevAO->hDev))
		{
			PXI6435D_DeviceClose(psDevAO->hDev);
			InitHandle(psDevAO->hDev);
		}
	}

	m_bCreateSuccess	= FALSE;
	return TRUE;
}

BOOL PXI6435D_CNT::LoadParam()
{
	return TRUE;
}

BOOL PXI6435D_CNT::Init()
{

	return TRUE;
}

BOOL PXI6435D_CNT::Start(ULONG ulChan)
{
	_IsWarningRet("Release");

	
	ULONG result;
	

	//for (int chan=0; chan <PXI6435D_MAX_CHAN_CNT; chan++)
	{

		LONG result = PXI6435D_CNT_InFreqChan(m_hDevice, ulChan, PXI6435D_MIN_VALUE, PXI6435D_MAX_VALUE, PXI6435D_EDGE_VALUE, PXI6435D_MASETIME_VALUE);
		if (_IsErrChk(result,0)) return FALSE;


		result = PXI6435D_CNT_Start(m_hDevice, ulChan);
		if (_IsErrChk(result,0))
		{
			_WriteLog("PXI6435D_CNT ch %d初始化失败!", ulChan);

			return FALSE;
		}
	}
	return TRUE;
}

BOOL PXI6435D_CNT::Stop(ULONG ulChan)
{
	return TRUE;
}


int PXI6435D_CNT::GetChCount()
{
	return PXI6435D_MAX_CHAN_CNT;
}

BOOL PXI6435D_CNT::GetdfFreqAnddfdfDutyCycle(ULONG ulChan, double* dfFreq,double* dfdfDutyCycle){

	_IsWarningRet("GetdfFreqAnddfdfDutyCycle");
	LONG result = PXI6435D_CNT_ReadF64(m_hDevice, ulChan, dfFreq, dfdfDutyCycle, 0.1);
	if (result == PXI6435D_WarningTimeOut)
	{
		
		_WriteLog("PXI6435D_WarningTimeOut!", ulChan);
		return FALSE;
	}
	else{

		PXI6435D_CNT_Stop(m_hDevice,ulChan);
		return TRUE;
	}
	
}
