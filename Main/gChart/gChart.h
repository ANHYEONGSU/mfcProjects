
// gChart.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CgChartApp:
// �� Ŭ������ ������ ���ؼ��� gChart.cpp�� �����Ͻʽÿ�.
//

class CgChartApp : public CWinApp
{
public:
	CgChartApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CgChartApp theApp;