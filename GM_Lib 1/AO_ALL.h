#pragma once
class CAO_ALL:public IBaseOutAO
{
public:
	CAO_ALL(void);
	~CAO_ALL(void);
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
	virtual BOOL WriteAO(ULONG ulChan, double pulseWidthMS);

public:
	BOOL Push_IBaseAO(IBaseOutAO* pIBaseCNT)
	{
		m_dqIBaseClass.push_back(pIBaseCNT);
		return TRUE;
	}
protected:
	std::deque<IBaseOutAO*> m_dqIBaseClass;
};

