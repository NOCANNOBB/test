#pragma once
#include "IBaseHead.h"

#define PXI8417_MAX_CHAN_OC		(24)

class CPXI8417_OC :
	public IBaseOC
{
public:
	CPXI8417_OC(void);
	~CPXI8417_OC(void);

public:
	virtual BOOL Create();
	virtual BOOL Release();

	virtual BOOL LoadParam();
	virtual BOOL Init();
	virtual BOOL Start(ULONG ulChan);
	virtual BOOL Stop(ULONG ulChan);
	virtual int GetChCount();

	virtual void SetErrorLog(ILogInfo* pInfo)
	{m_pLogInfo = pInfo;}

	virtual void SetHandle(HANDLE hDevice){m_hDevice = hDevice;}
public:
	virtual BOOL SetOC(ULONG ulChan, double pulseWidthMS);

public:
	BOOL _WriteLog(LPCSTR lpszInfo, ...);

public:
	HANDLE			m_hDevice;
	ILogInfo*		m_pLogInfo;
	CLogFile		m_LogFile;
};
