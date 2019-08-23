#ifndef __PXI8530_SYNC422_SEND__
#define __PXI8530_SYNC422_SEND__

#pragma once

class CPXI8530_Sync422Send : public IBaseSendSync422
{
public:
	enum {
		CARD_COUNT = 2,
	};

	virtual BOOL Create(void) ;
	virtual BOOL Release(void) ;
	virtual BOOL LoadParam(void) ;
	virtual BOOL Init(void) ;
	virtual int GetChCount(void) ;

	virtual BOOL Start(ULONG ulChan=0) ;
	virtual BOOL Stop(ULONG ulChan=0) ;

	virtual void SetErrorLog(ILogInfo* log) 
	{m_pLogInfo = log;}
public:

	// 发送圈协议 160字节
	virtual BOOL SendCircle(ULONG ulChan, BYTE byReadBuff[], ULONG ulWriteLen);
	// 发送帧协议 80字节
	virtual BOOL SendFrame(ULONG ulChan, BYTE byReadBuff[], ULONG ulWriteLen);
	// 脉冲输出配置
	virtual BOOL CfgPulseOut(		// 首先配置脉冲输出, 再写入圈协议和帧协议
		ULONG	ulChan,				// 通道号
		double	circleWidth,		// 圈脉冲宽度设置 单位mS 步进0.1 参考 50~150, 范围 0.1~6553.5
		double	circleCycle,		// 圈脉冲周期设置 单位mS 步进0.1 参考 500~3000, 范围 0.1~6553.5
		double	frameWidth,			// 帧同步宽度设置 单位mS 步进0.01 参考 0.25~1.5, 范围 0.01~2.55
		double	frameCycle,			// 帧同步周期设置 单位mS 最小0.01 参考 1~3, 范围 0.01~5.12
		double	frameDelayCircle,	// 帧输出相对于圈信号延时设置 单位mS 最小0.1 参考 50~600, 范围 0.1~819.2
		ULONG	unit1BeingPos,		// 第一组 起始位置 0 ~ 1023
		ULONG	unit1EndPos,		// 第一组 结束位置 0 ~ 1023
		ULONG	unit2BeingPos,		// 第二组 起始位置 0 ~ 1023
		ULONG	unit2EndPos,		// 第二组 结束位置 0 ~ 1023
		ULONG	unit3BeingPos,		// 第三组 起始位置 0 ~ 1023
		ULONG	unit3EndPos,		// 第三组 结束位置 0 ~ 1023
		ULONG	unit4BeingPos,		// 第四组 起始位置 0 ~ 1023
		ULONG	unit4EndPos,		// 第四组 结束位置 0 ~ 1023
		ULONG	unit5BeingPos,		// 第五组 起始位置 0 ~ 1023
		ULONG	unit5EndPos,		// 第五组 结束位置 0 ~ 1023
		ULONG	unit6BeingPos,		// 第六组 起始位置 0 ~ 1023
		ULONG	unit6EndPos,		// 第六组 结束位置 0 ~ 1023
		ULONG	unit7BeingPos,		// 第七组 起始位置 0 ~ 1023
		ULONG	unit7EndPos);
	virtual BOOL GetCount(			// 获得帧圈计数值
		ULONG	ulChan,				// 通道号
		ULONG*	pCircleCnt,			// 返回圈同步计数值
		ULONG*	pFrameCnt);			// 返回帧同步计数值
	// 选择pxitrig 输出通道
	virtual BOOL SelMainTrig(ULONG ulChan, BOOL bOut = TRUE);
	// PPS信号的主备使能
	virtual BOOL SetPPSMainOrViceEnable(ULONG ulChan, BOOL chan0En, BOOL chan1En);

public:
	BOOL	_IsDevEmpty() // 设备是否为空
	{
		return IsHandleInvalid(m_hDevice);
	};

	virtual void SetHandle(HANDLE hDevice0, HANDLE hDevice1){
		m_hDevice[0] = hDevice0;
		m_hDevice[1] = hDevice1;}

	CPXI8530_Sync422Send();
	virtual ~CPXI8530_Sync422Send();
private:
	BOOL __IsErr(LONG result, CString& strRetErr);

public:
	void _WriteLog(LPCSTR lpszInfo, ...);

private:
	HANDLE		m_hDevice[CARD_COUNT];
	ILogInfo*	m_pLogInfo;
	CLogFile	m_logFile;
	int			m_iAdd;
	ULONG		m_iLvdsSendRate;
	BOOL		m_bStart;
	BOOL		m_bInit;
	std::vector<BYTE>	m_vcCircle;
	std::vector<BYTE>	m_vcFrame;

	double m_circleWidth	;
	double m_circleCycle	;
	double m_frameWidth		;
	double m_frameCycle		;
	double m_frameDelayCircle;	
	ULONG m_unit1BeingPos	;	
	ULONG m_unit1EndPos		;
	ULONG m_unit2BeingPos	;	
	ULONG m_unit2EndPos		;
	ULONG m_unit3BeingPos	;	
	ULONG m_unit3EndPos		;
	ULONG m_unit4BeingPos	;	
	ULONG m_unit4EndPos		;
	ULONG m_unit5BeingPos	;	
	ULONG m_unit5EndPos		;
	ULONG m_unit6BeingPos	;	
	ULONG m_unit6EndPos		;
	ULONG m_unit7BeingPos	;	
	ULONG m_unit7EndPos		;

};

#endif