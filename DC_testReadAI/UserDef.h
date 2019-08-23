#ifndef __USER_DEF__
#define __USER_DEF__
#include "math.h"
#include "process.h"
#include "math.h"
//---------------------------------------------
#include "shlwapi.h"
#pragma  comment(lib, "shlwapi.lib")
//---------------------------------------------
#pragma once
// ����꣬��Ϊ�˺�vs2005����
#define for if(1)for

#define LIMIT_NUM(num,mn,mx) \
	(((num)<(mn))?(mn) : ((num)>(mx)?(mx):(num)))
//////////////////////////////////////////////////////////////////////////
#define LIMIT_MM(num, mx, mn) ((num)>(mx)?(mx):((num)<(mn)?(mn):(num)))
#define IsNotLimit(tmpnum, minnum, maxnum) \
			(((tmpnum)<=(maxnum))&&((tmpnum)>=(minnum)))

#define InitHandle(hHandle) hHandle = reinterpret_cast<HANDLE>(-1);

#define IsHandleInvalid(hHandle) (hHandle==reinterpret_cast<HANDLE>(-1))

#define DelEvent(hEvent) {\
	if(!IsHandleInvalid(hEvent))\
	{\
		CloseHandle(hEvent); \
		InitHandle(hEvent); \
	}\
}
#define WND_CTRL(id) GetDlgItem(id)
// �����Լ���Dialog
#define NewDlgCreateWindows(retX, cclass, thisclass) \
	do {\
		retX = new cclass(); \
		BOOL bRet = retX->Create(cclass::IDD, thisclass);\
		ASSERT(bRet!=FALSE); \
		retX->ShowWindow(SW_HIDE);\
	} while (0);
	
// �ͷ��Լ�������Dialog
#define DelDlgDestroyWindows(pDlg) \
	if (pDlg) { \
		pDlg->DestroyWindow(); \
		delete pDlg;\
		pDlg = NULL;\
	}
// �������Ҫ��������ʱʹ�ã������ͷ�������ƽʱ����ʹ��my_space_define::my_malloc �����ͷ��ڴ�
#define ExNewMemData(byteLen) malloc(byteLen)
#define ExDelMemData(pMemAddr) if (pMemAddr){free(pMemAddr);pMemAddr=NULL;}
//////////////////////////////////////////////////////////////////////////
#define _FindMssageChan(___retChanNum, ___ID_ARRAY, ___maxLoop) \
	do {\
	const MSG* __pMsg = GetCurrentMessage();\
	for (ULONG ___i=0; ___i<___maxLoop; ___i++){\
	if ( __pMsg->lParam == (LPARAM)GetDlgItem(___ID_ARRAY[___i])->GetSafeHwnd() ){\
	___retChanNum = ___i;\
	break;\
	}\
	}\
	} while (0);
// �����߳�
//#define ExCreateThread(fnThread, pParam) CreateThread(NULL, 0, fnThread, pParam, 0, NULL)
#define ExCreateThread(fnThread, pParam) reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, fnThread, pParam, 0, NULL))
// �ͷ��̣߳����Ϊ�˺ʹ����̺߳�������Ӧ��д
#define ExReleaseThread(__hThread, __timeoutMS) \
		{\
			if(!IsHandleInvalid(__hThread)){\
				if (WaitForSingleObject(__hThread, __timeoutMS)!=WAIT_OBJECT_0){\
					TerminateThread(__hThread, 0);\
				}\
			}\
			CloseHandle(__hThread);\
			InitHandle(__hThread); \
		}
// ԭ��ɾ���߳�ʹ�ú�
#define DelThread(hThread, timeoutMS) ExReleaseThread(hThread, timeoutMS)
//////////////////////////////////////////////////////////////////////////
// ������ֵ�����ֵ����Сֵ֮�䣬������������ֵ����Сֵ
#define LIMIT_NUM(num,mn,mx) \
	(((num)<(mn))?(mn) : ((num)>(mx)?(mx):(num)))
