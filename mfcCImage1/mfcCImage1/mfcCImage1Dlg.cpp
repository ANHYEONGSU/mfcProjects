
// mfcCImage1Dlg.cpp : 구현 파일
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


// CmfcCImage1Dlg 대화 상자



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


// CmfcCImage1Dlg 메시지 처리기

BOOL CmfcCImage1Dlg::OnInitDialog()
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmfcCImage1Dlg::OnPaint()
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

	m_image.Create(nWidth, -nHeight, nBpp);  // nWidth  = 비트맵의 너비
	                                         // nHeight = 비트맵의 높이
	                                         // 양수이면 nHeight 비트맵은 상향식 DIB이고 원점은 왼쪽 아래 모서리
	                                         // 음수이면 nHeight 비트맵은 하향식 DIB이고 원점은 왼쪽 위 모서리
	                                         // nBpp = 비트맵의 픽셀당 비트수

	if (nBpp == 8) {
		static RGBQUAD rgb[256];                                  // ㄱ RGB값 초기화 .
		for (int i = 0; i < 256; i++)                             // ㅣ
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i; // ㅣ
		m_image.SetColorTable(0, 256, rgb);                       // 」
	}

	int nPitch = m_image.GetPitch();                         // GetPitch = 이미지의 피치를 검색함. 
															 // pitch = 한 비트맵 줄의 시작부분과 다음 비트맵 줄의 시작을 나타내는 두 메모리 주소 사이의 거리(바이트)
	unsigned char* fm = (unsigned char*)m_image.GetBits();   // GetBits  = 지정된 픽셀의 실제 비트 값에 대한 포인터를 검색. ( m_image의 첫번째 포인터를 가지고 옴 )

	memset(fm, 0xff, nPitch*nHeight);         // memset 함수는 메모리의 내용(값)을 원하는 크기만큼 특정 값으로 세팅할 수 있는 함수
                                              // memory + setting 메모리를 (특정 값으로) 세팅
	                                          // 첫번째 인자 void *ptr  = 주소를 가리키고있는 포인터가 위치하는 자리
	                                          // 두번째 인자 value      = 메모리에 셋팅하고자 하는 값을 넣으면 됌
	                                          // 세번째 인자 size_t num = 길이 ( 바이트 단위로써 메모리의 크기 한조각 단위의 길이를 말함 )
	                                          //                          ex) 길이 * sizeof(데이터타입)

	

	//for (int j = 0; j < nHeight; j++) {
	//	for (int i = 0; i < nWidth; i++) { 
	//	fm[j*nPitch + i] = (j % 0xff ); // 숫자가 높을수록 밝은 값 (메모리의 값은 숫자의 배열)
	//	}							
	//}
	                                                         
	//fm[12 *nPitch + 16] = 0; // 센터값.
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

CString g_strFileImage = _T("c:\\image\\save.bmp"); // _T 는 CString 클래스를 초기화 시키는 매크로
                                                    // 글로벌로 선언. 함수내에서 불러내서 사용가능 

void CmfcCImage1Dlg::OnBnClickedBtnSave()
{
	m_image.Save(g_strFileImage); 
}


void CmfcCImage1Dlg::OnBnClickedBtnLoad()
{
	// Load를 하기 위해서는 CImage를 정리한후 Load를 해야 오류가 없다
	if (m_image != NULL) {  // CImage가  NULL 값이 아닐 경우
		m_image.Destroy();  // CImage에서 비트맵을 분리하고 제거한다.
	}
	m_image.Load(g_strFileImage); 

	UpdateDisplay();
}
 
void CmfcCImage1Dlg::UpdateDisplay()
{
	CClientDC dc(this);     // this = 현재 다이얼로그 말함.
							// CClientDC = 윈도우의 클라이언트 영역으로 한정되는 DC

	m_image.Draw(dc, 0, 0); // 원본 디바이스 컨텍스트에서 현재 디바이스 컨텍스트로 비트맵을 복사합니다.
							// hDestDC = 대상 디바이스 컨텍스트에 대한 핸들
							// xDest   = 대상 사각형의 왼쪽 위 모서리에 있는 x 좌표
							// yDest   = 대상 사각형의 왼쪽 위 모서리에 있는 y 좌표
}

