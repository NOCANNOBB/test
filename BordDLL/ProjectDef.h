#ifndef __PROJECT_DEFINE__
#define __PROJECT_DEFINE__
#include "IBaseHead.h"

// 外部库名称
#ifdef _DEBUG
	#define EXLIB_NAME_GM		"GM_LibD.dll"
#else
	#define EXLIB_NAME_GM		"GM_Lib.dll"
#endif
// 外部库导出函数
#define EXLIB_FUNC		"CreateLibrary"

#define EXLIB_VERSION	0x0001
#define MUTEX_NAME		"GMGui V1.0"
#define LOG_FILE		"GMGui.log"
#define EXCARD_LOGNAME	"GMLog.Log"
#define GUI_FILE_INI	"GMGui.INI"

#define GM_LIB_INI	"CardLibDC.ini"

#define MUTEX_IAD		"IBaseAD 1.0"
#define MUTEX_IDAAC		"IBaseAC 1.0"
#define MUTEX_IPWM		"IBasePWM 1.0"
#define MUTEX_IDADC_0	"IBaseDADC_0 1.0"
#define MUTEX_IDADC_1	"IBaseDADC_1 1.0"
#define MUTEX_IDAWAVE	"IBaseDAWave 1.0"
#define MUTEX_IDO		"IBaseDO 1.0"
#define MUTEX_IOHM		"IBaseOHM 1.0"

#if 1
//////////////////////////////////////////////////////////////////////////
// 读入外部库

class CExternClassDLL
{
public:
	BOOL InitExternLib(LPCSTR lpszExLibName, LPCSTR lpszFunNum)
	{
		if (m_hDll) FreeLibrary(m_hDll);

		m_hDll = LoadLibrary(lpszExLibName);
		PFN_CreateIBase pfnCreateLibrary = (PFN_CreateIBase )GetProcAddress(m_hDll, lpszFunNum);

		if (pfnCreateLibrary)
		{
			m_pExCardCtrl = static_cast<IExCardCtrl*>(pfnCreateLibrary());
		}

		return (m_pExCardCtrl != NULL);
	}

	IExCardCtrl* GetExCardCtrl()
		const{return m_pExCardCtrl;}
public:
	CExternClassDLL(void)
	{
		m_pExCardCtrl	= NULL;
		m_hDll			= NULL;
	}
	~CExternClassDLL(void)
	{
		TRACE("~CExternClassDLL(void)\n");
		Destory();

		if (m_hDll) FreeLibrary(m_hDll);
	}

#define SetErrorLogNULL(pIBase) 	\
	if (pIBase != NULL){ \
		pIBase->SetErrorLog(NULL);}

	void Destory()
	{
		if (m_pExCardCtrl!=NULL)
		{
			if (m_pExCardCtrl)
			{
				SetErrorLogNULL(m_pExCardCtrl->GetBaseAI());
				SetErrorLogNULL(m_pExCardCtrl->GetBaseCNT());
				SetErrorLogNULL(m_pExCardCtrl->GetBaseDO());
				SetErrorLogNULL(m_pExCardCtrl->GetBaseOutAO());

				m_pExCardCtrl->ReleaseLibrary();
				m_pExCardCtrl = NULL;
			}
		}
	}

private:
	IExCardCtrl*	m_pExCardCtrl;
	HINSTANCE		m_hDll;
};

#endif 


#endif