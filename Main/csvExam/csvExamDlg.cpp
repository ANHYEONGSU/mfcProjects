
// csvExamDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "csvExam.h"
#include "csvExamDlg.h"
#include "afxdialogex.h"

#include "../common/CSVWriter.h"			
#include "../common/csv.h"

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
END_MESSAGE_MAP()


// CcsvExamDlg 대화 상자



CcsvExamDlg::CcsvExamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CSVEXAM_DIALOG, pParent)
	, m_sItems(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcsvExamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ITEMS, m_sItems);
}

BEGIN_MESSAGE_MAP(CcsvExamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_READ_CSV, &CcsvExamDlg::OnBnClickedBtnReadCsv)
	ON_BN_CLICKED(IDC_BTN_WRITE_CSV, &CcsvExamDlg::OnBnClickedBtnWriteCsv)
END_MESSAGE_MAP()


// CcsvExamDlg 메시지 처리기

BOOL CcsvExamDlg::OnInitDialog()
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

void CcsvExamDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcsvExamDlg::OnPaint()
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
HCURSOR CcsvExamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcsvExamDlg::OnBnClickedBtnReadCsv()
{
	string fileName = "c:/glim/input.csv";
	io::CSVReader<3> in(fileName);
	in.read_header(io::ignore_extra_column, "string", "int", "double");
	DATA data;

	// read data
	m_Data.clear();
	while (in.read_row(data.strData, data.nData, data.dData))
		m_Data.push_back(data);

	// show at listbox
	m_sItems.Empty();
	for (int i = 0; i < m_Data.size(); i++) {
		string sLine;
		sLine = m_Data[i].strData + '\t' + to_string(m_Data[i].nData) + '\t' + to_string(m_Data[i].dData) + "\r\n";
		m_sItems += sLine.c_str();
	}
	UpdateData(FALSE);
}


void CcsvExamDlg::OnBnClickedBtnWriteCsv()
{
	string fileName = "c:/glim/output.csv";
	CSVWriter csv;

	// write to csv file
	if (!csv.isFile(fileName))
		//csv << "string" << "int" << "double" << "\n";
		csv.newRow() << "string" << "int" << "double";
	for (int i = 0; i < m_Data.size(); i++)
		csv.newRow() << m_Data[i].strData << m_Data[i].nData << m_Data[i].dData;
	csv.writeToFile(fileName, true);
	MessageBox(_T("쓰기 완료"));
}
