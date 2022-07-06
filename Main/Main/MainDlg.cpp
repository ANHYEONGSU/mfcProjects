
// MainDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#include <chrono>

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


// CMainDlg 대화 상자


CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_imgDisplay);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD, &CMainDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CMainDlg::OnBnClickedBtnProcess)
	ON_BN_CLICKED(IDC_BTN_CREATE_ROI, &CMainDlg::OnBnClickedBtnCreateRoi)
	ON_BN_CLICKED(IDC_BTN_CREATE_OBJ, &CMainDlg::OnBnClickedBtnCreateObj)
	ON_BN_CLICKED(IDC_BTN_DLELTE_OBJ, &CMainDlg::OnBnClickedBtnDlelteObj)
	ON_BN_CLICKED(IDC_BTN_FINE_EDGE_V, &CMainDlg::OnBnClickedBtnFineEdgeV)
	ON_BN_CLICKED(IDC_BTN_FIND_EDGE_H, &CMainDlg::OnBnClickedBtnFindEdgeH)
	ON_BN_CLICKED(IDC_BTN_DEL_LAST_DATA, &CMainDlg::OnBnClickedBtnDelLastData)
	ON_BN_CLICKED(IDC_BTN_SAVE_CSV, &CMainDlg::OnBnClickedBtnSaveCsv)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMainDlg::OnBnClickedBtnSave)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMainDlg 메시지 처리기

BOOL CMainDlg::OnInitDialog()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

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

	SetTimer(0, 100, NULL);	//mouse info display

	log_Exam->set_level(spdlog::level::trace);
	log_Exam->flush_on(spdlog::level::trace);

	//for(int i = 0; i <500000; i++)
	//	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMainDlg::OnPaint()
{
	//log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

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
HCURSOR CMainDlg::OnQueryDragIcon()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	return static_cast<HCURSOR>(m_hIcon);

	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}



void CMainDlg::OnBnClickedBtnLoad()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK) {
		m_imgDisplay.gLoad(dlg.GetPathName());
		log_Exam->info("이미지 로드 완료 경로 {}", string(CT2CA(dlg.GetPathName())));
	} else {
		log_Exam->warn("이미지 로드 취소됨, 사용자 취소");
	}
	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}

void CMainDlg::OnBnClickedBtnSave()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);
	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");

	CFileDialog dlg(FALSE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK) {
		m_imgDisplay.gSave(string(CT2CA(dlg.GetPathName())));

		log_Exam->info("사용자 저장완료 됨 경로 {}", string(CT2CA(dlg.GetPathName())));

	} 
	else {
		log_Exam->warn("이미지 저장 취소됨, 사용자 취소");
	}

	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);

	/*log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	string file = "c:/glim/image/test.bmp";
	m_imgDisplay.gSave(file);*/
}


void CMainDlg::OnBnClickedBtnProcess()
{

//#if // 디버그 모드일때
//	log_Exam->debug("start {}:{}", __FUNCTION__, __LINE__);
//#endif 

	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	int nWidth = m_imgDisplay.gGetWidth();
	int nHeight = m_imgDisplay.gGetHeight();
	int nPitch = m_imgDisplay.gGetPitch();
	unsigned char* fm = m_imgDisplay.gGetImgPtr();
	CRect rect = m_imgDisplay.gGetRoi();
	int nTh = 100;

	if (rect.bottom > nHeight) {
		log_Exam->critical("Bottem의 범위가 벗어나게 설정되었습니다.");
	} 
	else if (rect.top < 0) {
		log_Exam->critical("Top의 범위가 벗어나게 설정되었습니다.");
	}
	else {

		//imgBinary(fm, rect, nPitch, nTh);
		imgInverter(fm, rect, nPitch);

		DrawItem item;
		item.rect = rect;

		m_imgDisplay.UpdateDisplay();
	}

	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}


void CMainDlg::OnBnClickedBtnCreateRoi()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	m_imgDisplay.gSetUseRoi();

	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}

#include <random> // mt19937을 사용하기 위해

