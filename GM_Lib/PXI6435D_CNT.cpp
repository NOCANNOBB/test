#include "stdafx.h"
#include "PXI6435D_CNT.h"
#include "CardLib/PXI6435D.h"
#include "UserDef.h"

PXI6435D_CNT::PXI6435D_CNT(void)
{
	m_hDevice = INVALID_HANDLE_VALUE;
	//m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
	m_hThread = INVALID_HANDLE_VALUE;
	m_bCreateSuccess	= FALSE;
	PDEV_CNT psDevAO;
	PCHAN_CNT psChanCNT;
	InitializeCriticalSection(&m_ValueListSEC);
	m_ReadCntVec.reserve(PXI6435D_MAX_CHAN_CNT);

	for (ULONG cardNum=0; cardNum<PXI6435D_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];
		
		psDevAO->cardLgcID = cardNum;
		psDevAO->pClass = this;
		InitHandle(psDevAO ->hDev);
		for (ULONG chanNum = 0; chanNum < PXI6435D_MAX_CHAN_CNT; chanNum++)
		{
			psChanCNT = &m_sCHANCNT[chanNum];
			psChanCNT->pClass = this;
			psChanCNT->ulChan = chanNum;
			psChanCNT->bThreadRun = FALSE;
			psChanCNT->hDev = psDevAO ->hDev;

		}
	}

	

	InitHandle(m_hMutex);
}


PXI6435D_CNT::~PXI6435D_CNT(void)
{
	Release();
	DeleteCriticalSection(&m_ValueListSEC);
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
	for (ULONG cardNum=0; cardNum<PXI6435D_CARD_COUNT; cardNum++){
		for (ULONG chanNUM = 0; chanNUM < PXI6435D_MAX_CHAN_CNT; chanNUM++)
		{
			m_sCHANCNT[chanNUM].bThreadRun = FALSE;
			ExReleaseThread(m_sCHANCNT[cardNum].hThreadReadCNT,		1000);
		}
	}
	

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
	_IsWarningRet("Start");

	PDEV_CNT		psDevAO;
	ULONG cardNum = ulChan / PXI6435D_CARD_COUNT;
	ULONG chanNum = ulChan % PXI6435D_MAX_CHAN_CNT;
	
	//psDevAO = &m_sDevAO[cardNum];
	for (ULONG cardNum = 0; cardNum < PXI6435D_CARD_COUNT;cardNum++)
	{
		for (ULONG chanNum=0; chanNum<PXI6435D_MAX_CHAN_CNT; chanNum++)
		{
			m_sCHANCNT[chanNum].hDev = m_sDevAO[cardNum].hDev;
			m_sCHANCNT[chanNum].hThreadReadCNT = ExCreateThread(_ThreadReadCNT,&m_sCHANCNT[chanNum]);
			
		}
	}
	

	m_bIsStart = TRUE;
	return TRUE;
}


void PXI6435D_CNT::InserValueToList(double dfValue,ULONG ulChan){
	if (m_ReadCntVec.size() <= ulChan)
	{
		m_ReadCntVec.push_back(dfValue);
	}
	else
	{
		m_ReadCntVec.at(ulChan) = dfValue;
	}
}

double PXI6435D_CNT::GetRandomValue(){
	srand(time(0));
	return rand();
}


UINT __stdcall PXI6435D_CNT::_ThreadReadCNT(PVOID pData)
{
	PCHAN_CNT				psCHAN		= (PCHAN_CNT)pData;
	PXI6435D_CNT*		pClass		= psCHAN->pClass;
	//READ_AI_INFO*		sArrSegAI	= psDevAI->sArrSegAI;
	LONG result = PXI6435D_CNT_InFreqChan(psCHAN->hDev, psCHAN->ulChan, PXI6435D_MIN_VALUE, PXI6435D_MAX_VALUE, PXI6435D_EDGE_VALUE, PXI6435D_MASETIME_VALUE);

	result = PXI6435D_CNT_Start(psCHAN->hDev, psCHAN->ulChan);
	psCHAN->bThreadRun = TRUE;
	BOOL IsRead = FALSE;
	while (psCHAN->bThreadRun)
	{
		double dfFreq = 0;
		double dfDutycycle = 0;
		if (IsRead)
		{
			LONG result = PXI6435D_CNT_InFreqChan(psCHAN->hDev, psCHAN->ulChan, PXI6435D_MIN_VALUE, PXI6435D_MAX_VALUE, PXI6435D_EDGE_VALUE, PXI6435D_MASETIME_VALUE);

			result = PXI6435D_CNT_Start(psCHAN->hDev, psCHAN->ulChan);
		}
		IsRead = FALSE;
		LONG result =  PXI6435D_CNT_ReadF64(psCHAN->hDev, psCHAN->ulChan, &dfFreq, &dfDutycycle, 0.1);
		dfFreq =pClass->GetRandomValue();
		if (result == PXI6435D_WarningTimeOut)
		{
			IsRead = TRUE;
			PXI6435D_CNT_Stop(psCHAN->hDev,psCHAN->ulChan);
			__try{
				EnterCriticalSection(&(pClass->m_ValueListSEC));
				pClass->InserValueToList(dfFreq,psCHAN->ulChan);
			}
			__finally{
				LeaveCriticalSection(&(pClass->m_ValueListSEC));
			}
			PXI6435D_CNT_Stop(psCHAN->hDev,psCHAN->ulChan);
		}
		if (dfFreq != 0)
		{
			IsRead = TRUE;
			__try{
				EnterCriticalSection(&(pClass->m_ValueListSEC));
				pClass->InserValueToList(dfFreq,psCHAN->ulChan);
			}
			__finally{
				LeaveCriticalSection(&(pClass->m_ValueListSEC));
			}
			PXI6435D_CNT_Stop(psCHAN->hDev,psCHAN->ulChan);
		}

		//Sleep(1000 / (pClass->m_DataRate / PXI8265_SINGLE_LEN));
		Sleep(1);

	}

	

	return 0;
}

BOOL PXI6435D_CNT::Stop(ULONG ulChan)
{

	m_bIsStart = FALSE;

	return TRUE;
}


int PXI6435D_CNT::GetChCount()
{
	return PXI6435D_MAX_CHAN_CNT;
}

BOOL PXI6435D_CNT::GetdfFreqAnddfdfDutyCycle(ULONG ulChan, double* dfFreq,double* dfdfDutyCycle){
	__try{
		
		EnterCriticalSection(&m_ValueListSEC);
		if (m_ReadCntVec.size() > ulChan)
		{
			*dfFreq = m_ReadCntVec.at(ulChan);
		}
		else{
			*dfFreq = 0;
		}
		
	}
	__finally{
		LeaveCriticalSection(&m_ValueListSEC);
	}
	return TRUE;

}
