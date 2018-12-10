#pragma once
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "TinyContainer.h"
#include "freertos/FreeRTOS.h"

class DeviceMap {
public:
	int board;
	int id;
	DeviceMap(int b, int m): board(b), id(m){
	}
};

class UartForBoards;
class BoardDirect;
class UdpCmdPacket;
class UdpRetPacket;
//
class AllBoards{
public:
	enum ControlMode{
		CM_DIRECT,
		CM_INTERPOLATE
	} mode;
	unsigned char nTargetMin;			//	nTaret for all board
	unsigned char nTargetVacancy;		//	nTargetVecancy for all board
	unsigned char nTargetRemain;		//	minimum remaining targets in the board. Must be >= 3.
	unsigned char targetCountWrite;		//	targetCount for next writing. 
	unsigned char targetCountReadMax;	//	targetCount for read of one of the board.
	int nBoard;
	ip_addr_t returnIp;
	static const int NUART = 2;
	tiny::vector<DeviceMap> motorMap;
	tiny::vector<DeviceMap> forceMap;
	UartForBoards* uart[NUART];
	BoardDirect* boardDirect;
	SemaphoreHandle_t seUartFinished;
	int GetNTotalMotor() { return motorMap.size(); }
	int GetNTotalForce() { return forceMap.size(); }
	int GetNTarget() { return nTargetMin; }
	int GetSystemId() { return 0; }
	AllBoards();
	~AllBoards();
	void EnumerateBoard();	
	void Init();
	bool HasRet(unsigned short id);
	///	Write contents of the UdpCmdPacket to all boards. 
	void WriteCmd(UdpCmdPacket& packet);	
	///	Read returns of all boards to  UdpRetPacket. 
	void ReadRet(UdpRetPacket& packet);
};
extern AllBoards allBoards;
