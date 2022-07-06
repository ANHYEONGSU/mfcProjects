// glImage.cpp : implementation file
//

//#include "pch.h"
#include "stdafx.h"

#include "gImage.h"

#define MIN_ZOOM	10
#define MAX_ZOOM	1000
// glImage

IMPLEMENT_DYNAMIC(gImage, CStatic)

gImage::gImage()
{
	m_ptOffset = CPoint(0, 0);
	m_tracker.m_rect.SetRect(0, 0, 0, 0);
	m_tracker.m_nHandleSize = 5;
	m_tracker.m_nStyle |= (CRectTracker::dottedLine | CRectTracker::resizeInside);
}

gImage::~gImage()
{
	m_image.Destroy();
}

BEGIN_MESSAGE_MAP(gImage, CStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP()

// glImage message handlers

// step 1-1 : create glImage
BOOL gImage::gCreate(int nWidth, int nHeight, int nBpp)
{
	/*if (nWidth == m_nWidth && nHeight == m_nHeight && nBpp == m_nBPP)
		return true;*/

	gDestroy();

	if (!m_image.Create(nWidth, -nHeight, nBpp)) {
		// 하향식 DIB bitmap 생성을 위해 height 음수로 주어짐
		AfxMessageBox(_T("Can't Create Image"));
		return FALSE;
	}
	m_nWidth = m_image.GetWidth();
	m_nHeight = m_image.GetHeight();
	m_nPitch = m_image.GetPitch();
	m_nBPP = m_image.GetBPP();
	m_rectView.SetRect(0, 0, nWidth, nHeight);
	// step 1-2 : m_rectView initialize

	if (nBpp == 8)
		gSetBinaryColormap(false);
//Create Sample Image
	LPBYTE fm = (LPBYTE)m_image.GetBits();
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			//fm[j * nPitch + i] = (0xff - double(j) / nHeight) * 0xff;
			fm[j * m_nPitch + i] = 0xff - j%0xff;
		}
	}

	for (int j = 0; j < nHeight; j++) {
		fm[j * m_nPitch + nWidth/2] = 0xff;
	}

	return TRUE;
}

void gImage::gSetImage(unsigned char* fm_org, int nWidth, int nHeight, int nBpp)
{
	if (nWidth != m_nWidth || nHeight != m_nHeight || nBpp != m_nBPP) {
		string msg = "Camera image and display image are different";
		//m_logger->critical(msg);
//		AfxMessageBox(toCString(msg));
		return;
	}
	if (fm_org == NULL) {
		string msg = "Camera memory is invalid";
		//m_logger->critical(msg);
//		AfxMessageBox(toCString(msg));
		return;
	}
	int nPitch = m_image.GetPitch();
	LPBYTE fm_img = (LPBYTE)m_image.GetBits();
	memmove(fm_img, fm_org, nWidth*nHeight);
	UpdateDisplay();
}

void gImage::gSetImage(unsigned char nGray)
{
	LPBYTE fm = (LPBYTE)m_image.GetBits();
	memset(fm, nGray, m_nWidth * m_nHeight);
}

