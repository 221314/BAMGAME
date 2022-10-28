
// BAMGAMEView.h : CBAMGAMEView Ŭ������ �������̽�
//

#pragma once
#include "MAP.h"

class CBAMGAMEView : public CView
{
protected: // serialization������ ��������ϴ�.
	CBAMGAMEView();
	DECLARE_DYNCREATE(CBAMGAMEView)

// Ư���Դϴ�.
public:
	CBAMGAMEDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	CMAP m_map;
	
	DIRECTION m_vdir;

public:
	bool bStart;
	bool btimer;

	void ONtimer();
	void OFFtimer();
	int m_level;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CBAMGAMEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	LRESULT OnOut(WPARAM wp, LPARAM lp);

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // BAMGAMEView.cpp�� ����� ����
inline CBAMGAMEDoc* CBAMGAMEView::GetDocument() const
   { return reinterpret_cast<CBAMGAMEDoc*>(m_pDocument); }
#endif

