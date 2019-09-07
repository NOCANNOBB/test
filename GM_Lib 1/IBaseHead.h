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
// AD基础类
class IBaseAI : public IBaseCard
{
public:
	// 这里返回的是电压值，单位是V
	virtual BOOL ReadOneDC(ULONG ulChan, double* dfVolt) = NULL;
};
// 输出直流
class IBaseOutDC : public IBaseCard
{
public:
	// 这里输入的是电压值，单位是V
	virtual BOOL WriteDC(ULONG ulChan, double dfVolt) = NULL;
};



//--------------------------------------------------------------
//DIO 基础类
class IBaseDO : public IBaseCard
{
public:


	virtual BOOL WriteDO(ULONG ulChan, byte boolVlaue) = NULL;
	virtual BOOL ReadDO(ULONG ulChan,byte* boolValue) = NULL;
};


//--------------------------------------------------------------
//CNT 基础类
class IBaseCNT : public IBaseCard
{
public:
	// 获取频率，占空比
	virtual BOOL GetdfFreqAnddfdfDutyCycle(ULONG ulChan, double* dfFreq,double* dfdfDutyCycle = NULL) = NULL;
	
};

//--------------------------------------------------------------
// IR OC
class IBaseIR: public IBaseCard
{
public:
	// 返回IR状态，脉冲宽度, 计数值，通道号
	virtual BOOL GetIR(ULONG ulChan, PBOOL pbSts, double* pdfPulseWidth, PULONG pulCount) = NULL;
	// 设置IR状态
	virtual BOOL ClrIRSts(ULONG ulChann) = NULL;
};

class IBaseOutAO: public IBaseCard
{
public:
	virtual BOOL WriteAO(ULONG ulChan, double pulseWidthMS) = NULL;
};
//--------------------------------------------------------------
// 秒脉冲
class IBase1PPS : public IBaseCard
{
public:
	enum{ 
		//SelectOutSrc 函数使用
		SRC_GPS = 0,
		SRC_SIM = 1,
	};
public:
	// 获得秒脉冲值
	virtual BOOL GetPulseCount(ULONG* pulPulse) = NULL;
	// 秒脉冲复位，这时是时间值
	virtual BOOL Reset() = NULL;
	// 选择妙脉冲输出源 参考枚举定义 outSrc=0时GPS作为输出源，1时内部模拟输出源
	virtual BOOL SelectOutSrc(ULONG outSrc) = NULL;
	// 读出时间
	virtual BOOL Read(
		ULONG*	bIsValid,			// 时间是否有效，GPS在未定位时为0，定位后1，模拟常1
		ULONG*	dateHex,			// 16进制日期,例如2017年01月20日，反馈值为0x200117, 模拟输出从2000年1月1日开始
		ULONG*  timeHex) = NULL;			// 16进制时间,例如15:35:32,反馈值为153532,注意GPS反馈的时间为UTC时间，模拟从00:00:00开始计时

};
//--------------------------------------------------------------
// 电阻输出
class IBaseOHM : public IBaseCard
{
public:
	virtual BOOL OutputOHM(ULONG ulChan, double dfOHM) = NULL;
};
//--------------------------------------------------------------
// 异步422部分
class IBaseASync422 : public IBaseCard
{
public:
	virtual BOOL Write(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteSize) = NULL;
	virtual BOOL Read(ULONG ulChan, BYTE byReadBuff[], ULONG& cbSize, double timeOut) = NULL;
};

// 同步422部分
class IBaseRecvSync422 : public IBaseCard
{
public:
	virtual BOOL Recv(ULONG ulChan, BYTE byReadBuff[], ULONG& cbSize, double timeOut) = NULL;
};

class IBaseSendSync422 : public IBaseCard
{
public:
	// 发送圈协议 160字节
	virtual BOOL SendCircle(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen) = NULL;
	// 发送帧协议 80字节
	virtual BOOL SendFrame(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen) = NULL;
	// 脉冲输出配置
	virtual BOOL CfgPulseOut(					// 首先配置脉冲输出, 再写入圈协议和帧协议
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
					ULONG	unit7EndPos) = NULL;
	virtual BOOL GetCount(						// 获得帧圈计数值
					ULONG	ulChan,				// 通道号
					ULONG*	pCircleCnt,			// 返回圈同步计数值
					ULONG*	pFrameCnt)=NULL;	// 返回帧同步计数值
	// 选择pxitrig 输出通道
	virtual BOOL SelMainTrig(ULONG ulChan, BOOL bOut = TRUE) = NULL;
	// PPS信号的主备使能
	virtual BOOL SetPPSMainOrViceEnable(ULONG ulChan, BOOL chan0En, BOOL chan1En) = NULL;
};
//--------------------------------------------------------------
class IBaseLvdsSendFrameCircleData : public IBaseCard
{
public:
	// 发送圈协议 160字节
	virtual BOOL SendCircle(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen) = NULL;
	// 发送帧协议 80字节
	virtual BOOL SendFrame(ULONG ulChan, BYTE byWriteBuff[], ULONG ulWriteLen) = NULL;

};
// LVDS接口
class IBaseLvdsSend : public IBaseCard
{
public:
	virtual BOOL Write(
				ULONG ulChan,
				ULONG pulWriteBuff[],
				ULONG ulWriteLen, 
				ULONG ulLoopNum			// 循环次数
				) = NULL;
};

class IBaseLvdsRecv : public IBaseCard
{
public:
	virtual BOOL Read(
				ULONG ulChan,
				BYTE  pbyReadBuff[],
				ULONG& cbSize,		// 读取个数，如果超时，返回实际数量，如果缓冲区NULL，返回内部已读数据长度
				double dfTimeOut	// 读取超时时间
				) = NULL;
};
// 测量帧圈同步
class IBaseMeasFrameCircle : public IBaseCard
{
public:
	virtual BOOL SetCircleTime(ULONG timeData)= NULL;
	virtual BOOL SetFrameTime(ULONG timeData)= NULL;
	virtual BOOL Read(
		ULONG  ulChan,				// 通道号
		__int64	readArray[],		// 读取数组
		ULONG&	readLen,			// 读取长度
		double	timeOut)= NULL;		// 超时时间
};

//--------------------------------------------------------------
// 错误消息处理
class ILogInfo
{
public:
	virtual BOOL WriteLog(LPCSTR lpszInfo, ...) = NULL;
public:
	virtual ~ILogInfo(){};
};

#endif