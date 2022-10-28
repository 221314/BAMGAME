
// BAMGAMEView.cpp : CBAMGAMEView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "BAMGAME.h"
#endif

#include "BAMGAMEDoc.h"
#include "BAMGAMEView.h"
#include "Cdlgscore.h"
#include "Dlgset.h"

//�Ҹ����� �ֱ�
#include <mmsystem.h> 
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBAMGAMEView

IMPLEMENT_DYNCREATE(CBAMGAMEView, CView)

BEGIN_MESSAGE_MAP(CBAMGAMEView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_MESSAGE(UM_OUT, &CBAMGAMEView::OnOut)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CBAMGAMEView ����/�Ҹ�

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CBAMGAMEView �׸���

void CBAMGAMEView::ONtimer()
{	
		SetTimer(1, 1000, NULL); //Ÿ�̸�

		if (m_level == 1) //���̵� 1
		{
			SetTimer(2, 500, NULL);
		}
		else if (m_level == 2) //���̵� 2
		{
			SetTimer(2, 250, NULL);
		}
		else if (m_level == 3) //���̵� 3
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


	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CBAMGAMEView �μ�

BOOL CBAMGAMEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CBAMGAMEView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CBAMGAMEView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CBAMGAMEView ����

#ifdef _DEBUG
void CBAMGAMEView::AssertValid() const
{
	CView::AssertValid();
}

void CBAMGAMEView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CBAMGAMEDoc* CBAMGAMEView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBAMGAMEDoc)));
	return (CBAMGAMEDoc*)m_pDocument;
}
#endif //_DEBUG

LRESULT CBAMGAMEView::OnOut(WPARAM wp, LPARAM lp)
{
	//���Ӿƿ�, ���� ��� dlg
	PlaySound(_T(".\\res\\cancel5.wav"), 0, SND_ASYNC);
	OFFtimer();
	Cdlgscore dlg;
	dlg.m_dlgTime = m_map.m_Mtimer;
	dlg.m_dlgBam = m_map.m_Mbam;
	dlg.m_dlgBap = m_map.m_Mbap;
	dlg.m_dlgLev = m_level;

	dlg.m_dlgScore = m_map.m_Mscore = m_map.m_Mtimer * 5 + m_map.m_Mbap * 50;

	int result = dlg.DoModal();

	if (result == IDOK) //�����
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

// CBAMGAMEView �޽��� ó����

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
	CDlgset dlg(_T("����"),_T("���� ����"), 1);
	int result = dlg.DoModal();

	m_level = dlg.m_dlgLevel;

	//���������� �ߴ� dlg (���ӽ��� or ����)
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
		CDlgset dlg(_T("���"),_T("�����"),m_level);
		int result = dlg.DoModal();

		if (result == IDOK) //���̵����� ��Ʈ�� ���� �� Ȱ��ȭ, ���� �����(��Ȯ�� �޼��� ����)
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
		else //�۾�(���̵���) ����ϰ� �����簳
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
