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
	SetRate(200,10);// 200hz 1/s 读取200 个数据
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
		printf("获取AI数据：%d 个" ,retReadSize);
		for (int i = 0; i < retReadSize; i++)
		{
			printf("%f ",dfValAI[i]);
		}
		printf("\n");
		GetCNTData(0,&CNTValue,&dfVal2);
		printf("取得CNT数据%f \n", CNTValue);

		if (!bBalue)
		{
			WriteDOData(0,1);
		}
		else{
			WriteDOData(0,0);
		}
		printf("写入DO %d \n",bBalue);
		byte bValue = 0;
		ReadDOData(0,&bValue);
		printf("取出DO %d \n",bValue);
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
