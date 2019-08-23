#include "StdAfx.h"
#include "CardCtrl.h"

#define Init_PointClass(__pClass) __pClass=NULL;
#define New_PointClass(__pClass, __className) if (__pClass==NULL){__pClass=new __className;}
#define Delete_PointClass(__pClass) if (__pClass!=NULL){delete __pClass; Init_PointClass(__pClass);}

CCardCtrlATPLib::CCardCtrlATPLib(void)
{
	m_pILogInfo = NULL;
	m_pPXI8265_AI = NULL;
	m_pPXI8867_AO = NULL;
	m_pPXI8417 = NULL;
	m_pPXI8510 = NULL;
	m_pPXI8530 = NULL;
	m_pPXI8310 = NULL;
	Init_PointClass(m_aiALL);
}

CCardCtrlATPLib::~CCardCtrlATPLib(void)
{
	if (m_pPXI8265_AI != NULL)
	{
		delete m_pPXI8265_AI;
		m_pPXI8265_AI = NULL;
	}

	if (m_pPXI8867_AO != NULL)
	{
		delete m_pPXI8867_AO;
		m_pPXI8867_AO = NULL;
	}

	if (m_pPXI8417 != NULL)
	{
		delete m_pPXI8417;
		m_pPXI8417 = NULL;
	}
	
	if (m_pPXI8510 != NULL)
	{
		delete m_pPXI8510;
		m_pPXI8510 = NULL;
	}

	if (m_pPXI8530 != NULL)
	{
		delete m_pPXI8530;
		m_pPXI8530 = NULL;
	}

	if (m_pPXI8310 != NULL)
	{
		delete m_pPXI8310;
		m_pPXI8310 = NULL;
	}

	Delete_PointClass(m_aiALL);
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
		New_PointClass(m_pPXI8265_AI, CPXI8265_AI);
		New_PointClass(m_pPXI8417, CPXI8417_Total);

		m_aiALL->Push_IBaseAI(static_cast<IBaseAI*>(m_pPXI8265_AI));// 2*48 + 1*16
		m_aiALL->Push_IBaseAI(static_cast<IBaseAI*>(m_pPXI8417));
	}

	return static_cast<IBaseAI*>(m_aiALL);
}

IBaseOutDC* CCardCtrlATPLib::GetBaseOutDC(void)
{
	if (m_pPXI8867_AO == NULL)
	{
		m_pPXI8867_AO = new CPXI8867_AO;
	}
	return static_cast<IBaseOutDC*>(m_pPXI8867_AO);
}

IBaseIR* CCardCtrlATPLib::GetIR(void)
{
	if (m_pPXI8417 == NULL)
	{
		m_pPXI8417 = new CPXI8417_Total;
	}
	return static_cast<IBaseIR*>(m_pPXI8417);;
}

IBaseOC* CCardCtrlATPLib::GetOC(void)
{
	if (m_pPXI8417 == NULL)
	{
		m_pPXI8417 = new CPXI8417_Total;
	}
	return static_cast<IBaseOC*>(m_pPXI8417 );;
}

IBaseLvdsRecv* CCardCtrlATPLib::GetBseLvdsRecv(void)
{
	if (m_pPXI8510 == NULL)
	{
		m_pPXI8510 = new CPXI8510_Total;
	}

	return static_cast<IBaseLvdsRecv*>(m_pPXI8510);
}

IBase1PPS* CCardCtrlATPLib::GetGPS(void)
{
	if (m_pPXI8417 == NULL)
	{
		m_pPXI8417 = new CPXI8417_Total;
	}
	return static_cast<IBase1PPS*>(m_pPXI8417 );;
}

IBaseOHM* CCardCtrlATPLib::GetOHM(void)
{
	New_PointClass(m_pPXI8310, CPXI8310_OHM);

	return static_cast<IBaseOHM*>(m_pPXI8310);
}

IBaseRecvSync422* CCardCtrlATPLib::GetSync422Recv(void)
{
	if (m_pPXI8530 == NULL)
	{
		m_pPXI8530 = new CPXI8530_Total;
	}

	return static_cast<IBaseRecvSync422*>(m_pPXI8530);
}

IBaseSendSync422* CCardCtrlATPLib::GetSync422Send(void)
{
	if (m_pPXI8530 == NULL)
	{
		m_pPXI8530 = new CPXI8530_Total;
	}

	return static_cast<IBaseSendSync422*>(m_pPXI8530);
}

IBaseMeasFrameCircle*	CCardCtrlATPLib::GetMeasCircleFrame(void)
{
	New_PointClass(m_pPXI8530, CPXI8530_Total);

	return static_cast<IBaseMeasFrameCircle*>(m_pPXI8530);
}

IBaseLvdsSendFrameCircleData*	CCardCtrlATPLib::GetBseLvdsSendFrameCircleData()
{
	New_PointClass(m_pPXI8510, CPXI8510_Total);

	return static_cast<IBaseLvdsSendFrameCircleData*>(m_pPXI8510);
}

IBaseASync422* CCardCtrlATPLib::GetASync(void)
{
	New_PointClass(m_pPXI8530, CPXI8530_Total);

	return static_cast<IBaseASync422*>(m_pPXI8530);
}

IBaseLvdsSend* CCardCtrlATPLib::GetBseLvdsSend(void)
{
	return NULL;
}
