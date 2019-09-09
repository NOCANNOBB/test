#include "StdAfx.h"
#include "CardCtrl.h"

#define Init_PointClass(__pClass) __pClass=NULL;
#define New_PointClass(__pClass, __className) if (__pClass==NULL){__pClass=new __className;}
#define Delete_PointClass(__pClass) if (__pClass!=NULL){delete __pClass; Init_PointClass(__pClass);}

CCardCtrlATPLib::CCardCtrlATPLib(void)
{
	m_pILogInfo = NULL;
	
	m_pXI6416_DO		= NULL;
	m_pXI6435D_CNT		= NULL;
	m_pXI8265_AI		= NULL;
	m_pCPXI8265_Total	= NULL;
	m_pXI6860_AO		= NULL;
	Init_PointClass(m_doALL);
	Init_PointClass(m_CntALL);
	Init_PointClass(m_aiALL);
	Init_PointClass(m_aoALL);
}

CCardCtrlATPLib::~CCardCtrlATPLib(void)
{
	if (m_pXI6416_DO != NULL)
	{
		delete m_pXI6416_DO;
		m_pXI6416_DO = NULL;
	}
	if (m_pXI6435D_CNT != NULL)
	{
		delete m_pXI6435D_CNT;
		m_pXI6435D_CNT = NULL;
	}
	if (m_pXI6860_AO != NULL)
	{
		delete m_pXI6860_AO;
		m_pXI6860_AO = NULL;
	}
	if (m_pCPXI8265_Total != NULL)
	{
		delete m_pCPXI8265_Total;
		m_pCPXI8265_Total = NULL;
	}
	
	Delete_PointClass(m_doALL);
	Delete_PointClass(m_CntALL);
	Delete_PointClass(m_aiALL);
	Delete_PointClass(m_aoALL);
}

IExCardCtrl* __stdcall CCardCtrlATPLib::CreateLibrary()
{
	return static_cast<IExCardCtrl*>(new CCardCtrlATPLib);
}

ULONG CCardCtrlATPLib::GetVersion()
{
	return (EXLIB_VERSION);
}

void CCardCtrlATPLib::ReleaseLibrary()
{
	delete this;
}

IBaseAI* CCardCtrlATPLib::GetBaseAI(void)
{
	if (m_aiALL == NULL)
	{
		New_PointClass(m_aiALL, CAI_All);
		New_PointClass(m_pCPXI8265_Total,CPXI8265_Total)

		m_aiALL->Push_IBaseAI(static_cast<IBaseAI*>(m_pCPXI8265_Total));// 2*48 + 1*16
	}

	return static_cast<IBaseAI*>(m_aiALL);
}

IBaseOutAO* CCardCtrlATPLib::GetBaseOutAO(void){
	
	
	if (m_aoALL == NULL)
	{
		New_PointClass(m_aoALL, CAO_ALL);
		New_PointClass(m_pXI6860_AO,CPXI6860_AO);
		New_PointClass(m_pCPXI8265_Total,CPXI8265_Total);

		m_aoALL->Push_IBaseAO(static_cast<IBaseOutAO*>(m_pXI6860_AO));
		m_aoALL->Push_IBaseAO(static_cast<IBaseOutAO*>(m_pCPXI8265_Total));
	}

	return static_cast<IBaseOutAO*>(m_aoALL);
}


IBaseDO * CCardCtrlATPLib::GetBaseDO(void){

	if (m_doALL == NULL)
	{
		New_PointClass(m_doALL, CDO_All);
		New_PointClass(m_pXI6416_DO, PXI6416_DO);
		
		m_doALL->Push_IBaseDO(static_cast<IBaseDO*>(m_pXI6416_DO));// 2*48 + 1*16
	}

	return static_cast<IBaseDO*>(m_doALL);
}

IBaseCNT * CCardCtrlATPLib::GetBaseCNT(void){
	if (m_doALL == NULL)
	{
		New_PointClass(m_CntALL, CCNT_ALL);
		New_PointClass(m_pXI6435D_CNT, PXI6435D_CNT);

		m_CntALL->Push_IBaseCNT(static_cast<IBaseCNT*>(m_pXI6435D_CNT));// 2*48 + 1*16
	}

	return static_cast<IBaseCNT*>(m_CntALL);
}




