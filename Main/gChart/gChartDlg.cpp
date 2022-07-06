
// gChartDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "gChart.h"
#include "gChartDlg.h"
#include "afxdialogex.h"
#include "HotSpotDlg.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_MOUSEHWHEEL()
END_MESSAGE_MAP()


// CgChartDlg 대화 상자



CgChartDlg::CgChartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GCHART_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CgChartDlg::~CgChartDlg()
{
	delete m_ChartViewer.getChart();
}

void CgChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
}

BEGIN_MESSAGE_MAP(CgChartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_STN_CLICKED(IDC_ChartViewer, &CgChartDlg::OnStnClickedChartviewer)
	ON_BN_CLICKED(IDC_BTN_LINE, &CgChartDlg::OnBnClickedBtnLine)
	ON_BN_CLICKED(IDC_BTN_BAR, &CgChartDlg::OnBnClickedBtnBar)
	ON_BN_CLICKED(IDC_BTN_SCATTER, &CgChartDlg::OnBnClickedBtnScatter)
	ON_BN_CLICKED(IDC_BTN_TREND, &CgChartDlg::OnBnClickedBtnTrend)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CgChartDlg::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// CgChartDlg 메시지 처리기

BOOL CgChartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgChartDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgChartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgChartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CgChartDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}





void CgChartDlg::OnStnClickedChartviewer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CgChartDlg::checkChart(int idx)
{

}

void CgChartDlg::drawBarChart(CChartViewer *viewer, const char **imageMap)
{

}

void CgChartDlg::drawLineChart(CChartViewer *viewer, const char **imageMap)
{

}

void CgChartDlg::drawTrendChart(CChartViewer *viewer, const char **imageMap)
{

}

void CgChartDlg::drawScatterChart(CChartViewer *viewer, const char **imageMap)
{

}

void CgChartDlg::OnMouseMovePlotArea()
{

}

void CgChartDlg::trackLineLegend(XYChart *c, int mouseX)
{

}

void CgChartDlg::trackBarLegend(XYChart *c, int mouseX, int mouseY)
{

}

void CgChartDlg::trackScatterLegend(XYChart *c, int mouseX, int mouseY)
{

}

void CgChartDlg::trackTrendLegend(XYChart *c, int mouseX, int mouseY)
{

}


void CgChartDlg::OnBnClickedBtnLine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CgChartDlg::OnBnClickedBtnBar()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CgChartDlg::OnBnClickedBtnScatter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CgChartDlg::OnBnClickedBtnTrend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CgChartDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
