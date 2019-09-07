#pragma once
#include "IBaseHead.h"

class CPXI8510_LvdsSendFrameCircleData : public IBaseLvdsSendFrameCircleData
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

	CPXI8510_LvdsSendFrameCircleData();
	virtual ~CPXI8510_LvdsSendFrameCircleData();
private:
	BOOL __IsErr(LONG result, CString& strRetErr);

	enum{
		SEND_CH_MAX	 = (2),
	};

public:
	// 发送圈协议 160字节
	virtual BOOL SendCircle(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen);
	// 发送帧协议 80字节
	virtual BOOL SendFrame(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen);

public:
	void _WriteLog(LPCSTR lpszInfo, ...);

private:
	typedef struct _PARAM
	{
		double rate;
	}SEND_PARAM, *PSEND_PARAM;

	HANDLE		m_hDevice;
	ILogInfo*	m_pLogInfo;
	CLogFile	m_logFile;
	int			m_iAdd;
	ULONG		m_iLvdsSendRate;
	BOOL		m_bStart;
	std::vector<BYTE>	m_vcCircle;
	std::vector<BYTE>	m_vcFrame;
	SEND_PARAM	m_sParam[SEND_CH_MAX];

};