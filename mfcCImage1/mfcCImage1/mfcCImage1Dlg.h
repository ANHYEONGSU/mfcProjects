
// mfcCImage1Dlg.h : ��� ����
//

#pragma once


// CmfcCImage1Dlg ��ȭ ����
class CmfcCImage1Dlg : public CDialogEx
{
private: //�����̺� �ܺο��� �＼�� ��� �Ұ�
	CImage m_image;
	BOOL validImgPos(int x, int y);
// �����Դϴ�.
public:  //�ۺ�   �ܺο��� �＼�� ��� ����
	CmfcCImage1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCIMAGE1_DIALOG };
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
public: // �ܺο��� ������ ������
	afx_msg void OnBnClickedBtnImage();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnLoad();
	void UpdateDisplay();
	void moveRect();
	void moveCircle();
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int nColor);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnAction2();
};
