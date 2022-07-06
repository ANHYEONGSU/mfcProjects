
// MainDlg.h : 헤더 파일
//

#pragma once
#include "gImage.h"

#include <spdlog/spdlog.h>		
#include <spdlog/stopwatch.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/async.h>


#define LOG_EXAM	"logExam"

//	spdlog step 2 : 선언
extern std::shared_ptr<spdlog::logger> log_Exam; // extern = 


// CMainDlg 대화 상자
class CMainDlg : public CDialogEx
{
// 생성입니다.
public:
	CMainDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
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
	vector <double> m_data;
public:
	gImage m_imgDisplay;
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnProcess();
	afx_msg void OnBnClickedBtnCreateRoi();
	afx_msg void OnBnClickedBtnCreateObj();
	afx_msg void OnBnClickedBtnDlelteObj();
	afx_msg void OnBnClickedBtnFineEdgeV();
	afx_msg void OnBnClickedBtnFindEdgeH();
	afx_msg void OnBnClickedBtnDelLastData();
	afx_msg void OnBnClickedBtnSaveCsv();
	afx_msg void OnBnClickedBtnSave();

private:
	void imgBinary(unsigned char*fm, CRect rect, int nPitch, int nTh);
	void imgInverter(unsigned char*fm, CRect rect, int nPitch);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
