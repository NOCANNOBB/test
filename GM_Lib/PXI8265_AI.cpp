//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WRFileINI.h"
#include "ProjectDef.h"
#include "PXI8265_AI.h"
#include "PXI8265.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define PXI8265_SINGLE_LEN		(100)

CPXI8265_AI::CPXI8265_AI():m_logFile(EXCARD_LOGNAME)
{
	m_pIErrLog = NULL;

	PDEV_AI psDevAI;

	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		psDevAI = &m_sDevAI[cardNum];
		psDevAI->cardLgcID	= cardNum;
		psDevAI->bThreadRun = FALSE;

		InitHandle(psDevAI->hDev);
		InitHandle(psDevAI->hThreadReadAI);
		InitHandle(psDevAI->hThreadProcessing);

		for (ULONG i=0; i<PXI8265_SEG_MAX; i++)
		{
			psDevAI->sArrSegAI[i].readArray		= new LONG [PXI8265_SINGLE_LEN*PXI8265_CHAN_COUNT + 10];
			psDevAI->sArrSegAI[i].arrayLen		= PXI8265_SINGLE_LEN * PXI8265_CHAN_COUNT;
		}

		// ���ٵ�ѹ ��Чֵ�ռ�
		psDevAI->vcVolt.resize(PXI8265_CHAN_COUNT);
		psDevAI->vcVoltRMS.resize(PXI8265_CHAN_COUNT);
		psDevAI->pClass  = this;
	}

	m_bIsStart			= FALSE;
	m_bCreateSuccess	= FALSE;
}

CPXI8265_AI::~CPXI8265_AI()
{
	Release();

	PDEV_AI psDevAI;

	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		psDevAI = &m_sDevAI[cardNum];

		for (ULONG i=0; i<PXI8265_SEG_MAX; i++)
		{
			delete[] psDevAI->sArrSegAI[i].readArray;
			psDevAI->sArrSegAI[i].readArray = NULL;
			psDevAI->sArrSegAI[i].arrayLen	= 0;
		}
	}

}
// ��С��������
bool CompareLess(CPXI8265_AI::DEV_AI& __left, CPXI8265_AI::DEV_AI& __right)
{
	return (__left.cardSlotID < __right.cardSlotID);
}

BOOL CPXI8265_AI::Create(void)
{
	m_hMutex = CreateMutex(NULL, FALSE, MUTEX_IAD);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		DelEvent(m_hMutex);

		_WriteLog("�Ѿ��������������ظ�����");
		return FALSE;
	}

	PDEV_AI			psDevAI;

	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		psDevAI = &m_sDevAI[cardNum];

		if (_IsErrChk(PXI8265_DeviceOpen(cardNum, &psDevAI->hDev), cardNum)) goto errorExit;
		PXI8265_GetDevicePXISolt(psDevAI->hDev, &psDevAI->cardSlotID);
	}

	std::sort(m_sDevAI, m_sDevAI+PXI8265_CARD_COUNT, CompareLess);

	m_bCreateSuccess = TRUE;
	return TRUE;
errorExit:

	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		psDevAI = &m_sDevAI[cardNum];

		if (!IsHandleInvalid(psDevAI->hDev))
		{
			PXI8265_DeviceClose(psDevAI->hDev);
			InitHandle(psDevAI->hDev);
		}
	}

	return FALSE;
}

BOOL CPXI8265_AI::Release(void)
{
	if (!m_bCreateSuccess) return TRUE;

	DelEvent(m_hMutex);

	Stop(0);

	PDEV_AI			psDevAI;
	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		psDevAI = &m_sDevAI[cardNum];

		if (!IsHandleInvalid(psDevAI->hDev))
		{
			PXI8265_DeviceClose(psDevAI->hDev);
			InitHandle(psDevAI->hDev);
		}
	}

	m_bCreateSuccess	= FALSE;
	return TRUE;
}

BOOL CPXI8265_AI::LoadParam(void)
{
	_IsWarningRet("LoadParam");

	return TRUE;
}

