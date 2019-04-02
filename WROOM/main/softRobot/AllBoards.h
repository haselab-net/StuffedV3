#pragma once
#include "lwip/opt.h"
#include "lwip/tcpip.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "TinyContainer.h"
#include "../WroomEnv.h"
#include "BoardBase.h"
#include "RobotState.h"
#include "RobotCommand.h"

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
//	RobotState state;
//	RobotCommand command;
	int nBoard;
	int nTargetMin;
	static const int NUART = 2;
	tiny::vector<DeviceMap> motorMap;
	tiny::vector<DeviceMap> currentMap;
	tiny::vector<DeviceMap> forceMap;
	tiny::vector<DeviceMap> touchMap;
	UartForBoards* uart[NUART];
	BoardDirect* boardDirect;
	xTaskHandle taskExec;
	int GetNTotalMotor() { return (int)motorMap.size(); }
	int GetNTotalCurrent() { return (int)currentMap.size(); }
	int GetNTotalForce() { return (int)forceMap.size(); }
	int GetNTotalTouch() { return (int)touchMap.size(); }
	int GetNTarget() { return nTargetMin; }
	int GetSystemId() { return 0; }
	AllBoards();
	~AllBoards();
	void EnumerateBoard();	
	void Init();
	bool HasRet(unsigned short id);
	///	Write contents of the UdpCmdPacket to all boards. 
	void WriteCmd(unsigned short commandId, BoardCmdBase& packet);	
	///	Read returns of all boards to  UdpRetPacket.   bNext: start to read next UART data (send notify to recvTask).
	void ReadRet(unsigned short commandId, BoardRetBase& packet);

	void ExecLoop();
};
extern AllBoards allBoards;
