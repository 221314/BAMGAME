
// BAMGAME.h : BAMGAME ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CBAMGAMEApp:
// �� Ŭ������ ������ ���ؼ��� BAMGAME.cpp�� �����Ͻʽÿ�.
//

class CBAMGAMEApp : public CWinAppEx
{
public:
	CBAMGAMEApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBAMGAMEApp theApp;
