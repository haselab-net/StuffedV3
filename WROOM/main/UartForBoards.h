#pragma once

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
#include "BoardDirect.h"

class AllBoards;
class UartForBoards :public UTRefCount {
	uart_port_t port;
	AllBoards* allBoards;
public:
	TaskHandle_t taskRecv, taskSend;
	struct Cur {
		volatile int board;	//	boards[board]
	};
	Cur cmdCur;
	Cur retCur;
	Boards boards;
	UartForBoards(uart_port_t ch, AllBoards* u);
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