//-----------------------------	
// �ж��Ƿ������ֵ��Сֵ��Χ֮�ڣ��������ΪFALSE,������ΪTRUE
#define IsLimit(tmpnum, maxnum, minnum) (((tmpnum)<=(maxnum))&&((tmpnum)>=(minnum)))
//////////////////////////////////////////////////////////////////////////
// ����ת�� xת��ǰ��ֵ o_max,o_minת��������ֵ����Сֵ
// �������Ҫ��Ϊ�˷����Ķ�
//#define RangeConv(x, x_max, x_min, o_max, o_min, o_offset) \
//	(((((x)-x_min)*((o_max)-(o_min))/((x_max)-(x_min))) + (o_min)) + (o_offset))

#define RangeConv(x, x_max, x_min, o_max, o_min) \
	(((((x)-x_min)*((o_max)-(o_min))/((x_max)-(x_min))) + (o_min)) )

// �жϸ������Ƿ����,precision�ǱȽϾ���
// ���� DOUBLE_CMP_EQU(2.3, 2.33, 0.1) ��������Ϊ��������������ͬ
#define DOUBLE_CMP_EQU(a, b, pre) (fabs((a)-(b))<(pre))
//////////////////////////////////////////////////////////////////////////
// ���ڼ��㾲̬�ṹ����߾�̬�����Ա����
// ע�ⲻ��ʹ�ö�̬������ָ��������飬�������ݵ�ָ�벻����
#define GetStructSize(pStruct) (sizeof(pStruct)/sizeof(pStruct[0]))
//////////////////////////////////////////////////////////////////////////
// 16λ���ݸߵ�8λ��ת
#ifndef SWAP_WORD
	#define SWAP_WORD(wData) MAKEWORD(HIBYTE((wData)), LOBYTE((wData)))
#endif
// 32λ���� �ߵ�λ��ת������:0x12345678 ��ת�� 0x78563412
#ifndef SWAP_LONG
	#define SWAP_LONG(lData) MAKELONG(SWAP_WORD(HIWORD((lData))), SWAP_WORD(LOWORD((lData))))
#endif
#ifndef SWAP_LONGLONG
	#define MAKELONGLONG(a, b) (((__int64)(((LONG)a)&0xFFFFFFFF)) | (((__int64)((LONG)b&0xFFFFFFFF))<<32))
	#define HILONG(__i64Data) ((LONG)(__i64Data>>32)&0xFFFFFFFF)
	#define LOLONG(__i64Data) ((LONG)(__i64Data&0xFFFFFFFF))
	#define SWAP_LONGLONG(__i64Data) MAKELONGLONG(SWAP_LONG(HILONG(__i64Data)), SWAP_LONG(LOLONG(__i64Data)))
#endif
//////////////////////////////////////////////////////////////////////////
// �ֽ�ת�����ַ����� str������CString ���� ,num���ֽ���
#define BYTEtoSTRING(num, str) \
	do{\
		if      ( ((double)(num)) > (1024*1024*1024.0)) {str.Format(_T("%.2f GB"), ((double)(num))/(double)(1024.0*1024.0*1024.0));} \
		else if ( ((double)(num)) > (1024*1024.0) )     {str.Format(_T("%.2f MB"), ((double)(num))/(double)(1024.0*1024.0));} \
		else if ( ((double)(num)) > (1024.0)      )     {str.Format(_T("%.2f KB"), ((double)(num))/(double)(1024.0));} \
		else                                            {str.Format(_T("%.0f B"),  ((double)(num)));}\
	}while(0);
//////////////////////////////////////////////////////////////////////////
#define __FindMssageChan(__retChanNum, __ID_ARRAY, __maxLoop) \
	do {\
	const MSG* __pMsg = GetCurrentMessage();\
	for (ULONG __i=0; __i<(__maxLoop); __i++){\
	if ( __pMsg->lParam == (LPARAM)GetDlgItem((__ID_ARRAY)[__i])->GetSafeHwnd() ){\
	(__retChanNum) = __i;\
	break;\
	}\
	}\
	} while (0);
