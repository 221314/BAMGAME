#pragma once


// Cdlgscore ��ȭ �����Դϴ�.

class Cdlgscore : public CDialogEx
{
	DECLARE_DYNAMIC(Cdlgscore)

public:
	Cdlgscore(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Cdlgscore();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_dlgTime;
	UINT m_dlgBap;
	UINT m_dlgBam;
	UINT m_dlgScore;

	CToolTipCtrl m_tooltip;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_dlgLev;
};
