//////////////////////////////////////////////////////////////////////

#ifndef __PXI8265_AI__
#define __PXI8265_AI__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IBaseHead.h"
#include "vector"

#define PXI8265_CARD_COUNT		(1)
#define PXI8265_CHAN_COUNT		(48)
#define PXI8265_SEG_MAX			(16)



class CLogFile_PXI8265 
{
public:
	virtual BOOL WriteLog(LPCSTR lpszInfo, ...)
	{
		char szData[2048];
		SYSTEMTIME TmpTime;

		GetLocalTime(&TmpTime);			// 获得当地时间

		va_list va;
		va_start(va, lpszInfo);
		wvsprintfA(szData, lpszInfo, va);
		va_end(va);

		// 出错时间
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
	virtual BOOL ReadOneDC(ULONG ulChan, double* dfAD);
	virtual BOOL ReadOneRMS(ULONG ulChan, double* dfAD);
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
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return !m_bCreateSuccess;
	};

	void	_WriteLog(LPCSTR lpszInfo, ...);
	BOOL	_IsErrChk(LONG err, ULONG ulCard);
	ULONG	_FilteArray(LONG readArray[], ULONG arrayLen);
	// 获得电压值，顺便滤波
	double	_GetArrayVolt(LONG readArray[], ULONG arrayLen);
	// 获得有效值
	double	_GetArrayRMS(LONG readArray[], ULONG arrayLen);
private:
	HANDLE			m_hDevice;
	BOOL		m_bCreateSuccess;
	BOOL		m_bIsStart;
	HANDLE		m_hMutex;
	ILogInfo*	m_pIErrLog;
	CLogFile_PXI8265	m_logFile;

	typedef struct _READ_AI_INFO
	{
		LONG* readArray;	// 读取的数据
		LONG  arrayLen;		// arrayLen 读取的点数
		LONG  singleLen;	// 单通道数据点数
	}READ_AI_INFO, *PREAD_AI_INFO;

	typedef struct _DEV_AI
	{
		BOOL				bThreadRun;
		HANDLE				hDev;
		HANDLE				hThreadReadAI;		// 读取AI数据线程
		HANDLE				hThreadProcessing;	// 处理线程
		ULONG				cardLgcID;
		ULONG				cardSlotID;
		READ_AI_INFO		sArrSegAI[PXI8265_SEG_MAX];
		LONG				lastSegIndex;
		CPXI8265_AI*		pClass;
		std::vector<double>	vcVolt;
		std::vector<double>	vcVoltRMS;
	}DEV_AI, *PDEV_AI;

	DEV_AI			m_sDevAI[PXI8265_CARD_COUNT];
	
	friend bool CompareLess(DEV_AI& __left, DEV_AI& __right);
};

#endif // !defined(AFX_PCI8735CLASS_H__B81383EF_639D_4DEE_AB9A_F26ADE08C5BF__INCLUDED_)
