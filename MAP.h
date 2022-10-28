#pragma once

#include "BAM.h"

const int UM_OUT = WM_USER + 1;

class CMAP
{
public:
	CMAP(CWnd* pParent);
	~CMAP();

public:
	CWnd* m_pParent;
	CRect m_maprect;
	CRect m_MM[20][20];
	bool m_bFirst;
	CBAM m_bam;
	BAMPOS m_bap;
	bool m_bbb;

public:
	void Draw(CDC* pDC);
	void Drawmap(CDC* pDC);
	void playgame(DIRECTION dir);
	void bap();
	bool iseat();

public:
	int m_Mscore; //=timer*5+bap*20 �������

	int m_Mtimer; //����ð�
	int m_Mbap; //�������
	int m_Mbam; //�����
};

