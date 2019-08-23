// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


void SetDValue(int channelid,double* dValue){
	*dValue = channelid;
	
}

void Readtest(int channelud,double * dValue){
	for(int i = 0;i < channelud; i++){
		SetDValue(i,dValue);
	}
}





int _tmain(int argc, _TCHAR* argv[])
{
	double* dValues = new double[8];

	Readtest(8,dValues);

	for(int i = 0; i < 8; i++){
		printf("%f",dValues[i]);
		dValues++;
	}

	getchar();
	return 0;
}



