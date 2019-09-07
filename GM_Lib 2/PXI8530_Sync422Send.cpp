#include "stdafx.h"
#include "PXI8530_Sync422Send.h"
#include "PXI8530.h"

CPXI8530_Sync422Send::CPXI8530_Sync422Send()
{
	m_iAdd = 0;
	
	for (ULONG i=0; i<CARD_COUNT; i++)
	{
		m_hDevice[i] = INVALID_HANDLE_VALUE;
	}

	m_logFile.SetFileName(EXCARD_LOGNAME);
	m_pLogInfo = NULL;

	m_bStart = FALSE;
}

CPXI8530_Sync422Send::~CPXI8530_Sync422Send()
{
	for (ULONG i=0; i<CARD_COUNT; i++)
	{
		if (m_hDevice[i] != INVALID_HANDLE_VALUE)
		{
			Release();
			m_hDevice[i] = INVALID_HANDLE_VALUE;
		}
	}
}

BOOL CPXI8530_Sync422Send::Create(void)
{
	return TRUE;
}

BOOL CPXI8530_Sync422Send::Release(void)
{
	Stop();
	return TRUE;	
}

BOOL CPXI8530_Sync422Send::LoadParam(void)
{
	return TRUE;
}

BOOL CPXI8530_Sync422Send::Init(void)
{
	_IsWarningRet("Init");

	m_bInit = TRUE;

	for (ULONG i=0; i<CARD_COUNT; i++)
	{
		if (m_hDevice[i] != INVALID_HANDLE_VALUE)
		{
			PXI8530_SYNC422_SendInitChan(m_hDevice, 0, 1000, 1E+6, 100000);
			PXI8530_SYNC422_SendCfgTrigExtern(m_hDevice, 0);
		}
	}

	return TRUE;
}

int CPXI8530_Sync422Send::GetChCount(void)
{
	return (CARD_COUNT*1);
}

BOOL CPXI8530_Sync422Send::Start(ULONG ulChan)
{
	_IsWarningRet("Start");

	if ((ulChan<0) || (ulChan>CARD_COUNT))	return FALSE;

	LONG result;

 	result = PXI8530_SYNC422_SendInitChan(m_hDevice[ulChan], 0, 80, 1E+6, 100000);

	result = PXI8530_SYNC422_SendCfgTrigExtern(m_hDevice[ulChan], 0);

	if (m_vcFrame.size() != 0)
	{
		result = PXI8530_SYNC422_SendTrigFrame(m_hDevice[ulChan], 0, &m_vcFrame[0], m_vcFrame.size());
//		_WriteLog("frameLen:%d, %d", m_vcFrame.size(), result);
	}

	if (m_vcCircle.size() != 0)
	{
		PXI8530_SYNC422_SendTrigCircle(m_hDevice[ulChan], 0, &m_vcCircle[0], m_vcCircle.size());
//		_WriteLog("Circle:%d, %d", m_vcCircle.size(), result);
	}
	
	result = PXI8530_SYNC422_SendStart(m_hDevice[ulChan], 0, PXI8530_SYNC422_CLK_Continue);

	CString strErr;

	if (__IsErr(result, strErr))
	{ // ����
		PXI8530_PulseOut_Stop(m_hDevice[ulChan]);
		_WriteLog(_T("Sync422 Send  Start ����:%s"), strErr);
		return FALSE;
	}

	Sleep(1);
	PXI8530_PulseOut_Cfg(m_hDevice[ulChan],
		m_circleWidth,			m_circleCycle,		
		m_frameWidth,			m_frameCycle,			
		m_frameDelayCircle,
		m_unit1BeingPos,		m_unit1EndPos,
		m_unit2BeingPos,		m_unit2EndPos,
		m_unit3BeingPos,		m_unit3EndPos,
		m_unit4BeingPos,		m_unit4EndPos,
		m_unit5BeingPos,		m_unit5EndPos,
		m_unit6BeingPos,		m_unit6EndPos,
		m_unit7BeingPos,		m_unit7EndPos);


	result = PXI8530_PulseOut_Start(m_hDevice[ulChan]);

	m_bStart = TRUE;

	return TRUE;
}

