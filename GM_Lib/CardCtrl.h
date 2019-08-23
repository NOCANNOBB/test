#pragma once
#include "IBaseHead.h"
#include "PXI8265_AI.h"
#include "PXI8867_AO.h"
#include "PXI8417_Total.h"
#include "PXI8510_Total.h"
#include "PXI8530_Total.h"
#include "PXI8310_OHM.h"
#include "All_AI.h"

class CCardCtrlATPLib :
	public IExCardCtrl
{
public:
	static IExCardCtrl* __stdcall CreateLibrary();

public:
	virtual ULONG GetVersion();

	virtual IBaseAI* GetBaseAI(void);
	virtual IBaseOutDC* GetBaseOutDC(void);
	virtual IBaseIR* GetIR(void);
	virtual IBaseOC* GetOC(void);
	virtual IBase1PPS* GetGPS(void);
	virtual IBaseOHM* GetOHM(void);
	virtual IBaseRecvSync422* GetSync422Recv(void);
	virtual IBaseSendSync422* GetSync422Send(void);
	virtual IBaseASync422* GetASync(void);
	virtual IBaseLvdsSend* GetBseLvdsSend(void);
	virtual IBaseLvdsRecv* GetBseLvdsRecv(void);
	virtual IBaseMeasFrameCircle*	GetMeasCircleFrame(void);
	virtual IBaseLvdsSendFrameCircleData*	GetBseLvdsSendFrameCircleData();

	virtual BOOL SetLogInfo(ILogInfo* pInfo)
	{m_pILogInfo = pInfo; return TRUE;};

	virtual void ReleaseLibrary();
public:
	CCardCtrlATPLib(void);
	virtual ~CCardCtrlATPLib(void);
private:
	ILogInfo*	m_pILogInfo;
	CPXI8265_AI*	m_pPXI8265_AI;
	CPXI8867_AO*	m_pPXI8867_AO;
	CPXI8417_Total* m_pPXI8417;
	CPXI8510_Total* m_pPXI8510;
	CPXI8530_Total* m_pPXI8530;
	CPXI8310_OHM*	m_pPXI8310;
	CAI_All*		m_aiALL;
};
