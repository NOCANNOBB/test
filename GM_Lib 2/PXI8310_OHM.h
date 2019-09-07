#pragma once
#include "IBaseHead.h"
#include "PXI8310.h"

#define PXI8310_OHM_CH_MAX		(2)
#define PXI8310_CARD_COUNT		(1)

class CPXI8310_OHM : public IBaseOHM
{
public:
	virtual BOOL Create(void);
	virtual BOOL Release(void);
	virtual BOOL LoadParam(void);
	virtual BOOL Init(void);
	virtual int GetChCount(void);

	virtual BOOL Start(ULONG ulChan = 0);
	virtual BOOL Stop(ULONG ulChan = 0);

	virtual void SetErrorLog(ILogInfo* log)
	{ m_pLogInfo = log;	}

public:
	BOOL	m_bCreateSuccess;
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return !m_bCreateSuccess;
	};

	virtual void SetHandle(HANDLE hDevice){m_hDevice = hDevice;}

public:
	CPXI8310_OHM();
	virtual ~CPXI8310_OHM();

private:
	BOOL _IsErrChk(LONG err, ULONG ulCard);

public:
	virtual BOOL OutputOHM(ULONG ulChan, double dfOHM);
	void _WriteLog(LPCSTR lpszInfo, ...);

private:
	HANDLE		m_hMutex;
	HANDLE		m_hDevice;
	ILogInfo*	m_pLogInfo;
	CLogFile	m_logFile;
};
