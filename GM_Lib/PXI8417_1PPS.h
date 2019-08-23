#pragma once
#include "IBaseHead.h"

#define PXI8417_MAX_CHAN_1PPS		(2)

class CPXI8417_1PPS :
	public IBase1PPS
{
public:
	CPXI8417_1PPS(void);
	~CPXI8417_1PPS(void);

public:
	virtual BOOL Create();
	virtual BOOL Release();

	virtual BOOL LoadParam();
	virtual BOOL Init();
	virtual BOOL Start(ULONG ulChan);
	virtual BOOL Stop(ULONG ulChan);
	virtual int GetChCount();

	virtual void  SetErrorLog(ILogInfo* pInfo)
	{m_pLogInfo = pInfo;}

	virtual void SetHandle(HANDLE hDevice){m_hDevice = hDevice;}

public:
	// 获得秒脉冲值
	virtual BOOL GetPulseCount(ULONG* pulPulse);
	// 秒脉冲复位，这时是时间值
	virtual BOOL Reset();

	// 选择妙脉冲输出源
	virtual BOOL SelectOutSrc(ULONG outSrc);
	// 读出时间
	virtual BOOL Read(
		ULONG*	bIsValid,			// 时间是否有效，GPS在未定位时为0，定位后1，模拟常1
		ULONG*	dateHex,			// 16进制日期,例如2017年01月20日，反馈值为0x200117, 模拟输出从2000年1月1日开始
		ULONG*  timeHex);			// 16进制时间,例如15:35:32,反馈值为153532,注意GPS反馈的时间为UTC时间，模拟从00:00:00开始计时
private:
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return IsHandleInvalid(m_hDevice);
	};
	BOOL __IsErr(LONG result, CString& strRetErr);

public:
	BOOL _WriteLog(LPCSTR lpszInfo, ...);
	
public:
	HANDLE			m_hDevice;
	ILogInfo*		m_pLogInfo;
	CLogFile		m_LogFile;
	BOOL			m_chanInit[PXI8417_MAX_CHAN_1PPS];
};
