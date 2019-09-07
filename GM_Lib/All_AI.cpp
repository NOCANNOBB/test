#include "stdafx.h"
#include "All_AI.h"

CAI_All::CAI_All()
{

}

CAI_All::~CAI_All()
{

}

BOOL CAI_All::Create(void)
{
	BOOL bRet = TRUE;
	
	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Create();
	}

	return bRet;
}

BOOL CAI_All::Release(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Release();
	}

	return bRet;
}

BOOL CAI_All::LoadParam(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->LoadParam();
	}

	return bRet;
}

BOOL CAI_All::Init(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Init();
	}

	return bRet;
}

int CAI_All::GetChCount(void)
{
	ULONG chanCount = 0;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		chanCount += m_dqIBaseClass[i]->GetChCount();
	}

	return chanCount;
}

BOOL CAI_All::Start(ULONG ulChan)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Start(ulChan);
	}

	return bRet;
}

BOOL CAI_All::Stop(ULONG ulChan)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Stop(ulChan);
	}

	return bRet;
}

void CAI_All::SetErrorLog(ILogInfo* log)
{

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		 m_dqIBaseClass[i]->SetErrorLog(log);
	}

}

// 这里返回的是电压值，单位是V
BOOL CAI_All::ReadOneDC(ULONG ulChan, double* dfVolt)
{
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
			bRet = m_dqIBaseClass[i]->ReadOneDC(ulChan, dfVolt);
			break;
		}
	}

	return bRet;
}
void CAI_All::GetDataFromBord(ULONG ulChan,double* pBuffer, int ReadSize, int* retReadSize){
	ULONG ulChCount = 0;
	ULONG ulChCountBK; 
	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		ulChCountBK = ulChCount;
		ulChCount += m_dqIBaseClass[i]->GetChCount();
		if (ulChan < ulChCount)
		{
			ulChan = ulChan - ulChCountBK;
			m_dqIBaseClass[i]->GetDataFromBord(ulChan,pBuffer,ReadSize,retReadSize);
			break;
		}
	}
}

void CAI_All::SetDataRate(int RateValue,int PerRead){
	
	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		m_dqIBaseClass[i]->SetDataRate(RateValue,PerRead);
	}
}
