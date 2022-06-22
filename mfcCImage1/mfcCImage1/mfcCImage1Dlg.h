
// mfcCImage1Dlg.h : 헤더 파일
//

#pragma once


// CmfcCImage1Dlg 대화 상자
class CmfcCImage1Dlg : public CDialogEx
{
private: //프라이빗 외부에서 억세스 사용 불가
	CImage m_image;
	BOOL validImgPos(int x, int y);
// 생성입니다.
public:  //퍼블릭   외부에서 억세스 사용 가능
	CmfcCImage1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCIMAGE1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public: // 외부에서 접근이 가능함
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
