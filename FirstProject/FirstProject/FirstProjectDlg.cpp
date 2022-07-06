
// FirstProjectDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "FirstProject.h"
#include "FirstProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CFirstProjectDlg ��ȭ ����



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


// CFirstProjectDlg �޽��� ó����

BOOL CFirstProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//CWnd* pWnd0 = (CWnd*)GetDlgItem(IDC_BTN_ROI0);
	//pWnd0->EnableWindow(FALSE);

	//CWnd* pWnd1 = (CWnd*)GetDlgItem(IDC_BTN_ROI1);
	//pWnd1->EnableWindow(FALSE);



	m_logger.info("���ø� �˴ϴ�.");

	m_pIniView = new CIniView;
	m_pIniView->Create(IDD_INIVIEW, this);




	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CFirstProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CFirstProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include<iostream>
using namespace std;

void CFirstProjectDlg::OnBnClickedBtnRoi0()
{
	
	m_BtnRoi0.SetWindowText(_T("�����Ϸ�"));
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

	m_BtnRoi1.SetWindowText(_T("�����Ϸ�"));
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
	static TCHAR BASED_CODE szFilter[] = _T("�̹��� ����(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |�������(*.*)|*.*||");

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
	static TCHAR BASED_CODE szFilter[] = _T("�̹��� ����(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |�������(*.*)|*.*||");

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CFirstProjectDlg::OnBnClickedBtnExit()
{
	SendMessage(WM_CLOSE, 0, 0);
}
