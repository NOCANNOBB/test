#include "stdafx.h"
#include "AO_ALL.h"


CAO_ALL::CAO_ALL(void)
{
}


CAO_ALL::~CAO_ALL(void)
{
}


BOOL CAO_ALL::Create(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Create();
	}

	return bRet;
}

BOOL CAO_ALL::Release(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Release();
	}

	return bRet;
}

BOOL CAO_ALL::LoadParam(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->LoadParam();
	}

	return bRet;
}

BOOL CAO_ALL::Init(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Init();
	}

	return bRet;
}

int CAO_ALL::GetChCount(void)
{
	ULONG chanCount = 0;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		chanCount += m_dqIBaseClass[i]->GetChCount();
	}

	return chanCount;
}

BOOL CAO_ALL::Start(ULONG ulChan)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Start(ulChan);
	}

	return bRet;
}

BOOL CAO_ALL::Stop(ULONG ulChan)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Stop(ulChan);
	}

	return bRet;
}

void CAO_ALL::SetErrorLog(ILogInfo* log)
{

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		m_dqIBaseClass[i]->SetErrorLog(log);
	}

}

BOOL CAO_ALL::WriteAO(ULONG ulChan, double pulseWidthMS){

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
			bRet = m_dqIBaseClass[i]->WriteAO(ulChan, pulseWidthMS);
			break;
		}
	}

	return bRet;
}