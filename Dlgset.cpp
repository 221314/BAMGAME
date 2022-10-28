// Dlgset.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BAMGAME.h"
#include "Dlgset.h"
#include "afxdialogex.h"


// CDlgset 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgset, CDialogEx)

CDlgset::CDlgset(CString str, CString sstr, int lev, CWnd* pParent /*=NULL*/): CDialogEx(IDD_DIALOG3, pParent)
, m_dlgLevel(lev)
{
	m_str = str;
	m_sstr = sstr;

}

CDlgset::~CDlgset()
{
}

void CDlgset::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dlgLevel);
	DDV_MinMaxInt(pDX, 1, 1, 3);
	DDX_Control(pDX, IDC_SPIN1, m_dlgSpin);
}


BEGIN_MESSAGE_MAP(CDlgset, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgset::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgset 메시지 처리기입니다.


BOOL CDlgset::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDCANCEL)->SetWindowTextW(m_str);
	GetDlgItem(IDOK)->SetWindowTextW(m_sstr);

	m_dlgSpin.SetRange(1, 3);
	m_dlgSpin.SetPos(m_dlgLevel);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgset::OnBnClickedOk()
{
	if (m_str == _T("취소"))
	{

		int res = MessageBox(_T("선택된 난이도로 게임을 재시작합니다. \n진행하던 게임을 재개 하려면 아니오 버튼을 선택하세요."),
			_T(" "), MB_YESNO | MB_ICONEXCLAMATION);

		if (res == IDYES)
		{
			EndDialog(IDOK);
		}
		else
		{
			return;
		}
	}

	CDialogEx::OnOK();
}