BOOL CPXI8530_Sync422Send::Stop(ULONG ulChan)
{
	if (!m_bStart) return TRUE;
	if ((ulChan<0) || (ulChan>CARD_COUNT))	return FALSE;

	_IsWarningRet("Stop");

	PXI8530_PulseOut_Stop(m_hDevice[ulChan]);
	Sleep(1);
	LONG result = PXI8530_SYNC422_SendStop(m_hDevice[ulChan], 0);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ����
		_WriteLog(_T("Sync422 Send Stop ����:%s"), strErr);
		return FALSE;
	}

	m_bStart = FALSE;

	return TRUE;

}

// ����ȦЭ�� 160�ֽ�
BOOL CPXI8530_Sync422Send::SendCircle(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen)
{
	_IsWarningRet("SendCircle");

	LONG result = PXI8530_SYNC422_SendTrigCircle(m_hDevice, 0, byWriteBuff, ulWriteLen);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ����
		_WriteLog(_T("SendTrigCircle ����:%s"), strErr);
		return FALSE;
	}

	m_vcCircle.resize(ulWriteLen);
	memcpy(&m_vcCircle[0], byWriteBuff, ulWriteLen);

	return TRUE;
}

// ����֡Э�� 80�ֽ�
BOOL CPXI8530_Sync422Send::SendFrame(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen)
{
	_IsWarningRet("SendFrame");

	LONG result = PXI8530_SYNC422_SendTrigFrame(m_hDevice[ulChan], 0, byWriteBuff, ulWriteLen);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ����
		_WriteLog(_T("SendTrigFrame ����:%s"), strErr);
		return FALSE;
	}

	m_vcFrame.resize(ulWriteLen);
	memcpy(&m_vcFrame[0], byWriteBuff, ulWriteLen);

	return TRUE;
}

// PPS�źŵ�����ʹ��
BOOL CPXI8530_Sync422Send::SetPPSMainOrViceEnable(ULONG ulChan, BOOL chan0En, BOOL chan1En)
{
	_IsWarningRet("SetPPSMainOrViceEnable");

	LONG result = PXI8530_SetPPSMainOrViceEnable(m_hDevice[ulChan], chan0En, chan1En);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ����
		_WriteLog(_T("SetPPSMainOrViceEnable ����:%s"), strErr);
		return FALSE;
	}

	return TRUE;
}

// �����������
BOOL CPXI8530_Sync422Send::CfgPulseOut(				// ���������������, ��д��ȦЭ���֡Э��
						 ULONG	ulChan,				// ͨ����
						 double	circleWidth,		// Ȧ���������� ��λmS ����0.1 �ο� 50~150, ��Χ 0.1~6553.5
						 double	circleCycle,		// Ȧ������������ ��λmS ����0.1 �ο� 500~3000, ��Χ 0.1~6553.5
						 double	frameWidth,			// ֡ͬ��������� ��λmS ����0.01 �ο� 0.25~1.5, ��Χ 0.01~2.55
						 double	frameCycle,			// ֡ͬ���������� ��λmS ��С0.01 �ο� 1~3, ��Χ 0.01~5.12
						 double	frameDelayCircle,	// ֡��������Ȧ�ź���ʱ���� ��λmS ��С0.1 �ο� 50~600, ��Χ 0.1~819.2
						 ULONG	unit1BeingPos,		// ��һ�� ��ʼλ�� 0 ~ 1023
						 ULONG	unit1EndPos,		// ��һ�� ����λ�� 0 ~ 1023
						 ULONG	unit2BeingPos,		// �ڶ��� ��ʼλ�� 0 ~ 1023
						 ULONG	unit2EndPos,		// �ڶ��� ����λ�� 0 ~ 1023
						 ULONG	unit3BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
						 ULONG	unit3EndPos,		// ������ ����λ�� 0 ~ 1023
						 ULONG	unit4BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
						 ULONG	unit4EndPos,		// ������ ����λ�� 0 ~ 1023
						 ULONG	unit5BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
						 ULONG	unit5EndPos,		// ������ ����λ�� 0 ~ 1023
						 ULONG	unit6BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
						 ULONG	unit6EndPos,		// ������ ����λ�� 0 ~ 1023
						 ULONG	unit7BeingPos,		// ������ ��ʼλ�� 0 ~ 1023
						 ULONG	unit7EndPos)
{
	_IsWarningRet("GetCount");
	m_circleWidth		=	circleWidth;
	m_circleCycle		=	circleCycle;
	m_frameWidth		=	frameWidth;
	m_frameCycle		=	frameCycle;
	m_frameDelayCircle	=	frameDelayCircle;
	m_unit1BeingPos		=	unit1BeingPos;
	m_unit1EndPos		=	unit1EndPos;
	m_unit2BeingPos		=	unit2BeingPos;
	m_unit2EndPos		=	unit2EndPos;
	m_unit3BeingPos		=	unit3BeingPos;
	m_unit3EndPos		=	unit3EndPos;
	m_unit4BeingPos		=	unit4BeingPos;
	m_unit4EndPos		=	unit4EndPos;
	m_unit5BeingPos		=	unit5BeingPos;
	m_unit5EndPos		=	unit5EndPos;
	m_unit6BeingPos		=	unit6BeingPos;
	m_unit6EndPos		=	unit6EndPos;
	m_unit7BeingPos		=	unit7BeingPos;
	m_unit7EndPos		=	unit7EndPos;

	LONG result = PXI8530_PulseOut_Cfg(m_hDevice[ulChan],
					circleWidth,		circleCycle,		
					frameWidth,			frameCycle,			
					frameDelayCircle,
					unit1BeingPos,		unit1EndPos,
					unit2BeingPos,		unit2EndPos,
					unit3BeingPos,		unit3EndPos,
					unit4BeingPos,		unit4EndPos,
					unit5BeingPos,		unit5EndPos,
					unit6BeingPos,		unit6EndPos,
					unit7BeingPos,		unit7EndPos);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ����
		_WriteLog(_T("PulseOut_Cfg ����:%s"), strErr);
		return FALSE;
	}

	return TRUE;
}

