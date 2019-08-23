
#include<afx.h>
#include "BordDLL.h"
#include "IBaseHead.h"
#include "ProjectDef.h"

CExternClassDLL g_exClassDLL;
IExCardCtrl*	g_pExCard = NULL;
IBaseAI* g_pBaseAI = NULL;



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


bool DoInit(){


	g_exClassDLL.InitExternLib("GM_LibD.dll", "CreateLibrary");
	g_pExCard = g_exClassDLL.GetExCardCtrl();
	ASSERT(g_pExCard != NULL);
	//ILogInfo* logInfo = static_cast<ILogInfo*>(&g_LogInfo);

	//CDlgBaseAI dlg(g_pExCard->GetBaseAI());
	g_pBaseAI = g_pExCard->GetBaseAI();
	if (!InitCard(static_cast<IBaseCard*>(g_pBaseAI),NULL))
	{
		printf("´íÎó´´½¨\n");
	}

	return true;
}


void GetDataFromBord(int Bordi,double* BordBuffer){
	if(g_pBaseAI == NULL || BordBuffer == NULL){return;}
	g_pBaseAI->ReadOneDC(Bordi, BordBuffer);
	
}

void Release(){
	g_exClassDLL.Destory();
}