#include "UartCom.h"
#include "UdpCom.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "board.h"
#include "../../PIC/boardType.h"

static char zero[80];

void Uart::Init(uart_config_t conf, int txPin, int rxPin){
	uart_param_config(port, &conf);
	uart_set_pin(port, txPin, rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	uart_driver_install(port, 512, 512, 10, NULL, 0);
}
static void recvTask(void* a){
	((Uart*)a)->RecvTask();
}
static void sendTask(void* a){
	((Uart*)a)->SendTask();
}
void Uart::CreateTask(){
	xTaskCreate(recvTask, "RecvTask", 4*1024, this, 10, &taskRecv);
	xTaskCreate(sendTask, "SendTask", 4*1024, this, 12, &taskSend);
}
void Uart::SendTask(){
	while(1){
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);	//	given by WriteCmd()
//		ESP_LOGI("SendTask", "#%d start\n", port);
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
		}
		if (!bRet){
			xSemaphoreGive(uarts->seUartFinished);
		}
		xTaskNotifyGive(taskRecv);					//	start to receive.
//		ESP_LOGI(SendTask, "#%d  end\n", port);
	}
}
void Uart::RecvTask(){
	const ulong READWAIT = 200;	//[ticks(=ms)]
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
					ESP_LOGE("Uart::RecvTask", "Read %d != ret %d, H%2x C%2x pos%d", readLen, retLen,
						 (int)boards[retCur.board]->RetStart()[0], (int)boards[retCur.board]->CmdStart()[0], i);
					ets_delay_us(2000);
					uart_flush_input(port);
				}
				//	ESP_LOGI("RecvTask", "#%d H:%x L:%d", port, (int)boards[retCur.board]->RetStart()[0], boards[retCur.board]->RetLen());
			}
		}
		xSemaphoreGive(uarts->seUartFinished);		//	To finish WriteCmd()
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);	//	Given by ReadRet().
	}
}

void Uart::EnumerateBoard() {
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
						b->motorMap.push_back(uarts->motorMap.size());
						uarts->motorMap.push_back(DeviceMap(i, m));
					}
					for (int m = 0; m < b->GetNForce(); ++m) {
						b->forceMap.push_back(uarts->forceMap.size());
						uarts->forceMap.push_back(DeviceMap(i, m));
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
}
void Uarts::EnumerateBoard() {
	motorMap.clear();
	forceMap.clear();
	for (int i = 0; i < NUART; ++i) {
		uart[i]->EnumerateBoard();
	}
	nTargetMin = 0xFF;
	nBoard = 0;
	for (int i = 0; i < NUART; ++i) {
		nBoard += uart[i]->boards.size();
		for (int j = 0; j < uart[i]->boards.size(); ++j) {
			int nt = uart[i]->boards[j]->GetNTarget();
			nTargetMin = nt < nTargetMin ? nt : nTargetMin;
		}
	}
}
#if defined BOARD1_MOTORDRIVER
#define U1TXPIN	33	
#define U1RXPIN	32
#define U2TXPIN	17
#define U2RXPIN	16
#elif defined BOARD2_COMBINATION
#define U1TXPIN	16
#define U1RXPIN	17	
#define U2TXPIN	5
#define U2RXPIN	18
#else
#error
#endif

void Uarts::Init() {
	assert(NUART == 2);	//NUART must be much to followings.
	printf("Start uarts");
	uart_config_t uconf;
	uconf.baud_rate = 2000000;
	uconf.data_bits = UART_DATA_8_BITS;
    uconf.parity = UART_PARITY_DISABLE;
    uconf.stop_bits = UART_STOP_BITS_1;
    uconf.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uconf.rx_flow_ctrl_thresh = 0;
    uconf.use_ref_tick = false;
	uart[0]->Init(uconf, U1TXPIN, U1RXPIN); // pin must be changed. IO6-11 are reserved. (RX=32 Yellow, TX=33 Green)
	printf(".");
	uart[1]->Init(uconf, U2TXPIN, U2RXPIN);
	printf(". done.\n");
	EnumerateBoard();
	uart[0]->CreateTask();
	uart[1]->CreateTask();
}

