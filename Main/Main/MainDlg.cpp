
// MainDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#include <chrono>

#ifdef _DEBUG
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


// CMainDlg ��ȭ ����


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


// CMainDlg �޽��� ó����

BOOL CMainDlg::OnInitDialog()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

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
	m_imgDisplay.gCreate(1920, 1080, 8);

	SetTimer(0, 100, NULL);	//mouse info display

	log_Exam->set_level(spdlog::level::trace);
	log_Exam->flush_on(spdlog::level::trace);

	//for(int i = 0; i <500000; i++)
	//	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMainDlg::OnPaint()
{
	//log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

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
HCURSOR CMainDlg::OnQueryDragIcon()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	return static_cast<HCURSOR>(m_hIcon);

	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}



void CMainDlg::OnBnClickedBtnLoad()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	static TCHAR BASED_CODE szFilter[] = _T("�̹��� ����(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |�������(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK) {
		m_imgDisplay.gLoad(dlg.GetPathName());
		log_Exam->info("�̹��� �ε� �Ϸ� ��� {}", string(CT2CA(dlg.GetPathName())));
	} else {
		log_Exam->warn("�̹��� �ε� ��ҵ�, ����� ���");
	}
	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);
}

void CMainDlg::OnBnClickedBtnSave()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);
	static TCHAR BASED_CODE szFilter[] = _T("�̹��� ����(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |�������(*.*)|*.*||");

	CFileDialog dlg(FALSE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	if (dlg.DoModal() == IDOK) {
		m_imgDisplay.gSave(string(CT2CA(dlg.GetPathName())));

		log_Exam->info("����� ����Ϸ� �� ��� {}", string(CT2CA(dlg.GetPathName())));

	} 
	else {
		log_Exam->warn("�̹��� ���� ��ҵ�, ����� ���");
	}

	log_Exam->info("end {}:{}", __FUNCTION__, __LINE__);

	/*log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	string file = "c:/glim/image/test.bmp";
	m_imgDisplay.gSave(file);*/
}


void CMainDlg::OnBnClickedBtnProcess()
{

//#if // ����� ����϶�
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
		log_Exam->critical("Bottem�� ������ ����� �����Ǿ����ϴ�.");
	} 
	else if (rect.top < 0) {
		log_Exam->critical("Top�� ������ ����� �����Ǿ����ϴ�.");
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

#include <random> // mt19937�� ����ϱ� ����

void CMainDlg::OnBnClickedBtnCreateObj()
{
	log_Exam->info("start {}:{}", __FUNCTION__, __LINE__);

	static int nIndex = 0;
	std::random_device rd;
	std::mt19937 rand(rd());    // Mersenne Twister 
								// mt19937 = ��û����ū �ݺ��ֱ�� �� ������ ���� ����������.

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
		log_Exam->warn("���������� ������Ʈ�� ������ �ʰ� �Ǿ����ϴ�.");
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
		m_data.pop_back();	//x, y �ι� ����
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