void CMainDlg::OnBnClickedBtnCreateObj()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	static int nIndex = 0;
	std::random_device rd;
	std::mt19937 rand(rd());    // Mersenne Twister 
								// mt19937 = 엄청나게큰 반복주기와 고른 분포를 가진 난수생성기.

	int nWidth = m_imgDisplay.gGetWidth(); 
	int nHeight = m_imgDisplay.gGetHeigth();
	DrawItem item;
	item.type = static_cast<objType>(rand() % 3);// objType::RECT_OBJ;
	int l = rand() % (nWidth / 2);
	int t = rand() % (nHeight / 2);
	int r = l + rand() % (nWidth / 2);
	int b = t + rand() % (nHeight / 2);
	item.rect.SetRect(l, t, r, b);
	item.text = "Roi : " + to_string(nIndex++);
	item.colorObj = RGB(rand() % 0xff, rand() % 0xff, rand() % 0xff);

	if (m_imgDisplay.gGetObjCount() >= MAX_OBJ) {
		CString str;
		str.Format(L"MAX OBJECT = %d", MAX_OBJ);
		AfxMessageBox(str);
		log_Exam->warn("생성가능한 오브젝트의 갯수가 초과 되었습니다.");
	}
	else
	{
		m_imgDisplay.gAddObj(item);
	}
	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}


void CMainDlg::OnBnClickedBtnDlelteObj()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	m_imgDisplay.gDelObj(0);

	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);

}

#include "ginspro.h"
void CMainDlg::OnBnClickedBtnFineEdgeV()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	int nWidth = m_imgDisplay.gGetWidth();
	int nHeight = m_imgDisplay.gGetHeigth();
	int nPitch = m_imgDisplay.gGetPitch();
	unsigned char* fm = m_imgDisplay.gGetImgPtr();
	gInsPro ins(nWidth, nHeight, nPitch, fm);

	CRect rect = m_imgDisplay.gGetRoi();
	double dPos = ins.getEdgePosH(rect);

	DrawItem item;
	item.type = objType::LINE_OBJ;
	item.rect.SetRect(rect.left, int(dPos + 0.5), rect.right, int(dPos + 0.5));
	m_imgDisplay.gAddObj(item);

	m_data.push_back(rect.CenterPoint().x);
	m_data.push_back(dPos);

	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);

}


void CMainDlg::OnBnClickedBtnFindEdgeH()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	int nWidth = m_imgDisplay.gGetWidth();
	int nHeight = m_imgDisplay.gGetHeigth();
	int nPitch = m_imgDisplay.gGetPitch();
	unsigned char* fm = m_imgDisplay.gGetImgPtr();
	gInsPro ins(nWidth, nHeight, nPitch, fm);

	CRect rect = m_imgDisplay.gGetRoi();
	double dPos = ins.getEdgePosV(rect);

	DrawItem item;
	item.type = objType::LINE_OBJ;
	item.rect.SetRect(int(dPos + 0.5), rect.top, int(dPos + 0.5), rect.bottom);
	m_imgDisplay.gAddObj(item);
	
	m_data.push_back(dPos);
	m_data.push_back(rect.CenterPoint().y);

	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}


void CMainDlg::OnBnClickedBtnDelLastData()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	if (m_data.size()) {
		m_data.pop_back();	//x, y 두번 제거
		m_data.pop_back();	//
		m_imgDisplay.gDelObj(m_imgDisplay.gGetObjCount() - 1);
		m_imgDisplay.UpdateDisplay();
	}
	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}
#define FILE_CSV	"c:/glim/measure.csv"
#include "CSVWriter.h"

void CMainDlg::OnBnClickedBtnSaveCsv()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	bool bRet;
	string fileName = FILE_CSV;
	CSVWriter csv;
	if (csv.isWriteFile(fileName)) {
		for (auto i : m_data)
			csv << i;
		cout << csv.writeToFile(fileName, true);
		m_data.clear();
		m_imgDisplay.gDelObjAll();
	}
	else {
		AfxMessageBox(_T("write csv fail!"));
	}
	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}

void CMainDlg::imgBinary(unsigned char*fm, CRect rect, int nPitch, int nTh)
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);


	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j*nPitch + i] > nTh)
				fm[j*nPitch + i] = 0xff;
			else
				fm[j*nPitch + i] = 0x00;
		}
	}
	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}

void CMainDlg::imgInverter(unsigned char*fm, CRect rect, int nPitch)
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			fm[j*nPitch + i] = 0xff - fm[j*nPitch + i];
		}
	}
	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}

 
void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	CPoint ptMouse, ptImg;
	int nGray = m_imgDisplay.gGetPixelInfo(ptMouse, ptImg);
	CString str;
	str.Format(_T("[pixel pos] (gray level)\n\n[%04d, %04d] (%03d)"), ptImg.x, ptImg.y, nGray);
	SetDlgItemText(IDC_STATIC_INFO, str);

	CDialogEx::OnTimer(nIDEvent);
}



