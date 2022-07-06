
// FirstProjectDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "FirstProject.h"
#include "FirstProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


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
END_MESSAGE_MAP()


// CFirstProjectDlg 대화 상자



CFirstProjectDlg::CFirstProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FIRSTPROJECT_DIALOG, pParent), m_logger("dlg.cpp", "c:/glim/log/log.txt")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFirstProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_imgDisplay);
	DDX_Control(pDX, IDC_BTN_ROI0, m_BtnRoi0);
	DDX_Control(pDX, IDC_BTN_ROI1, m_BtnRoi1);
}

BEGIN_MESSAGE_MAP(CFirstProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ROI0, &CFirstProjectDlg::OnBnClickedBtnRoi0)
	ON_BN_CLICKED(IDC_BTN_ROI1, &CFirstProjectDlg::OnBnClickedBtnRoi1)
	ON_BN_CLICKED(IDC_BTN_IMAGE_LOAD, &CFirstProjectDlg::OnBnClickedBtnImageLoad)
	ON_BN_CLICKED(IDC_BTN_IMAGE_SAVE, &CFirstProjectDlg::OnBnClickedBtnImageSave)
	ON_BN_CLICKED(IDC_BTN_INI_VIEW, &CFirstProjectDlg::OnBnClickedBtnIniView)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_EXIT, &CFirstProjectDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CFirstProjectDlg 메시지 처리기

BOOL CFirstProjectDlg::OnInitDialog()
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
	//CWnd* pWnd0 = (CWnd*)GetDlgItem(IDC_BTN_ROI0);
	//pWnd0->EnableWindow(FALSE);

	//CWnd* pWnd1 = (CWnd*)GetDlgItem(IDC_BTN_ROI1);
	//pWnd1->EnableWindow(FALSE);



	m_logger.info("쓰시면 됩니다.");

	m_pIniView = new CIniView;
	m_pIniView->Create(IDD_INIVIEW, this);




	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFirstProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFirstProjectDlg::OnPaint()
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
HCURSOR CFirstProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include<iostream>
using namespace std;

void CFirstProjectDlg::OnBnClickedBtnRoi0()
{
	
	m_BtnRoi0.SetWindowText(_T("설정완료"));
	CWnd* pWnd = (CWnd*)GetDlgItem(IDC_BTN_ROI1);
	pWnd->EnableWindow(FALSE);

	m_imgDisplay.gSetUseRoi();
	m_rect1 = m_imgDisplay.gGetRoi();
	DrawItem item;
	item.rect = m_rect1;
	m_imgDisplay.gAddObj(item);
	
	//m_imgDisplay.gSetUseRoi(TRUE, &m_rect1);
	
}


void CFirstProjectDlg::OnBnClickedBtnRoi1()
{
	int nIndex = 0;

	m_BtnRoi1.SetWindowText(_T("설정완료"));
	CWnd* pWnd = (CWnd*)GetDlgItem(IDC_BTN_ROI0);
	pWnd->EnableWindow(FALSE);

	m_imgDisplay.gSetUseRoi();

	m_rect2 = m_imgDisplay.gGetRoi();
	DrawItem item;
	item.rect = m_rect2;
	
	m_imgDisplay.gAddObj(item);

	//m_imgDisplay.gSetObj(nIndex, item);
	//m_imgDisplay.gDelObj(nIndex);
	

}


void CFirstProjectDlg::OnBnClickedBtnImageLoad()
{
	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK) {
		m_imgDisplay.gLoad(dlg.GetPathName());
	}
	CWnd* pWnd0 = (CWnd*)GetDlgItem(IDC_BTN_ROI0);
	pWnd0->EnableWindow(TRUE);

	CWnd* pWnd1 = (CWnd*)GetDlgItem(IDC_BTN_ROI1);
	pWnd1->EnableWindow(TRUE);

	CWnd* pWnd2 = (CWnd*)GetDlgItem(IDC_BTN_IMAGE_SAVE);
	pWnd2->EnableWindow(TRUE);
}


void CFirstProjectDlg::OnBnClickedBtnImageSave()
{
	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");

	CFileDialog dlg(FALSE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK) {
		m_imgDisplay.gSave(string(CT2CA(dlg.GetPathName())));
	}

}


void CFirstProjectDlg::OnBnClickedBtnIniView()
{
	int pointX = 600;
	int pointY = 400;
	int Width = 600;
	int Height = 400;

	m_pIniView->ShowWindow(SW_SHOW);
	m_pIniView->MoveWindow(pointX, pointY, Width, Height);
}


void CFirstProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete m_pIniView;
}


void CFirstProjectDlg::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CFirstProjectDlg::OnBnClickedBtnExit()
{
	SendMessage(WM_CLOSE, 0, 0);
}
