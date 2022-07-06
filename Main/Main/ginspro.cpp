#include "gInsPro.h"
//#include "../common/FindEdge.h"

gInsPro::gInsPro(int nWidth, int nHeight, int nPitch, unsigned char* fm)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nPitch = nPitch;
	m_fm = fm;
}

gInsPro::~gInsPro()
{

}


INS_RET gInsPro::mainInspect(ng_info* ngInfo)
{
	INS_RET insRet;

	//spdlog::get(ngInfo->camId)->trace("Step 3.\t{}\t\t\t\t{}", __FUNCTION__, ngInfo->nFrame);

	//if (m_nWidth < 0) {
	//	//spdlog::get(LOG_INSPRO)->critical("{} : {} ", __FUNCTION__, "image width not defined");
	//	log_insPro->critical("{} : {} ", __FUNCTION__, "image width not defined");
	//	return insRet;
	//}
	//CRect rect(0, m_nHeight/2 - 100, m_nWidth, m_nHeight/2 + 100);	//추 후 찾는 루틴 필요.
	//serchLR(rect, &insRet);
	//inspectDone(ngInfo);

	return insRet;
}

void gInsPro::inspectDone(ng_info* ngInfo)
{
	//string result;
	//string defaultfilePath = "c:/glim/ng/";
	//
	//if (ngInfo->nRet == ng_code::good) {
	//	result = "good";

	//}
	//else {
	//	result = "ng";
	//	CRect rect(ngInfo->rectNg.CenterPoint(), CSize(NG_IMG_SIZE_X, NG_IMG_SIZE_X));
	//	ngInfo->rectNg = validRect(rect);
	//	cropImage(ngInfo->img.glGetImgPtr(), ngInfo->rectNg);
	//	ngInfo->fileName = defaultfilePath +
	//		ngInfo->camId + "/" +
	//		getNgCodeString(ngInfo->nRet) +
	//		to_string(ngInfo->nFrame) + ".jpg";

	//}
	//spdlog::get(ngInfo->camId)->trace("Step 4.\t{}\t{}\t\t\t\t{}", __FUNCTION__, result, ngInfo->nFrame);
}


CRect gInsPro::validRect(CRect rect)
{
	CRect rectImg(0, 0, m_nWidth, m_nHeight);
	CRect rectRet;
	rectRet.IntersectRect(rectImg, rect);
	return rectRet;
}

void gInsPro::cropImage(unsigned char* fm, CRect rect)
{
	int y = 0;
	int nPitchCrop = rect.right - rect.left;
	int nPitch = m_nWidth;
	for (int j = rect.top; j < rect.bottom; j++) {
		int x = 0;
		for (int i = rect.left; i < rect.right; i++) {
			fm[y * nPitchCrop + x] = m_fm[j * nPitch + i];
			x++;
		}
		y++;
	}
}

string gInsPro::getNgCodeString(int ngCode) 
{
	switch (ngCode) 
	{
	case ng_code::good:
		return "good";
	case ng_code::ng_black:
		return "ng_black";
	case ng_code::ng_white:
		return "ng_white";
	default :
		return "not_defined";
	}
}

#define MAXEDGENUMBER 100
//	LN_FindEdgeM_ABS(int n, int *data, int slope, double *edge, int *dir);
void gInsPro::serchLR(CRect rect, INS_RET* insRet)
{
/*
	static int nIndex = 0;
	int w = m_nWidth;
	int h = m_nHeight;
	unsigned char* fm = m_fm;
	int* pHisto = (int*)malloc(sizeof(int)*w);
	memset(pHisto, 0, sizeof(int)*w);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			pHisto[i] += fm[w*j + i];
		}
	}
	//for (int i = 0; i < w; i++) {
	//	glTrace(_T("%d\t%d\t%d\n"), nIndex, i, pHisto[i]);
	//}
	//find max slope
	int nMaxSlope = 0;
	for (int i = 1; i < w; i++) {
		int nSlope = abs(pHisto[i] - pHisto[i-1]);
		if (nSlope > nMaxSlope)	nMaxSlope = nSlope;
	}
	nIndex++;
	double dEdge[MAXEDGENUMBER];
	int nDir[MAXEDGENUMBER];
	int nSlope = int(nMaxSlope * 0.7);
	LN_FindEdgeM_ABS(w, pHisto, nSlope, dEdge, nDir);

	insRet->dLout = dEdge[0];
	insRet->dLin = dEdge[1];

	free(pHisto);
	*/
}
void gInsPro::serchRL(CRect rect, INS_RET* insRet)
{

}
void gInsPro::serchRB(CRect rect, INS_RET* insRet)
{

}
void gInsPro::serchBT(CRect rect, INS_RET* insRet)
{

}

void gInsPro::setBinary(CRect rect, int nTh)
{
	int nPitch = m_nPitch;
	unsigned char* fm = m_fm;
	rect = validRect(rect);
	for (int j = rect.top; j < rect.bottom; j++) {	
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j*nPitch + i] > nTh)	fm[j*nPitch + i] = 0xff;
			else fm[j*nPitch + i] = 0x00;
		}
	}
}

double gInsPro::getEdgePos(CRect rect, int nDir)
{
	unsigned char* fm = m_fm;
	double dRet = 0;
	int* projV = new int[rect.Width()]{ 0, };
	int* projH = new int[rect.Height()]{ 0, };
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			projV[i - rect.left] += fm[j*m_nPitch + i];
			projH[j - rect.top] += fm[j*m_nPitch + i];
		}
	}
	int nSlope;
	int nSlopeMaxV = 0;
	for (int i = 1; i < rect.Width(); i++) {
		nSlope = projV[i] - projV[i - 1];
		if (nSlope > nSlopeMaxV)
			nSlopeMaxV = nSlope;
	}
	int nSlopeMaxH = 0;
	for (int j = 1; j < rect.Height(); j++) {
		nSlope = projH[j] - projH[j - 1];
		if (nSlope > nSlopeMaxH)
			nSlopeMaxH = nSlope;
	}

	nDir = (nSlopeMaxV > nSlopeMaxH) ? edgeDir::edgeV : edgeDir::edgeH;

	if (nDir == edgeDir::edgeH) {
		dRet = getEdgePosH(rect);
	}
	else if (nDir == edgeDir::edgeV) {
		dRet = getEdgePosV(rect);
	}
	delete[] projH;
	delete[] projV;
	return dRet;
}

#include "gFindEdge.h"
double gInsPro::getEdgePosV(CRect rect)
{
	unsigned char* fm = m_fm;
	double dRet = 0;
	int* proj = new int[rect.Width()]{ 0, };
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			proj[i - rect.left] += fm[j*m_nPitch + i];
		}
	}
	int slope, dir;
	LN_FindEdge1_ABS(rect.Width(), proj, &dRet, &slope , &dir);
	dRet = rect.left + dRet;
	if (rect.Width() != 0)	delete[] proj;
	return dRet;
}
double gInsPro::getEdgePosH(CRect rect)
{
	unsigned char* fm = m_fm;
	double dRet = 0;
	int* proj = new int[rect.Height()]{ 0, };
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			proj[j - rect.top] += fm[j*m_nPitch + i];
		}
	}
	int slope, dir;
	LN_FindEdge1_ABS(rect.Height(), proj, &dRet, &slope, &dir);
	dRet = rect.top + dRet;
	if(rect.Height() != 0)	delete[] proj;
	return dRet;
}
