#ifndef __PXI8530_SYNC422_RECV__
#define __PXI8530_SYNC422_RECV__

#pragma once

class CPXI8530_Sync422Recv : public IBaseRecvSync422
{
public:
	virtual BOOL Create(void) ;
	virtual BOOL Release(void) ;
	virtual BOOL LoadParam(void) ;
	virtual BOOL Init(void) ;
	virtual int GetChCount(void) ;

	virtual BOOL Start(ULONG ulChan=0) ;
	virtual BOOL Stop(ULONG ulChan=0) ;

	virtual void SetErrorLog(ILogInfo* log) 
	{m_pLogInfo = log;}
public:
	virtual BOOL Recv(ULONG ulChan, BYTE byReadBuff[], ULONG& cbSize, double timeOut);

public:
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return IsHandleInvalid(m_hDevice);
	};

	virtual void SetHandle(HANDLE hDevice){m_hDevice = hDevice;}

	CPXI8530_Sync422Recv();
	virtual ~CPXI8530_Sync422Recv();
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
	BOOL		m_bStart;
};

#endif