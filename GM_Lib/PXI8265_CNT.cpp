#include "stdafx.h"
#include "PXI8265_CNT.h"
#include "CardLib/PXI8265.h"

CPXI8265_CNT::CPXI8265_CNT(void)
{
	m_hDevice = INVALID_HANDLE_VALUE;
	//m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
	m_hThread = INVALID_HANDLE_VALUE;
	m_bCreateSuccess	= FALSE;
	PDEV_CNT psDevAO;

	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];
		psDevAO->cardLgcID = cardNum;

		InitHandle(psDevAO ->hDev);
	}
}


CPXI8265_CNT::~CPXI8265_CNT(void)
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}



BOOL CPXI8265_CNT::_WriteLog(LPCSTR lpszInfo, ...)
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


BOOL CPXI8265_CNT::_IsErrChk(LONG err, ULONG ulCard)
{
	if (PXI8265_Failed(err))
	{
		char errString[128]; 
		PXI8265_GetErrorString(err, errString, 128); 
		_WriteLog("[Dev-%d] %s", ulCard, errString);
		return TRUE;
	}

	return FALSE;
}

BOOL CPXI8265_CNT::Create()
{

	return TRUE;
}

bool CompareLess(CPXI8265_CNT::DEV_CNT& __left, CPXI8265_CNT::DEV_CNT& __right)
{
	return (__left.cardSlotID < __right.cardSlotID);
}

BOOL CPXI8265_CNT::Release()
{
	
	return TRUE;
}

BOOL CPXI8265_CNT::LoadParam()
{
	return TRUE;
}

BOOL CPXI8265_CNT::Init()
{

	return TRUE;
}

BOOL CPXI8265_CNT::Start(ULONG ulChan)
{
	_IsWarningRet("Start");


	ULONG result;
	if (ulChan >= (ULONG)GetChCount())
	{
		_WriteLog("WriteDC Í¨µÀ³¬ÏÞ(%d):%d", GetChCount(), ulChan);
		return FALSE;
	}
	ULONG chanNum = 0;
	ULONG ulMode = PXI8265_CNT_POSITIVE_0;
	ULONG ulValue = 0;
	ULONG initValue = 100;
	_IsErrChk(PXI8265_CNT_CfgDev(m_hDevice, chanNum, ulMode, initValue),ulChan);
	return TRUE;
}

BOOL CPXI8265_CNT::Stop(ULONG ulChan)
{
	return TRUE;
}


int CPXI8265_CNT::GetChCount()
{
	return PXI8265_MAX_CHAN_CNT;
}

BOOL CPXI8265_CNT::GetdfFreqAnddfdfDutyCycle(ULONG ulChan, double* dfFreq,double* dfdfDutyCycle){

	_IsWarningRet("GetdfFreqAnddfdfDutyCycle");

	ULONG countValue = 0;

	LONG result = PXI8265_CNT_Read(m_hDevice, ulChan,&countValue);
	_IsErrChk(result,ulChan);

	*dfFreq = (double)countValue;

	return TRUE;

}
