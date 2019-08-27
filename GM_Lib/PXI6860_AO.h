#pragma once
#include "ibasehead.h"
#include "afxmt.h"
#define PXI6416_MAX_CHAN_AO		(31)
#define CARD_NAME_PXI6860				_T("PXI6860")
#define PXI6860_CARD_COUNT	1
#define PXI6860_VAL_MAX		(+10.0)
#define PXI6860_VAL_MIN		(-10.0)

class CLogFile_PXI6860 
{
public:
	virtual BOOL WriteLog(LPCSTR lpszInfo, ...)
	{
		char szData[2048];
		SYSTEMTIME TmpTime;

		GetLocalTime(&TmpTime);			// ��õ���ʱ��

		va_list va;
		va_start(va, lpszInfo);
		wvsprintfA(szData, lpszInfo, va);
		va_end(va);

		// ����ʱ��
		CString strInfo(szData);
		CString strTimeDate;

		strTimeDate.Format(_T("%d/%2.2d/%2.2d : %2.2d:%2.2d:%2.2d"),
			TmpTime.wYear, TmpTime.wMonth, TmpTime.wDay, 
			TmpTime.wHour, TmpTime.wMinute, TmpTime.wSecond);

		printf(strInfo);

		return TRUE;
	}
};


class CPXI6860_AO :
	public IBaseOutAO
{
public:
	CPXI6860_AO(void);
	~CPXI6860_AO(void);

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
	// ����IR״̬��������, ����ֵ��ͨ����
	virtual BOOL WriteAO(ULONG ulChan, double dfVolt);

private:
	BOOL		m_bCreateSuccess;
	
	BOOL	_IsDevEmpty() // �豸�Ƿ�Ϊ��
	{
		return !m_bCreateSuccess;
	};
	void _WriteLog(LPCSTR lpszInfo, ...);
	//void	_WriteLog(LPCSTR lpszInfo, ...);
	BOOL	_IsErrChk(LONG err, ULONG ulCard);
public:
	HANDLE			m_hDevice;
	ULONG			m_ulPhysicalID; // �豸������ID
	ULONG			m_ulLogicID;	// �豸���߼�ID
	ILogInfo*		m_pLogInfo;
	CLogFile_PXI6860		m_LogFile;
	BOOL			m_bRun;
	HANDLE			m_hThread;
	//IR_PARAM		m_sIrParam[PXI8417_MAX_CHAN_IR];
	int				m_iAdd;
	CCriticalSection	m_crLock;
private:
	HANDLE		m_hMutex;

	typedef struct _DEV_AI
	{
		HANDLE				hDev;
		ULONG				cardLgcID;
		ULONG				cardSlotID;
	}DEV_AO, *PDEV_AO;

	DEV_AO	m_sDevAO[PXI6860_CARD_COUNT];
private:
	static bool _CompareLess(CPXI6860_AO::DEV_AO& __left, CPXI6860_AO::DEV_AO& __right);
};

