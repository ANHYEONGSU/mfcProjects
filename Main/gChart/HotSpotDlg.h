#pragma once
#include "afxcmn.h"


// HotSpotDlg ��ȭ �����Դϴ�.

class HotSpotDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HotSpotDlg)

public:
	HotSpotDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~HotSpotDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOTSPOTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ParamList;
};
