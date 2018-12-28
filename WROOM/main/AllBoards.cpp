#include "AllBoards.h"
#include "UartForBoards.h"
#include "Board.h"
#include "driver/uart.h"

//	PIN definition
#if defined BOARD3_SEPARATE
#define U1TXPIN	16
#define U1RXPIN	17
#define U2TXPIN	5
#define U2RXPIN	18
#elif defined BOARD2_COMBINATION
#define U1TXPIN	16
#define U1RXPIN	17	
#define U2TXPIN	5
#define U2RXPIN	18
#elif defined BOARD1_MOTORDRIVER
#define U1TXPIN	33	
#define U1RXPIN	32
#define U2TXPIN	17
#define U2RXPIN	16
#else 
#error
#endif

AllBoards allBoards;
UartForBoards uart1(UART_NUM_1, &allBoards);
UartForBoards uart2(UART_NUM_2, &allBoards);
AllBoards::AllBoards(){
	uart[0] = &uart1;
	uart[1] = &uart2;
	boardDirect = new BoardDirect();
	nBoard = 0;
	nTargetMin = 0;
	seUartFinished = xSemaphoreCreateCounting(0xFFFF, 0);
	mode = CM_DIRECT;
}
AllBoards::~AllBoards(){
	vSemaphoreDelete(seUartFinished);
	delete boardDirect;
}
void AllBoards::Init() {
	assert(NUART == 2);	//NUART must be much to followings.
	printf("Start allBoards");
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
void AllBoards::EnumerateBoard() {
	motorMap.clear();
	forceMap.clear();
	for(int m=0; m<boardDirect->GetNMotor(); ++m){	
		boardDirect->motorMap.push_back(allBoards.motorMap.size());
		allBoards.motorMap.push_back(DeviceMap(-1, m));
	}
	for (int i = 0; i < NUART; ++i) {
		uart[i]->EnumerateBoard();
	}
	nTargetMin = boardDirect->GetNTarget();
	nBoard = 1;
	for (int i = 0; i < NUART; ++i) {
		nBoard += uart[i]->boards.size();
		for (int j = 0; j < uart[i]->boards.size(); ++j) {
			int nt = uart[i]->boards[j]->GetNTarget();
			nTargetMin = nt < nTargetMin ? nt : nTargetMin;
		}
	}
}

bool AllBoards::HasRet(unsigned short id){
	if (boardDirect->retPacketLen[id]) return true;
	for (int i = 0; i < NUART; ++i) {
		for (int j = 0; j < uart[i]->boards.size(); ++j) {
			if (uart[i]->boards[j]->retPacketLen[id]) return true;
		}
	}
	return false;
}

void AllBoards::WriteCmd(UdpCmdPacket& packet) {
	if (UartForBoards::bDebug) ESP_LOGI("AllBorads::WriteCmd", "cmd=%d\r\n", packet.command);
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
	boardDirect->WriteCmd(packet);
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
void AllBoards::ReadRet(UdpRetPacket& packet){
	boardDirect->ReadRet(packet);
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
