
// FirstProject.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CFirstProjectApp:
// �� Ŭ������ ������ ���ؼ��� FirstProject.cpp�� �����Ͻʽÿ�.
//

class CFirstProjectApp : public CWinApp
{
public:
	CFirstProjectApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CFirstProjectApp theApp;