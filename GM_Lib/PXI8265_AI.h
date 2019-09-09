//////////////////////////////////////////////////////////////////////

#ifndef __PXI8265_AI__
#define __PXI8265_AI__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IBaseHead.h"
#include "vector"



class CLogFile_PXI8265 
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

class CPXI8265_AI : public IBaseAI  
{
public:

	enum 
	{
		CARD_COUNT		= (1),
		CHAN_COUNT		= (48),
		SEG_MAX			= (16),
		MAX_ARRAY_SIZE = 1024,
	};


public:
	virtual BOOL ReadOneDC(ULONG ulChan, double* dfAD);
	virtual BOOL ReadOneRMS(ULONG ulChan, double* dfAD);
	virtual void SetDataRate(int RateValue,int PerRead);
	virtual void GetDataFromBord(ULONG ulChan,double* pBuffer, int ReadSize, int* retReadSize);
public:
	virtual BOOL Create(void);
	virtual BOOL Release(void);
	virtual BOOL LoadParam(void);
	virtual BOOL Init(void);
	virtual int GetChCount(void);
	
	virtual BOOL Start(ULONG ulChan = 0);
	virtual BOOL Stop(ULONG ulChan = 0);
	
	virtual void SetErrorLog(ILogInfo* log)
	{ m_pIErrLog = log;	}
	virtual void SetHandle(HANDLE hDevice){m_hDevice = hDevice;}
public:
	CPXI8265_AI();
	virtual ~CPXI8265_AI();
public:
	static UINT __stdcall _ThreadReadAI(PVOID);
	static UINT __stdcall _ThreadProcessing(PVOID);
private:
	BOOL	_IsDevEmpty() // �豸�Ƿ�Ϊ��
	{
		return !m_bCreateSuccess;
	};
	void GetData(ULONG ulChan,double* pBuffer, int ReadSize, int* retReadSize);
	void	_WriteLog(LPCSTR lpszInfo, ...);
	BOOL	_IsErrChk(LONG err, ULONG ulCard);
	ULONG	_FilteArray(LONG readArray[], ULONG arrayLen);
	// ��õ�ѹֵ��˳���˲�
	double	_GetArrayVolt(LONG readArray[], ULONG arrayLen);
	// �����Чֵ
	double	_GetArrayRMS(LONG readArray[], ULONG arrayLen);

	std::vector<std::vector<double>>	m_ReadVec;

	std::vector<int> m_VecInsertIndex;
	std::vector<int> m_VecOutIndex;
	void InsertAChannelValue(int iChannel,double* dValue,int ValueCount);

	int m_DataRate;
	int m_PerRead;
	CRITICAL_SECTION m_ValueListSEC;

private:
	HANDLE			m_hDevice;
	BOOL		m_bCreateSuccess;
	BOOL		m_bIsStart;
	HANDLE		m_hMutex;
	ILogInfo*	m_pIErrLog;
	CLogFile_PXI8265	m_logFile;

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
		ULONG				cardLgcID;
		ULONG				cardSlotID;
		READ_AI_INFO		sArrSegAI[SEG_MAX];
		LONG				lastSegIndex;
		CPXI8265_AI*		pClass;
		std::vector<double>	vcVolt;
		std::vector<double>	vcVoltRMS;
	}DEV_AI, *PDEV_AI;

	DEV_AI			m_sDevAI[CARD_COUNT];
	
	friend bool CompareLess(DEV_AI& __left, DEV_AI& __right);
};

#endif // !defined(AFX_PCI8735CLASS_H__B81383EF_639D_4DEE_AB9A_F26ADE08C5BF__INCLUDED_)
