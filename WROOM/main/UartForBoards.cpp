#include "UartForBoards.h"
#include "UdpCom.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "board.h"
#include "MotorDriver.h"
#include "../../PIC/boardType.h"

static char zero[80];

bool UartForBoards::bDebug = false;
UartForBoards::UartForBoards(uart_port_t ch, AllBoards* u) : port(ch), allBoards(u){
}
void UartForBoards::Init(uart_config_t conf, int txPin, int rxPin){
	uart_param_config(port, &conf);
	uart_set_pin(port, txPin, rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	uart_driver_install(port, 512, 512, 10, NULL, 0);
}

static void recvTask(void* a){
	((UartForBoards*)a)->RecvTask();
}
static void sendTask(void* a){
	((UartForBoards*)a)->SendTask();
}
void UartForBoards::CreateTask(){
	xTaskCreate(recvTask, "RecvTask", 4*1024, this, 10, &taskRecv);
	xTaskCreate(sendTask, "SendTask", 4*1024, this, 12, &taskSend);
}


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
//			wait = retLen - boards[cmdCur.board]->CmdLen() + 80;
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
					ESP_LOGE("UartForBoards::RecvTask", "Read %d != ret %d, H%2x C%2x pos%d", readLen, retLen,
						 (int)boards[retCur.board]->RetStart()[0], (int)boards[retCur.board]->CmdStart()[0], i);
					ets_delay_us(2000);
					uart_flush_input(port);
				}
				if(bDebug) ESP_LOGI("RecvTask", "Recv #%d H:%x L:%d", port, (int)boards[retCur.board]->RetStart()[0], boards[retCur.board]->RetLen());
			}
		}
		xSemaphoreGive(allBoards->seUartFinished);		//	To finish WriteCmd()
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);	//	Given by ReadRet().
	}
}

void UartForBoards::EnumerateBoard() {
	boards.clear();
	CommandPacketBD0 cmd;
	ReturnPacketBD0 ret;
	for (int i = 0; i <= MAXBOARDID; ++i) {
		printf("Enumerate borad on uart #%d-%d.", port, i);
		cmd.commandId = CI_BOARD_INFO;
		cmd.boardId = i;
		uart_write_bytes(port, zero, 40);	//	clear pending command
		uart_flush_input(port);	//	clear input buffer
		uart_write_bytes(port, (char*)cmd.bytes, BD0_CLEN_BOARD_INFO);	//	send board info command
		uart_write_bytes(port, zero, 5);
		for (int w = 0; w < 20; ++w) {
			printf(".");
			ets_delay_us(1000);
			size_t rxLen;
			uart_get_buffered_data_len(port, &rxLen);
			if (rxLen >= BD0_RLEN_BOARD_INFO) {
				//	found a borad
				memset(&ret.boardInfo, 0, sizeof(ret.boardInfo));
				uart_read_bytes(port, ret.bytes, BD0_RLEN_BOARD_INFO, 0);
				int s = ret.boardInfo.nForce + ret.boardInfo.nMotor;
				//	Check if the board is real board or not.
				if (ret.boardInfo.modelNumber > 0 && (0 < s && s < 100)) {
					BoardBase* b = boards.Create(ret.boardInfo.modelNumber, i);
					for (int m = 0; m < b->GetNMotor(); ++m) {
						b->motorMap.push_back(allBoards->motorMap.size());
						allBoards->motorMap.push_back(DeviceMap(i, m));
					}
					for (int m = 0; m < b->GetNForce(); ++m) {
						b->forceMap.push_back(allBoards->forceMap.size());
						allBoards->forceMap.push_back(DeviceMap(i, m));
					}
					printf("%dT%dM%dF%d", ret.boardInfo.modelNumber, ret.boardInfo.nTarget,
						ret.boardInfo.nMotor, ret.boardInfo.nForce);
					break;
				}
			}
		}
		printf("\n");
	}
	cmdCur.board = boards.size();
	retCur.board = 0;
	//	set command length for all boards
	for (int i = 0; i < boards.size(); ++i) {
		printf("Board %d CLEN:", boards[i]->GetBoardId());
		for (int c = 0; c < CI_NCOMMAND; ++c) {
			cmd.cmdLen.len[c] = boards[i]->cmdPacketLen[c];
			printf(" %d", (int) boards[i]->cmdPacketLen[c]);
		}
		printf(" RLEN:");
		for (int c = 0; c < CI_NCOMMAND; ++c) {
			printf(" %d", (int) boards[i]->retPacketLen[c]);
		}
		printf("\n");
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
