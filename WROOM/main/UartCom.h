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
	int id;
	uart_port_t port;
//	friend void uartEvent(void* a);
public:
	struct Cur {
		volatile int board;	//	boards[board]
#if 0
		int cur;	//	cursor in board packet
#endif
	};
	Cur cmdCur;
	Cur retCur;
	Boards boards;
	Uart(uart_port_t ch) : port(ch) {}
	void Init(uart_config_t conf, int rxPin, int txPin);
	void EnumerateBoard(Uarts* s);
#if 0
	void Loop();
	bool IsIdle() { return cmdCur.board == boards.size(); }
	void StartCmd() {
		//	start to write command
		cmdCur.cur = 0;
		cmdCur.board = 0;
	}
	void RetBegin() {
		retCur.cur = 0;
		retCur.board = 0;
	}
#endif
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
	bool bRetFinished = true;
	int nTargetMin;			//	nTaret for all board
	int nTargetVacancy;		//	nTargetVecancy for all board
	int nBoard;
	ip_addr_t returnIp;
	static const int NUART = 2;
	tiny::vector<DeviceMap> motorMap;
	tiny::vector<DeviceMap> forceMap;
	int GetNTotalMotor() { return motorMap.size(); }
	int GetNTotalForce() { return forceMap.size(); }
	int GetNTarget() { return nTargetMin; }
	int GetSystemId() { return 0; }
	Uart* uart[NUART];
	Uarts();
	void EnumerateBoard();	
	void Init();
	void WriteCmd(UdpCmdPacket& packet);
	void ReadRet(UdpRetPacket& packet);
	///	If all return packet from boards are arrived or not. Works between RetBegin and RetEnd.
	bool RetReady(){
		if (nBoard == 0) return false;
		if (bRetFinished)  return false;
		for (int i = 0; i < NUART; ++i) {
			if (uart[i]->retCur.board < uart[i]->boards.size()) {
				printf(".");
				return false;
			}
		}
		return true;
	}
	///	Prepare for receiving return packet from boards
	void RetBegin() {
		for (int i = 0; i < NUART; ++i) uart[i]->RetBegin();	//	 set retCur = 0
		bRetFinished = false;
	}
	///	Release ret packet buffers. Must call after RetReady()==true and finished to read buffer.
	void RetEnd() {
		bRetFinished = true;
	}
	///	Get the command id of the ret packet from one of the boards.
	int RetCommand() {
		for (int i = 0; i < NUART; ++i) {
			if (uart[i]->boards.size() > 0) return uart[i]->boards[0]->GetRetCommand();
		}
		return -1;
	}
	///	Is uarts are idle (finished to both sending and receiveing)
	bool IsIdle() {
		if (!bRetFinished) return false;
		bool rv = true;
		for (int i = 0; i < NUART; ++i) {
			if (!uart[i]->IsIdle()) rv = false;
		}
		return rv;
	}
	///	Start to send commmand. Prepare for receive packet from board if needed.
	bool StartCmd() {
		bool rv = false;
		//	prepare to receive return
		for(int i=0; i<NUART; ++i){
			for (int j = 0; j < uart[i]->boards.size(); ++j) {
				if (uart[i]->boards[j]->RetLenForCommand()) {
					RetBegin();	//	if receive packet from any boards
					rv = true;
					goto next;
				}
			}
		}
		next:;
		for (int i = 0; i < NUART; ++i) {
			uart[i]->StartCmd();
		}
		Loop();
		return rv;
	}
	///	loop for uart
	void Loop() {
		for (int i = 0; i < NUART; ++i) {
			uart[i]->Loop();
		}
	}
};

extern Uarts uarts;