BOOL CPXI8265_AI::Init(void)
{
	_IsWarningRet("Init");

	LONG			lResult;
	PDEV_AI			psDevAI;
	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		psDevAI = &m_sDevAI[cardNum];

		lResult = PXI8265_AI_InitChan(
							psDevAI->hDev,
							0,
							PXI8265_CHAN_COUNT - 1,
							PXI8265_AI_B_5_V,
							PXI8265_AI_RSE);
		if (_IsErrChk(lResult, psDevAI->cardSlotID)) goto errorExit;

		lResult = PXI8265_AI_CfgTiming(
							psDevAI->hDev,
							PXI8265_SRCCLK_Default,
							1000,		// Ŀǰ�����Ƶ�� 5200 * 48 = 249600
							PXI8265_ContSamps,
							400000); // ����1M�ռ�
		if (_IsErrChk(lResult, psDevAI->cardSlotID)) goto errorExit;
	}
	return TRUE;

errorExit:
	return FALSE;

}

int CPXI8265_AI::GetChCount(void)
{
	return (PXI8265_CARD_COUNT * PXI8265_CHAN_COUNT);
}

BOOL CPXI8265_AI::Start(ULONG ulChan)
{
	_IsWarningRet("Start");

	if (m_bIsStart) return TRUE;

	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		m_sDevAI[cardNum].lastSegIndex		= -1;

		m_sDevAI[cardNum].hThreadReadAI		= ExCreateThread(_ThreadReadAI,		&m_sDevAI[cardNum]);
		m_sDevAI[cardNum].hThreadProcessing	= ExCreateThread(_ThreadProcessing, &m_sDevAI[cardNum]);
	}

	m_bIsStart = TRUE;

	return TRUE;
}

BOOL CPXI8265_AI::Stop(ULONG ulChan)
{
	_IsWarningRet("Stop");

	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		m_sDevAI[cardNum].bThreadRun = FALSE;
		ExReleaseThread(m_sDevAI[cardNum].hThreadProcessing,	1000);
		ExReleaseThread(m_sDevAI[cardNum].hThreadReadAI,		1000);
	}

	m_bIsStart = FALSE;

	return TRUE;
}

