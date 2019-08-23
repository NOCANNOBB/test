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
// 这个宏，是为了和vs2005兼容
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
// 创建自己的Dialog
#define NewDlgCreateWindows(retX, cclass, thisclass) \
	do {\
		retX = new cclass(); \
		BOOL bRet = retX->Create(cclass::IDD, thisclass);\
		ASSERT(bRet!=FALSE); \
		retX->ShowWindow(SW_HIDE);\
	} while (0);
	
// 释放自己创建的Dialog
#define DelDlgDestroyWindows(pDlg) \
	if (pDlg) { \
		pDlg->DestroyWindow(); \
		delete pDlg;\
		pDlg = NULL;\
	}
// 这个宏主要是用于临时使用，方便释放制作，平时尽量使用my_space_define::my_malloc 创建释放内存
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
// 创建线程
//#define ExCreateThread(fnThread, pParam) CreateThread(NULL, 0, fnThread, pParam, 0, NULL)
#define ExCreateThread(fnThread, pParam) reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, fnThread, pParam, 0, NULL))
// 释放线程，这个为了和创建线程函数名对应所写
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
// 原来删除线程使用宏
#define DelThread(hThread, timeoutMS) ExReleaseThread(hThread, timeoutMS)
//////////////////////////////////////////////////////////////////////////
// 限制数值在最大值和最小值之间，超过这等于最大值或最小值
#define LIMIT_NUM(num,mn,mx) \
	(((num)<(mn))?(mn) : ((num)>(mx)?(mx):(num)))
//-----------------------------	
// 判断是否在最大值最小值范围之内，如果超出为FALSE,不超出为TRUE
#define IsLimit(tmpnum, maxnum, minnum) (((tmpnum)<=(maxnum))&&((tmpnum)>=(minnum)))
//////////////////////////////////////////////////////////////////////////
// 量程转换 x转换前的值 o_max,o_min转换后的最大值和最小值
// 这个宏主要是为了方便阅读
//#define RangeConv(x, x_max, x_min, o_max, o_min, o_offset) \
//	(((((x)-x_min)*((o_max)-(o_min))/((x_max)-(x_min))) + (o_min)) + (o_offset))

#define RangeConv(x, x_max, x_min, o_max, o_min) \
	(((((x)-x_min)*((o_max)-(o_min))/((x_max)-(x_min))) + (o_min)) )

// 判断浮点数是否相等,precision是比较精度
// 例如 DOUBLE_CMP_EQU(2.3, 2.33, 0.1) 这样会认为这两个浮点数相同
#define DOUBLE_CMP_EQU(a, b, pre) (fabs((a)-(b))<(pre))
//////////////////////////////////////////////////////////////////////////
// 用于计算静态结构体或者静态数组成员个数
// 注意不能使用动态创建的指针或者数组，函数传递的指针不可以
#define GetStructSize(pStruct) (sizeof(pStruct)/sizeof(pStruct[0]))
//////////////////////////////////////////////////////////////////////////
// 16位数据高低8位翻转
#ifndef SWAP_WORD
	#define SWAP_WORD(wData) MAKEWORD(HIBYTE((wData)), LOBYTE((wData)))
