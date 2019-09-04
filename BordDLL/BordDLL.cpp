
#include<afx.h>
#include "BordDLL.h"
#include "IBaseHead.h"
#include "ProjectDef.h"

CExternClassDLL g_exClassDLL;
IExCardCtrl*	g_pExCard = NULL;

IBaseOutDC* g_pBaseOutDC = NULL;


IBaseCNT* g_pBaseCnt = NULL;
IBaseDO* g_pBaseDO = NULL;
IBaseOutAO* g_pBaseAO = NULL;
IBaseAI* g_pBaseAI = NULL;
IBaseCard* g_pBase = NULL;
ILogInfo* g_log =NULL;



BOOL InitCard(IBaseCard* pIBase, ILogInfo* log)
{
	g_pBase = pIBase;
	g_log = log;
	BOOL bRet = TRUE;
	if (pIBase == NULL) return FALSE;
	pIBase->SetErrorLog(log);

	bRet = bRet && pIBase->Create();
	bRet = bRet && pIBase->LoadParam();
	bRet = bRet && pIBase->Init();
	bRet = bRet && pIBase->Start(0);

	return bRet;
}


bool StartChannel(ULONG ulChan){

	BOOL bRet = TRUE;
	if (g_pBase == NULL) return FALSE;
	g_pBase->SetErrorLog(g_log);

	bRet = bRet && g_pBase->Start(ulChan);
	return bRet;
}


bool DoInit(){

	//MessageBox(NULL,"1231231","12312312",0);
	g_exClassDLL.InitExternLib("GM_Lib.dll", "CreateLibrary");
	g_pExCard = g_exClassDLL.GetExCardCtrl();
	ASSERT(g_pExCard != NULL);
	//ILogInfo* logInfo = static_cast<ILogInfo*>(&g_LogInfo);

	//CDlgBaseAI dlg(g_pExCard->GetBaseAI());
	g_pBaseAI = g_pExCard->GetBaseAI();
	g_pBaseAO = g_pExCard->GetBaseOutAO();
	g_pBaseCnt = g_pExCard->GetBaseCNT();
	g_pBaseDO = g_pExCard->GetBaseDO();
	if (!InitCard(static_cast<IBaseCard*>(g_pBaseAI),NULL))
	{
		printf("错误创建\n");
	}
	if (!InitCard(static_cast<IBaseCard*>(g_pBaseAO),NULL))
	{
		printf("错误创建\n");
	}
	if (!InitCard(static_cast<IBaseCard*>(g_pBaseCnt),NULL))
	{
		printf("错误创建\n");
	}
	if (!InitCard(static_cast<IBaseCard*>(g_pBaseDO),NULL))
	{
		printf("错误创建\n");
	}

	return true;
}


void GetAIDataFromBord(int Bordi,double* BordBuffer){
	if(g_pBaseAI == NULL || BordBuffer == NULL){return;}
	g_pBaseAI->ReadOneDC(Bordi, BordBuffer);
	
}

void WriteDOData(ULONG ulChan, BOOL boolVlaue){
	if(g_pBaseAI == NULL){return;}
	g_pBaseDO->WriteDO(ulChan, boolVlaue);
}

void WriteDOData_1(ULONG ulChan, byte boolVlaue[]){
	if(g_pBaseDO == NULL){return;}
	g_pBaseDO->WriteDO(ulChan, boolVlaue);
}

void ReadDOData(ULONG ulChan, BOOL* boolVlaue){
	if(g_pBaseDO == NULL){return;}
	g_pBaseDO->ReadDO(ulChan, boolVlaue);
}

void ReadDOData_1(ULONG ulChan, byte boolVlaue[]){
	if(g_pBaseDO == NULL){return;}
	g_pBaseDO->ReadDO(ulChan, boolVlaue);
}

void GetCNTData(ULONG ulChan,double* dfFreq,double * dfDutyCycle){
	if(g_pBaseCnt == NULL){return;}
	g_pBaseCnt->GetdfFreqAnddfdfDutyCycle(ulChan, dfFreq,dfDutyCycle);

}

void WriteAOData(ULONG ulChan,double dfFreq){
	if(g_pBaseAO == NULL){return;}
	g_pBaseAO->WriteAO(ulChan, dfFreq);

}

void Release(){
	g_exClassDLL.Destory();
}