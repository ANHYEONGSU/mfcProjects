// IniView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FirstProject.h"
#include "IniView.h"
#include "afxdialogex.h"


// CIniView 대화 상자입니다.

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


// CIniView 메시지 처리기입니다.
