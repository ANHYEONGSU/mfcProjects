
// csvExam.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CcsvExamApp:
// �� Ŭ������ ������ ���ؼ��� csvExam.cpp�� �����Ͻʽÿ�.
//

class CcsvExamApp : public CWinApp
{
public:
	CcsvExamApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CcsvExamApp theApp;