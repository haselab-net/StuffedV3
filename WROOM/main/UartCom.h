#pragma once

#include "VCEdit.h"
#include "BoardBase.h"
#include "driver/uart.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <stdio.h>

class Uarts;
class Uart :public UTRefCount {
	uart_port_t port;
	Uarts* uarts;
public:
	TaskHandle_t taskRecv, taskSend;
	struct Cur {
		volatile int board;	//	boards[board]
	};
	Cur cmdCur;
	Cur retCur;
	Boards boards;
	Uart(uart_port_t ch, Uarts* u) : port(ch), uarts(u) {}
	void Init(uart_config_t conf, int rxPin, int txPin);
	void EnumerateBoard();
	void CreateTask();
	void RecvTask();
	void SendTask();
};

class DeviceMap {
public:
	int board;
	int id;
	DeviceMap(int b, int m): board(b), id(m){
	}
};

class Uarts{
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
	Uart* uart[NUART];
	SemaphoreHandle_t seUartFinished;
	int GetNTotalMotor() { return motorMap.size(); }
	int GetNTotalForce() { return forceMap.size(); }
	int GetNTarget() { return nTargetMin; }
	int GetSystemId() { return 0; }
	Uarts();
	~Uarts();
	void EnumerateBoard();	
	void Init();
	bool HasRet(unsigned short id){
		for (int i = 0; i < NUART; ++i) {
			for (int j = 0; j < uart[i]->boards.size(); ++j) {
				if (uart[i]->boards[j]->retPacketLen[id]) return true;
			}
		}
		return false;
	}
	///	Write contents of the UdpCmdPacket to all boards. 
	void WriteCmd(UdpCmdPacket& packet);	
	///	Read returns of all boards to  UdpRetPacket. 
	void ReadRet(UdpRetPacket& packet);
};
extern Uarts uarts;