void gImage::gSetBinaryColormap(bool bBinary, int nThreshold)
{
	static RGBQUAD rgb[256];
	int	i;
	if (bBinary) {
		for (i = 0; i < nThreshold; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = 0;
		for (; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = 255;
	}
	else {
		for (i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
	}
	m_image.SetColorTable(0, 256, rgb);
	UpdateDisplay();
}

unsigned char* gImage::gGetImgPtr()
{
	return  (unsigned char*)m_image.GetBits();
}

string gImage::gCreateFolder(string strFile)
{
	int find = (int)strFile.rfind("\\") + 1;
	string filePath = strFile.substr(0, find);
	string fileName = strFile.substr(find, strFile.length() - find);
	string Path = filePath;

	char DirName[256];				
	const char* p = Path.c_str();   
	char* q = DirName;
	while (*p){
		if (('\\' == *p) || ('/' == *p)){
			if (':' != *(p - 1)){
				CreateDirectory((CString)DirName, NULL);
			}
		}
		*q++ = *p++;
		*q = '\0';
	}
	CreateDirectory((CString)DirName, NULL);
	return (string)DirName;
}

int getFileCountInFolder(string dir) 
{
	int counter = 0;
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	CString strDir(dir.c_str());//
	// Start iterating over the files in the path directory.
	hFind = FindFirstFile(strDir + L"*.*", &ffd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do // Managed to locate and create an handle to that folder.
		{
			counter++;
		} while (::FindNextFile(hFind, &ffd) == TRUE);
		::FindClose(hFind);
	}
	else {
		printf("Failed to find path: %s", strDir);
	}

	return counter;
	
	return 0;
}
#include <regex>
#include <thread>
string m_strFile;
void threadSaveImg(CWnd* pWnd)
{
	gImage *pImg = (gImage*)pWnd;
	pImg->gSaveThread();
	//static int n = 0;
	//HRESULT ret = img->Save(LPCTSTR(file));
//	img->Save(file, NULL);
}

HRESULT gImage::gSaveThread()
{
	string toCString = regex_replace(m_strFile, regex("/"), "\\");
	CString strPath(toCString.c_str());
	string folder = gCreateFolder(toCString);
	int nCount = getFileCountInFolder(folder);

	HRESULT ret = S_FALSE;
	int nMaxFile = 1000;
	if (nCount < nMaxFile) {
		HRESULT ret = m_image.Save(strPath);
	}
	return ret;
}

HRESULT gImage::gSave(string strFile)
{
	m_strFile = strFile;
	thread _thread(threadSaveImg, this);
	_thread.detach();
/*
	string toCString = regex_replace(strFile, regex("/"), "\\");
	CString strPath(toCString.c_str());
	string folder = glCreateFolder(toCString);
	int nCount = getFileCountInFolder(folder);

	HRESULT ret = S_FALSE;
	int nMaxFile = 1000;
	if (nCount < nMaxFile) {
		thread _thread(threadSaveImg, this);
		_thread.detach();
//		HRESULT ret = m_image.Save(strPath);

		/*
		if (ret != S_OK) {
			//		AfxMessageBox(_T("Can't Save Image file"));
			//m_logger->critical("{} Can't Save file : {}", __FUNCTION__, strFile);
		}
		*/
//	}
	/*
	else {
		//m_logger->critical("{} There are more than {} files in the folder : {}", __FUNCTION__, nMaxFile, folder);
	}
	*/
	HRESULT ret = S_OK;
	return ret;
}
HRESULT gImage::gLoad(CString strFile)
{
	gDestroy();

	// step 1-3 : image load
	HRESULT ret = m_image.Load(strFile);
	if (ret != S_OK) {
		gCreate(m_nWidth, m_nHeight, m_nBPP);
		AfxMessageBox(_T("Can't Load Image file"));
		return ERROR_BAD_FORMAT;
	}
	m_nWidth = m_image.GetWidth();
	m_nHeight = m_image.GetHeight();
	m_nPitch = m_image.GetPitch();
	m_nBPP = m_image.GetBPP();

	if (m_nPitch < 0) {
		unsigned char* fm2 = new unsigned char[m_nHeight*m_nWidth];
		memset(fm2, 0, m_nWidth*m_nHeight);

		LPBYTE fm1 = (LPBYTE)m_image.GetBits();

		for (int j = 0; j < m_nHeight; j++) {
			for (int i = 0; i < m_nWidth; i++) {
				fm2[j*m_nWidth + i] = fm1[j*m_nPitch + i];
			}
		}

		m_image.Destroy();
		m_image.Create(m_nWidth, -m_nHeight, 8);

		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);

		fm1 = (LPBYTE)m_image.GetBits();

		for (int j = 0; j < m_nHeight; j++) {
			for (int i = 0; i < m_nWidth; i++) {
				fm1[j*m_nWidth + i] = fm2[j*m_nWidth + i];
			}
		}
		delete[] fm2;
	}

	m_nPitch = m_nWidth;
	m_rectView.SetRect(0, 0, m_nWidth, m_nHeight);
	// load image에 맞게 m_rectView init

	{	// step 1-4 : init zoom
		CRect rectDisp;
		GetClientRect(rectDisp);
		int	z;
		int	vW, vH;
		vW = rectDisp.right - rectDisp.left;
		vH = rectDisp.bottom - rectDisp.top;
		for (z = MIN_ZOOM + 1; TRUE; z += 1) {
			if (z * m_nWidth / 100 > vW)
				break;
			if (z * m_nHeight / 100 > vH)
				break;
		}
		m_dScaleZoom = z - 1; // percentange 단위, 10(%) ~ 1000(%)
	}

	UpdateView(TRUE); // zoom에 맞춰 image display
	return ret;
}

void gImage::gDestroy()
{
	m_image.Destroy();
	m_nWidth = 0;
	m_nHeight = 0;
	m_nPitch = 0;
	m_nBPP = 0;
	m_rectView.SetRectEmpty();
}

HRESULT gImage::gLoad(string file)
{
	string strFile = regex_replace(file, regex("/"), "\\");
	CString str(strFile.c_str());
	HRESULT ret = gLoad(str);
	return ret;
}

void gImage::gDrawObj(CDC* pDC, DrawItem item)
{
	// step 2-1. draw random obj
	CString str(item.text.c_str());
	switch (item.type)
	{
	case objType::LINE_OBJ:
		gDrawLine(pDC, item.rect.TopLeft(), item.rect.BottomRight(), item.colorObj);
		break;
	case objType::RECT_OBJ:
		gDrawRect(pDC, item.rect, item.colorObj);
		gDrawText(pDC, item.rect.TopLeft(), str);
		break;
	case objType::TEXT_OBJ:
		gDrawText(pDC, item.rect.TopLeft(), str, item.colorObj);
		break;
	}
}

int gImage::gAddObj(DrawItem item)
{
	if (m_drawObj.size() < MAX_OBJ) {
		m_drawObj.push_back(item);
		UpdateDisplay();
	}
	return m_drawObj.size() - 1;
}

bool gImage::gDelObj(int nIndex)
{
	// step 2-2. delete object (nIndex in vector)
	if (m_drawObj.empty()) {
		AfxMessageBox(_T("Object doesn't exist"));
		return false;
	}

	if (nIndex > m_drawObj.size()) {
		AfxMessageBox(_T("out of range 'glDelOjb'"));
		return false;
	}
	vector<DrawItem>::iterator iter = m_drawObj.begin();
	iter += nIndex;
	m_drawObj.erase(iter);
	UpdateDisplay();
	return true;
}

void gImage::gSetObj(int nIndex, DrawItem item)
{
	if (nIndex >= m_drawObj.size()) {
		string err = "SetObj Index " + to_string(nIndex) + " > " + "Darw Obj Count " + to_string(MAX_OBJ);
		return;
	}
	m_drawObj[nIndex] = item;
	UpdateDisplay();
}

DrawItem gImage::gGetObj(int nIndex)
{
	return m_drawObj[nIndex];
}

/*
void gImage::checkRectView()
{
	CString str;
	CRect rect = m_rectView;
	str.Format(_T("View %d, %d, %d, %d\n"), rect.left, rect.top, rect.right, rect.bottom);
	TRACE(str);

	CString str2;
	CRect rect2 = m_rectDst;
	str2.Format(_T("Dst %d, %d, %d, %d\n"), rect2.left, rect2.top, rect2.right, rect2.bottom);
	TRACE(str2);

	CRect rect3;
	GetClientRect(rect3);
	CString str3;
	str3.Format(_T("Client %d, %d, %d, %d\n"), rect3.left, rect3.top, rect3.right, rect3.bottom);
	TRACE(str3);

}
*/

#include <chrono>
void gImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CStatic::OnPaint() for painting messages
	CRect rect;
	CRgn clipRgn;	// clipping region
	GetClientRect(rect);
	clipRgn.CreateRectRgnIndirect(&rect);
	//checkRectView();

	chrono::system_clock::time_point start = std::chrono::system_clock::now();

	dc.SelectClipRgn(&clipRgn);	// clippinf

	if (!m_image.IsNull()) {
		SetStretchBltMode(dc.m_hDC, COLORONCOLOR);
		m_image.StretchBlt(dc, rect, m_rectView); // rect(client rect) 영역에 맞춰 m_rectView 그리기
		for (int i = 0; i < m_drawObj.size(); i++) {
			if(!m_drawObj[i].rect.IsRectNull())
				gDrawObj(&dc, m_drawObj[i]);
		}
	}
	else {
		dc.SelectStockObject(BLACK_BRUSH);
		dc.Rectangle(&rect);
	}
	if (m_Lclick)
		m_tracker.Draw(&dc);

	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;

	CString sReturn;

	sReturn.Format(_T("OnPaint process %03f msec"), sec*1000);
	TRACE(_T("%s\n"), sReturn);
	//AfxMessageBox(sReturn);
}


void gImage::gDrawLine(CDC* pDC, CPoint pt1, CPoint pt2, COLORREF lColor)
{
	int nLineWidth = 1;
	CPen pen, *pOldPen;
	pen.CreatePen(PS_SOLID, nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	pt1 = toScale(pt1);
	pt2 = toScale(pt2);
	//clipped CRect rectDisp;
	//clipped GetClientRect(rectDisp);
	//clipped if (rectDisp.PtInRect(pt1) && rectDisp.PtInRect(pt2)) {
		pDC->MoveTo(pt1);
		pDC->LineTo(pt2);
	//clipped }

	pDC->SelectObject(pOldPen);
	DeleteObject(pen);
}

void gImage::gDrawText(CDC* pDC, CPoint pt, CString text, COLORREF lColor)
{
	pDC->SetBkMode(TRANSPARENT);

	CFont font, *pOldFont;
	font.CreatePointFont(100, _T("Consolas"));
	pOldFont = (CFont*)pDC->SelectObject(&font);

	pDC->SetTextColor(RGB(0xff, 0, 0));
	pDC->TextOutW(toScale(pt).x, toScale(pt).y, text);

	pDC->SelectObject(pOldFont);
	DeleteObject(font);
}

void gImage::gDrawRect(CDC* pDC, CRect rect, COLORREF lColor)
{
	pDC->SetBkMode(TRANSPARENT);

	int nLineWidth = 1;
	CPen pen, *pOldPen;
	pen.CreatePen(PS_SOLID, nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	CBrush brush, *pOldBrush;
	brush.CreateStockObject(NULL_BRUSH);
	pOldBrush = pDC->SelectObject(&brush);

	CRect rectDraw = toScale(rect);
	//clipped CRect rectDisp;
	//clipped GetClientRect(rectDisp);
	//clipped rect.IntersectRect(rectDraw, rectDisp);
	//clipped if(rect == rectDraw)
		pDC->Rectangle(rectDraw);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	DeleteObject(pen);
	DeleteObject(brush);
}

CRect gImage::toScale(CRect rect)
{
	rect = getImgtoDispRect(rect);
	return rect;
}

CPoint gImage::toScale(CPoint pt)
{
	CRect rect(pt, pt);
	rect = getImgtoDispRect(rect);
	pt = rect.CenterPoint();
	return pt;
}

void gImage::UpdateDisplay()
{
	CRect rect;
	GetClientRect(rect);
	InvalidateRect(rect, FALSE);
}

void gImage::gSetUseRoi(bool m_bUse, LPRECT pImageRect) {

	m_Lclick = m_bUse;
	if (m_bUse && pImageRect)	// set initial tracker rect
		m_tracker.m_rect = getImgtoDispRect(pImageRect);
	UpdateDisplay();
}

void gImage::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_Lclick) {
		// step 3-1. Create ins Roi 버튼 눌린 후에 m_tracker rect 생성 (inspect Roi) 

		if (m_tracker.HitTest(point) < 0)
		{
			CRectTracker trk;
			if (trk.TrackRubberBand(this, point, true))
			{
				trk.m_rect.NormalizeRect();
				m_tracker.m_rect = trk.m_rect;
			}
			else
			{
				m_tracker.m_rect = CRect(0, 0, 0, 0);
			}
		}
		else
		{
			if (m_tracker.Track(this, point, true))
			{
				m_tracker.m_rect.NormalizeRect();
			}
			else
			{
				m_tracker.m_rect = CRect(0, 0, 0, 0);
			}
		}
		this->Invalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}


BOOL gImage::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//nFlags option
	//MK_CONTROL	Set if the CTRL key is down.
	//MK_LBUTTON	Set if the left mouse button is down.
	//MK_MBUTTON	Set if the middle mouse button is down.
	//MK_RBUTTON	Set if the right mouse button is down.
	//MK_SHIFT		Set if the SHIFT key is down.
	if (nFlags == MK_MBUTTON) {

		// 마우스 가운데 버튼을 눌렀을 때는 zoom X, 이동만 가능
		UpdateDisplay();
	}
	else {
		CRect rectDisp;
		GetClientRect(rectDisp);

		ScreenToClient(&pt);
		long vx, vy;
		DstToView(pt.x, pt.y, vx, vy);
		// DstToView : 현재 마우스 좌표와 zoom scale에 따라 display에서 변화된 정도를 m_rectView에 반영
		// vx, vy에 display에서 변화된 정도 저장

		if (zDelta > 0) {
			m_dScaleZoom += 10;
		}
		else {
			m_dScaleZoom -= 10;
		}

		if (m_dScaleZoom > MAX_ZOOM)	m_dScaleZoom = MAX_ZOOM;
		if (m_dScaleZoom < MIN_ZOOM)	m_dScaleZoom = MIN_ZOOM;
		
		// get display center
		double	dcx, dcy;
		dcx = 0.5 * (rectDisp.left + rectDisp.right - 1);
		dcy = 0.5 * (rectDisp.top + rectDisp.bottom - 1);
		// get new view center
		double	vcx, vcy;
		vcx = vx - 100.0 * (pt.x - dcx) / (double)m_dScaleZoom;
		vcy = vy - 100.0 * (pt.y - dcy) / (double)m_dScaleZoom;

		// get new view rect
		m_rectView.left = max((int)(vcx - 0.5 * 100.0 * (rectDisp.right - rectDisp.left) / (double)m_dScaleZoom + 0.5) + 1, 0);
		m_rectView.top = max((int)(vcy - 0.5 * 100.0 * (rectDisp.bottom - rectDisp.top) / (double)m_dScaleZoom + 0.5) + 1, 0);
		m_rectView.right = min((int)(vcx + 0.5 * 100.0 * (rectDisp.right - rectDisp.left) / (double)m_dScaleZoom + 0.5), m_nWidth);
		m_rectView.bottom = min((int)(vcy + 0.5 * 100.0 * (rectDisp.bottom - rectDisp.top) / (double)m_dScaleZoom + 0.5), m_nHeight);

		UpdateView(TRUE);
	}

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void gImage::setPan(CPoint pt)
{
	CRect rect = m_rectView;
	pt.x = int(pt.x / (getScaleX()*2));
	pt.y = int(pt.y / (getScaleY()*2));
	rect.OffsetRect(pt);

	if(rect.left > 0 && rect.top > 0 && rect.right < m_nWidth && rect.bottom < m_nHeight)
		m_rectView = rect;

	UpdateDisplay();
}

void gImage::OnMouseMove(UINT nFlags, CPoint point)
{
	m_ptCurMouse = point;
	if (nFlags == MK_MBUTTON) // mouse 가운데 버튼을 눌렀을 때는 zoom in / out 불가, 이동만 가능
	{
		CPoint pt(m_ptPan - point);
		m_ptPan = point;
		setPan(pt);
	}

	CWnd::OnMouseMove(nFlags, point);
}
BOOL gImage::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_tracker.SetCursor(pWnd, nHitTest))
		return TRUE;
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

CRect gImage::getDisptoImgRect(CRect rect)
{
	CRect rectDisp;
	CRect rectImg = m_rectView;
	GetClientRect(rectDisp);
	double dScaleX = double(rectImg.Width()) / rectDisp.Width();
	double dScaleY = double(rectImg.Height()) / rectDisp.Height();

	CRect rectRet = rect;
	CPoint offset;
	offset.x = (rectDisp.left - rectImg.left);
	offset.y = (rectDisp.top - rectImg.top); // offset : m_rectView의 원점이 원본 img의 원점에서 얼마나 벗어났는지에 대한 정도
	rectRet.left = rectRet.left * dScaleX - offset.x;
	rectRet.right = rectRet.right* dScaleX - offset.x;
	rectRet.top = rectRet.top * dScaleY - offset.y;
	rectRet.bottom = rectRet.bottom * dScaleY - offset.y;

	return rectRet;
}

CRect gImage::getImgtoDispRect(CRect rect)
{
	CRect rectDisp;
	CRect rectImg = m_rectView;
	GetClientRect(rectDisp);
	double dScaleX = double(rectDisp.Width()) / rectImg.Width();
	double dScaleY = double(rectDisp.Height()) / rectImg.Height();

	CRect rectRet = rect;
	CPoint offset;
	offset.x = (-rectDisp.left + rectImg.left);
	offset.y = (-rectDisp.top + rectImg.top);
	rectRet.left = (rectRet.left -offset.x) * dScaleX;
	rectRet.right = (rectRet.right- offset.x) * dScaleX;
	rectRet.top = (rectRet.top - offset.y) * dScaleY;
	rectRet.bottom = (rectRet.bottom -offset.y) * dScaleY;
	return rectRet;
}

CRect gImage::gGetRoi()
{
	return getDisptoImgRect(m_tracker.m_rect);

}

double gImage::getScaleX()
{
	CRect rect;
	GetClientRect(rect);
	return (double)rect.Width() / m_nWidth;
}

double gImage::getScaleY()
{
	CRect rect;
	GetClientRect(rect);
	return (double)rect.Height() / m_nHeight;
}

int gImage::gGetPixelInfo(CPoint &ptMouse, CPoint &ptImg)
{
	int nRet = 0;
	ptMouse = m_ptCurMouse; // mouse가 움직일 때의 point
	CRect rect(ptMouse, ptMouse);

	rect = getDisptoImgRect(rect);

	ptImg = rect.CenterPoint();

	unsigned char* fm = gGetImgPtr();
	CRect rectImg(0, 0, m_nWidth, m_nHeight);
	if(rectImg.PtInRect(ptImg))
		nRet = fm[m_nPitch * ptImg.y + ptImg.x];
	return nRet;
}


void gImage::OnMButtonDown(UINT nFlags, CPoint point)
{
	m_ptPan = point;

	CWnd::OnMButtonDown(nFlags, point);
}

void gImage::ViewToDst(long vx, long vy, long& dx, long& dy)
{
	CRect rectDisp;
	GetClientRect(rectDisp);
	double	vcx, vcy, dcx, dcy;
	vcx = 0.5 * (m_rectView.left + m_rectView.right - 1);
	vcy = 0.5 * (m_rectView.top + m_rectView.bottom - 1);
	// vcx, vcy : m_rectView의 원점(0) ~ width 중심 거리, 원점 ~ height 중심 거리

	dcx = 0.5 * (rectDisp.left + rectDisp.right - 1);
	dcy = 0.5 * (rectDisp.top + rectDisp.bottom - 1);
	// dcx, dcy : rectDisp(client rect)의 원점 ~ width 중심 거리, 원점 ~ height 중심 거리

	dx = (long)(dcx + m_dScaleZoom * (vx - vcx) / 100.0 + 0.5);
	dy = (long)(dcy + m_dScaleZoom * (vy - vcy) / 100.0 + 0.5);
}

void gImage::DstToView(long dx, long dy, long& vx, long& vy)
{
	// dx, dy : client rect 내에서 현재 마우스의 좌표

	CRect rectDisp;
	GetClientRect(rectDisp);
	double	vcx, vcy, dcx, dcy;
	vcx = 0.5 * (m_rectView.left + m_rectView.right - 1);
	vcy = 0.5 * (m_rectView.top + m_rectView.bottom - 1);
	// vcx, vcy : m_rectView의 원점(0) ~ width 중심 거리, 원점 ~ height 중심 거리

	dcx = 0.5 * (rectDisp.left + rectDisp.right - 1);
	dcy = 0.5 * (rectDisp.top + rectDisp.bottom - 1);
	// dcx, dcy : rectDisp(client rect)의 원점 ~ width 중심 거리, 원점 ~ height 중심 거리

	vx = (long)(vcx + 100.0 * (dx - dcx) / (double)m_dScaleZoom + 0.5);
	vy = (long)(vcy + 100.0 * (dy - dcy) / (double)m_dScaleZoom + 0.5);
	// display에서 zoom scale만큼 변화된 정도를 m_rectView에 반영

	if (vx < 0)
		vx = 0;
	else if (vx >= m_nWidth)
		vx = m_nWidth - 1;

	if (vy < 0)
		vy = 0;
	else if (vy >= m_nHeight)
		vy = m_nHeight - 1;
}

void gImage::UpdateView(BOOL bZoomChanged)
{
	CRect rectDisp;
	GetClientRect(rectDisp);

	if (bZoomChanged) {
		ViewToDst(m_rectView.left, m_rectView.top, m_rectDst.left, m_rectDst.top);
		ViewToDst(m_rectView.right - 1, m_rectView.bottom - 1, m_rectDst.right, m_rectDst.bottom);
		m_rectDst.right++;
		m_rectDst.bottom++;
	}

	InvalidateRect(&rectDisp, FALSE);
}