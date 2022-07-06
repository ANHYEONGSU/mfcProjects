
// ObjectDlg.h : ��� ����
//

#pragma once
#include "gImage.h"


// CObjectDlg ��ȭ ����
class CObjectDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CObjectDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	gImage m_imgDisplay;
	afx_msg void OnBnClickedBtnImageLoad();
	afx_msg void OnBnClickedBtnCreateObj();
	afx_msg void OnBnClickedBtnDeleteObj();
};
