#pragma once
#include "PXI8265.h"
#include "PXI8265_AI.h"
#include "PXI8265_AO.h"
#include "PXI8265_CNT.h"
#include "PXI8265_DO.h"

class CLogFile_PXI8265_Total
{
public:
	virtual BOOL WriteLog(LPCSTR lpszInfo, ...)
	{
		char szData[2048];
		SYSTEMTIME TmpTime;

		GetLocalTime(&TmpTime);			// 获得当地时间

		va_list va;
		va_start(va, lpszInfo);
		wvsprintfA(szData, lpszInfo, va);
		va_end(va);

		// 出错时间
		CString strInfo(szData);
		CString strTimeDate;

		strTimeDate.Format(_T("%d/%2.2d/%2.2d : %2.2d:%2.2d:%2.2d"),
			TmpTime.wYear, TmpTime.wMonth, TmpTime.wDay, 
			TmpTime.wHour, TmpTime.wMinute, TmpTime.wSecond);

		printf(strInfo);

		return TRUE;
	}
};

class CPXI8265_Total:public CPXI8265_AI,public CPXI8265_CNT,public CPXI8265_AO
{
public:
	CPXI8265_Total(void);
	virtual ~CPXI8265_Total(void);
public:
	virtual BOOL Create();
	virtual BOOL Release();
	virtual void SetErrorLog(ILogInfo* pInfo)
	{
		m_pLogInfo = pInfo;
		CPXI8265_AI::SetErrorLog(pInfo);
		CPXI8265_CNT::SetErrorLog(pInfo);
		CPXI8265_AO::SetErrorLog(pInfo);
	}
public:
	BOOL _WriteLog(LPCSTR lpszInfo, ...);

public:
	HANDLE		m_hDevice;
	ILogInfo*	m_pLogInfo;
	CLogFile_PXI8265_Total	m_LogFile;
	int			m_iAdd;
};