#endif
// 32位数据 高低位翻转，例如:0x12345678 翻转后 0x78563412
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
// 字节转换成字符串， str必须是CString 类型 ,num是字节数
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
// 设置ListCtrl中文本，如果设置文本和原来相同，则不进行写入
// listCtrl CListCtrl类，index是行号 subItem是列号 strText写入的字符串
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
{ // 自定义函数
	static void DoEvents()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);
			TranslateMessage(&msg);
		}
	}
	// 获得当前应用程序文件夹
	static void GetAppPath(CString& strRetPath)
	{
		CString strTmp;
		LPTSTR pStr = strTmp.GetBuffer(MAX_PATH);
		GetModuleFileName(NULL, pStr, MAX_PATH);
		pStr[strTmp.ReverseFind(_T('\\'))] = _T('\0');
		strTmp.ReleaseBuffer();
		strRetPath = strTmp;
	}
	// 把16进制字符串转换为byte数组
	static void StringToHexByte(LPCTSTR lpszString, BYTE byData[], ULONG& cbSize)
	{
		CString strData;
		strData = lpszString;
		// 把字符串字母最小化
		strData.MakeLower();
		// 自定义分割
		CString strToks(_T(", "));
		CString strTmp;
		LPTSTR	lpszTmp,
				lpszData = _tcstok(strData.GetBuffer(0), strToks);
		ULONG ulCount = 0;

		while ((lpszData != NULL)
			&& (ulCount < cbSize))
		{
			// 判断第一个字符是否x
			lpszTmp = *lpszData=='x' ? (lpszData+1) : lpszData;

			byData[ulCount++] =(BYTE)(_tcstoul(lpszTmp, NULL, 16)&0xFF);
			lpszData = _tcstok(NULL, strToks);
		}

		cbSize = ulCount;
	}
	// 把byte数组转换成字符串
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
	// 把byte数组转换成字符串,中间没有空格
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
	// 解析文本文件，把文本文件中的数值转换为8位数据
	//例如文本文件内容 55aa22556699,转换到数组中为 0x55 0xaa 0x22 0x55 0x66 0x99
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

	// 自动识别是文本文件，还是2进制文件
	static BOOL AuotReadFileTxtOrDat(LPCSTR lpszFileName, std::vector<BYTE>& vcBuff, ULONG ulReadMode=0/*0:自动 1:文本 2:二进制*/)
	{ // 返回假，是文件打开错误
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

	// 压缩路径
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
	// 打开文件对话框
	// 参数 lpszFilter 例子 _T("Open Files (*.dat)|*.dat|All Files(*.*)|*.*||")
	static BOOL FileOpenDlg(CString& strPathName,	// 文件反馈
							LPCTSTR lpszTitle,		// 打开文件
							LPCTSTR lpszFilter,		// 文件过滤
							CWnd* pParentWnd)		// 父类
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
			{ // 如果是确定
				::SetCurrentDirectory(strTmp);
				CFile fileIN;
				if (!fileIN.Open(fileOpenDlg.GetPathName(), CFile::modeRead|CFile::typeBinary))
				{
					if (AfxMessageBox(_T("文件打开错误，按OK继续打开文件"), MB_OKCANCEL) == IDOK) continue;
					else break;
				}
				fileIN.Close();

				strPathName = fileOpenDlg.GetPathName();
				bResult = TRUE;
			}

		}while(0);

		return bResult;
	}
	// 保存对话框
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
			{ // 如果是确定
				::SetCurrentDirectory(strTmp);
				CFile fileIN;
				CFile fileOut;
				if (!fileOut.Open(fileSaveDlg.GetPathName(), CFile::modeWrite|CFile::modeCreate|CFile::typeBinary))
				{
					if (AfxMessageBox(_T("文件打开错误，按OK继续打开文件"), MB_OKCANCEL) == IDOK) continue;
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
			{ // 如果是确定
				::SetCurrentDirectory(strTmp);
				CFile fileIN;
				CFile fileOut;
				if (!fileOut.Open(fileSaveDlg.GetPathName(), CFile::modeWrite|CFile::modeCreate|CFile::typeBinary))
				{
					if (AfxMessageBox(_T("文件打开错误，按OK继续打开文件"), MB_OKCANCEL) == IDOK) continue;
					else break;
				}

				bResult = TRUE;
				strPathName = fileSaveDlg.GetPathName();
			}

		}while(0);

		return bResult;
	}
	// 读取文件内容
	static BOOL ReadFileData(LPCTSTR lpszFileName, BYTE byBuff[], ULONG& cbSize)
	{
		CFile fileIN;
		if (fileIN.Open(lpszFileName, CFile::shareDenyNone|CFile::typeBinary))
		{ // 如果打开成功
			cbSize = fileIN.Read(byBuff, cbSize);
			fileIN.Close();
			return TRUE;
		}

		cbSize = 0;
		return FALSE;
	}
	// 写文件
	static BOOL WriteFileData(LPCTSTR lpszFileName, BYTE byBuff[], ULONG ulSize)
	{
		CFile fileWrite;
		CFileFind finder;
		if (finder.FindFile(lpszFileName))
		{ // 如果文件存在
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

	// 把array的数据以文本模式保存
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
	// 选择路径
	static BOOL BrowsePath(HWND hwndParent, CString& strRetPath, LPCTSTR lpszDisplayString)
	{
		BROWSEINFO bi;//保存用户选择的目录信息
		LPITEMIDLIST  p;
		TCHAR szPath[MAX_PATH] = {0};

		if (!strRetPath.IsEmpty())
			_tcscpy(szPath, strRetPath.GetBuffer());

		bi.hwndOwner		= hwndParent;//Handle to the owner window for the dialog box.
		bi.pidlRoot			= NULL;//对话框的根目录
		bi.pszDisplayName	= szPath;//保存用户选择的目录路径，长度至少为MAX_PATH
		bi.lpszTitle		= lpszDisplayString;//对话框的显示名称
		bi.ulFlags			= BIF_RETURNONLYFSDIRS | 0x0040 ;//0x0040 BIF_NEWDIALOGSTYLE
		bi.lpfn				= BrowsePathCallProc;
		bi.lParam			= (LPARAM)szPath;
		bi.iImage			= 0;

		p = SHBrowseForFolder(&bi); //弹出选择路径对话框
		if( (p != NULL) && 
			SHGetPathFromIDList(p, szPath) )
		{
			strRetPath = szPath;
			return TRUE;
		}

		return FALSE;
	}

	// 字符串分割，和strtok功能类似，但是做了更全面处理, 处理后把分割的字符串放入dqArrayStr中
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
		{ // 防止最后有数据
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