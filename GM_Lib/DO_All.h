#pragma once
#include "ibasehead.h"


class CDO_All :
	public IBaseDO
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
	virtual BOOL WriteDO(ULONG ulChan, BOOL boolVlaue);
	virtual BOOL ReadDO(ULONG ulChan,BOOL* boolVlaue);

	virtual BOOL WriteDO(ULONG ulChan, byte* boolVlaue);
	virtual BOOL ReadDO(ULONG ulChan,byte* boolVlaue);

public:
	BOOL Push_IBaseDO(IBaseDO* pIBaseDO)
	{
		m_dqIBaseClass.push_back(pIBaseDO);
		return TRUE;
	}
protected:
	std::deque<IBaseDO*> m_dqIBaseClass;
public:
	CDO_All(void);
	~CDO_All(void);
};

