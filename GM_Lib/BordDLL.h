#ifndef BORDDLL_H

#define BORDDLL_H
#pragma once

// #ifdef MYDLL_EXPORTS
// #define BORDDLL_API __declspec(dllexport)
// #else
// #define BORDDLL_API __declspec(dllimport)
// #endif
#define BORDDLL_API  
extern "C"  BORDDLL_API bool DoInit();
extern "C"  BORDDLL_API bool StartChannel(ULONG ulChan);
extern "C"  BORDDLL_API void SetRate(int SleepTime, int PerRead);
extern "C"  BORDDLL_API void GetAIDataFromBord(int Bordi,double* BordBuffer);
extern "C"  BORDDLL_API void GetDataFromBord(ULONG ulChan,double* dfVla,int ReadSize, int* retReadSize);
extern "C"  BORDDLL_API void WriteDOData(ULONG ulChan, byte boolVlaue);//록폴
extern "C"  BORDDLL_API void WriteDOData_1(ULONG ulChan, byte boolVlaue[]);
extern "C"  BORDDLL_API void ReadDOData(ULONG ulChan, byte* boolVlaue);//록폴
extern "C"  BORDDLL_API void ReadDOData_1(ULONG ulChan, byte boolVlaue[]);
extern "C"  BORDDLL_API void GetCNTData(ULONG ulChan,double* dfFreq,double * dfDutyCycle = NULL);
extern "C"  BORDDLL_API void WriteAOData(ULONG ulChan,double dfFreq);
extern "C"  BORDDLL_API void Release();



#endif