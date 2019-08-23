#pragma once
#include "IBaseHead.h"
#include "PXI8510_LvdsRecv.h"
#include "PXI8510_LvdsSendFrameCircle.h"

class CPXI8510_LvdsRecv;
class CPXI8510_LvdsSendFrameCircleData;

class CPXI8510_Total : public CPXI8510_LvdsRecv, public CPXI8510_LvdsSendFrameCircleData
{
public:
	virtual BOOL Create(void) ;
	virtual BOOL Release(void) ;

	virtual void SetErrorLog(ILogInfo* log) ;
public:
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return IsHandleInvalid(m_hDevice);
	};

	CPXI8510_Total();
	virtual ~CPXI8510_Total();

private:
	BOOL __IsErr(LONG result, CString& strRetErr);

public:
	void _WriteLog(LPCSTR lpszInfo, ...);

private:
	HANDLE		m_hDevice;
	ILogInfo*	m_pLogInfo;
	CLogFile	m_logFile;
	int			m_iAdd;
	ULONG		m_iLvdsSendRate;
};