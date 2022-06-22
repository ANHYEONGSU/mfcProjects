
// mfcCImage1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "mfcCImage1.h"
#include "mfcCImage1Dlg.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#define new DEBUG_NEW
#endif


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


// CmfcCImage1Dlg ��ȭ ����



CmfcCImage1Dlg::CmfcCImage1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCCIMAGE1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcCImage1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcCImage1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE, &CmfcCImage1Dlg::OnBnClickedBtnImage)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CmfcCImage1Dlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CmfcCImage1Dlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CmfcCImage1Dlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_ACTION2, &CmfcCImage1Dlg::OnBnClickedBtnAction2)
END_MESSAGE_MAP()


// CmfcCImage1Dlg �޽��� ó����

BOOL CmfcCImage1Dlg::OnInitDialog()
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CmfcCImage1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmfcCImage1Dlg::OnPaint()
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
HCURSOR CmfcCImage1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcCImage1Dlg::OnBnClickedBtnImage()
{
	if (m_image != NULL) {
		m_image.Destroy();
	}

	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);  // nWidth  = ��Ʈ���� �ʺ�
	                                         // nHeight = ��Ʈ���� ����
	                                         // ����̸� nHeight ��Ʈ���� ����� DIB�̰� ������ ���� �Ʒ� �𼭸�
	                                         // �����̸� nHeight ��Ʈ���� ����� DIB�̰� ������ ���� �� �𼭸�
	                                         // nBpp = ��Ʈ���� �ȼ��� ��Ʈ��

	if (nBpp == 8) {
		static RGBQUAD rgb[256];                                  // �� RGB�� �ʱ�ȭ .
		for (int i = 0; i < 256; i++)                             // ��
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i; // ��
		m_image.SetColorTable(0, 256, rgb);                       // ��
	}

	int nPitch = m_image.GetPitch();                         // GetPitch = �̹����� ��ġ�� �˻���. 
															 // pitch = �� ��Ʈ�� ���� ���ۺκа� ���� ��Ʈ�� ���� ������ ��Ÿ���� �� �޸� �ּ� ������ �Ÿ�(����Ʈ)
	unsigned char* fm = (unsigned char*)m_image.GetBits();   // GetBits  = ������ �ȼ��� ���� ��Ʈ ���� ���� �����͸� �˻�. ( m_image�� ù��° �����͸� ������ �� )

	memset(fm, 0xff, nPitch*nHeight);         // memset �Լ��� �޸��� ����(��)�� ���ϴ� ũ�⸸ŭ Ư�� ������ ������ �� �ִ� �Լ�
                                              // memory + setting �޸𸮸� (Ư�� ������) ����
	                                          // ù��° ���� void *ptr  = �ּҸ� ����Ű���ִ� �����Ͱ� ��ġ�ϴ� �ڸ�
	                                          // �ι�° ���� value      = �޸𸮿� �����ϰ��� �ϴ� ���� ������ ��
	                                          // ����° ���� size_t num = ���� ( ����Ʈ �����ν� �޸��� ũ�� ������ ������ ���̸� ���� )
	                                          //                          ex) ���� * sizeof(������Ÿ��)

	

	//for (int j = 0; j < nHeight; j++) {
	//	for (int i = 0; i < nWidth; i++) { 
	//	fm[j*nPitch + i] = (j % 0xff ); // ���ڰ� �������� ���� �� (�޸��� ���� ������ �迭)
	//	}							
	//}
	                                                         
	//fm[12 *nPitch + 16] = 0; // ���Ͱ�.
	//fm[0 * nPitch + 0] = 128;
	//fm[0 * nPitch + 1] = 128;
	//fm[1 * nPitch + 0] = 128;
	
	//fm[12 * nWidth + 16] = 0;
	//fm[0 * nWidth + 1] = 128;
	//fm[3 * nWidth + 3] = 128;

	//for (int j = 0; j < nHeight; j++) {
	//	for (int i = 0; i < nWidth; i++) {
	//		fm[j*nPitch + i] = 0xff; 
	//	}
	//}

	UpdateDisplay();
}

CString g_strFileImage = _T("c:\\image\\save.bmp"); // _T �� CString Ŭ������ �ʱ�ȭ ��Ű�� ��ũ��
                                                    // �۷ι��� ����. �Լ������� �ҷ����� ��밡�� 

void CmfcCImage1Dlg::OnBnClickedBtnSave()
{
	m_image.Save(g_strFileImage); 
}


void CmfcCImage1Dlg::OnBnClickedBtnLoad()
{
	// Load�� �ϱ� ���ؼ��� CImage�� �������� Load�� �ؾ� ������ ����
	if (m_image != NULL) {  // CImage��  NULL ���� �ƴ� ���
		m_image.Destroy();  // CImage���� ��Ʈ���� �и��ϰ� �����Ѵ�.
	}
	m_image.Load(g_strFileImage); 

	UpdateDisplay();
}
 
