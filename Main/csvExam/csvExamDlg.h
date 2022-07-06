
// csvExamDlg.h : 헤더 파일
//

#pragma once

using namespace std;

#include <string>
#include <vector>

typedef struct tagData {
	string strData;
	int nData;
	double dData;
} DATA;


// CcsvExamDlg 대화 상자
class CcsvExamDlg : public CDialogEx
{
// 생성입니다.
public:
	CcsvExamDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSVEXAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다

// 구현입니다.
protected:
	HICON m_hIcon;
	std::vector<DATA> m_Data;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnReadCsv();
	afx_msg void OnBnClickedBtnWriteCsv();

	CString m_sItems;
};
