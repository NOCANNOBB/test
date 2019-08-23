#pragma once
#include "afxcmn.h"


// CDlgBaseAI 对话框

class CDlgBaseAI : public CDialog
{
	DECLARE_DYNAMIC(CDlgBaseAI)

public:
	CDlgBaseAI(IBaseAI* pIBaseAI);   // 标准构造函数
	virtual ~CDlgBaseAI();

// 对话框数据
	enum { IDD = IDD_DIALOG_BASEAI,
			TM_REFRESH = 1,
			TM_READ_AI
	};

private:
	std::vector<double> m_vcVolt;
	IBaseAI*	m_pIBaseAI;
	CImageList	m_ImageForList;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk(){};
	afx_msg void OnBnClickedCancel(){};
	CListCtrl m_listCtrl;
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedExit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
