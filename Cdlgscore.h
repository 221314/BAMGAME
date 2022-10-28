#pragma once


// Cdlgscore 대화 상자입니다.

class Cdlgscore : public CDialogEx
{
	DECLARE_DYNAMIC(Cdlgscore)

public:
	Cdlgscore(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Cdlgscore();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
