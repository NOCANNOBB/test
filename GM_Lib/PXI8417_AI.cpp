#include "StdAfx.h"
#include "PXI8417.h"
#include "PXI8417_AI.h"

using namespace std;

CPXI8417_AI::CPXI8417_AI(void)
{
	m_hDevice = INVALID_HANDLE_VALUE;
	m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;


	m_sThread.hDev				=
	m_sThread.hThreadProcessing = 
	m_sThread.hThreadReadAI		= INVALID_HANDLE_VALUE;

	m_sThread.pClass	= this;
	m_bIsStart			= FALSE;

	for (ULONG i=0; i<SEG_MAX; i++)
	{
		m_sThread.sArrSegAI[i].readArray	= new LONG [SINGLE_LEN* MAX_CHAN_AI + 10];
		m_sThread.sArrSegAI[i].arrayLen		= SINGLE_LEN * MAX_CHAN_AI;
	}

	m_sThread.vcVolt.resize(MAX_CHAN_AI);

}

CPXI8417_AI::~CPXI8417_AI(void)
{
	Release();

	for (ULONG i=0; i<SEG_MAX; i++)
	{
		delete[] m_sThread.sArrSegAI[i].readArray;
		m_sThread.sArrSegAI[i].arrayLen	= 0;
	}
}

