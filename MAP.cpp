#include "stdafx.h"
#include "MAP.h"

//소리파일 넣기
#include <mmsystem.h> 
#pragma comment(lib,"winmm.lib")

CMAP::CMAP(CWnd* pParent) 
{	
	m_pParent = pParent;
	m_bFirst = true;
	srand( unsigned int(time(NULL)));
	m_bbb = false;
	bap();

	m_Mscore = 0;
	m_Mtimer = 0;
	m_Mbam = 3;
	m_Mbap = 0;

}


CMAP::~CMAP()
{
	
}



void CMAP::Drawmap(CDC * pDC)
{
	CRect rect;
	m_pParent->GetClientRect(&rect);

	//더블버퍼링 ...
	CDC memDC;

	memDC.CreateCompatibleDC(pDC);

	CBitmap bmp, *pbmp;

	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	pbmp = memDC.SelectObject(&bmp);

	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	//




	CString str;
	CString ttt;
	CString rrr;
	CString sss;
	str.Format(_T("BAP : %d"), m_Mbap);
	memDC.TextOutW(150, 7, str);
	ttt.Format(_T("TIME : %d"), m_Mtimer);
	memDC.TextOutW(50, 7, ttt);
	sss.Format(_T("SCORE : %d"), m_Mscore);
	memDC.TextOutW(250, 7, sss);
	str.Format(_T("일시정지 : SPACE키를 선택하세요"));
	memDC.TextOutW(500, 7, str);


	int gap = 30;

	m_maprect = rect;
	m_maprect.DeflateRect(gap, gap);

	int MAP_H = m_maprect.Height() / m_ROW;
	int MAP_W = m_maprect.Width() / m_COL;

	for (int i = 0; i < m_ROW + 1; i++)
	{
		// 가로줄 그리기
		memDC.MoveTo(rect.left + gap, rect.top + gap + (i*MAP_H));
		memDC.LineTo(rect.right - gap, rect.top + gap + (i*MAP_H));

		// 세로줄 그리기
		memDC.MoveTo(rect.left + gap + (i*MAP_W), rect.top + gap);
		memDC.LineTo(rect.left + gap+(i*MAP_W), rect.bottom -(gap+18));
	}

	if (m_bFirst == true)
	{
		for (int i = 0; i < m_ROW; i++)
		{
			for (int k = 0; k < m_COL; k++)
			{
				CPoint pt = m_maprect.TopLeft();
				pt.Offset(k*MAP_W, i*MAP_H);
				CPoint pt2 = pt;
				pt2.Offset(MAP_W, MAP_H);
				
				m_MM[i][k] = CRect(pt, pt2);
			}
		}

		m_bFirst = false;
	}
	CBrush h, m, y, *p = NULL; //브러쉬생성
	h.CreateSolidBrush(RGB(53,104,216));
	m.CreateSolidBrush(RGB(100,153,255));
	y.CreateSolidBrush(RGB(255, 188, 106));

	//밥그리기
	if (m_bbb == true)
	{
		memDC.SelectObject(&y);
		memDC.Ellipse(m_MM[m_bap.y][m_bap.x]);
		rect.DeflateRect(2, 2);
	}

	// 뱀마디를 순환하는 포인터
	list<BAMPOS>::iterator itr;
	//memDC.SelectStockObject(BLACK_BRUSH);
	for (itr = m_bam.m_bamlist.begin(); itr != m_bam.m_bamlist.end(); ++itr)
	{
		if (itr == m_bam.m_bamlist.begin())
			p = memDC.SelectObject(&h);
		else
			memDC.SelectObject(&m);

		// 뱀 사각형 크기 축소
		CRect rect(m_MM[itr->y][itr->x]);
		rect.DeflateRect(2, 2);

		memDC.Rectangle(rect);
	}

	//더블버퍼링...memDC로 그린 (완성된)비트맵이미지를 pDC로 복사하기
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);


	pDC->SelectObject(p);
	h.DeleteObject();
	m.DeleteObject();

	memDC.SelectObject(pbmp); //더블버퍼링...memDC삭제
	bmp.DeleteObject();
	
}

void CMAP::playgame(DIRECTION dir)
{
	if (m_bam.move(dir) == false)
	{
		m_pParent->PostMessage(UM_OUT, 0, 0); //부모(뷰)에 메세지전달
	}
	else
	{

		if (m_bam.iscontact())
		{
			//PlaySound(_T(".\\res\\cancel5.wav"), 0, SND_ASYNC);
			m_pParent->PostMessage(UM_OUT, 0, 0);
		}
		bool b = iseat();
	}
}

void CMAP::bap()
{
	if(m_bbb==false)
	{
		m_bbb = true;

		bool b = false;
		int cnt = 0;

		while (1)
		{	
			cnt = 0;

			m_bap.x = rand() % m_COL;
			m_bap.y = rand() % m_ROW;

			list<BAMPOS>::iterator itr;
			for (itr = m_bam.m_bamlist.begin(); itr != m_bam.m_bamlist.end(); ++itr)
			{
				if (itr->x == m_bap.x && itr->y == m_bap.y)
					break;
				else
					cnt++;
			}

			if (cnt == m_bam.m_bamlist.size())
				break;
		}

	}	
}

bool CMAP::iseat()
{
	BAMPOS head = m_bam.m_bamlist.front();
	if (head.x == m_bap.x)
	{
		if (head.y == m_bap.y)
		{			
			PlaySound(_T(".\\res\\4se.wav"), 0, SND_ASYNC);
			m_Mbap += 1;
			m_Mbam += 1;
			m_Mscore += 50;
			m_bbb = false;
			bap();
			m_bam.addtail();
		}
	}
	return false;
}

void CMAP::Draw(CDC * pDC)
{
	CRect rect;
	m_pParent->GetClientRect(&rect);

	Drawmap(pDC);
}


