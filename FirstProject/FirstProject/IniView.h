#pragma once

#include "../include/gLogger.h"
#pragma comment(lib, "../lib/gLogger.lib")

// CIniView ��ȭ �����Դϴ�.

class CIniView : public CDialogEx
{
	DECLARE_DYNAMIC(CIniView)

public:
	CIniView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CIniView();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INIVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

private:
	gLogger m_logger;
};
