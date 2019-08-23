// PCI6860DCOut.h: interface for the CPCI6860DCOut class.
//////////////////////////////////////////////////////////////////////

#ifndef __PXI8867_AO__
#define __PXI8867_AO__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IBaseHead.h"
#include "PXI8867.h"

#define PXI8867_CH_COUNT	32
#define PXI8867_CARD_COUNT	1

#define PXI8867_VAL_MAX		(+10.0)
#define PXI8867_VAL_MIN		(-10.0)

class CPXI8867_AO : public IBaseOutDC  
{
public:
	virtual BOOL WriteDC(ULONG ulChan, double dfVolt);

public:
	virtual BOOL Create(void);
	virtual BOOL Release(void);
	virtual BOOL LoadParam(void);
	virtual BOOL Init(void);
	virtual int GetChCount(void);

	virtual BOOL Start(ULONG ulChan = 0);
	virtual BOOL Stop(ULONG ulChan = 0);

	virtual void SetErrorLog(ILogInfo* log)
	{ m_pIErrLog = log;	}
public:
	CPXI8867_AO();
	virtual ~CPXI8867_AO();
private:
	BOOL	m_bCreateSuccess;
	BOOL	_IsErrChk(LONG err, ULONG ulCard);
	void	_WriteLog(LPCSTR lpszInfo, ...);
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return !m_bCreateSuccess;
	};
private:
	HANDLE		m_hMutex;

	ILogInfo*	m_pIErrLog;
	CLogFile	m_logFile;

	typedef struct _DEV_AI
	{
		HANDLE				hDev;
		ULONG				cardLgcID;
		ULONG				cardSlotID;
	}DEV_AO, *PDEV_AO;

	DEV_AO	m_sDevAO[PXI8867_CARD_COUNT];
private:
	static bool _CompareLess(CPXI8867_AO::DEV_AO& __left, CPXI8867_AO::DEV_AO& __right);
};

#endif // !defined(AFX_PCI6860DCOUT_H__590B8E48_AC81_4137_8BD2_1D1E9E1253DB__INCLUDED_)