BOOL CPXI8417_AI::_WriteLog(LPCSTR lpszInfo, ...)
{
	char szText[1024];
	char szWriteText[2048];
	va_list va;
	va_start(va, lpszInfo);
	wvsprintfA(szText, lpszInfo, va);
	va_end(va);

	sprintf(szWriteText, "[PXI8417-AI] %s", szText);

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

BOOL CPXI8417_AI::Create()
{
	return TRUE;
}

BOOL CPXI8417_AI::Release()
{

	Stop();

	return TRUE;
}

BOOL CPXI8417_AI::LoadParam()
{
	return TRUE;
}

BOOL CPXI8417_AI::Init()
{
	LONG			lResult;
	PDEV_AI			psDevAI;

	m_sThread.hDev = m_hDevice;

	psDevAI = &m_sThread;

	lResult = PXI8417_AI_InitChan(
		psDevAI->hDev,
		0,
		MAX_CHAN_AI - 1,
		PXI8417_AI_B_5_V,
		PXI8417_AI_RSE);
	if (_IsErrChk(lResult)) goto errorExit;

	lResult = PXI8417_AI_CfgTiming(
		psDevAI->hDev,
		PXI8417_SRCCLK_Default,
		1000,		// 目前的最大频率 5200 * 48 = 249600
		PXI8417_ContSamps,
		400000); // 开辟1M空间
	if (_IsErrChk(lResult)) goto errorExit;

	return TRUE;

errorExit:
	return FALSE;
}

BOOL CPXI8417_AI::Start(ULONG )
{
	if (m_bIsStart) return TRUE;

	m_sThread.lastSegIndex		= -1;

	m_sThread.hThreadReadAI		= ExCreateThread(_ThreadReadAI,		&m_sThread);
	m_sThread.hThreadProcessing	= ExCreateThread(_ThreadProcessing, &m_sThread);

	m_bIsStart = TRUE;
	return TRUE;
}

BOOL CPXI8417_AI::Stop(ULONG )
{
	m_sThread.bThreadRun = FALSE;
	ExReleaseThread(m_sThread.hThreadProcessing,	1000);
	ExReleaseThread(m_sThread.hThreadReadAI,		1000);

	m_bIsStart = FALSE;
	return TRUE;
}

int CPXI8417_AI::GetChCount()
{
	return MAX_CHAN_AI;
}

// 这里返回的是电压值，单位是V
BOOL CPXI8417_AI::ReadOneDC(ULONG ulChan, double* dfVolt)
{
	*dfVolt = 0.0;

	if (ulChan >= (ULONG)GetChCount())
	{
		_WriteLog("ReadOne 通道号超过了最大值(%d):%d", GetChCount(), ulChan);
		return FALSE;
	}

	*dfVolt = m_sThread.vcVolt[ulChan];

	return TRUE;
}

BOOL CPXI8417_AI::_IsErrChk(LONG err)
{
	if (PXI8417_Failed(err))
	{
		char errString[128]; 
		PXI8417_GetErrorString(err, errString, 128); 
		_WriteLog("%s", errString);
		return TRUE;
	}

	return FALSE;
}

UINT __stdcall CPXI8417_AI::_ThreadReadAI(PVOID pData)
{
	PDEV_AI				psDevAI		= (PDEV_AI)pData;
	CPXI8417_AI*		pClass		= psDevAI->pClass;
	READ_AI_INFO*		sArrSegAI	= psDevAI->sArrSegAI;
	PREAD_AI_INFO		psReadAI	= NULL;
	ULONG				ulSegIndex	= 0;
	LONG				lResult;
	ULONG				perChanRead;

	lResult = PXI8417_AI_Start(psDevAI->hDev);
	if (pClass->_IsErrChk(lResult))
	{
		pClass->_WriteLog("线程没有启动");
		return 0;
	}

	psDevAI->bThreadRun = TRUE;

	while (psDevAI->bThreadRun)
	{
		psReadAI = &sArrSegAI[ulSegIndex];

		lResult = PXI8417_AI_Read(psDevAI->hDev,
			CPXI8417_AI::SINGLE_LEN, 
			&perChanRead,
			psReadAI->readArray,
			psReadAI->arrayLen,
			PXI8417_AI_GroupByChannel,
			10);

		pClass->_IsErrChk(lResult);

		psReadAI->singleLen		= perChanRead;
		psDevAI->lastSegIndex	= ulSegIndex;
		ulSegIndex = (ulSegIndex + 1) % SEG_MAX;
	}

	PXI8417_AI_Stop(psDevAI->hDev);

	return 0;
}

double	CPXI8417_AI::_GetArrayVolt(LONG readArray[], ULONG arrayLen)
{
	double dfResult = 0.0;

#if 1
	arrayLen /= 10;
	vector<LONG> vcArray(readArray, readArray+arrayLen);

	std::sort(vcArray.begin(), vcArray.end(), less<LONG>() );
	// 分3份，去掉头尾，取中间
	ULONG ulSumLen = arrayLen / 3;
	double dfSum = 0.0;

	for (ULONG i=0; i<ulSumLen; i++)
	{ 
		dfSum += (double)vcArray[i+ulSumLen];
	}

	LONG lLsb = (LONG)(dfSum /(double)ulSumLen);
#else
	LONG lLsb = _FilteArray(readArray, arrayLen);
#endif
	ULONG ulTmp;

	PXI8417_AI_ConvLsbToVolt(PXI8417_AI_B_5_V,
		&lLsb, 1,
		&dfResult, 1, &ulTmp);

	return dfResult;
}

UINT __stdcall CPXI8417_AI::_ThreadProcessing(PVOID pData)
{
	PDEV_AI				psDevAI		= (PDEV_AI)pData;
	CPXI8417_AI*		pClass		= psDevAI->pClass;
	PREAD_AI_INFO		psReadAI	= NULL;

	psDevAI->bThreadRun = TRUE;
	ULONG ulBkSegIndex = psDevAI->lastSegIndex ;
	while (psDevAI->bThreadRun)
	{
		if (psDevAI->lastSegIndex == ulBkSegIndex)
		{ // 如果没有数据则等待
			Sleep(1);
			continue;
		}

		ulBkSegIndex = psDevAI->lastSegIndex;

		psReadAI	= &psDevAI->sArrSegAI[psDevAI->lastSegIndex];

		for (ULONG chanNum=0; chanNum<MAX_CHAN_AI; chanNum++)
		{
			psDevAI->vcVolt[chanNum]	= pClass->_GetArrayVolt(&psReadAI->readArray[chanNum*psReadAI->singleLen], psReadAI->singleLen);
		}
		Sleep(1);
	}

	return 0;
}
