
// mfcCImage1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CmfcCImage1App:
// �� Ŭ������ ������ ���ؼ��� mfcCImage1.cpp�� �����Ͻʽÿ�.
//

class CmfcCImage1App : public CWinApp
{
public:
	CmfcCImage1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CmfcCImage1App theApp;