void CmfcCImage1Dlg::UpdateDisplay()
{
	CClientDC dc(this);     // this = ���� ���̾�α� ����.
							// CClientDC = �������� Ŭ���̾�Ʈ �������� �����Ǵ� DC

	m_image.Draw(dc, 0, 0); // ���� ����̽� ���ؽ�Ʈ���� ���� ����̽� ���ؽ�Ʈ�� ��Ʈ���� �����մϴ�.
							// hDestDC = ��� ����̽� ���ؽ�Ʈ�� ���� �ڵ�
							// xDest   = ��� �簢���� ���� �� �𼭸��� �ִ� x ��ǥ
							// yDest   = ��� �簢���� ���� �� �𼭸��� �ִ� y ��ǥ
}

void CmfcCImage1Dlg::moveRect() // ���̹��� ���� + ��� ( ��ҹ��ڷ� ���� )
{                                             // static ������ ó�� ȣ��ɶ� �� �ѹ��� �ʱ�ȭ�ȴ�.
	static int nSttX = 0;                     // static ������ ������ ���� �޸𸮿� �����ȴ�.
	static int nSttY = 0;                     // static ������ �ش� ��� �ȿ����� ��� ���� ( �������� )

	int nColor = 128;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();   // unsigned = 0 ~ 255 (����� ǥ�� ����, �ּҰ��� ��� ������ �������� ���� )
															 // GetBits  = ������ �ȼ��� ���� ��Ʈ ���� ���� �����͸� �˻�. 
															 //            ( m_image�� ù��° �����͸� ������ �� )

	memset(fm, 0xff, nPitch*nHeight);    // memset �Լ��� �޸��� ����(��)�� ���ϴ� ũ�⸸ŭ Ư�� ������ ������ �� �ִ� �Լ�
                                         // memory + setting �޸𸮸� (Ư�� ������) ����
	
	for (int j = nSttY; j < nSttY+48; j++) {
		for (int i = nSttX; i < nSttX+64; i++) {
			if(validImgPos(i, j))
				fm[j*nPitch + i] = nColor;
		}
	}
	nSttX++;
	nSttY++;
	UpdateDisplay();
}

void CmfcCImage1Dlg::OnBnClickedBtnAction()
{
	for (int i = 0; i < 640; i++) {
		moveRect();
		Sleep(10);  // Sleep(); = �������Լ�
		            // ex) Sleep(1000); = 1000ms�� 1�ʸ� �ǹ��Ѵ�.   
	}
	
}
BOOL CmfcCImage1Dlg::validImgPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight);      // CRect (int l, int t, int r, int b)
											// int l = left  �� ��ġ�� ����
											// int t = top   �� ��ġ�� ����
											// int r = right �� ��ġ�� ����
	                                        // int b = bottom�� ��ġ�� ����

	return rect.PtInRect(CPoint(x, y));     // PtInRect(); = ������ ������ ���� �ִ��� ���θ� Ȯ����
	                                        // ���� ���� ������ 0�� �ƴѰ�� CRect, �׷��������� 0
	                                        // CPoint ���·� �ٲ���� �Ѵ�
	                                        // CPoint = ������ǥ�� ������ (x��ǥ, y��ǥ)
	                                        
}

void CmfcCImage1Dlg::moveCircle()
{
	static int nSttX = 0;                     // static ������ ������ ���� �޸𸮿� �����ȴ�.
	static int nSttY = 0;                     // static ������ �ش� ��� �ȿ����� ��� ���� ( �������� )

	int nColor = 128;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = 10;                         // ���� ������

	unsigned char* fm = (unsigned char*)m_image.GetBits();   // GetBits  = ������ �ȼ��� ���� ��Ʈ ���� ���� �����͸� �˻�. 
															 //            ( m_image�� ù��° �����͸� ������ �� )

	/*memset(fm, 0xff, nPitch*nHeight);*/                    // Image Ŭ���� 

	drawCircle(fm, nSttX, nSttY, nRadius, 0xff);             
	drawCircle(fm, ++nSttX, ++nSttY, nRadius, nColor);      // ���� ������( ++x ) = �ǿ����� ���� "1"������Ų �Ŀ� �ش� ������ ����.
															//            ( --x ) =               "1"����

	//drawCircle(fm, nSttX++, nSttY++, nRadius, nColor);    // ���� ������( x++ ) = �ش� ������ ���� �����ϰ� ����, �ǿ������� ���� "1"������Ŵ
	                                                        //            ( x-- ) =                                                 "1"����

	UpdateDisplay();
}

void CmfcCImage1Dlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nColor) // ���׸���
{                            //        �ּ� ����Ʈ,                 ������
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (validImgPos(i, j))
				if(isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j*nPitch + i] = nColor;
		}
	}
}

void CmfcCImage1Dlg::OnBnClickedBtnAction2()
{
	for (int i = 0; i < 640; i++) {
		moveCircle();
		Sleep(10);  // Sleep(); = �������Լ�
					// ex) Sleep(1000); = 1000ms�� 1�ʸ� �ǹ��Ѵ�.   
	}
}

bool CmfcCImage1Dlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{

	//���������� ū�� ������ ����

	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius*nRadius) {
		bRet = true;
	}

	return bRet;
} 