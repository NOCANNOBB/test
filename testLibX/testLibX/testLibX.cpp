// testLibX.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "testLibX.h"
#include "BordDLL.h"
#include "conio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}
	SetRate(200,100);// 200hz 1/s 读取200 个数据
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
