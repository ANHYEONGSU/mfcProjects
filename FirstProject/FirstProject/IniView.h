#pragma once

#include "../include/gLogger.h"
#pragma comment(lib, "../lib/gLogger.lib")

// CIniView 대화 상자입니다.

class CIniView : public CDialogEx
{
	DECLARE_DYNAMIC(CIniView)

public:
	CIniView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CIniView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INIVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	gLogger m_logger;
};
