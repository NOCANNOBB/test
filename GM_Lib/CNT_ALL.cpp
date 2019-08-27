#include "stdafx.h"
#include "CNT_ALL.h"


CCNT_ALL::CCNT_ALL(void)
{
}


CCNT_ALL::~CCNT_ALL(void)
{
}

BOOL CCNT_ALL::Create(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Create();
	}

	return bRet;
}

BOOL CCNT_ALL::Release(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Release();
	}

	return bRet;
}

BOOL CCNT_ALL::LoadParam(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->LoadParam();
	}

	return bRet;
}

BOOL CCNT_ALL::Init(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Init();
	}

	return bRet;
}

int CCNT_ALL::GetChCount(void)
{
	ULONG chanCount = 0;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		chanCount += m_dqIBaseClass[i]->GetChCount();
	}

	return chanCount;
}

BOOL CCNT_ALL::Start(ULONG ulChan)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Start(ulChan);
	}

	return bRet;
}

BOOL CCNT_ALL::Stop(ULONG ulChan)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Stop(ulChan);
	}

	return bRet;
}

void CCNT_ALL::SetErrorLog(ILogInfo* log)
{

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		m_dqIBaseClass[i]->SetErrorLog(log);
	}

}

BOOL CCNT_ALL::GetdfFreqAnddfdfDutyCycle(ULONG ulChan, double* dfFreq,double* dfdfDutyCycle){

	BOOL bRet = TRUE;
	ULONG ulChCount = 0;
	ULONG ulChCountBK; 

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		ulChCountBK = ulChCount;
		ulChCount += m_dqIBaseClass[i]->GetChCount();
		if (ulChan < ulChCount)
		{
			ulChan = ulChan - ulChCountBK;
			bRet = m_dqIBaseClass[i]->GetdfFreqAnddfdfDutyCycle(ulChan, dfFreq,dfdfDutyCycle);
			break;
		}
	}

	return bRet;
}
