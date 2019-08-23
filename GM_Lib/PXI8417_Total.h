
#pragma once
#include "IBaseHead.h"
#include "PXI8417_IR.h"
#include "PXI8417_OC.h"
#include "PXI8417_1PPS.h"
#include "PXI8417_AI.h"

class CPXI8417_IR;
class CPXI8417_OC;
class CPXI8417_1PPS;
class CPXI8417_AI;

class CPXI8417_Total :
	public CPXI8417_IR, public CPXI8417_OC, public CPXI8417_1PPS, public CPXI8417_AI
{
public:
	CPXI8417_Total(void);
	virtual ~CPXI8417_Total(void);

public:
	virtual BOOL Create();
	virtual BOOL Release();
	virtual void SetErrorLog(ILogInfo* pInfo)
	{
		m_pLogInfo = pInfo;
		CPXI8417_OC::SetErrorLog(pInfo);
		CPXI8417_IR::SetErrorLog(pInfo);
		CPXI8417_1PPS::SetErrorLog(pInfo);
	}

public:
	BOOL _WriteLog(LPCSTR lpszInfo, ...);

public:
	HANDLE		m_hDevice;
	ILogInfo*	m_pLogInfo;
	CLogFile	m_LogFile;
	int			m_iAdd;
};
