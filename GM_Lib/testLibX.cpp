// testLibX.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "testLibX.h"
#include "BordDLL.h"
#include "conio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}
	SetRate(200,10);// 200hz 1/s ��ȡ200 ������
	DoInit();	
	/*byte bValue = 1;
	ReadDOData(0,&bValue);*/
	BOOL bBalue = TRUE;
int k = 0;
	while (true)
	{
		//k++;
		int ReadSize = 10;
		int retReadSize = 0;
		double* dfValAI = new double[ReadSize];
		
		double CNTValue = 0;
		double AOValue = 3.2;
		double dfVal2 = 0;
	
		GetDataFromBord(0,dfValAI,ReadSize,&retReadSize);
		printf("��ȡAI���ݣ�%d ��" ,retReadSize);
		for (int i = 0; i < retReadSize; i++)
		{
			printf("%f ",dfValAI[i]);
		}
		printf("\n");
		GetCNTData(0,&CNTValue,&dfVal2);
		printf("ȡ��CNT����%f \n", CNTValue);

		if (!bBalue)
		{
			WriteDOData(0,1);
		}
		else{
			WriteDOData(0,0);
		}
		printf("д��DO %d \n",bBalue);
		byte bValue = 0;
		ReadDOData(0,&bValue);
		printf("ȡ��DO %d \n",bValue);
		if (bValue == 1)
		{
			bBalue = TRUE;
		}
		else
		{
			bBalue = FALSE;
		}
		delete[] dfValAI;
		dfValAI = NULL;
		Sleep(50);
		if (_kbhit()) if (getch() == 27) break;
	}
	
	//Release();
	getchar();
	Release();
	return nRetCode;
}