BOOL CPXI8265_AI::ReadOneDC(ULONG ulChan, double* dfAD)
{
	_IsWarningRet("ReadOneDC");
	
	*dfAD = 0.0;
	if (ulChan >= (ULONG)GetChCount())
	{
		_WriteLog("ReadOne ͨ���ų��������ֵ(%d):%d", GetChCount(), ulChan);
		return FALSE;
	}

	// ��ÿ���
	ULONG cardNum = ulChan / PXI8265_CHAN_COUNT;
	// ��ÿ���Ӧ��ͨ����
	ULONG cardChan = ulChan % PXI8265_CHAN_COUNT;

	*dfAD = m_sDevAI[cardNum].vcVolt[cardChan];

	return TRUE;
}
BOOL CPXI8265_AI::ReadOneRMS(ULONG ulChan, double* dfAD)
{
	_IsWarningRet("ReadOneRMS");

	*dfAD = 0.0;

	if (ulChan >= (ULONG)GetChCount())
	{
		_WriteLog("ReadOne ͨ���ų��������ֵ(%d):%d", GetChCount(), ulChan);
		return FALSE;
	}

	// ��ÿ���
	ULONG cardNum = ulChan / PXI8265_CHAN_COUNT;
	// ��ÿ���Ӧ��ͨ����
	ULONG cardChan = ulChan % PXI8265_CHAN_COUNT;

	*dfAD = m_sDevAI[cardNum].vcVoltRMS[cardChan];

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOL CPXI8265_AI::_IsErrChk(LONG err, ULONG ulCard)
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

void CPXI8265_AI::_WriteLog(LPCSTR lpszInfo, ...)
{
	char strText[1024];
	char strWriteText[2048];
	va_list va;

	va_start(va, lpszInfo);
	::_vstprintf(strText, lpszInfo, va);
	va_end(va);

	sprintf(strWriteText, "[PXI8265] %s", strText);

	if (m_pIErrLog)
	{
		m_pIErrLog->WriteLog(strWriteText);
	}
	else 
	{
		m_logFile.WriteInfo(strWriteText);
	}
}
//------------------------------------------------------------------------
UINT __stdcall CPXI8265_AI::_ThreadReadAI(PVOID pData)
{
	PDEV_AI				psDevAI		= (PDEV_AI)pData;
	CPXI8265_AI*		pClass		= psDevAI->pClass;
	READ_AI_INFO*		sArrSegAI	= psDevAI->sArrSegAI;
	PREAD_AI_INFO		psReadAI	= NULL;
	ULONG				ulSegIndex	= 0;
	LONG				lResult;
	ULONG				perChanRead;

	lResult = PXI8265_AI_Start(psDevAI->hDev);
	if (pClass->_IsErrChk(lResult, psDevAI->cardSlotID))
	{
		pClass->_WriteLog("�߳�û������");
		return 0;
	}

	psDevAI->bThreadRun = TRUE;

	while (psDevAI->bThreadRun)
	{
		psReadAI = &sArrSegAI[ulSegIndex];

		lResult = PXI8265_AI_Read(psDevAI->hDev,
									PXI8265_SINGLE_LEN, 
									&perChanRead,
									psReadAI->readArray,
									psReadAI->arrayLen,
									PXI8265_AI_GroupByChannel,
									10);
		pClass->_IsErrChk(lResult, psDevAI->cardSlotID);

		psReadAI->singleLen		= perChanRead;
		psDevAI->lastSegIndex	= ulSegIndex;
		ulSegIndex = (ulSegIndex + 1) % PXI8265_SEG_MAX;
	}

	PXI8265_AI_Stop(psDevAI->hDev);

	return 0;
}

ULONG CPXI8265_AI::_FilteArray(LONG readArray[], ULONG arrayLen)
{
	vector<ULONG> vcArray(65535);
	ZeroMemory(&vcArray[0], vcArray.size() * sizeof(ULONG));

	for (ULONG i=0; i<arrayLen; i++)
	{

		vcArray[readArray[i]&0xFFFF]++;
		
	}

	ULONG ulMaxCount = 0;
	ULONG ulResult = 0;

	for (ULONG i=0; i<65535; i++)
	{
		if (vcArray[i] > ulMaxCount)
		{
			ulMaxCount = vcArray[i];
			ulResult = i;
		}
	}

	return ulResult;
}

double	CPXI8265_AI::_GetArrayVolt(LONG readArray[], ULONG arrayLen)
{
	double dfResult = 0.0;
	
#if 1
	arrayLen /= 10;
	vector<LONG> vcArray(readArray, readArray+arrayLen);

	std::sort(vcArray.begin(), vcArray.end(), less<LONG>() );
	// ��3�ݣ�ȥ��ͷβ��ȡ�м�
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

	PXI8265_AI_ConvLsbToVolt(PXI8265_AI_B_5_V,
								&lLsb, 1,
								&dfResult, 1, &ulTmp);

	return dfResult;
}

double	CPXI8265_AI::_GetArrayRMS(LONG readArray[], ULONG arrayLen)
{
	double dfResult = 0.0;
	vector<double> vcdfArray(arrayLen);
	ULONG ulTmp;

	PXI8265_AI_ConvLsbToVolt(PXI8265_AI_B_5_V,
						readArray, arrayLen,
						&vcdfArray[0], vcdfArray.size(),
						&ulTmp);

	double fSquaresSum = 0;
	double dfFilteRMS = 0.0;
	double dfA = 0.7;
	double dfRMS = 1;

	// Yn = a * Xn + (1-a)*Y(n-1)

	for (ULONG i=0; i<ulTmp; i++)
	{
		fSquaresSum += vcdfArray[i]*vcdfArray[i];
		// ʵʱ���� ��Чֵ
		dfRMS = sqrt(fSquaresSum / (double)(i+1));
		// һ���˲������Чֵ
		dfFilteRMS = dfA * dfRMS + (1-dfA)*dfFilteRMS;
	}

	// �˲������Чֵ
	return dfFilteRMS;
}

UINT __stdcall CPXI8265_AI::_ThreadProcessing(PVOID pData)
{
	PDEV_AI				psDevAI		= (PDEV_AI)pData;
	CPXI8265_AI*		pClass		= psDevAI->pClass;
	PREAD_AI_INFO		psReadAI	= NULL;

	psDevAI->bThreadRun = TRUE;
	ULONG ulBkSegIndex = psDevAI->lastSegIndex ;
	while (psDevAI->bThreadRun)
	{
		if (psDevAI->lastSegIndex == ulBkSegIndex)
		{ // ���û��������ȴ�
			Sleep(1);
			continue;
		}

		ulBkSegIndex = psDevAI->lastSegIndex;

		psReadAI	= &psDevAI->sArrSegAI[psDevAI->lastSegIndex];

		for (ULONG chanNum=0; chanNum<PXI8265_CHAN_COUNT; chanNum++)
		{
			psDevAI->vcVolt[chanNum]	= pClass->_GetArrayVolt(&psReadAI->readArray[chanNum*psReadAI->singleLen], psReadAI->singleLen);
		}
		Sleep(1);
	}

	return 0;
}