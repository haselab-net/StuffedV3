#include "UartForBoards.h"
#include "UdpCom.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "board.h"
#include "MotorDriver.h"
#include "../../../PIC/boardType.h"
#include "../../../PIC/env.h"

static char zero[80];

bool UartForBoards::bDebug = false;
UartForBoards::UartForBoards(uart_port_t ch, AllBoards* u) : port(ch), allBoards(u){
}
void UartForBoards::Init(uart_config_t conf, int txPin, int rxPin){
	uart_param_config(port, &conf);
	uart_set_pin(port, txPin, rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	uart_driver_install(port, 512, 512, 10, NULL, 0);
}

void UartForBoards::SendUart(){
	int wait = 0;
	const char* TAG = "SendUart";
	for(cmdCur.board=0; cmdCur.board<(int)boards.size(); cmdCur.board++){
		int retLen = boards[cmdCur.board]->RetLenForCommand();
		wait = retLen - boards[cmdCur.board]->CmdLen() + 20;
		if (wait < 5) wait = 5;
		assert(wait < CMDWAITMAXLEN);
		memset(boards[cmdCur.board]->CmdStart() + boards[cmdCur.board]->CmdLen(), 0, wait);
		uart_write_bytes(port, (char*)boards[cmdCur.board]->CmdStart(),
			(size_t)boards[cmdCur.board]->CmdLen()+wait);
		if(bDebug) ESP_LOGI(TAG, "Send #%d CMD=%x L=%d to Board %d on UART%d \n", port, boards[cmdCur.board]->CmdStart()[0]>>3, boards[cmdCur.board]->CmdLen(), boards[cmdCur.board]->GetBoardId(), this->port);
	}
	if(bDebug) ESP_LOGI(TAG, "#%d  end\n", port);
}
void UartForBoards::RecvUart(){
	const ulong READWAIT = 2000;	//[ticks(=ms)]
	for (retCur.board=0; retCur.board < (int)boards.size(); retCur.board++) {
		int retLen = boards[retCur.board]->RetLenForCommand();
		if (retLen){
			//	receive the header byte
			int readLen = uart_read_bytes(port, (uint8_t*)(boards[retCur.board]->RetStart()), retLen, READWAIT);
			if (readLen != retLen){
				//	timeout
				int i;
				for(i=0; i<readLen; ++i){
					if (boards[retCur.board]->RetStart()[i] == boards[retCur.board]->CmdStart()[0]){
						break;
					}
				}
				ESP_LOGE("UartForBoards::RecvTask", "#%d ReadLen %d != RetLen %d, H%2x C%2x pos%d", port, readLen, retLen,
						(int)boards[retCur.board]->RetStart()[0], (int)boards[retCur.board]->CmdStart()[0], i);
				vTaskDelay(2000);
				uart_flush_input(port);
			}else{
				if (boards[retCur.board]->RetStart()[0] != boards[retCur.board]->CmdStart()[0]){
					ESP_LOGW("RecvTask", "Recv #%d H:%x L:%d for Cmd H:%x", port, (int)boards[retCur.board]->RetStart()[0], 
						boards[retCur.board]->RetLen(), (int)boards[retCur.board]->CmdStart()[0]);
				}
			}
			if(bDebug) ESP_LOGI("RecvTask", "Recv #%d H:%x L:%d", port, (int)boards[retCur.board]->RetStart()[0], boards[retCur.board]->RetLen());
		}
	}
	//	check if the buffer is empty
	size_t remain;
	uart_get_buffered_data_len(port, &remain);
	if (remain){
		uint8_t buf[256];
		uart_read_bytes(port, buf, remain, 0);
		char str[1024];
		char* ptr = str;
		for(int i=0; i<(int)remain; ++i){
			logPrintf(ptr, " %02x", buf[i]);
			ptr += strlen(ptr);
		}
		int i;
		for(i=0; i<(int)boards.size(); ++i){
			if (boards[i]->RetLenForCommand() > 0) break;
		}
		ESP_LOGE("RecvTask", "Uart #%d %d bytes remains. cmd %x ret %x  remain:%s", port, remain, boards[i]->CmdStart()[0], boards[i]->RetStart()[0], str);
	}
}

#if 0
void UartForBoards::SendTask(){
	while(1){
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);	//	given by WriteCmd()
		if(bDebug) ESP_LOGI("SendTask", "#%d start\n", port);
		int wait = 0;
		bool bRet = false;
		for(cmdCur.board=0; cmdCur.board<boards.size(); cmdCur.board++){
			int retLen = boards[cmdCur.board]->RetLenForCommand();
			if (retLen) bRet = true;
			wait = retLen - boards[cmdCur.board]->CmdLen() + 20;
			if (wait < 5) wait = 5;
			assert(wait < CMDWAITMAXLEN);
			memset(boards[cmdCur.board]->CmdStart() + boards[cmdCur.board]->CmdLen(), 0, wait);
			uart_write_bytes(port, (char*)boards[cmdCur.board]->CmdStart(),
				(size_t)boards[cmdCur.board]->CmdLen()+wait);
			if(bDebug) ESP_LOGI("SendTask", "Send #%d CMD=%x L=%d to Board %d on UART%d \n", port, boards[cmdCur.board]->CmdStart()[0]>>3, boards[cmdCur.board]->CmdLen(), boards[cmdCur.board]->GetBoardId(), this->port);
		}
		if (!bRet){
			xSemaphoreGive(allBoards->seUartFinished);
		}
		xTaskNotifyGive(taskRecv);					//	start to receive.
		if(bDebug) ESP_LOGI("SendTask", "#%d  end\n", port);
	}
}
void UartForBoards::RecvTask(){
	const ulong READWAIT = 2000;	//[ticks(=ms)]
	while(1){
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);	//	Start to receive
		for (retCur.board=0; retCur.board < boards.size(); retCur.board++) {
			int retLen = boards[retCur.board]->RetLenForCommand();
			if (retLen){
				//	receive the header byte
				int readLen = uart_read_bytes(port, (uint8_t*)(boards[retCur.board]->RetStart()), retLen, READWAIT);
				if (readLen != retLen){
					//	timeout
					int i;
					for(i=0; i<readLen; ++i){
						if (boards[retCur.board]->RetStart()[i] == boards[retCur.board]->CmdStart()[0]){
							break;
						}
					}
					ESP_LOGE("UartForBoards::RecvTask", "#%d ReadLen %d != RetLen %d, H%2x C%2x pos%d", port, readLen, retLen,
						 (int)boards[retCur.board]->RetStart()[0], (int)boards[retCur.board]->CmdStart()[0], i);
					ets_delay_us(2000);
					uart_flush_input(port);
				}else{
					if (boards[retCur.board]->RetStart()[0] != boards[retCur.board]->CmdStart()[0]){
						ESP_LOGW("RecvTask", "Recv #%d H:%x L:%d for Cmd H:%x", port, (int)boards[retCur.board]->RetStart()[0], 
							boards[retCur.board]->RetLen(), (int)boards[retCur.board]->CmdStart()[0]);
					}
				}
				if(bDebug) ESP_LOGI("RecvTask", "Recv #%d H:%x L:%d", port, (int)boards[retCur.board]->RetStart()[0], boards[retCur.board]->RetLen());
			}
		}
		//	check if the buffer is empty
		size_t remain;
		uart_get_buffered_data_len(port, &remain);
		if (remain){
			uint8_t buf[256];
			uart_read_bytes(port, buf, remain, 0);
			char str[1024];
			char* ptr = str;
			for(int i=0; i<remain; ++i){
				slogPrintf(ptr, " %02x", buf[i]);
				ptr += strlen(ptr);
			}
			int i;
			for(i=0; i<boards.size(); ++i){
				if (boards[i]->RetLenForCommand() > 0) break;
			}
			ESP_LOGE("RecvTask", "Uart #%d %d bytes remains. cmd %x ret %x  remain:%s", port, remain, boards[i]->CmdStart()[0], boards[i]->RetStart()[0], str);
		}
		xSemaphoreGive(allBoards->seUartFinished);		//	To finish WriteCmd()
		//ulTaskNotifyTake(pdFALSE, portMAX_DELAY);	//	Given by ReadRet().
	}
}
#endif

