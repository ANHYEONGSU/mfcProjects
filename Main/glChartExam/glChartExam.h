
// glChartExam.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CglChartExamApp:
// �� Ŭ������ ������ ���ؼ��� glChartExam.cpp�� �����Ͻʽÿ�.
//

class CglChartExamApp : public CWinApp
{
public:
	CglChartExamApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CglChartExamApp theApp;