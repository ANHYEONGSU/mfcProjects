// IniView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FirstProject.h"
#include "IniView.h"
#include "afxdialogex.h"


// CIniView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CIniView, CDialogEx)

CIniView::CIniView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INIVIEW, pParent), m_logger("dlg1.cpp", "c:/glim/log/log.txt")
{

}

CIniView::~CIniView()
{
}

void CIniView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIniView, CDialogEx)
END_MESSAGE_MAP()


// CIniView �޽��� ó�����Դϴ�.
