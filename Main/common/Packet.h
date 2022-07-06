#pragma once

enum pcID{
	P0,
	P1,
	P2,
	P3,
	P4,
	P5,
	P6,
	PS,		//server
};

enum camID {
	Cam0AT,
	Cam0AB,
	Cam0CT,
	Cam0CB,
	Cam1AT,
	Cam1AB,
	Cam1CT,
	Cam1CB,
};

enum ngType {
	white,
	black,
	size,
};


enum DATA_TYPE { _NICK, _TEXT, _IMAGE_NAME, _IMAGE, _FILE, _FILE_NAME, _PACKET, _UNKNOWN };

typedef struct tagPacketData
{
	int nPId;
	int nCamId;
	char filePath[100];
	int ngType;
	double dRet;

}PACKET_DATA;

class CPacket
{
public:
	CPacket();
	~CPacket();
};
