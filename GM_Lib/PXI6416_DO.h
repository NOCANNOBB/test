#pragma once
#include "ibasehead.h"
#include "afxmt.h"
#define PXI6416_MAX_CHAN_DO		(64)
#define PXI6416_CARD_COUNT	1
#define CARD_NAME				_T("PXI6416")

class CLogFile 
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


class PXI6416_DO :
	public IBaseDO
{

public:
	PXI6416_DO(void);
	~PXI6416_DO(void);

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
	virtual BOOL WriteDO(ULONG ulChan, BOOL boolValue);
	virtual BOOL ReadDO(ULONG ulChann,BOOL* boolValue);

	virtual BOOL WriteDO(ULONG ulChan, byte boolValue[]){return TRUE;}
	virtual BOOL ReadDO(ULONG ulChann, byte boolValue[]){return TRUE;}

private:
	BOOL		m_bCreateSuccess;
	HANDLE		m_hMutex;
	BOOL	_IsDevEmpty() // �豸�Ƿ�Ϊ��
	{
		return !m_bCreateSuccess;
	};
	BOOL _WriteLog(LPCSTR lpszInfo, ...);
	//void	_WriteLog(LPCSTR lpszInfo, ...);
	BOOL	_IsErrChk(LONG err, ULONG ulCard);
private:
	HANDLE			m_hDevice;
	ULONG			m_ulPhysicalID; // �豸������ID
	ULONG			m_ulLogicID;	// �豸���߼�ID
	ILogInfo*		m_pLogInfo;
	CLogFile		m_LogFile;
	BOOL			m_bRun;
	BYTE m_byteDO[PXI6416_MAX_CHAN_DO];
	HANDLE			m_hThread;
	//IR_PARAM		m_sIrParam[PXI8417_MAX_CHAN_IR];
	int				m_iAdd;
	CCriticalSection	m_crLock;

	typedef struct _DEV_DO
	{
		HANDLE				hDev;
		ULONG				cardLgcID;
		ULONG				cardSlotID;
	}DEV_DO, *PDEV_DO;

	DEV_DO	m_sDevAO[PXI6416_CARD_COUNT];
	friend bool CompareLess(DEV_DO& __left, DEV_DO& __right);
};

