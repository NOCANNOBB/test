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
	SetRate(200,100);// 200hz 1/s ��ȡ200 ������
	DoInit();	
	
	
	int k = 0;
	while (k < 50)
	{
		k++;
		int ReadSize = 10;
		int retReadSize = 0;
		double* dfVal = new double[ReadSize];
		//GetAIDataFromBord(0, &dfVal);
		GetDataFromBord(0,dfVal,10,&retReadSize);
		printf("%d", retReadSize);
		for (int i = 0; i < retReadSize; i++)
		{
			printf("  %f  ",dfVal[i]);
		}
		printf("\n");
		delete[] dfVal;
		dfVal = NULL;
		Sleep(50);
		if (_kbhit()) if (getch() == 27) break;
	}
	
	Release();
	getchar();
	return nRetCode;
}
