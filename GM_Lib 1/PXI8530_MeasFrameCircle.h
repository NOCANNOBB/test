#ifndef __PXI8530_MEAS_CIRCLE_FRAME__
#define __PXI8530_MEAS_CIRCLE_FRAME__

#pragma once

class CPXI8530_MeasFrameCircle : public IBaseMeasFrameCircle
{
public:
	enum {
		CARD_COUNT = 2,
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
	virtual BOOL SetCircleTime(ULONG timeData);
	virtual BOOL SetFrameTime(ULONG timeData);
	virtual BOOL Read(
				ULONG  ulChan,				// 通道号
				__int64	readArray[],		// 读取数组
				ULONG&	readLen,			// 读取长度
				double	timeOut);			// 超时时间

public:
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return IsHandleInvalid(m_hDevice);
	};

	virtual void SetHandle(HANDLE hDevice0, HANDLE hDevice1){
		m_hDevice[0] = hDevice0;
		m_hDevice[1] = hDevice1;}

	CPXI8530_MeasFrameCircle();
	virtual ~CPXI8530_MeasFrameCircle();
private:
	BOOL __IsErr(LONG result, CString& strRetErr);

public:
	void _WriteLog(LPCSTR lpszInfo, ...);

private:
	HANDLE		m_hDevice[CARD_COUNT];
	ILogInfo*	m_pLogInfo;
	CLogFile	m_logFile;
	int			m_iAdd;
	BOOL		m_bStart[CARD_COUNT];
};

#endif