// ѡ��pxitrig ���ͨ��
BOOL CPXI8530_Sync422Send::SelMainTrig(ULONG ulChan, BOOL bOut)
{
	_IsWarningRet("SelMainTrig");
	LONG result;

	switch (ulChan)
	{
	case 0:
		result = PXI8530_PulseOut_MainTrig(m_hDevice[0], bOut);
		result = PXI8530_PulseOut_MainTrig(m_hDevice[1], !bOut);
		break;
	case 1:
		result = PXI8530_PulseOut_MainTrig(m_hDevice[0], !bOut);
		result = PXI8530_PulseOut_MainTrig(m_hDevice[1], bOut);
		break;
	default:
		result = PXI8530_PulseOut_MainTrig(m_hDevice[0], FALSE);
		result = PXI8530_PulseOut_MainTrig(m_hDevice[1], FALSE);
	}

	CString strErr;

	if (__IsErr(result, strErr))
	{ // ����
		_WriteLog(_T("SelMainTrig ����:%s"), strErr);
		return FALSE;
	}

	return TRUE;
}

BOOL CPXI8530_Sync422Send::GetCount(			// ���֡Ȧ����ֵ
					  ULONG		ulChan,			// ͨ����
					  ULONG*	pCircleCnt,		// ����Ȧͬ������ֵ
					  ULONG*	pFrameCnt)		// ����֡ͬ������ֵ
{
	_IsWarningRet("GetCount");

	LONG result = PXI8530_PulseOut_GetCount(m_hDevice[ulChan], pCircleCnt, pFrameCnt);
	CString strErr;

	if (__IsErr(result, strErr))
	{ // ����
		_WriteLog(_T("GetCount ����:%s"), strErr);
		return FALSE;
	}

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
void CPXI8530_Sync422Send::_WriteLog(LPCSTR lpszInfo, ...)
{
	char strText[1024];
	char strWriteText[2048];
	va_list va;

	va_start(va, lpszInfo);
	::_vstprintf(strText, lpszInfo, va);
	va_end(va);

	sprintf(strWriteText, "[PXI8530] %s", strText);

	if (m_pLogInfo)
	{
		m_pLogInfo->WriteLog(strWriteText);
	}
	else 
	{
		m_logFile.WriteInfo(strWriteText);
	}
}

BOOL CPXI8530_Sync422Send::__IsErr(LONG result, CString& strRetErr)
{
	if (PXI8530_Failed(result))
	{
		char szText[256];
		PXI8530_GetErrorString(result, szText, 256);

		strRetErr = szText;

		return TRUE;
	}

	return FALSE;
}