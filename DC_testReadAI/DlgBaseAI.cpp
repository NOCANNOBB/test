// DlgBaseAI.cpp : 实现文件
//

#include "stdafx.h"
#include "pro.h"
#include "DlgBaseAI.h"


// CDlgBaseAI 对话框

IMPLEMENT_DYNAMIC(CDlgBaseAI, CDialog)

CDlgBaseAI::CDlgBaseAI(IBaseAI* pIBaseAI)
	: CDialog(CDlgBaseAI::IDD, NULL)
{
	m_pIBaseAI = pIBaseAI;
}

CDlgBaseAI::~CDlgBaseAI()
{
}

void CDlgBaseAI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AI, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CDlgBaseAI, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgBaseAI::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgBaseAI::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_EXIT, &CDlgBaseAI::OnBnClickedExit)
	ON_WM_TIMER()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// CDlgBaseAI 消息处理程序

BOOL CDlgBaseAI::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ImageForList.Create(IDB_BITMAP_FORLIST, 18, 5, RGB(0, 0, 0));

	ListView_SetExtendedListViewStyle(m_listCtrl.m_hWnd, LVS_EX_FULLROWSELECT);
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle()|LVS_EX_GRIDLINES);

	m_listCtrl.SetImageList(&m_ImageForList,LVSIL_SMALL);
	m_listCtrl.InsertColumn(0, _T("通道号"), LVCFMT_LEFT, 100, 100);
	m_listCtrl.InsertColumn(1, _T("值"), LVCFMT_LEFT, 120, 120);

	CString str;

	if (m_pIBaseAI == NULL) 
	{
		AfxMessageBox(_T("基类错误!"));
		CDialog::OnCancel();
		return FALSE;
	}

	m_vcVolt.resize(m_pIBaseAI->GetChCount());

	for (ULONG i=0; i<m_vcVolt.size(); i++)
	{
		str.Format(_T("通道%d"), i);
		m_listCtrl.InsertItem(i, str);
		m_listCtrl.SetItemData(i, (DWORD_PTR)&m_vcVolt[i]);
	}

	SetTimer(TM_REFRESH, 300, NULL);
	SetTimer(TM_READ_AI, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgBaseAI::OnClose()
{
	CDialog::OnCancel();
	CDialog::OnClose();
}

void CDlgBaseAI::OnDestroy()
{

	CDialog::OnDestroy();
}

void CDlgBaseAI::OnBnClickedExit()
{
	CDialog::OnCancel();
}

void CDlgBaseAI::OnTimer(UINT_PTR nIDEvent)
{
	if (TM_READ_AI == nIDEvent)
	{
		static BOOL bReadAI = FALSE;

		if (bReadAI) return ;
		bReadAI = TRUE;

		for (ULONG i=0; i<m_vcVolt.size(); i++)
		{
			m_pIBaseAI->ReadOneDC(&m_vcVolt[i], i);
		}

		bReadAI = FALSE;
	}
	else if (TM_REFRESH == nIDEvent)
	{
		static BOOL bRefresh = FALSE;
		double* pdfVolt;
		if (bRefresh) return ;
		bRefresh = TRUE;

		CString strNew, strOld;

		for (int i=0; i<m_listCtrl.GetItemCount(); i++)
		{
			pdfVolt = (double*)m_listCtrl.GetItemData(i);
			strNew.Format(_T("%.3f"), *pdfVolt);

			strOld = m_listCtrl.GetItemText(i, 1);

			if (strOld != strNew)
			{
				m_listCtrl.SetItemText(i, 1, strNew);
			}
		}

		bRefresh = FALSE;;
	}

	CDialog::OnTimer(nIDEvent);
}