void CmfcCImage1Dlg::moveRect() // 네이밍은 동사 + 명사 ( 대소문자로 구분 )
{                                             // static 변수는 처음 호출될때 딱 한번만 초기화된다.
	static int nSttX = 0;                     // static 변수의 데이터 값은 메모리에 유지된다.
	static int nSttY = 0;                     // static 변수는 해당 블록 안에서만 사용 가능 ( 지역변수 )

	int nColor = 128;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();   // unsigned = 0 ~ 255 (양수만 표시 가능, 주소값의 경우 음수가 존재하지 않음 )
															 // GetBits  = 지정된 픽셀의 실제 비트 값에 대한 포인터를 검색. 
															 //            ( m_image의 첫번째 포인터를 가지고 옴 )

	memset(fm, 0xff, nPitch*nHeight);    // memset 함수는 메모리의 내용(값)을 원하는 크기만큼 특정 값으로 세팅할 수 있는 함수
                                         // memory + setting 메모리를 (특정 값으로) 세팅
	
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
		Sleep(10);  // Sleep(); = 딜레이함수
		            // ex) Sleep(1000); = 1000ms로 1초를 의미한다.   
	}
	
}
BOOL CmfcCImage1Dlg::validImgPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight);      // CRect (int l, int t, int r, int b)
											// int l = left  의 위치를 지정
											// int t = top   의 위치를 지정
											// int r = right 의 위치를 지정
	                                        // int b = bottom의 위치를 지정

	return rect.PtInRect(CPoint(x, y));     // PtInRect(); = 지정된 지점이 내에 있는지 여부를 확인함
	                                        // 점이 내에 있으면 0이 아닌경우 CRect, 그렇지않으면 0
	                                        // CPoint 형태로 바꿔줘야 한다
	                                        // CPoint = 점의좌표를 저장함 (x좌표, y좌표)
	                                        
}

void CmfcCImage1Dlg::moveCircle()
{
	static int nSttX = 0;                     // static 변수의 데이터 값은 메모리에 유지된다.
	static int nSttY = 0;                     // static 변수는 해당 블록 안에서만 사용 가능 ( 지역변수 )

	int nColor = 128;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = 10;                         // 원의 반지름

	unsigned char* fm = (unsigned char*)m_image.GetBits();   // GetBits  = 지정된 픽셀의 실제 비트 값에 대한 포인터를 검색. 
															 //            ( m_image의 첫번째 포인터를 가지고 옴 )

	/*memset(fm, 0xff, nPitch*nHeight);*/                    // Image 클리어 

	drawCircle(fm, nSttX, nSttY, nRadius, 0xff);             
	drawCircle(fm, ++nSttX, ++nSttY, nRadius, nColor);      // 전위 연산자( ++x ) = 피연산자 값을 "1"증가시킨 후에 해당 연산을 진행.
															//            ( --x ) =               "1"감소

	//drawCircle(fm, nSttX++, nSttY++, nRadius, nColor);    // 후위 연산자( x++ ) = 해당 연산을 먼저 수행하고 나서, 피연산자의 값을 "1"증가시킴
	                                                        //            ( x-- ) =                                                 "1"감소

	UpdateDisplay();
}

void CmfcCImage1Dlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nColor) // 원그리기
{                            //        주소 포인트,                 반지름
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
		Sleep(10);  // Sleep(); = 딜레이함수
					// ex) Sleep(1000); = 1000ms로 1초를 의미한다.   
	}
}

bool CmfcCImage1Dlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{

	//반지름보다 큰가 작은가 차이

	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius*nRadius) {
		bRet = true;
	}

	return bRet;
} 