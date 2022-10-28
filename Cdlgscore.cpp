// Cdlgscore.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BAMGAME.h"
#include "Cdlgscore.h"
#include "afxdialogex.h"


// Cdlgscore 대화 상자입니다.

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


// Cdlgscore 메시지 처리기입니다.


BOOL Cdlgscore::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_tooltip.Create(this);
	m_tooltip.SetMaxTipWidth(200);    //<- "\n"사용에 필요한 것...
	m_tooltip.AddTool(GetDlgItem(IDC_SCORE), _T("점수 계산 기준 :\n경과시간*5+먹은 사과갯수*50점"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL Cdlgscore::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}
