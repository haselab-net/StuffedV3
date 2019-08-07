#pragma once

#include "BoardBase.h"
#include "driver/uart.h"
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
	static const char* Tag(){ return "Uart"; };
	struct Cur {
		volatile int board;	//	boards[board]
	};
	Cur cmdCur;
	Cur retCur;
	Boards boards;
	UartForBoards(uart_port_t ch, AllBoards* u);
	void Init(uart_config_t conf, int rxPin, int txPin);
	void EnumerateBoard(char uartId);
	void RecvUart();
	void SendUart();
};