Uarts uarts;
Uart uart1(UART_NUM_1, &uarts);
Uart uart2(UART_NUM_2, &uarts);
Uarts::Uarts(){
	uart[0] = &uart1;
	uart[1] = &uart2;
	nBoard = 0;
	nTargetMin = 0;
	seUartFinished = xSemaphoreCreateCounting(0xFFFF, 0);
	mode = CM_DIRECT;
}
Uarts::~Uarts(){
	vSemaphoreDelete(seUartFinished);
}
void Uarts::WriteCmd(UdpCmdPacket& packet) {
	//	Update state based on packet
	if (packet.command == CI_INTERPOLATE || packet.command == CI_FORCE_CONTROL){
		targetCountWrite = (unsigned char)packet.GetTargetCount();
		if (mode == CM_DIRECT){
			mode = CM_INTERPOLATE;
			assert(packet.GetTargetCount() == 0);
		} 
	}else if(packet.command == CI_DIRECT){
		mode = CM_DIRECT;
	}
	//	Write command to borads via uart;
	for (int i = 0; i < NUART; ++i) {
		for (int j = 0; j < uart[i]->boards.size(); ++j) {
			uart[i]->boards[j]->WriteCmd(packet);
		}
	}
	returnIp = packet.returnIp;
	//	Start uart communications 
	for (int i = 0; i < NUART; ++i) {
		xTaskNotifyGive(uart[i]->taskSend);
	}
	//	Wait for ending of uart communications
	for (int i = 0; i < NUART; ++i) {
		xSemaphoreTake(seUartFinished, portMAX_DELAY);
	}
}
void Uarts::ReadRet(UdpRetPacket& packet){
	if (packet.command == CI_INTERPOLATE || packet.command == CI_FORCE_CONTROL) {
		int diffMin = 0x100;
		int diffMax = -0x100;
		unsigned short tickMin = 0xFFFF;
		unsigned short tickMax = 0;
		int countOfRead[20];
		int nCoR = 0;
		memset(countOfRead, 0, sizeof(countOfRead));
		for (int i = 0; i < NUART; ++i) {
			for (int j = 0; j < uart[i]->boards.size(); ++j) {
				uart[i]->boards[j]->ReadRet(packet);
				countOfRead[nCoR++] = (int)uart[i]->boards[j]->GetTargetCountOfRead();
				int diff = ((int)targetCountWrite - (int)uart[i]->boards[j]->GetTargetCountOfRead() + 0x100) & 0xFF;
				if (diff < diffMin) diffMin = diff;
				if (diff > diffMax) diffMax = diff;
				unsigned short tick = uart[i]->boards[j]->GetTick();
				if (tick < tickMin) tickMin = tick;
				if (tick > tickMax) tickMax = tick;
			}
			xTaskNotifyGive(uart[i]->taskRecv);	//	recv next
		}		
		targetCountReadMax = targetCountWrite - diffMin;
		nTargetVacancy = nTargetMin - diffMax;
		nTargetRemain = diffMin;
		if (tickMax - tickMin > 0x7FFF){
			unsigned short temp = tickMin;
			tickMin = tickMax;
			tickMax = temp;
		}
		ESP_LOGI("TGT", "remain:%d vac:%d cor%d %d %d  cow%d",
			 (int)nTargetRemain, (int)nTargetVacancy, countOfRead[0], countOfRead[1], countOfRead[2], targetCountWrite);
		packet.SetTargetCountRead(targetCountReadMax);
		packet.SetTickMin(tickMin);
		packet.SetTickMax(tickMax);
		packet.SetNTargetRemain(nTargetRemain);
		packet.SetNTargetVacancy(nTargetVacancy);
	}else{
		for (int i = 0; i < NUART; ++i) {
			for (int j = 0; j < uart[i]->boards.size(); ++j) {
				uart[i]->boards[j]->ReadRet(packet);
			}
			xTaskNotifyGive(uart[i]->taskRecv);	//	recv next
		}		
	}
}
