#ifndef __AI_ALL__
#define __AI_ALL__
#include <deque>

class CAI_All : public IBaseAI
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
	// 这里返回的是电压值，单位是V
	virtual BOOL ReadOneDC(ULONG ulChan, double* dfVolt) ;

public:
	BOOL Push_IBaseAI(IBaseAI* pIBaseAI)
	{
		m_dqIBaseClass.push_back(pIBaseAI);
		return TRUE;
	}
public:
	CAI_All();
	virtual ~CAI_All();
protected:
	std::deque<IBaseAI*> m_dqIBaseClass;
};
#endif