//////////////////////////////////////////////////////////////////////////
#define CmbGetCurPtrData(pcmbClas,index,_Ty) ((_Ty)(pcmbClas)->GetItemData(index))
//////////////////////////////////////////////////////////////////////////
// ����ListCtrl���ı�����������ı���ԭ����ͬ���򲻽���д��
// listCtrl CListCtrl�࣬index���к� subItem���к� strTextд����ַ���
#define LIST_SET_ITEM_TEXT(listCtrl, index, subItem, strText) \
	do { \
		CString ___strTmp;\
		___strTmp = (listCtrl).GetItemText((index), (subItem));\
		if (___strTmp != strText){(listCtrl).SetItemText((index), (subItem), strText);} \
	} while (0);

#define TEXT_SET_TEXT(__editCtrl, __strNew) \
	do { \
		CString __strTmp;\
		(__editCtrl).GetWindowText(__strTmp); \
		if ( __strTmp != __strNew) { \
			int startChar, endChar; \
			(__editCtrl).GetSel(startChar, endChar);\
			(__editCtrl).SetWindowText(__strNew);\
			(__editCtrl).SetSel(startChar, endChar);\
		}\
	} while (0);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
namespace my_space_define
{ // �Զ��庯��
	static void DoEvents()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);
			TranslateMessage(&msg);
		}
	}
	// ��õ�ǰӦ�ó����ļ���
	static void GetAppPath(CString& strRetPath)
	{
		CString strTmp;
		LPTSTR pStr = strTmp.GetBuffer(MAX_PATH);
		GetModuleFileName(NULL, pStr, MAX_PATH);
		pStr[strTmp.ReverseFind(_T('\\'))] = _T('\0');
		strTmp.ReleaseBuffer();
		strRetPath = strTmp;
	}
	// ��16�����ַ���ת��Ϊbyte����
	static void StringToHexByte(LPCTSTR lpszString, BYTE byData[], ULONG& cbSize)
	{
		CString strData;
		strData = lpszString;
		// ���ַ�����ĸ��С��
		strData.MakeLower();
		// �Զ���ָ�
		CString strToks(_T(", "));
		CString strTmp;
		LPTSTR	lpszTmp,
				lpszData = _tcstok(strData.GetBuffer(0), strToks);
		ULONG ulCount = 0;

		while ((lpszData != NULL)
			&& (ulCount < cbSize))
		{
			// �жϵ�һ���ַ��Ƿ�x
			lpszTmp = *lpszData=='x' ? (lpszData+1) : lpszData;

			byData[ulCount++] =(BYTE)(_tcstoul(lpszTmp, NULL, 16)&0xFF);
			lpszData = _tcstok(NULL, strToks);
		}

		cbSize = ulCount;
	}
	// ��byte����ת�����ַ���
	static void HexByteToString(CString& strRetString, BYTE* byDataBegin, BYTE* byDataEnd)
	{
		strRetString.Empty();
		CString strTmp;
		
		int iIncOne = byDataEnd - byDataBegin;
		int iLoopCount = abs(byDataEnd - byDataBegin) + 1;

		if (iIncOne == 0)
		{
			iIncOne = 1;
		}
		else
		{
			iIncOne = iIncOne/abs(iIncOne);
		}
		

		PBYTE pbyTmp=byDataBegin;

		for (int i=0; i<iLoopCount; i++, pbyTmp+=iIncOne)
		{
			strTmp.Format("%02X ", (*pbyTmp)&0xff);
			strRetString+=strTmp;
		}
	}
	// ��byte����ת�����ַ���,�м�û�пո�
	static void HexByteToStringNoSpace(CString& strRetString, BYTE* byDataBegin, BYTE* byDataEnd)
	{
		strRetString.Empty();
		CString strTmp;

		int iIncOne = byDataEnd - byDataBegin;
		int iLoopCount = abs(byDataEnd - byDataBegin) + 1;

		if (iIncOne == 0)
		{
			iIncOne = 1;
		}
		else
		{
			iIncOne = iIncOne/abs(iIncOne);
		}


		PBYTE pbyTmp=byDataBegin;

		for (int i=0; i<iLoopCount; i++, pbyTmp+=iIncOne)
		{
			strTmp.Format("%02X", (*pbyTmp)&0xff);
			strRetString+=strTmp;
		}
	}
	// �����ı��ļ������ı��ļ��е���ֵת��Ϊ8λ����
	//�����ı��ļ����� 55aa22556699,ת����������Ϊ 0x55 0xaa 0x22 0x55 0x66 0x99
	static BOOL AnalyTxtToHexBuff(LPCTSTR lpszFile, std::vector<BYTE>& vcData)
	{
		CFile fileIN;
		if (!fileIN.Open(lpszFile, CFile::modeRead|CFile::typeBinary)) return FALSE;

		std::vector<BYTE> vcBuffer;
		vcBuffer.resize((ULONG)fileIN.GetLength());

		fileIN.SeekToBegin();
		fileIN.Read(&vcBuffer[0], vcBuffer.size());
		fileIN.Close();
		vcData.resize(vcBuffer.size()/2);

		BYTE* pbyData = &vcBuffer[0];
		char strDat[3]= {0,0,0};
		for (ULONG i=0; i<vcData.size(); i++)
		{
			strDat[0] = pbyData[i*2+0];
			strDat[1] = pbyData[i*2+1];
			vcData[i] = (BYTE)(_tcstoul(strDat, NULL, 16)) & 0xFF;
		}

		return TRUE;
	}

	// �Զ�ʶ�����ı��ļ�������2�����ļ�
	static BOOL AuotReadFileTxtOrDat(LPCSTR lpszFileName, std::vector<BYTE>& vcBuff, ULONG ulReadMode=0/*0:�Զ� 1:�ı� 2:������*/)
	{ // ���ؼ٣����ļ��򿪴���
		CFile fileRead;

		if (!fileRead.Open(lpszFileName, CFile::modeRead|CFile::typeBinary))
		{
			return FALSE;
		}

		std::vector<BYTE> vcBuffTmp;
		vcBuffTmp.resize((UINT)fileRead.GetLength());
		fileRead.Read(&vcBuffTmp[0], vcBuffTmp.size());
		fileRead.Close();

		BOOL bTxt = FALSE;

		if (ulReadMode == 0)
		{
#if 0
			for(ULONG i=0; i<vcBuffTmp.size(); i++)
			{
				if (!__isascii(vcBuffTmp[i]) && i>=2)
				{
					if (!IsDBCSLeadByte(vcBuffTmp[i]))
					{
						bTxt = FALSE;
						break;
					}
				}
			}
#else
			
			CString strTmp = CString(lpszFileName).Right(3);

			if (strTmp.CompareNoCase(_T("txt")) == 0)
			{
				bTxt = TRUE;
			}
#endif
		}
		else if (ulReadMode == 1)
		{
			bTxt = TRUE;
		}
		else
		{
			bTxt = FALSE;
		}

		if (bTxt)
		{
			my_space_define::AnalyTxtToHexBuff(lpszFileName, vcBuff);
		}
		else
		{
			vcBuff = vcBuffTmp;
		}

		return TRUE;
	}

	// ѹ��·��
	static void MyPathCompactPath(CWnd* pWnd, CString& str, LPRECT pRect)
	{
		CRect rect;
		if (pRect == NULL)
			pWnd->GetWindowRect(rect);
		else 
			rect = *pRect;

		HDC hDC = ::GetWindowDC(pWnd->GetSafeHwnd());
		PathCompactPath(hDC, str.GetBuffer(0), rect.Width());
		str.ReleaseBuffer();
		::ReleaseDC(pWnd->GetSafeHwnd(), hDC);
	}

	static double MyGetTickSec()
	{
		LARGE_INTEGER m_freq, end;
		QueryPerformanceFrequency(&m_freq);
		QueryPerformanceCounter(&end);
		return (double)(end.QuadPart)/(double)m_freq.QuadPart;
	}
	// ���ļ��Ի���
	// ���� lpszFilter ���� _T("Open Files (*.dat)|*.dat|All Files(*.*)|*.*||")
	static BOOL FileOpenDlg(CString& strPathName,	// �ļ�����
							LPCTSTR lpszTitle,		// ���ļ�
							LPCTSTR lpszFilter,		// �ļ�����
							CWnd* pParentWnd)		// ����
	{
		BOOL bResult = FALSE;
		CString strTmp;
		CFileDialog fileOpenDlg(TRUE, NULL, "", NULL, lpszFilter, pParentWnd);
		fileOpenDlg.m_ofn.lpstrTitle = lpszTitle;

		do 
		{
			::GetCurrentDirectory(MAX_PATH,strTmp.GetBuffer(MAX_PATH));
			strTmp.ReleaseBuffer();

			if (fileOpenDlg.DoModal() == IDOK)
			{ // �����ȷ��
				::SetCurrentDirectory(strTmp);
				CFile fileIN;
				if (!fileIN.Open(fileOpenDlg.GetPathName(), CFile::modeRead|CFile::typeBinary))
				{
					if (AfxMessageBox(_T("�ļ��򿪴��󣬰�OK�������ļ�"), MB_OKCANCEL) == IDOK) continue;
					else break;
				}
				fileIN.Close();

				strPathName = fileOpenDlg.GetPathName();
				bResult = TRUE;
			}

		}while(0);

		return bResult;
	}
	// ����Ի���
	static BOOL FileSaveDlg(CString& strPathName,
							LPCTSTR lpszTitle,
							LPCTSTR lpszFilter,
							CWnd* pParentWnd)
	{
		BOOL bResult = FALSE;
		CString strTmp;
		CFileDialog fileSaveDlg(FALSE, NULL, strPathName, OFN_OVERWRITEPROMPT, lpszFilter, pParentWnd);
		fileSaveDlg.GetOFN().lpstrTitle = lpszTitle;

		do 
		{
			::GetCurrentDirectory(MAX_PATH,strTmp.GetBuffer(MAX_PATH));
			strTmp.ReleaseBuffer();

			if (fileSaveDlg.DoModal() == IDOK)
			{ // �����ȷ��
				::SetCurrentDirectory(strTmp);
				CFile fileIN;
				CFile fileOut;
				if (!fileOut.Open(fileSaveDlg.GetPathName(), CFile::modeWrite|CFile::modeCreate|CFile::typeBinary))
				{
					if (AfxMessageBox(_T("�ļ��򿪴��󣬰�OK�������ļ�"), MB_OKCANCEL) == IDOK) continue;
					else break;
				}

				bResult = TRUE;
				strPathName = fileSaveDlg.GetPathName();
			}

		}while(0);

		return bResult;
	}

	static BOOL FileSaveDlgEx(CString& strPathName,
		LPCTSTR lpszExt,
		LPCTSTR lpszTitle,
		LPCTSTR lpszFilter,
		CWnd* pParentWnd)
	{
		BOOL bResult = FALSE;
		CString strTmp;
		CFileDialog fileSaveDlg(FALSE, lpszExt, strPathName, OFN_OVERWRITEPROMPT, lpszFilter, pParentWnd);
		fileSaveDlg.GetOFN().lpstrTitle = lpszTitle;

		do 
		{
			::GetCurrentDirectory(MAX_PATH,strTmp.GetBuffer(MAX_PATH));
			strTmp.ReleaseBuffer();

			if (fileSaveDlg.DoModal() == IDOK)
			{ // �����ȷ��
				::SetCurrentDirectory(strTmp);
				CFile fileIN;
				CFile fileOut;
				if (!fileOut.Open(fileSaveDlg.GetPathName(), CFile::modeWrite|CFile::modeCreate|CFile::typeBinary))
				{
					if (AfxMessageBox(_T("�ļ��򿪴��󣬰�OK�������ļ�"), MB_OKCANCEL) == IDOK) continue;
					else break;
				}

				bResult = TRUE;
				strPathName = fileSaveDlg.GetPathName();
			}

		}while(0);

		return bResult;
	}
	// ��ȡ�ļ�����
	static BOOL ReadFileData(LPCTSTR lpszFileName, BYTE byBuff[], ULONG& cbSize)
	{
		CFile fileIN;
		if (fileIN.Open(lpszFileName, CFile::shareDenyNone|CFile::typeBinary))
		{ // ����򿪳ɹ�
			cbSize = fileIN.Read(byBuff, cbSize);
			fileIN.Close();
			return TRUE;
		}

		cbSize = 0;
		return FALSE;
	}
	// д�ļ�
	static BOOL WriteFileData(LPCTSTR lpszFileName, BYTE byBuff[], ULONG ulSize)
	{
		CFile fileWrite;
		CFileFind finder;
		if (finder.FindFile(lpszFileName))
		{ // ����ļ�����
			if (!fileWrite.Open(lpszFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite|CFile::typeBinary))
			{
				return FALSE;
			}
		}
		else 
		{
			if (!fileWrite.Open(lpszFileName, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
			{
				return FALSE;
			}
		}

		fileWrite.Write(byBuff, ulSize);
		fileWrite.Close();
		return TRUE;
	}

	static BOOL SetClipboardText(CString& strData)
	{
		if (OpenClipboard(NULL))
		{
			EmptyClipboard();
			ULONG ulLen = (strData.GetLength()+1)*sizeof(TCHAR);
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, ulLen);
			TCHAR* szTmp= (TCHAR*)GlobalLock(hMem);
			_tcscpy(szTmp, strData.GetBuffer());
			SetClipboardData(CF_TEXT, hMem);
			CloseClipboard();
			GlobalFree(hMem);
			return TRUE;
		}

		return FALSE;
	}

	// ��array���������ı�ģʽ����
	static void WriteHexToTxt(CFile* pfileOut, BYTE array[], ULONG ulSize)
	{
		BYTE byTmp;
		BYTE* pbyTmpArray = array;
		std::vector<TCHAR> vcSaveBuff;
		vcSaveBuff.resize(ulSize*2+10);

		for (ULONG i=0; i<ulSize; i++, pbyTmpArray++)
		{
			byTmp = ((*pbyTmpArray)&0xF0) >> 4;
			vcSaveBuff[i*2 + 0] = byTmp>=10 ? ('A'+ (byTmp-10)) : '0'+ byTmp;

			byTmp = (*pbyTmpArray)&0xF;
			vcSaveBuff[i*2 + 1] = byTmp>=10 ? ('A'+ (byTmp-10)) : '0'+ byTmp;
		}

		pfileOut->Write(&vcSaveBuff[0], ulSize*2);
	}
	//------------------------------------------------------------------------

	static int CALLBACK BrowsePathCallProc( HWND hWnd,UINT uMsg,LPARAM lParam, LPARAM lpData )   
	{
		LPTSTR lpszPath = (LPTSTR)lpData;

		switch( uMsg )
		{
		case   BFFM_INITIALIZED:
			::SendMessage(hWnd, BFFM_SETSELECTION, 1, (long)lpszPath);
			break;
		default: 
			break;
		}
		return 0;
	}    
	// ѡ��·��
	static BOOL BrowsePath(HWND hwndParent, CString& strRetPath, LPCTSTR lpszDisplayString)
	{
		BROWSEINFO bi;//�����û�ѡ���Ŀ¼��Ϣ
		LPITEMIDLIST  p;
		TCHAR szPath[MAX_PATH] = {0};

		if (!strRetPath.IsEmpty())
			_tcscpy(szPath, strRetPath.GetBuffer());

		bi.hwndOwner		= hwndParent;//Handle to the owner window for the dialog box.
		bi.pidlRoot			= NULL;//�Ի���ĸ�Ŀ¼
		bi.pszDisplayName	= szPath;//�����û�ѡ���Ŀ¼·������������ΪMAX_PATH
		bi.lpszTitle		= lpszDisplayString;//�Ի������ʾ����
		bi.ulFlags			= BIF_RETURNONLYFSDIRS | 0x0040 ;//0x0040 BIF_NEWDIALOGSTYLE
		bi.lpfn				= BrowsePathCallProc;
		bi.lParam			= (LPARAM)szPath;
		bi.iImage			= 0;

		p = SHBrowseForFolder(&bi); //����ѡ��·���Ի���
		if( (p != NULL) && 
			SHGetPathFromIDList(p, szPath) )
		{
			strRetPath = szPath;
			return TRUE;
		}

		return FALSE;
	}

	// �ַ����ָ��strtok�������ƣ��������˸�ȫ�洦��, �����ѷָ���ַ�������dqArrayStr��
	static void StringSplit(LPCTSTR lpszSrc, LPCTSTR lpszControl, std::deque<CString>& dqArrayStr)
	{
		CString strMiddleSrc(lpszSrc);
		CString strCtrl(lpszControl);

		TCHAR* pTmpCtrl; 
		TCHAR* pStrSrc = strMiddleSrc.GetBuffer();
		TCHAR* pStrBegin = strMiddleSrc.GetBuffer();
		CString strTmp;
		TCHAR* pString;
		ULONG ulLen;

		dqArrayStr.clear();

		while(*pStrSrc != 0)
		{
			pTmpCtrl = strCtrl.GetBuffer();;

			do 
			{
				if ((*pStrSrc == *pTmpCtrl)
					|| (*pStrSrc == NULL))
				{
					ulLen = pStrSrc - pStrBegin;

					if (ulLen != 0)
					{
						pString = strTmp.GetBuffer(ulLen + 2);
						memcpy(pString, pStrBegin, ulLen*sizeof(TCHAR));
						pString[ulLen] = 0;

						strTmp.ReleaseBuffer();
					}
					else
					{
						strTmp.Empty();
					}

					dqArrayStr.push_back(strTmp);

					//pTmpString++;
					pStrBegin = pStrSrc+1;
					break;
				}
				pTmpCtrl++;
			} while (*pTmpCtrl != 0);

			pStrSrc++;
		}

		if (pStrBegin != pStrSrc)
		{ // ��ֹ���������
			ulLen = pStrSrc - pStrBegin ;

			pString = strTmp.GetBuffer(ulLen + 2);
			memcpy(pString, pStrBegin, ulLen*sizeof(TCHAR));
			pString[ulLen] = 0;
			strTmp.ReleaseBuffer();

			dqArrayStr.push_back(strTmp);
		}
	}
	//------------------------------------------------------------------------
	template<class _Ty> 
	static _Ty* __mynew(ULONG ulSize)
	{
		return new _Ty[ulSize];
	}

	template<class _Ty> 
	static void __mydelete(_Ty* &pData)
	{
		if (pData )
		{
			delete[] pData;
			pData = NULL;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
        
class CLoadLib
{
public:
	FARPROC GetProcAddress(IN LPCSTR lpProcName)
	{return ::GetProcAddress(_hInst, lpProcName);}
public:
	CLoadLib(){;};
	CLoadLib(IN LPCTSTR libName){SetLibName(libName);}
	BOOL SetLibName(IN LPCTSTR libName){_hInst = ::LoadLibrary(libName);return _hInst!=NULL;};
	~CLoadLib(){FreeLibrary(_hInst);}
private:
	HINSTANCE _hInst;
};

class w2a 
{
public:
	explicit w2a(const wchar_t* wstr)
		: buffer_(0)
	{ 
		if (wstr)
		{
			size_t len = wcslen(wstr);
			int conv = ::WideCharToMultiByte(CP_ACP, 0, wstr, int(len), 0, 0, 0, 0);
			buffer_ = new char[conv + 1];
			::WideCharToMultiByte(CP_ACP, 0, wstr, int(len), buffer_, conv, 0, 0);
			buffer_[conv] = 0;
		}
	}

	~w2a()
	{ delete[] buffer_;  }

	operator const char*() const
	{ return buffer_; }

private:
	char* buffer_;
};

class a2w 
{
public:
	explicit a2w(const char* str)
		: buffer_(0)
	{ 
		if (str)
		{
			size_t len = strlen(str);
			int conv = ::MultiByteToWideChar(CP_ACP, 0, str, int(len), 0, 0);
			buffer_ = new wchar_t[conv + 1];
			::MultiByteToWideChar(CP_ACP, 0, str, int(len), buffer_, conv);
			buffer_[conv] = 0;
		}
	}

	~a2w()
	{ delete[] buffer_;  }

	operator const wchar_t*() const
	{ return buffer_; }

private:
	wchar_t* buffer_;
};
#endif