void UartForBoards::EnumerateBoard() {
	boards.clear();
	CommandPacketBD0 cmd;
	ReturnPacketBD0 ret;
	for (int i = 0; i <= MAXBOARDID; ++i) {
		logPrintf("Enumerate borad on uart #%d-%d.", port, i);
		cmd.commandId = CI_BOARD_INFO;
		cmd.boardId = i;
		uart_write_bytes(port, zero, 40);	//	clear pending command
		uart_flush_input(port);	//	clear input buffer
		uart_write_bytes(port, (char*)cmd.bytes, BD0_CLEN_BOARD_INFO);	//	send board info command
		uart_write_bytes(port, zero, 5);
		for (int w = 0; w < 20; ++w) {
			logPrintf(".");
#ifndef _WIN32
			vTaskDelay(1);
#endif
			size_t rxLen;
			uart_get_buffered_data_len(port, &rxLen);
			if (rxLen >= BD0_RLEN_BOARD_INFO) {
				//	found a borad
				memset(&ret.boardInfo, 0, sizeof(ret.boardInfo));
				uart_read_bytes(port, ret.bytes, BD0_RLEN_BOARD_INFO, 0);
				int s = ret.boardInfo.nMotor + ret.boardInfo.nCurrent + ret.boardInfo.nForce;
				//	Check if the board info is appropriate or not.
				if (ret.boardInfo.modelNumber > 0 && (0 < s && s < 100)) {
					BoardBase* b = boards.Create(ret.boardInfo.modelNumber, i);
					for (int m = 0; m < b->GetNMotor(); ++m) {
						b->motorMap.push_back(allBoards->motorMap.size());
						allBoards->motorMap.push_back(DeviceMap(i, m));
					}
					for (int m = 0; m < b->GetNCurrent(); ++m) {
						b->currentMap.push_back(allBoards->currentMap.size());
						allBoards->currentMap.push_back(DeviceMap(i, m));
					}
					for (int m = 0; m < b->GetNForce(); ++m) {
						b->forceMap.push_back(allBoards->forceMap.size());
						allBoards->forceMap.push_back(DeviceMap(i, m));
					}
					for (int m = 0; m < b->GetNTouch(); ++m) {
						b->touchMap.push_back(allBoards->touchMap.size());
						allBoards->touchMap.push_back(DeviceMap(i, m));
					}
					logPrintf("%dT%dM%dC%dF%d", ret.boardInfo.modelNumber, ret.boardInfo.nTarget,
						ret.boardInfo.nMotor, ret.boardInfo.nCurrent, ret.boardInfo.nForce);
					break;
				}
			}
		}
		logPrintf("\n");
	}
	cmdCur.board = boards.size();
	retCur.board = 0;
	//	set command length for all boards
	for (int i = 0; i < (int)boards.size(); ++i) {
		logPrintf("Board %d CLEN:", boards[i]->GetBoardId());
		for (int c = 0; c < CI_NCOMMAND; ++c) {
			cmd.cmdLen.len[c] = boards[i]->cmdPacketLen[c];
			logPrintf(" %d", (int) boards[i]->cmdPacketLen[c]);
		}
		logPrintf(" RLEN:");
		for (int c = 0; c < CI_NCOMMAND; ++c) {
			logPrintf(" %d", (int) boards[i]->retPacketLen[c]);
		}
		logPrintf("\n");
		cmd.commandId = CI_SET_CMDLEN;
		cmd.boardId = boards[i]->GetBoardId();
		uart_flush_input(port);												//	clear input buffer
		uart_write_bytes(port, (char*)cmd.bytes, BD0_CLEN_SET_CMDLEN);		//	send board info command
	}
	uart_write_bytes(port, zero, 5);
	#if 0	// For UART command test
	for (int i = 0; i < boards.size(); ++i) {
		ets_delay_us(10000);
		cmd.commandId = CI_TORQUE_LIMIT;
		uart_write_bytes(port, (char*)cmd.bytes, boards[i]->cmdPacketLen[cmd.commandId]);	//	send board info command
	}
	uart_write_bytes(port, zero, 5);
	#endif
}
