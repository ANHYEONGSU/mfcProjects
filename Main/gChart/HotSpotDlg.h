#pragma once
#include "afxcmn.h"


// HotSpotDlg 대화 상자입니다.

class HotSpotDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HotSpotDlg)

public:
	HotSpotDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~HotSpotDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOTSPOTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ParamList;
};
