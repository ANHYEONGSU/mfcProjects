// Copyright(c) 2021-present, Kwack man-young<kmy@iglim.net> glInsPro(gLim Inspect Process) contributors.
// 이 코드는 (주)그림 에서 제작한 문서로 저작권은 (주)그림에 있습니다.

#pragma once
#include <string>
#include <afxwin.h>         // MFC core and standard components

using namespace std;

typedef struct tagInsRet {
	double dTout = 0;
	double dBout = 0;
	double dLout = 0;
	double dRout = 0;
	double dTin = 0;
	double dBin = 0;
	double dLin = 0;
	double dRin = 0;
}INS_RET;

enum ng_code {
	good,
	ng_white,
	ng_black,
};

typedef struct ng_info {
	//glImage img;
	string camId;
	string cellId;
	string fileName;
	int nRet = ng_code::good;	//true:ok ng:flase
	int nFrame;
	CRect rectNg;
	double dCurPos;
	double dMin = 0;
	double dMax = 0;
	double dRet = 0;
	//	CPoint ptRet;
}ng_info;
enum edgeDir{
	edgeAuto,
	edgeV,
	edgeH,
};

class gInsPro	
{
public:
	gInsPro(int nWidth, int nHeight, int nPitch, unsigned char* fm);
	~gInsPro();

	INS_RET mainInspect(ng_info* ngInfo);
	string getNgCodeString(int ngCode);
	void setBinary(CRect rect, int nTh);
	double getEdgePos(CRect rect, int nDir = edgeDir::edgeAuto);
	double getEdgePosV(CRect rect);
	double getEdgePosH(CRect rect);

private:
	int m_nWidth = -1;
	int m_nHeight = -1;
	int m_nPitch = 0;
	int nBpp = 0;
	unsigned char* m_fm;

	CRect validRect(CRect rect);
	void cropImage(unsigned char* fm, CRect rect);
	void inspectDone(ng_info* ngInfo);
	void serchLR(CRect rect, INS_RET* insRet);
	void serchRL(CRect rect, INS_RET* insRet);
	void serchRB(CRect rect, INS_RET* insRet);
	void serchBT(CRect rect, INS_RET* insRet);

	//string getNgCodeString(int ngCode);
};

