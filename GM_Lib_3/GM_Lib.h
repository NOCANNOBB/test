// GM_Lib.h : GM_Lib DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGM_LibApp
// �йش���ʵ�ֵ���Ϣ������� GM_Lib.cpp
//

class CGM_LibApp : public CWinApp
{
public:
	CGM_LibApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
