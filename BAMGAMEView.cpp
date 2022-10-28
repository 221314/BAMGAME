
// BAMGAMEView.cpp : CBAMGAMEView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "BAMGAME.h"
#endif

#include "BAMGAMEDoc.h"
#include "BAMGAMEView.h"
#include "Cdlgscore.h"
#include "Dlgset.h"

//소리파일 넣기
#include <mmsystem.h> 
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBAMGAMEView

IMPLEMENT_DYNCREATE(CBAMGAMEView, CView)

BEGIN_MESSAGE_MAP(CBAMGAMEView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_MESSAGE(UM_OUT, &CBAMGAMEView::OnOut)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CBAMGAMEView 생성/소멸

CBAMGAMEView::CBAMGAMEView() : m_map(this)
{
	//m_vdir = KEY_RIGHT;
	m_vdir = KEY_NULL;
	bStart = false;
	btimer = false;
}

CBAMGAMEView::~CBAMGAMEView()
{
}

BOOL CBAMGAMEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CBAMGAMEView 그리기

void CBAMGAMEView::ONtimer()
{	
		SetTimer(1, 1000, NULL); //타이머

		if (m_level == 1) //난이도 1
		{
			SetTimer(2, 500, NULL);
		}
		else if (m_level == 2) //난이도 2
		{
			SetTimer(2, 250, NULL);
		}
		else if (m_level == 3) //난이도 3
		{
			SetTimer(2, 50, NULL);
		}
}

void CBAMGAMEView::OFFtimer()
{
	KillTimer(1);
	KillTimer(2);
}

void CBAMGAMEView::OnDraw(CDC* pDC)
{
	CBAMGAMEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_map.Draw(pDC);


	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CBAMGAMEView 인쇄

BOOL CBAMGAMEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CBAMGAMEView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CBAMGAMEView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CBAMGAMEView 진단

#ifdef _DEBUG
void CBAMGAMEView::AssertValid() const
{
	CView::AssertValid();
}

void CBAMGAMEView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CBAMGAMEDoc* CBAMGAMEView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBAMGAMEDoc)));
	return (CBAMGAMEDoc*)m_pDocument;
}
#endif //_DEBUG

LRESULT CBAMGAMEView::OnOut(WPARAM wp, LPARAM lp)
{
	//게임아웃, 게임 결과 dlg
	PlaySound(_T(".\\res\\cancel5.wav"), 0, SND_ASYNC);
	OFFtimer();
	Cdlgscore dlg;
	dlg.m_dlgTime = m_map.m_Mtimer;
	dlg.m_dlgBam = m_map.m_Mbam;
	dlg.m_dlgBap = m_map.m_Mbap;
	dlg.m_dlgLev = m_level;

	dlg.m_dlgScore = m_map.m_Mscore = m_map.m_Mtimer * 5 + m_map.m_Mbap * 50;

	int result = dlg.DoModal();

	if (result == IDOK) //재시작
	{
		bStart = false;
		btimer = false;
		m_vdir = KEY_NULL;
		m_map.m_bam.m_bamlist.clear();
		m_map.m_bam.bbam();
		m_map.m_bbb = false;

		m_map.bap();
		m_map.m_Mbap = 0;
		m_map.m_Mtimer = 0;
		m_map.m_Mbam = 3;
		m_map.m_Mscore = 0;
		//ONtimer();
		Invalidate(TRUE);
			
	}
	else if(result==IDCANCEL)
	{
		AfxGetMainWnd()->PostMessageW(WM_CLOSE, 0, 0);
	}

	return LRESULT();
}

// CBAMGAMEView 메시지 처리기

void CBAMGAMEView::OnTimer(UINT_PTR nIDEvent)
{

	if (nIDEvent == 1)
	{		
		m_map.m_Mtimer += 1;
		m_map.m_Mscore += 5;
		Invalidate(TRUE);
	}
	if (nIDEvent == 2)
	{
		btimer = true;
		m_map.playgame(m_vdir);
		Invalidate(TRUE);
	}

	CView::OnTimer(nIDEvent);
}


void CBAMGAMEView::OnInitialUpdate()
{
	CDlgset dlg(_T("종료"),_T("게임 시작"), 1);
	int result = dlg.DoModal();

	m_level = dlg.m_dlgLevel;

	//게임켰을때 뜨는 dlg (게임시작 or 종료)
	if (result == IDOK)
	{
		PlaySound(_T(".\\res\\decision22.wav"), 0, SND_ASYNC);
		//ONtimer();
	}
	else if (result == IDCANCEL)
	{
		//AfxGetMainWnd()->SendMessageW(WM_CLOSE, 0, 0);
		AfxGetMainWnd()->ShowWindow(false);
		AfxGetMainWnd()->PostMessageW(WM_CLOSE, 0, 0);
		ShowWindow(false);		
	}

	CView::OnInitialUpdate();
}


void CBAMGAMEView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	switch (nChar)
	{
	
	case 32:
	{
		OFFtimer();
		CDlgset dlg(_T("취소"),_T("재시작"),m_level);
		int result = dlg.DoModal();

		if (result == IDOK) //난이도조절 컨트롤 조작 시 활성화, 게임 재시작(재확인 메세지 띄우기)
		{
			m_level = dlg.m_dlgLevel;


			m_vdir = KEY_NULL;
			bStart = false;
			btimer = false;
			m_map.m_bam.m_bamlist.clear();
			m_map.m_bam.bbam();
			m_map.m_bbb = false;

			m_map.bap();
			m_map.m_Mbap = 0;
			m_map.m_Mtimer = 0;
			m_map.m_Mbam = 3;
			Invalidate(TRUE);
			//ONtimer();


		}
		else //작업(난이도등) 취소하고 게임재개
		{
			if(bStart)
				ONtimer();
		}
	}
		break;
	case VK_LEFT:

		if (btimer == true)
			m_vdir = KEY_LEFT;
		PlaySound(_T(".\\res\\29.wav"), 0, SND_ASYNC);
		break;
	case VK_RIGHT:
		if (!bStart)
		{
			ONtimer();
			bStart = !bStart;
		}

		m_vdir = KEY_RIGHT;
		PlaySound(_T(".\\res\\25.wav"), 0, SND_ASYNC);
		break;
	case VK_UP:
		if (!bStart)
		{
			ONtimer();
			bStart = !bStart;
		}
		m_vdir = KEY_UP;
		PlaySound(_T(".\\res\\27.wav"), 0, SND_ASYNC);
		break;
	case VK_DOWN:
		if (!bStart)
		{
			ONtimer();
			bStart = !bStart;
		}
		m_vdir = KEY_DOWN;
		PlaySound(_T(".\\res\\30.wav"), 0, SND_ASYNC);
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CBAMGAMEView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;

	//return CView::OnEraseBkgnd(pDC);
}
