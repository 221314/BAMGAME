#pragma once
#include "afxcmn.h"


// CDlgset ��ȭ �����Դϴ�.

class CDlgset : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgset)

public:
	CDlgset(CString str,CString sstr, int lev, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgset();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_dlgLevel;
	CSpinButtonCtrl m_dlgSpin;
	CString m_str;
	CString m_sstr;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
