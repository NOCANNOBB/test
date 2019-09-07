#ifndef __PXI8530_ASYNC422__
#define __PXI8530_ASYNC422__

#pragma once

class CPXI8530_ASync422 : public IBaseASync422
{
public:
	enum {
		CARD_COUNT = 2,
		ASYNC422_CH_COUNT =	4,
	};

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
	virtual BOOL Write(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteSize);
	virtual BOOL Read(ULONG ulChan, BYTE byReadBuff[], ULONG& cbSize, double timeOut);

public:
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return IsHandleInvalid(m_hDevice);
	};

	virtual void SetHandle(HANDLE hDevice0, HANDLE hDevice1){
		m_hDevice[0] = hDevice0;
		m_hDevice[1] = hDevice1;}

	CPXI8530_ASync422();
	virtual ~CPXI8530_ASync422();
private:
	BOOL __IsErr(LONG result, CString& strRetErr);

public:
	void _WriteLog(LPCSTR lpszInfo, ...);

private:
	HANDLE		m_hDevice[CARD_COUNT];
	ILogInfo*	m_pLogInfo;
	CLogFile	m_logFile;
	ULONG		m_ulRateIndex[CARD_COUNT*ASYNC422_CH_COUNT];
	ULONG		m_ulParityBit[CARD_COUNT*ASYNC422_CH_COUNT];
	BOOL		m_bArrStart[CARD_COUNT*ASYNC422_CH_COUNT];
};

#endif