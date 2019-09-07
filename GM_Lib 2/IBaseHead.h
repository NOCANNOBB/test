#ifndef __IBASE_HEAD__
#define __IBASE_HEAD__
#pragma once
//////////////////////////////////////////////////////////////////////////
typedef void* (*PFN_CreateIBase)();
typedef void (WINAPI *PFN_ReleaseIBase)(void* pData);
//////////////////////////////////////////////////////////////////////////
class ILogInfo;
class IBaseCard;
class IBaseAI;
class IBaseDO;
class IBaseOutAO;
class IBaseCNT;


class IExCardCtrl
{
public:
	static IExCardCtrl* CreateLibrary(void);
	virtual void ReleaseLibrary(void) = NULL;

	virtual DWORD GetVersion() = NULL;

	virtual IBaseAI* GetBaseAI(void) = NULL;
	
	virtual IBaseDO* GetBaseDO(void) = NULL;

	virtual IBaseCNT* GetBaseCNT(void)=NULL;

	virtual IBaseOutAO* GetBaseOutAO(void) = NULL;

};




class IBaseCard
{
public:
	virtual BOOL Create(void) = NULL;
	virtual BOOL Release(void) = NULL;
	virtual BOOL LoadParam(void) = NULL;
	virtual BOOL Init(void) = NULL;
	virtual int GetChCount(void) = NULL;

	virtual BOOL Start(ULONG ulChan=0) = NULL;
	virtual BOOL Stop(ULONG ulChan=0) = NULL;
	
	virtual void SetErrorLog(ILogInfo* log) = NULL;
};
//--------------------------------------------------------------
// AD������
class IBaseAI : public IBaseCard
{
public:
	// ���ﷵ�ص��ǵ�ѹֵ����λ��V
	virtual BOOL ReadOneDC(ULONG ulChan, double* dfVolt) = NULL;
};
// ���ֱ��
class IBaseOutDC : public IBaseCard
{
public:
	// ����������ǵ�ѹֵ����λ��V
	virtual BOOL WriteDC(ULONG ulChan, double dfVolt) = NULL;
};



//--------------------------------------------------------------
//DIO ������
class IBaseDO : public IBaseCard
{
public:


	virtual BOOL WriteDO(ULONG ulChan, byte boolVlaue) = NULL;
	virtual BOOL ReadDO(ULONG ulChan,byte* boolValue) = NULL;
};


//--------------------------------------------------------------
//CNT ������
class IBaseCNT : public IBaseCard
{
public:
	// ��ȡƵ�ʣ�ռ�ձ�
	virtual BOOL GetdfFreqAnddfdfDutyCycle(ULONG ulChan, double* dfFreq,double* dfdfDutyCycle = NULL) = NULL;
	
};

//--------------------------------------------------------------
// IR OC
class IBaseIR: public IBaseCard
{
public:
	// ����IR״̬��������, ����ֵ��ͨ����
	virtual BOOL GetIR(ULONG ulChan, PBOOL pbSts, double* pdfPulseWidth, PULONG pulCount) = NULL;
	// ����IR״̬
	virtual BOOL ClrIRSts(ULONG ulChann) = NULL;
};

