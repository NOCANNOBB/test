#ifndef __PXI8530_SYNC422_SEND__
#define __PXI8530_SYNC422_SEND__

#pragma once

class CPXI8530_Sync422Send : public IBaseSendSync422
{
public:
	enum {
		CARD_COUNT = 2,
	};

	virtual BOOL Create(void) ;
	virtual BOOL Release(void) ;
	virtual BOOL LoadParam(void) ;
	virtual BOOL Init(void) ;
	virtual int GetChCount(void) ;

	virtual BOOL Start(ULONG ulChan=0) ;
	virtual BOOL Stop(ULONG ulChan=0) ;

	virtual void SetErrorLog(ILogInfo* log) 
	{m_pLogInfo = log;}
public:

	// ����ȦЭ�� 160�ֽ�
	virtual BOOL SendCircle(ULONG ulChan, BYTE byReadBuff[], ULONG ulWriteLen);
	// ����֡Э�� 80�ֽ�
	virtual BOOL SendFrame(ULONG ulChan, BYTE byReadBuff[], ULONG ulWriteLen);
	// �����������
	virtual BOOL CfgPulseOut(		// ���������������, ��д��ȦЭ���֡Э��
		ULONG	ulChan,				// ͨ����
		double	circleWidth,		// Ȧ���������� ��λmS ����0.1 �ο� 50~150, ��Χ 0.1~6553.5
		double	circleCycle,		// Ȧ������������ ��λmS ����0.1 �ο� 500~3000, ��Χ 0.1~6553.5
		double	frameWidth,			// ֡ͬ��������� ��λmS ����0.01 �ο� 0.25~1.5, ��Χ 0.01~2.55
		double	frameCycle,			// ֡ͬ���������� ��λmS ��С0.01 �ο� 1~3, ��Χ 0.01~5.12
		double	frameDelayCircle,	// ֡��������Ȧ�ź���ʱ���� ��λmS ��С0.1 �ο� 50~600, ��Χ 0.1~819.2
		ULONG	unit1BeingPos,		// ��һ�� ��ʼλ�� 0 ~ 1023
		ULONG	unit1EndPos,		// ��һ�� ����λ�� 0 ~ 1023
		ULONG	unit2BeingPos,		// �ڶ��� ��ʼλ�� 0 ~ 1023
		ULONG	unit2EndPos,		// �ڶ��� ����λ�� 0 ~ 1023
		ULONG	unit3BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
		ULONG	unit3EndPos,		// ������ ����λ�� 0 ~ 1023
		ULONG	unit4BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
		ULONG	unit4EndPos,		// ������ ����λ�� 0 ~ 1023
		ULONG	unit5BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
		ULONG	unit5EndPos,		// ������ ����λ�� 0 ~ 1023
		ULONG	unit6BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
		ULONG	unit6EndPos,		// ������ ����λ�� 0 ~ 1023
		ULONG	unit7BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
		ULONG	unit7EndPos);
	virtual BOOL GetCount(			// ���֡Ȧ����ֵ
		ULONG	ulChan,				// ͨ����
		ULONG*	pCircleCnt,			// ����Ȧͬ������ֵ
		ULONG*	pFrameCnt);			// ����֡ͬ������ֵ
	// ѡ��pxitrig ���ͨ��
	virtual BOOL SelMainTrig(ULONG ulChan, BOOL bOut = TRUE);
	// PPS�źŵ�����ʹ��
	virtual BOOL SetPPSMainOrViceEnable(ULONG ulChan, BOOL chan0En, BOOL chan1En);

public:
	BOOL	_IsDevEmpty() // �豸�Ƿ�Ϊ��
	{
		return IsHandleInvalid(m_hDevice);
	};

	virtual void SetHandle(HANDLE hDevice0, HANDLE hDevice1){
		m_hDevice[0] = hDevice0;
		m_hDevice[1] = hDevice1;}

	CPXI8530_Sync422Send();
	virtual ~CPXI8530_Sync422Send();
private:
	BOOL __IsErr(LONG result, CString& strRetErr);

public:
	void _WriteLog(LPCSTR lpszInfo, ...);

private:
	HANDLE		m_hDevice[CARD_COUNT];
	ILogInfo*	m_pLogInfo;
	CLogFile	m_logFile;
	int			m_iAdd;
	ULONG		m_iLvdsSendRate;
	BOOL		m_bStart;
	BOOL		m_bInit;
	std::vector<BYTE>	m_vcCircle;
	std::vector<BYTE>	m_vcFrame;

	double m_circleWidth	;
	double m_circleCycle	;
	double m_frameWidth		;
	double m_frameCycle		;
	double m_frameDelayCircle;	
	ULONG m_unit1BeingPos	;	
	ULONG m_unit1EndPos		;
	ULONG m_unit2BeingPos	;	
	ULONG m_unit2EndPos		;
	ULONG m_unit3BeingPos	;	
	ULONG m_unit3EndPos		;
	ULONG m_unit4BeingPos	;	
	ULONG m_unit4EndPos		;
	ULONG m_unit5BeingPos	;	
	ULONG m_unit5EndPos		;
	ULONG m_unit6BeingPos	;	
	ULONG m_unit6EndPos		;
	ULONG m_unit7BeingPos	;	
	ULONG m_unit7EndPos		;

};

#endif