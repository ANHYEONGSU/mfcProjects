
// csvExamDlg.h : ��� ����
//

#pragma once

using namespace std;

#include <string>
#include <vector>

typedef struct tagData {
	string strData;
	int nData;
	double dData;
} DATA;


// CcsvExamDlg ��ȭ ����
class CcsvExamDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CcsvExamDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSVEXAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�

// �����Դϴ�.
protected:
	HICON m_hIcon;
	std::vector<DATA> m_Data;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnReadCsv();
	afx_msg void OnBnClickedBtnWriteCsv();

	CString m_sItems;
};
