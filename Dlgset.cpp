// Dlgset.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BAMGAME.h"
#include "Dlgset.h"
#include "afxdialogex.h"


// CDlgset ��ȭ �����Դϴ�.

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


// CDlgset �޽��� ó�����Դϴ�.


BOOL CDlgset::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDCANCEL)->SetWindowTextW(m_str);
	GetDlgItem(IDOK)->SetWindowTextW(m_sstr);

	m_dlgSpin.SetRange(1, 3);
	m_dlgSpin.SetPos(m_dlgLevel);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDlgset::OnBnClickedOk()
{
	if (m_str == _T("���"))
	{

		int res = MessageBox(_T("���õ� ���̵��� ������ ������մϴ�. \n�����ϴ� ������ �簳 �Ϸ��� �ƴϿ� ��ư�� �����ϼ���."),
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
