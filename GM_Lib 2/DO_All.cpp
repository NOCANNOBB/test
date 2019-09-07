#include "stdafx.h"
#include "DO_All.h"


CDO_All::CDO_All(void)
{
}


CDO_All::~CDO_All(void)
{
}

BOOL CDO_All::Create(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Create();
	}

	return bRet;
}

BOOL CDO_All::Release(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Release();
	}

	return bRet;
}

BOOL CDO_All::LoadParam(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->LoadParam();
	}

	return bRet;
}

BOOL CDO_All::Init(void)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Init();
	}

	return bRet;
}

int CDO_All::GetChCount(void)
{
	ULONG chanCount = 0;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		chanCount += m_dqIBaseClass[i]->GetChCount();
	}

	return chanCount;
}

BOOL CDO_All::Start(ULONG ulChan)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Start(ulChan);
	}

	return bRet;
}

BOOL CDO_All::Stop(ULONG ulChan)
{
	BOOL bRet = TRUE;

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		bRet = bRet && m_dqIBaseClass[i]->Stop(ulChan);
	}

	return bRet;
}

void CDO_All::SetErrorLog(ILogInfo* log)
{

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		m_dqIBaseClass[i]->SetErrorLog(log);
	}

}

//

BOOL CDO_All::WriteDO(ULONG ulChan, byte boolVlaue)
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
			bRet = m_dqIBaseClass[i]->WriteDO(ulChan, boolVlaue);
			break;
		}
	}

	return bRet;
}


//
BOOL CDO_All::ReadDO(ULONG ulChan,byte* boolValue)
{
	BOOL bRet = FALSE;
	ULONG ulChCount = 0;
	ULONG ulChCountBK; 

	for (ULONG i=0; i<m_dqIBaseClass.size(); i++)
	{
		ulChCountBK = ulChCount;
		ulChCount += m_dqIBaseClass[i]->GetChCount();
		if (ulChan < ulChCount)
		{
			ulChan = ulChan - ulChCountBK;
			bRet = m_dqIBaseClass[i]->ReadDO(ulChan, boolValue);
			break;
		}
	}

	return bRet;
}
