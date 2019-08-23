#include "stdafx.h"
#include "PXI8530_Total.h"
#include "PXI8530.h"

CPXI8530_Total::CPXI8530_Total()
{
	m_iAdd = 0;

	for (ULONG i=0; i<CARD_COUNT; i++)
	{
		m_sDev[i].hDev = INVALID_HANDLE_VALUE;
		m_sDev[i].cardSlotID = 0;
	}

	m_logFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;
}

CPXI8530_Total::~CPXI8530_Total()
{
	if (m_sDev[0].hDev != INVALID_HANDLE_VALUE)
	{
		CPXI8530_Sync422Send::Release();
		CPXI8530_Sync422Recv::Release();
		CPXI8530_ASync422::Release();
		CPXI8530_MeasFrameCircle::Release();
		Release();
		CPXI8530_Sync422Send::SetHandle(INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE);
		CPXI8530_Sync422Recv::SetHandle(INVALID_HANDLE_VALUE);
		CPXI8530_ASync422::SetHandle(INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE);
		CPXI8530_MeasFrameCircle::SetHandle(INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE);
		m_sDev[0].hDev = INVALID_HANDLE_VALUE;
		m_sDev[1].hDev = INVALID_HANDLE_VALUE;
	}
}

// 由小到大排序
bool CompareLess(CPXI8530_Total::DEV_PXI8530& __left, CPXI8530_Total::DEV_PXI8530& __right)
{
	return (__left.cardSlotID < __right.cardSlotID);
}

BOOL CPXI8530_Total::Create(void)
{
	if (m_iAdd > 0) 
	{
		m_iAdd ++;
		return TRUE;
	}

	m_iAdd ++;

	PDEV_PXI8530	psDev;
	BOOL bNoCard = TRUE;

	for (ULONG cardNum=0; cardNum<CARD_COUNT; cardNum++)
	{
		psDev = &m_sDev[cardNum];

		ULONG result = PXI8530_DeviceOpen(cardNum, &psDev->hDev);

		if (psDev->hDev != INVALID_HANDLE_VALUE)
		{
			bNoCard = FALSE;
			PXI8530_GetDevicePXISolt(psDev->hDev, &psDev->cardSlotID);
		}
		else 
		{
			if (bNoCard)
			{
				m_iAdd--;
				_WriteLog("PXI8530_DeviceOpen Error!");
				return FALSE;
			}
			else
			{
				psDev->cardSlotID = 0xFFFF;
				_WriteLog("没找到卡 %d", cardNum);
			}
		}
		
	}

	std::sort(m_sDev, m_sDev+CARD_COUNT, CompareLess);

	CPXI8530_Sync422Send::SetHandle(m_sDev[0].hDev, m_sDev[1].hDev);
	CPXI8530_Sync422Recv::SetHandle(m_sDev[0].hDev);
	CPXI8530_ASync422::SetHandle(m_sDev[0].hDev, m_sDev[1].hDev);

	if (m_sDev[0].hDev != INVALID_HANDLE_VALUE)
	{
		PXI8530_PulseOut_MainTrig(m_sDev[0].hDev, FALSE);
	}

	if (m_sDev[1].hDev != INVALID_HANDLE_VALUE)
	{
		PXI8530_PulseOut_MainTrig(m_sDev[1].hDev, FALSE);
	}

	CPXI8530_MeasFrameCircle::SetHandle(m_sDev[0].hDev, m_sDev[1].hDev);

	return TRUE;
}

BOOL CPXI8530_Total::Release(void)
{
	if (m_iAdd > 1)
	{
		m_iAdd --;
		return TRUE;
	}

	m_iAdd = 0;

	for (ULONG cardNum=0; cardNum<CARD_COUNT; cardNum++)
	{
		if (m_sDev[cardNum].hDev != INVALID_HANDLE_VALUE)
		{
			ULONG result = PXI8530_DeviceClose(m_sDev[cardNum].hDev);

			if (result != PXI8530_NoError)
			{
				_WriteLog("PXI8530_DeviceClose Error!");
				return FALSE;
			}

			InitHandle(m_sDev[cardNum].hDev);
		}
	}

	return TRUE;	
}
void CPXI8530_Total::SetErrorLog(ILogInfo* log) 
{
	m_pLogInfo = log;
	CPXI8530_Sync422Send::SetErrorLog(m_pLogInfo);
	CPXI8530_Sync422Recv::SetErrorLog(m_pLogInfo);
	CPXI8530_ASync422::SetErrorLog(m_pLogInfo);
	CPXI8530_MeasFrameCircle::SetErrorLog(m_pLogInfo);
}

void CPXI8530_Total::_WriteLog(LPCSTR lpszInfo, ...)
{
	char strText[1024];
	char strWriteText[2048];
	va_list va;

	va_start(va, lpszInfo);
	::_vstprintf(strText, lpszInfo, va);
	va_end(va);

	sprintf(strWriteText, "[PXI8530] %s", strText);

	if (m_pLogInfo)
	{
		m_pLogInfo->WriteLog(strWriteText);
	}
	else 
	{
		m_logFile.WriteInfo(strWriteText);
	}
}
