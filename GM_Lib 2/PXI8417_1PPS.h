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
	// ���������ֵ
	virtual BOOL GetPulseCount(ULONG* pulPulse);
	// �����帴λ����ʱ��ʱ��ֵ
	virtual BOOL Reset();

	// ѡ�����������Դ
	virtual BOOL SelectOutSrc(ULONG outSrc);
	// ����ʱ��
	virtual BOOL Read(
		ULONG*	bIsValid,			// ʱ���Ƿ���Ч��GPS��δ��λʱΪ0����λ��1��ģ�ⳣ1
		ULONG*	dateHex,			// 16��������,����2017��01��20�գ�����ֵΪ0x200117, ģ�������2000��1��1�տ�ʼ
		ULONG*  timeHex);			// 16����ʱ��,����15:35:32,����ֵΪ153532,ע��GPS������ʱ��ΪUTCʱ�䣬ģ���00:00:00��ʼ��ʱ
private:
	BOOL	_IsDevEmpty() // �豸�Ƿ�Ϊ��
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
