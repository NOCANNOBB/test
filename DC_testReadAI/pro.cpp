// pro.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "pro.h"
#include "DlgBaseAI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

class CLogInfo : public ILogInfo
{
public:
	virtual BOOL WriteLog(LPCSTR lpszInfo, ...)
	{
		char szData[2048];
		SYSTEMTIME TmpTime;

		GetLocalTime(&TmpTime);			// ��õ���ʱ��

		va_list va;
		va_start(va, lpszInfo);
		wvsprintfA(szData, lpszInfo, va);
		va_end(va);

		// ����ʱ��
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
// ȫ�ֱ���
CLogInfo		g_LogInfo;
CExternClassDLL g_exClassDLL;
IExCardCtrl*	g_pExCard = NULL;
//////////////////////////////////////////////////////////////////////////
// ��ʼ���忨
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

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
	}
#if 1
	g_exClassDLL.InitExternLib("GM_LibD.dll", "CreateLibrary");
	g_pExCard = g_exClassDLL.GetExCardCtrl();
	ASSERT(g_pExCard != NULL);
	ILogInfo* logInfo = static_cast<ILogInfo*>(&g_LogInfo);

	CDlgBaseAI dlg(g_pExCard->GetBaseAI());

	if (!InitCard(static_cast<IBaseCard*>(g_pExCard->GetBaseAI()), logInfo))
	{
		printf("���󴴽�\n");
		goto __Exit;
	}
#endif
	//CDlgBaseAI dlg(NULL);
	dlg.DoModal();

__Exit:
	g_exClassDLL.Destory();
	printf("���س��˳�\n");
	getchar();
	return nRetCode;
}