class IBaseOutAO: public IBaseCard
{
public:
	virtual BOOL WriteAO(ULONG ulChan, double pulseWidthMS) = NULL;
};
//--------------------------------------------------------------
// ������
class IBase1PPS : public IBaseCard
{
public:
	enum{ 
		//SelectOutSrc ����ʹ��
		SRC_GPS = 0,
		SRC_SIM = 1,
	};
public:
	// ���������ֵ
	virtual BOOL GetPulseCount(ULONG* pulPulse) = NULL;
	// �����帴λ����ʱ��ʱ��ֵ
	virtual BOOL Reset() = NULL;
	// ѡ�����������Դ �ο�ö�ٶ��� outSrc=0ʱGPS��Ϊ���Դ��1ʱ�ڲ�ģ�����Դ
	virtual BOOL SelectOutSrc(ULONG outSrc) = NULL;
	// ����ʱ��
	virtual BOOL Read(
		ULONG*	bIsValid,			// ʱ���Ƿ���Ч��GPS��δ��λʱΪ0����λ��1��ģ�ⳣ1
		ULONG*	dateHex,			// 16��������,����2017��01��20�գ�����ֵΪ0x200117, ģ�������2000��1��1�տ�ʼ
		ULONG*  timeHex) = NULL;			// 16����ʱ��,����15:35:32,����ֵΪ153532,ע��GPS������ʱ��ΪUTCʱ�䣬ģ���00:00:00��ʼ��ʱ

};
//--------------------------------------------------------------
// �������
class IBaseOHM : public IBaseCard
{
public:
	virtual BOOL OutputOHM(ULONG ulChan, double dfOHM) = NULL;
};
//--------------------------------------------------------------
// �첽422����
class IBaseASync422 : public IBaseCard
{
public:
	virtual BOOL Write(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteSize) = NULL;
	virtual BOOL Read(ULONG ulChan, BYTE byReadBuff[], ULONG& cbSize, double timeOut) = NULL;
};

// ͬ��422����
class IBaseRecvSync422 : public IBaseCard
{
public:
	virtual BOOL Recv(ULONG ulChan, BYTE byReadBuff[], ULONG& cbSize, double timeOut) = NULL;
};

class IBaseSendSync422 : public IBaseCard
{
public:
	// ����ȦЭ�� 160�ֽ�
	virtual BOOL SendCircle(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen) = NULL;
	// ����֡Э�� 80�ֽ�
	virtual BOOL SendFrame(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen) = NULL;
	// �����������
	virtual BOOL CfgPulseOut(					// ���������������, ��д��ȦЭ���֡Э��
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
					ULONG	unit7EndPos) = NULL;
	virtual BOOL GetCount(						// ���֡Ȧ����ֵ
					ULONG	ulChan,				// ͨ����
					ULONG*	pCircleCnt,			// ����Ȧͬ������ֵ
					ULONG*	pFrameCnt)=NULL;	// ����֡ͬ������ֵ
	// ѡ��pxitrig ���ͨ��
	virtual BOOL SelMainTrig(ULONG ulChan, BOOL bOut = TRUE) = NULL;
	// PPS�źŵ�����ʹ��
	virtual BOOL SetPPSMainOrViceEnable(ULONG ulChan, BOOL chan0En, BOOL chan1En) = NULL;
};
//--------------------------------------------------------------
class IBaseLvdsSendFrameCircleData : public IBaseCard
{
public:
	// ����ȦЭ�� 160�ֽ�
	virtual BOOL SendCircle(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen) = NULL;
	// ����֡Э�� 80�ֽ�
	virtual BOOL SendFrame(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen) = NULL;

};
// LVDS�ӿ�
class IBaseLvdsSend : public IBaseCard
{
public:
	virtual BOOL Write(
				ULONG ulChan,
				ULONG pulWriteBuff[],
				ULONG ulWriteLen, 
				ULONG ulLoopNum			// ѭ������
				) = NULL;
};

class IBaseLvdsRecv : public IBaseCard
{
public:
	virtual BOOL Read(
				ULONG ulChan,
				BYTE  pbyReadBuff[],
				ULONG& cbSize,		// ��ȡ�����������ʱ������ʵ�����������������NULL�������ڲ��Ѷ����ݳ���
				double dfTimeOut	// ��ȡ��ʱʱ��
				) = NULL;
};
// ����֡Ȧͬ��
class IBaseMeasFrameCircle : public IBaseCard
{
public:
	virtual BOOL SetCircleTime(ULONG timeData)= NULL;
	virtual BOOL SetFrameTime(ULONG timeData)= NULL;
	virtual BOOL Read(
		ULONG  ulChan,				// ͨ����
		__int64	readArray[],		// ��ȡ����
		ULONG&	readLen,			// ��ȡ����
		double	timeOut)= NULL;		// ��ʱʱ��
};

//--------------------------------------------------------------
// ������Ϣ����
class ILogInfo
{
public:
	virtual BOOL WriteLog(LPCSTR lpszInfo, ...) = NULL;
public:
	virtual ~ILogInfo(){};
};

#endif