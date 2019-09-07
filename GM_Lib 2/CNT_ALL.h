#pragma once
#include "ibasehead.h"

class CCNT_ALL:public IBaseCNT
{

public:
	virtual BOOL Create(void) ;
	virtual BOOL Release(void) ;
	virtual BOOL LoadParam(void) ;
	virtual BOOL Init(void) ;
	virtual int GetChCount(void) ;

	virtual BOOL Start(ULONG ulChan=0) ;
	virtual BOOL Stop(ULONG ulChan=0) ;

	virtual void SetErrorLog(ILogInfo* log) ;
public:
	// ���ﷵ�ص��ǵ�ѹֵ����λ��V
	virtual BOOL GetdfFreqAnddfdfDutyCycle(ULONG ulChan, double* dfFreq,double* dfdfDutyCycle);

public:
	BOOL Push_IBaseCNT(IBaseCNT* pIBaseCNT)
	{
		m_dqIBaseClass.push_back(pIBaseCNT);
		return TRUE;
	}
protected:
	std::deque<IBaseCNT*> m_dqIBaseClass;
public:
	CCNT_ALL(void);
	~CCNT_ALL(void);
};

