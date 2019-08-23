#ifndef BORDDLL_H

#define BORDDLL_H
#pragma once

#ifdef MYDLL_EXPORTS
#define BORDDLL_API __declspec(dllexport)//注意decl前面是两个下划线
#else
#define BORDDLL_API __declspec(dllimport)
#endif

extern "C"  BORDDLL_API bool DoInit();
extern "C"  BORDDLL_API void GetDataFromBord(int Bordi,double* BordBuffer);
extern "C"  BORDDLL_API void Release();



#endif