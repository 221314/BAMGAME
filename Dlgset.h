#pragma once
#include "afxcmn.h"


// CDlgset 대화 상자입니다.

class CDlgset : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgset)

public:
	CDlgset(CString str,CString sstr, int lev, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgset();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_dlgLevel;
	CSpinButtonCtrl m_dlgSpin;
	CString m_str;
	CString m_sstr;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
