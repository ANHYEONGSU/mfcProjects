#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include "gImage.h"
//#include <spdlog/spdlog.h>

using namespace std;
// glImage

#define MAX_OBJ			20		//�ִ� Object Count

#define COLOR_RED		RGB(0xff, 0x00, 0x00)
#define COLOR_GREEN		RGB(0x00, 0xff, 0x00)
#define COLOR_BLUE		RGB(0x00, 0x00, 0xff)

enum objType
{
	RECT_OBJ,
	LINE_OBJ,
	TEXT_OBJ,
};

typedef struct tagDrawItem {
	objType type	= objType::RECT_OBJ;
	CRect rect		= NULL;
	string text		= "";
	bool bText		= true;		// text�� ȭ�鿡 ǥ�� �ϴ� �ɼ�
	COLORREF colorObj = COLOR_RED;
	COLORREF colortxt = COLOR_GREEN;
}DrawItem;

class gImage : public CWnd//CStatic
{
	DECLARE_DYNAMIC(gImage)

public:
	gImage();
	virtual ~gImage();

	int m_nIndex = 0;
	bool m_bFlag = 0;
	
	unsigned char* gGetImgPtr();
	BOOL gCreate(int nWidth, int nHeight, int nBpp);
	void gSetImage(unsigned char* fm, int nWidth, int nHeight, int nBpp);
	void gSetImage(unsigned char nGray);			//	�̹��� ��ü ��� ����
	void gSetBinaryColormap(bool bBinary, int nThreshold = 128);


	int  gAddObj(DrawItem item);					//	overlay object Add
	void gSetObj(int nIndex, DrawItem item);		//	�ش� index overlay object data����
	bool gDelObj(int nIndex);						//  �ش� index overlay object delete
	int  gGetObjCount(){							//	overaly object total count return;
		return (int)m_drawObj.size();
	}		
	void gDelObjAll(){
		m_drawObj.clear();
		UpdateDisplay(); 
	}

	HRESULT gSaveThread();
	HRESULT gSave(string strFile);
	HRESULT gLoad(string strFile);
	HRESULT gLoad(CString strFile);

	void	gDestroy();

	int	 gGetWidth() { return m_nWidth; }
	int  gGetHeight() { return m_nHeight; }
	int  gGetHeigth() { return gGetHeight(); }
	int  gGetPitch() { return m_nPitch; }
	int  gGetBPP() { return m_nBPP; }
	CRect gGetRoi();
	int gGetPixelInfo(CPoint &ptMouse, CPoint &ptImg);
	DrawItem gGetObj(int nIndex);
	void UpdateDisplay();
	void gSetUseRoi(bool m_bUse = true, LPRECT pImageRect = NULL);

	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);

private:
	string	gCreateFolder(string strPath);	//���� ������� ���� ����
	void	gDrawObj(CDC* pDC, DrawItem item);
	void	gDrawLine(CDC* pDC, CPoint pt1, CPoint pt2, COLORREF lColor = COLOR_RED);
	void	gDrawText(CDC* pDC, CPoint pt, CString text, COLORREF lColor = COLOR_RED);
	void	gDrawRect(CDC* pDC, CRect rect, COLORREF lColor = COLOR_RED);
	CRect toScale(CRect rect);
	CPoint toScale(CPoint pt);
	double getScaleX();
	double getScaleY();
	//void checkRectView();
	void setPan(CPoint pt);
	
	CRect getDisptoImgRect(CRect rect);
	CRect getImgtoDispRect(CRect rect);
	double m_dScaleZoom = 10; // zoom scale( percentage ���� )
	CPoint m_ptOffset;
	bool m_Lclick = false;

protected:
	vector<DrawItem>	m_drawObj;
	CImage	m_image;
	CPoint m_ptCurMouse;
	CPoint m_ptPan;
	int m_nWidth;			//origin image Width
	int m_nHeight;			//origin image Height
	int m_nPitch;			// m_image pitch
	int m_nBPP;				// Bits Per Pixel
	CRect m_rectView, m_rectDst;
	// m_rectView : img ����� rect, ���� img ������ ȭ�鿡 ǥ�õ� �κ�
	// m_rectDst : zoom in, out �̷������ ���� ���ϴ� window ����� rect
	CRectTracker m_tracker;

	void ViewToDst(long sx, long sy, long& vx, long& vy);
	void DstToView(long sx, long sy, long& vx, long& vy);
	// ViewToDst, DstToView
	// zoom in, out ��ɿ��� ȭ�鿡 �������� ������ image �������� ������ ��ũ�� ���߱� ���� �Լ�
	void UpdateView(BOOL bZoomChanged);

	DECLARE_MESSAGE_MAP()
};
