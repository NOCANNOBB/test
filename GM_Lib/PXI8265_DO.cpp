#include "stdafx.h"
#include "PXI8265_DO.h"
#include "CardLib/PXI8265.h"

CPXI8265_DO::CPXI8265_DO(void)
{
	m_hDevice = INVALID_HANDLE_VALUE;
	//m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;

	m_hThread = INVALID_HANDLE_VALUE;
	m_bCreateSuccess	= FALSE;

	PDEV_DO psDevAO;

	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];
		psDevAO->cardLgcID = cardNum;

		InitHandle(psDevAO ->hDev);
	}

	InitHandle(m_hMutex);
}

CPXI8265_DO::~CPXI8265_DO(void)
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL CPXI8265_DO::_WriteLog(LPCSTR lpszInfo, ...)
{
	char szText[1024];
	char szWriteText[2048];
	va_list va;
	va_start(va, lpszInfo);
	wvsprintfA(szText, lpszInfo, va);
	va_end(va);

	sprintf(szWriteText, "[PXI8265] %s", szText);

	if (m_pLogInfo != NULL)
	{
		m_pLogInfo->WriteLog(szWriteText);
	}

	return TRUE;
}

bool CompareLess(CPXI8265_DO::DEV_DO& __left, CPXI8265_DO::DEV_DO& __right)
{
	return (__left.cardSlotID < __right.cardSlotID);
}

BOOL CPXI8265_DO::_IsErrChk(LONG err, ULONG ulCard)
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

BOOL CPXI8265_DO::Create()
{
	_IsWarningRet("Create");
	CString szText;
	int iIndex = 0;
	m_hMutex = CreateMutex(NULL, FALSE, MUTEX_IDO);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		_WriteLog("已经创建，不可以重复创建");
		return FALSE;
	}
	ULONG ulCount;

	PXI8265_GetDeviceCount(&ulCount);

	if (ulCount < PXI8265_CARD_COUNT)
	{
		_WriteLog("没有足够板卡，只有%d", ulCount);

		return FALSE;
	}
	try
	{
		PDEV_DO			psDevAO;

		for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
		{
			psDevAO = &m_sDevAO[cardNum];

			if (_IsErrChk(PXI8265_DeviceOpen(cardNum, &psDevAO->hDev), cardNum)) throw "error";
			PXI8265_GetDevicePXISolt(psDevAO->hDev, &psDevAO->cardSlotID);
		}

		std::sort(m_sDevAO, m_sDevAO+PXI8265_CARD_COUNT, CompareLess);

		m_bCreateSuccess = TRUE;
	}
	catch (char* )
	{
		Release();

		return FALSE;
	}

	return TRUE;
}

BOOL CPXI8265_DO::Release()
{
	if (!m_bCreateSuccess) return TRUE;

	DelEvent(m_hMutex);

	Stop(0);
	PDEV_DO			psDevAO;

	for (ULONG cardNum=0; cardNum<PXI8265_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];

		if (!IsHandleInvalid(psDevAO->hDev))
		{
			PXI8265_DeviceClose(psDevAO->hDev);
			InitHandle(psDevAO->hDev);
		}
	}

	m_bCreateSuccess	= FALSE;
	return TRUE;
}

BOOL CPXI8265_DO::LoadParam()
{
	return TRUE;
}

BOOL CPXI8265_DO::Init()
{

	return TRUE;
}

BOOL CPXI8265_DO::Start(ULONG ulChan)
{
	return TRUE;
}

BOOL CPXI8265_DO::Stop(ULONG ulChan)
{


	return TRUE;
}


int CPXI8265_DO::GetChCount()
{
	return PXI8265_MAX_CHAN_DO;
}


BOOL CPXI8265_DO::WriteDO(ULONG ulChan, byte boolValue[]){
	_IsWarningRet("WriteDO");
	
	

	_IsErrChk(PXI8265_DIO_CfgDev(m_hDevice, ulChan, PXI8265_DIO_OUTPORT),ulChan);

	BOOL bRet = _IsErrChk(PXI8265_DIO_Write(m_hDevice,ulChan, boolValue, PXI8265_SET_CHAN_DO_ARR), 0);

	return bRet;
}

BOOL CPXI8265_DO::ReadDO(ULONG ulChan, byte boolValue[]){

	_IsWarningRet("ReadDO");
	BOOL bRet = _IsErrChk(PXI8265_DIO_Read(m_hDevice, ulChan,boolValue, PXI8265_SET_CHAN_DO_ARR), 0);

	return bRet;

}
