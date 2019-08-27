#pragma once
#include "ibasehead.h"

#define PXI8265_MAX_CHAN_DO		(8)
#define PXI8265_SET_CHAN_DO_ARR		(8)
#define PXI8265_CARD_COUNT	1
class CLogFile_PXI8265_DO
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
class CPXI8265_DO :
	public IBaseDO
{
public:
	CPXI8265_DO(void);
	~CPXI8265_DO(void);
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
	
	virtual BOOL WriteDO(ULONG ulChan, BOOL boolValue){return TRUE;}
	virtual BOOL ReadDO(ULONG ulChann,BOOL* boolValue){return TRUE;}

	virtual BOOL WriteDO(ULONG ulChan, byte boolValue[]);
	virtual BOOL ReadDO(ULONG ulChann, byte boolValue[]);
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
	CLogFile_PXI8265_DO		m_LogFile;
	BOOL			m_bRun;
	BYTE m_byteDO[8];
	HANDLE			m_hThread;
	//IR_PARAM		m_sIrParam[PXI8417_MAX_CHAN_IR];
	int				m_iAdd;
	

	typedef struct _DEV_DO
	{
		HANDLE				hDev;
		ULONG				cardLgcID;
		ULONG				cardSlotID;
	}DEV_DO, *PDEV_DO;

	DEV_DO	m_sDevAO[PXI8265_CARD_COUNT];
	friend bool CompareLess(DEV_DO& __left, DEV_DO& __right);
};

