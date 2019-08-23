// pro.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "pro.h"
#include "DlgBaseAI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

class CLogInfo : public ILogInfo
{
public:
	virtual BOOL WriteLog(LPCSTR lpszInfo, ...)
	{
		char szData[2048];
		SYSTEMTIME TmpTime;

		GetLocalTime(&TmpTime);			// 获得当地时间

		va_list va;
		va_start(va, lpszInfo);
		wvsprintfA(szData, lpszInfo, va);
		va_end(va);

		// 出错时间
		CString strInfo(szData);
		CString strTimeDate;

		strTimeDate.Format(_T("%d/%2.2d/%2.2d : %2.2d:%2.2d:%2.2d"),
			TmpTime.wYear, TmpTime.wMonth, TmpTime.wDay, 
			TmpTime.wHour, TmpTime.wMinute, TmpTime.wSecond);

		printf(strInfo);

		return TRUE;
	}
};

//////////////////////////////////////////////////////////////////////////
// 全局变量
CLogInfo		g_LogInfo;
CExternClassDLL g_exClassDLL;
IExCardCtrl*	g_pExCard = NULL;
//////////////////////////////////////////////////////////////////////////
// 初始化板卡
BOOL InitCard(IBaseCard* pIBase, ILogInfo* log)
{
	BOOL bRet = TRUE;
	if (pIBase == NULL) return FALSE;
	pIBase->SetErrorLog(log);

	bRet = bRet && pIBase->Create();
	bRet = bRet && pIBase->LoadParam();
	bRet = bRet && pIBase->Init();
	bRet = bRet && pIBase->Start(0);

	return bRet;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: 在此处为应用程序的行为编写代码。
	}
#if 1
	g_exClassDLL.InitExternLib("GM_LibD.dll", "CreateLibrary");
	g_pExCard = g_exClassDLL.GetExCardCtrl();
	ASSERT(g_pExCard != NULL);
	ILogInfo* logInfo = static_cast<ILogInfo*>(&g_LogInfo);

	CDlgBaseAI dlg(g_pExCard->GetBaseAI());

	if (!InitCard(static_cast<IBaseCard*>(g_pExCard->GetBaseAI()), logInfo))
	{
		printf("错误创建\n");
		goto __Exit;
	}
#endif
	//CDlgBaseAI dlg(NULL);
	dlg.DoModal();

__Exit:
	g_exClassDLL.Destory();
	printf("按回车退出\n");
	getchar();
	return nRetCode;
}
