// PCI6860DCOut.cpp: implementation of the CPCI6860DCOut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PXI8265_AO.h"
#include "CardLib/PXI8265.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPXI8265_AO::CPXI8265_AO()
{
	m_pLogInfo = NULL;

	PDEV_AO psDevAI;

	for (ULONG cardNum=0; cardNum<CARD_COUNT; cardNum++)
	{
		psDevAI = &m_sDevAO[cardNum];
		psDevAI->cardLgcID	= cardNum;
		//psDevAI->bThreadRun = FALSE;

		InitHandle(psDevAI->hDev);
		//InitHandle(psDevAI->hThreadReadAI);
		//InitHandle(psDevAI->hThreadProcessing);

		
	}
	m_bCreateSuccess	= FALSE;
}

CPXI8265_AO::~CPXI8265_AO()
{
	Release();
}




BOOL CPXI8265_AO::Create(void)
{
	m_bCreateSuccess = TRUE;
	return TRUE;
}

BOOL CPXI8265_AO::Release(void)
{
	m_bCreateSuccess	= FALSE;
	return TRUE;
}

BOOL CPXI8265_AO::LoadParam(void)
{
	_IsWarningRet("LoadParam");
	return TRUE;
}


BOOL CPXI8265_AO::Init(void)
{
	return TRUE;

}

int CPXI8265_AO::GetChCount(void)
{
	return MAX_CHAN_AO * CARD_COUNT;
}

BOOL CPXI8265_AO::Start(ULONG ulChan)
{
	_IsWarningRet("Start");
	
	ULONG result;
	


	
	if (ulChan >= (ULONG)GetChCount())
	{
		_WriteLog("WriteDC 通道超限(%d):%d", GetChCount(), ulChan);
		return FALSE;
	}

	//for (int chan=0; chan<PXI8265_MAX_CHAN_AO; chan++)
	{

		result = PXI8265_AO_InitChan(m_hDevice,ulChan, VAL_MIN, VAL_MAX);
		if (result != PXI8265_NoError)
		{
			_WriteLog("AO ch %d初始化失败!", ulChan);
			return FALSE;
		}
	}

	


	return TRUE;
}

BOOL CPXI8265_AO::Stop(ULONG)
{
	_IsWarningRet("Stop");

	return TRUE;
}

BOOL CPXI8265_AO::WriteAO(ULONG ulChan, double dfVolt)
{
	_IsWarningRet("WriteDC");

	if (ulChan >= (ULONG)GetChCount())
	{
		_WriteLog("WriteDC 通道超限(%d):%d", GetChCount(), ulChan);
		return FALSE;
	}
	if ((dfVolt>VAL_MAX) || (dfVolt<VAL_MIN))
	{
		_WriteLog("WriteDC 输出超限(范围%.0f~%.0f) 当前%.3f",  VAL_MIN, VAL_MAX, dfVolt);
		dfVolt = LIMIT_NUM(dfVolt, VAL_MIN, VAL_MAX);
	}

	// 获得卡号
	ULONG cardNum = ulChan / MAX_CHAN_AO;
	// 获得卡对应的通道号
	ULONG cardChan = ulChan % MAX_CHAN_AO;

	PDEV_AO	psDevAO = &m_sDevAO[cardNum];


	PXI8265_AO_Write(psDevAO->hDev, cardChan, 1,TRUE,&dfVolt,1,10);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOL CPXI8265_AO::_IsErrChk(LONG err, ULONG ulCard)
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

void CPXI8265_AO::_WriteLog(LPCSTR lpszInfo, ...)
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
bool CPXI8265_AO::_CompareLess(CPXI8265_AO::DEV_AO& __left, CPXI8265_AO::DEV_AO& __right)
{
	return (__left.cardSlotID < __right.cardSlotID);
}