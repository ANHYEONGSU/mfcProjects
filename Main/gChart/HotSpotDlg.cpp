// HotSpotDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "gChart.h"
#include "HotSpotDlg.h"
#include "afxdialogex.h"


// HotSpotDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(HotSpotDlg, CDialogEx)

HotSpotDlg::HotSpotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HOTSPOTDLG, pParent)
{

}

HotSpotDlg::~HotSpotDlg()
{
}

void HotSpotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PARAMLIST, m_ParamList);
}


BEGIN_MESSAGE_MAP(HotSpotDlg, CDialogEx)
END_MESSAGE_MAP()


// HotSpotDlg 메시지 처리기입니다.


BOOL HotSpotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
