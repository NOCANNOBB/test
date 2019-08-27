#pragma once
#include "IBaseHead.h"
#include "PXI6416_DO.h"
#include "DO_All.h"
#include "CNT_ALL.h"
#include "PXI6435D_CNT.h"
#include "PXI6860_AO.h"
#include "All_AI.h"
#include "PXI8265_AI.h"
#include "PXI8265_Total.h"
#include "AO_ALL.h"
class CCardCtrlATPLib :
	public IExCardCtrl
{
public:
	static IExCardCtrl* __stdcall CreateLibrary();

public:
	virtual ULONG GetVersion();

	virtual IBaseAI* GetBaseAI(void);
	
	virtual IBaseDO* GetBaseDO(void);
	virtual IBaseCNT* GetBaseCNT(void);

	virtual IBaseOutAO* GetBaseOutAO(void);
	//virtual IBaseDIO* GetDIO(void);



	virtual BOOL SetLogInfo(ILogInfo* pInfo)
	{m_pILogInfo = pInfo; return TRUE;};

	virtual void ReleaseLibrary();
public:
	CCardCtrlATPLib(void);
	virtual ~CCardCtrlATPLib(void);
private:
	ILogInfo*	m_pILogInfo;
	PXI6416_DO* m_pXI6416_DO;
	PXI6435D_CNT * m_pXI6435D_CNT;
	CPXI6860_AO* m_pXI6860_AO;
	
	CPXI8265_AI* m_pXI8265_AI;

	CPXI8265_Total* m_pCPXI8265_Total;
	CDO_All*        m_doALL;
	CCNT_ALL*		m_CntALL;
	CAI_All*	m_aiALL;
	CAO_ALL*	m_aoALL;
};
