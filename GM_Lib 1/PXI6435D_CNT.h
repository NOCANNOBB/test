#pragma once
#include "ibasehead.h"
#include "afxmt.h"
#define PXI6435D_MAX_CHAN_CNT		(8)
#define CARD_NAME_PXI6435D				_T("PXI6435D")
#define PXI6435D_MIN_VALUE	(1)
#define PXI6435D_MAX_VALUE	(20000000)
#define PXI6435D_EDGE_VALUE	(1)
#define PXI6435D_MASETIME_VALUE	(1)
#define PXI6435D_CARD_COUNT	1


class MyCLogFile 
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

class PXI6435D_CNT:public IBaseCNT
{

	typedef struct _INTPARAM
	{
		ULONG ulIntCount;
		double dfPulseWidthMS;
		BOOL bIntSts;
	} IR_PARAM, *PIR_PARAM;

public:
	PXI6435D_CNT(void);
	~PXI6435D_CNT(void);
public:
	virtual BOOL Create();
	virtual BOOL Release();

	virtual BOOL LoadParam();
	virtual BOOL Init();
	virtual BOOL Start(ULONG ulChan);
	virtual BOOL Stop(ULONG ulChan);
	virtual int GetChCount();

	virtual void  SetErrorLog(ILogInfo* pInfo)
	{m_pLogInfo = pInfo;}

	virtual void SetHandle(HANDLE hDevice){m_hDevice = hDevice;}
private:
	BOOL		m_bCreateSuccess;
	HANDLE		m_hMutex;
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return !m_bCreateSuccess;
	};
	BOOL _WriteLog(LPCSTR lpszInfo, ...);
	//void	_WriteLog(LPCSTR lpszInfo, ...);
	BOOL	_IsErrChk(LONG err, ULONG ulCard);
public:
	BOOL GetdfFreqAnddfdfDutyCycle(ULONG ulChan, double* dfFreq,double* dfdfDutyCycle = NULL);
private:
	HANDLE			m_hDevice;
	ULONG			m_ulPhysicalID; // 设备的物理ID
	ULONG			m_ulLogicID;	// 设备的逻辑ID
	ULONG           m_ulSortID;
	ILogInfo*		m_pLogInfo;
	MyCLogFile		m_LogFile;
	BOOL			m_bRun;
	BYTE m_byteDO[PXI6435D_MAX_CHAN_CNT];
	HANDLE			m_hThread;
	//IR_PARAM		m_sIrParam[PXI8417_MAX_CHAN_IR];
	int				m_iAdd;
	typedef struct _DEV_CNT
	{
		HANDLE				hDev;
		ULONG				cardLgcID;
		ULONG				cardSlotID;
	}DEV_CNT, *PDEV_CNT;

	DEV_CNT	m_sDevAO[PXI6435D_CARD_COUNT];
	friend bool CompareLess(DEV_CNT& __left, DEV_CNT& __right);
};

