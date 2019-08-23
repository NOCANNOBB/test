#pragma once
#include "IBaseHead.h"

class CPXI8417_AI :	public IBaseAI
{
public:
	enum{
		MAX_CHAN_AI	= 16,
		SEG_MAX		= 16,
		SINGLE_LEN	= 100,
	};
public:
	CPXI8417_AI(void);
	~CPXI8417_AI(void);

public:
	virtual BOOL Create();
	virtual BOOL Release();

	virtual BOOL LoadParam();
	virtual BOOL Init();
	virtual BOOL Start(ULONG ulChan=0);
	virtual BOOL Stop(ULONG ulChan=0);
	virtual int GetChCount();

	virtual void  SetErrorLog(ILogInfo* pInfo)
	{m_pLogInfo = pInfo;}

	virtual void SetHandle(HANDLE hDevice){m_hDevice = hDevice;}

public:
	// ���ﷵ�ص��ǵ�ѹֵ����λ��V
	virtual BOOL ReadOneDC(ULONG ulChan, double* dfVolt);

public:
	BOOL _WriteLog(LPCSTR lpszInfo, ...);
	BOOL _IsErrChk(LONG err);

private:
	static UINT __stdcall _ThreadReadAI(PVOID);
	static UINT __stdcall _ThreadProcessing(PVOID);

	double	_GetArrayVolt(LONG readArray[], ULONG arrayLen);
public:
	HANDLE			m_hDevice;
	ILogInfo*		m_pLogInfo;
	CLogFile		m_LogFile;
	BOOL			m_bIsStart;
	int				m_iAdd;
	CCriticalSection	m_crLock;

	HANDLE		m_hMutex;

	typedef struct _READ_AI_INFO
	{
		LONG* readArray;	// ��ȡ������
		LONG  arrayLen;		// arrayLen ��ȡ�ĵ���
		LONG  singleLen;	// ��ͨ�����ݵ���
	}READ_AI_INFO, *PREAD_AI_INFO;

	typedef struct _DEV_AI
	{
		BOOL				bThreadRun;
		HANDLE				hDev;
		HANDLE				hThreadReadAI;		// ��ȡAI�����߳�
		HANDLE				hThreadProcessing;	// �����߳�
		READ_AI_INFO		sArrSegAI[SEG_MAX];
		LONG				lastSegIndex;
		CPXI8417_AI*		pClass;
		std::vector<double>	vcVolt;
	}DEV_AI, *PDEV_AI;

	DEV_AI			m_sThread;
};
