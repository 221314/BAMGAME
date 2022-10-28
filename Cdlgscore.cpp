// Cdlgscore.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BAMGAME.h"
#include "Cdlgscore.h"
#include "afxdialogex.h"


// Cdlgscore ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Cdlgscore, CDialogEx)

Cdlgscore::Cdlgscore(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_dlgTime(0)
	, m_dlgBap(0)
	, m_dlgBam(0)
	, m_dlgScore(0)
	, m_dlgLev(0)
{

}

Cdlgscore::~Cdlgscore()
{
}

void Cdlgscore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TIMER, m_dlgTime);
	DDX_Text(pDX, IDC_BAP, m_dlgBap);
	DDX_Text(pDX, IDC_BAM, m_dlgBam);
	DDX_Text(pDX, IDC_SCORE, m_dlgScore);
	DDX_Text(pDX, IDC_TIMER2, m_dlgLev);
}


BEGIN_MESSAGE_MAP(Cdlgscore, CDialogEx)
END_MESSAGE_MAP()


// Cdlgscore �޽��� ó�����Դϴ�.


BOOL Cdlgscore::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_tooltip.Create(this);
	m_tooltip.SetMaxTipWidth(200);    //<- "\n"��뿡 �ʿ��� ��...
	m_tooltip.AddTool(GetDlgItem(IDC_SCORE), _T("���� ��� ���� :\n����ð�*5+���� �������*50��"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


BOOL Cdlgscore::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}
