#include "stdafx.h"
#include "PXI6416_DO.h"
#include "CardLib/PXI6416.h"

PXI6416_DO::PXI6416_DO(void)
{
	m_hDevice = INVALID_HANDLE_VALUE;
	//m_LogFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
	
	m_hThread = INVALID_HANDLE_VALUE;
	m_bCreateSuccess	= FALSE;

	PDEV_DO psDevAO;

	for (ULONG cardNum=0; cardNum<PXI6416_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];
		psDevAO->cardLgcID = cardNum;

		InitHandle(psDevAO ->hDev);
	}

	InitHandle(m_hMutex);
}

PXI6416_DO::~PXI6416_DO(void)
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		Release();
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL PXI6416_DO::_WriteLog(LPCSTR lpszInfo, ...)
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

bool CompareLess(PXI6416_DO::DEV_DO& __left, PXI6416_DO::DEV_DO& __right)
{
	return (__left.cardSlotID < __right.cardSlotID);
}

BOOL PXI6416_DO::_IsErrChk(LONG err, ULONG ulCard)
{
	if (PXI6416_Failed(err))
	{
		char errString[128]; 
		PXI6416_GetErrorString(err, errString, 128); 
		_WriteLog("[Dev-%d] %s", ulCard, errString);
		return TRUE;
	}

	return FALSE;
}

BOOL PXI6416_DO::Create()
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

	PXI6416_GetDeviceCount(&ulCount);

	if (ulCount < PXI6416_CARD_COUNT)
	{
		_WriteLog("没有足够板卡，只有%d", ulCount);

		return FALSE;
	}
	try
	{
		PDEV_DO			psDevAO;

		for (ULONG cardNum=0; cardNum<PXI6416_CARD_COUNT; cardNum++)
		{
			psDevAO = &m_sDevAO[cardNum];

			if (_IsErrChk(PXI6416_DeviceOpen(cardNum, &psDevAO->hDev), cardNum)) throw "error";
			PXI6416_GetDevicePXISolt(psDevAO->hDev, &psDevAO->cardSlotID);
		}

		std::sort(m_sDevAO, m_sDevAO+PXI6416_CARD_COUNT, CompareLess);

		m_bCreateSuccess = TRUE;
	}
	catch (char* )
	{
		Release();

		return FALSE;
	}

	return TRUE;
}

BOOL PXI6416_DO::Release()
{
	if (!m_bCreateSuccess) return TRUE;

	DelEvent(m_hMutex);

	Stop(0);
	PDEV_DO			psDevAO;

	for (ULONG cardNum=0; cardNum<PXI6416_CARD_COUNT; cardNum++)
	{
		psDevAO = &m_sDevAO[cardNum];

		if (!IsHandleInvalid(psDevAO->hDev))
		{
			PXI6416_DeviceClose(psDevAO->hDev);
			InitHandle(psDevAO->hDev);
		}
	}

	m_bCreateSuccess	= FALSE;
	return TRUE;
}

BOOL PXI6416_DO::LoadParam()
{
	return TRUE;
}

BOOL PXI6416_DO::Init()
{

	return TRUE;
}

BOOL PXI6416_DO::Start(ULONG ulChan)
{
	return TRUE;
}

BOOL PXI6416_DO::Stop(ULONG ulChan)
{
	

	return TRUE;
}


int PXI6416_DO::GetChCount()
{
	return PXI6416_MAX_CHAN_DO;
}


BOOL PXI6416_DO::WriteDO(ULONG ulChan, byte boolValue[]){
	_IsWarningRet("WriteDO");
	BOOL ulVal;
	ReadDO(ulChan, &ulVal);

	m_byteDO[ulChan] = boolValue[0]!=0;

	BOOL bRet = _IsErrChk(PXI6416_DO_Write(m_hDevice, m_byteDO, PXI6416_MAX_CHAN_DO), 0);

	return bRet;
}

BOOL PXI6416_DO::ReadDO(ULONG ulChan, byte boolValue[]){
	
	_IsWarningRet("ReadDO");
	BOOL bRet = _IsErrChk(PXI6416_DO_Read(m_hDevice, m_byteDO, 64), 0);

	if (bRet)
	{
		boolValue[0] = m_byteDO[ulChan];
	}

	return bRet;

}
