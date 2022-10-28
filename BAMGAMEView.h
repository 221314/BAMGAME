
// BAMGAMEView.h : CBAMGAMEView 클래스의 인터페이스
//

#pragma once
#include "MAP.h"

class CBAMGAMEView : public CView
{
protected: // serialization에서만 만들어집니다.
	CBAMGAMEView();
	DECLARE_DYNCREATE(CBAMGAMEView)

// 특성입니다.
public:
	CBAMGAMEDoc* GetDocument() const;

// 작업입니다.
public:
	CMAP m_map;
	
	DIRECTION m_vdir;

public:
	bool bStart;
	bool btimer;

	void ONtimer();
	void OFFtimer();
	int m_level;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CBAMGAMEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	LRESULT OnOut(WPARAM wp, LPARAM lp);

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // BAMGAMEView.cpp의 디버그 버전
inline CBAMGAMEDoc* CBAMGAMEView::GetDocument() const
   { return reinterpret_cast<CBAMGAMEDoc*>(m_pDocument); }
#endif

