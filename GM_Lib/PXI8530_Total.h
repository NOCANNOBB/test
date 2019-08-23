#pragma once

#include "IBaseHead.h"
#include "PXI8530_Sync422Send.h"
#include "PXI8530_Sync422Recv.h"
#include "PXI8530_ASync422.h"
#include "PXI8530_MeasFrameCircle.h"

class CPXI8530_Sync422Send;
class CPXI8530_Sync422Recv;

class CPXI8530_Total : 
						public CPXI8530_Sync422Send,
						public CPXI8530_Sync422Recv,
						public CPXI8530_ASync422,
						public CPXI8530_MeasFrameCircle
{
public:
	enum{
		CARD_COUNT=2,
	};
	virtual BOOL Create(void) ;
	virtual BOOL Release(void) ;

	virtual void SetErrorLog(ILogInfo* log) ;
public:
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return IsHandleInvalid(m_sDev[0].hDev);
	};

	CPXI8530_Total();
	virtual ~CPXI8530_Total();

private:
	BOOL __IsErr(LONG result, CString& strRetErr);

public:
	void _WriteLog(LPCSTR lpszInfo, ...);

private:
	typedef struct _DEV_PXI8530
	{
		HANDLE				hDev;
		ULONG				cardSlotID;
	}DEV_PXI8530, *PDEV_PXI8530;

	DEV_PXI8530			m_sDev[CARD_COUNT];

	friend bool CompareLess(DEV_PXI8530& __left, DEV_PXI8530& __right);

private:
	ILogInfo*	m_pLogInfo;
	CLogFile	m_logFile;
	int			m_iAdd;
	ULONG		m_iLvdsSendRate;
};