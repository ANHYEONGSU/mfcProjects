// HotSpotDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "gChart.h"
#include "HotSpotDlg.h"
#include "afxdialogex.h"


// HotSpotDlg ��ȭ �����Դϴ�.

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


// HotSpotDlg �޽��� ó�����Դϴ�.


BOOL HotSpotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
