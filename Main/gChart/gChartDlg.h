
// gChartDlg.h : 헤더 파일
//
#include "ChartViewer.h"
#include <afxmt.h>

#pragma once

#define COLOR_DLG_BG		RGB(0x58, 0x58, 0x58)
#define CHART_NUM			4
#define CHART_WIDTH			540
#define CHART_HEIGHT		600
#define CHART_AREA_WIDTH	450
#define CHART_AREA_HEIGHT	370

// CgChartDlg 대화 상자
class CgChartDlg : public CDialogEx
{
// 생성입니다.
public:
	CgChartDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GCHART_DIALOG };
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

private:
	void drawBarChart(CChartViewer *viewer, const char **imageMap);
	void drawLineChart(CChartViewer *viewer, const char **imageMap);
	void drawTrendChart(CChartViewer *viewer, const char **imageMap);
	void drawScatterChart(CChartViewer *viewer, const char **imageMap);

	void OnMouseMovePlotArea();
	void trackLineLegend(XYChart *c, int mouseX);
	void trackBarLegend(XYChart *c, int mouseX, int mouseY);
	void trackScatterLegend(XYChart *c, int mouseX, int mouseY);
	void trackTrendLegend(XYChart *c, int mouseX, int mouseY);


	bool m_ActiveChart[CHART_NUM] = { false }; // 0: line, 1: Bar, 2: Scatter, 3: Trend

	void checkChart(int idx);
	int check = 0;

public:
	enum { IDD = IDD_GLCHARTEXAM_DIALOG };

	CChartViewer m_ChartViewer;

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnStnClickedChartviewer();
	afx_msg void OnBnClickedBtnLine();
	afx_msg void OnBnClickedBtnBar();
	afx_msg void OnBnClickedBtnScatter();
	afx_msg void OnBnClickedBtnTrend();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
};
