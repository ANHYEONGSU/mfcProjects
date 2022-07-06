
// FirstProjectDlg.h : ��� ����
//

#pragma once
#include "../include/gImage.h"
#pragma comment(lib, "../lib/gImage.lib")

#include "../include/gLogger.h"
#pragma comment(lib, "../lib/gLogger.lib")
#include "IniView.h"
#include "afxwin.h"


// CFirstProjectDlg ��ȭ ����
class CFirstProjectDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CFirstProjectDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CIniView *m_pIniView;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIRSTPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	gImage m_imgDisplay;
	afx_msg void OnBnClickedBtnRoi0();
	afx_msg void OnBnClickedBtnRoi1();
	afx_msg void OnBnClickedBtnImageLoad();
	afx_msg void OnBnClickedBtnImageSave();
	afx_msg void OnBnClickedBtnIniView();
	afx_msg void OnDestroy();

private:
	CRect m_rect1;
	CRect m_rect2;

	gLogger m_logger;

public:
	CButton m_BtnRoi0;
	CButton m_BtnRoi1;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedBtnExit();
};
