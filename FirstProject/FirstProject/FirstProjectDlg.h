
// FirstProjectDlg.h : 헤더 파일
//

#pragma once
#include "../include/gImage.h"
#pragma comment(lib, "../lib/gImage.lib")

#include "../include/gLogger.h"
#pragma comment(lib, "../lib/gLogger.lib")
#include "IniView.h"
#include "afxwin.h"


// CFirstProjectDlg 대화 상자
class CFirstProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CFirstProjectDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	CIniView *m_pIniView;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIRSTPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
