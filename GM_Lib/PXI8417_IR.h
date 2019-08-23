#pragma once
#include "IBaseHead.h"

#define PXI8417_MAX_CHAN_IR		(16)

class CPXI8417_IR :
	public IBaseIR
{
typedef struct _INTPARAM
{
	ULONG ulIntCount;
	double dfPulseWidthMS;
	BOOL bIntSts;
} IR_PARAM, *PIR_PARAM;

public:
	CPXI8417_IR(void);
	~CPXI8417_IR(void);

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
	// 返回IR状态，脉冲宽度, 计数值，通道号
	virtual BOOL GetIR(ULONG ulChan, PBOOL pbSts, double* pdfPulseWidth, PULONG pulCount);
	virtual BOOL ClrIRSts(ULONG ulChann);

public:
	BOOL _WriteLog(LPCSTR lpszInfo, ...);

	static UINT __stdcall GetIntPulseWidthThread(PVOID pVoid);
public:
	HANDLE			m_hDevice;
	ILogInfo*		m_pLogInfo;
	CLogFile		m_LogFile;
	BOOL			m_bRun;

	HANDLE			m_hThread;
	IR_PARAM		m_sIrParam[PXI8417_MAX_CHAN_IR];
	int				m_iAdd;
	CCriticalSection	m_crLock;
};
