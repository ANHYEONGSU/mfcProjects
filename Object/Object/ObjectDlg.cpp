
// ObjectDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Object.h"
#include "ObjectDlg.h"
#include "afxdialogex.h"

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
END_MESSAGE_MAP()


// CObjectDlg 대화 상자



CObjectDlg::CObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OBJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_imgDisplay);
}

BEGIN_MESSAGE_MAP(CObjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE_LOAD, &CObjectDlg::OnBnClickedBtnImageLoad)
	ON_BN_CLICKED(IDC_BTN_CREATE_OBJ, &CObjectDlg::OnBnClickedBtnCreateObj)
	ON_BN_CLICKED(IDC_BTN_DELETE_OBJ, &CObjectDlg::OnBnClickedBtnDeleteObj)
END_MESSAGE_MAP()


// CObjectDlg 메시지 처리기

BOOL CObjectDlg::OnInitDialog()
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

	m_imgDisplay.gCreate(1920, 1080, 8);
	m_imgDisplay.gSetUseRoi();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CObjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CObjectDlg::OnPaint()
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
HCURSOR CObjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CObjectDlg::OnBnClickedBtnImageLoad()
{
	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK) {
		m_imgDisplay.gLoad(dlg.GetPathName());
	}
}

#include <random>
void CObjectDlg::OnBnClickedBtnCreateObj()
{
	static int nIndex = 0;
	std::random_device rd;
	std::mt19937 rand(rd());
	int nWidth = m_imgDisplay.gGetWidth();
	int nHeight = m_imgDisplay.gGetHeight();

	DrawItem item;
	item.type = static_cast<objType>(rand() % 3);// objType::RECT_OBJ;
	int l = rand() % (nWidth / 2);
	int t = rand() % (nHeight / 2);
	int r = l + rand() % (nWidth / 2);
	int b = t + rand() % (nHeight / 2);
	item.rect.SetRect(l, t, r, b);
	item.text = "Roi : " + to_string(nIndex++);
	item.colorObj = RGB(rand() % 0xff, rand() % 0xff, rand() % 0xff);
	m_imgDisplay.gAddObj(item);
}


void CObjectDlg::OnBnClickedBtnDeleteObj()
{
	m_imgDisplay.gDelObj(0);
}
