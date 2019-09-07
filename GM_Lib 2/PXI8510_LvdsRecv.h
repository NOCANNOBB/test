#pragma once
#include "IBaseHead.h"

#define PXI8510_RECV_CH_MAX		(4)

class CPXI8510_LvdsRecv : public IBaseLvdsRecv 
{
public:
	virtual BOOL Create(void) ;
	virtual BOOL Release(void) ;
	virtual BOOL LoadParam(void) ;
	virtual BOOL Init(void) ;
	virtual int GetChCount(void) ;

	virtual BOOL Start(ULONG ulChan) ;
	virtual BOOL Stop(ULONG ulChan) ;

	virtual void SetErrorLog(ILogInfo* log) 
	{m_pLogInfo = log;}
public:
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return IsHandleInvalid(m_hDevice);
	};

	virtual void SetHandle(HANDLE hDevice){m_hDevice = hDevice;}

	CPXI8510_LvdsRecv();
	virtual ~CPXI8510_LvdsRecv();
private:
	BOOL __IsErr(LONG result, CString& strRetErr);


public:
	virtual BOOL Read(
		ULONG ulChan,
		BYTE pbyReadBuff[],
		ULONG& cbSize,		// 读取个数，如果超时，返回实际数量，如果缓冲区NULL，返回内部已读数据长度
		double dfTimeOut	// 读取超时时间
		);

public:
	void _WriteLog(LPCSTR lpszInfo, ...);

private:
	HANDLE		m_hDevice;
	ILogInfo*	m_pLogInfo;
	CLogFile	m_logFile;
	int			m_iAdd;
	ULONG		m_iLvdsSendRate;
};