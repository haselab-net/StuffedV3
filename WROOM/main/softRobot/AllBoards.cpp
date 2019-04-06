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
	nBoard = 0;
	uart[0] = &uart1;
	uart[1] = &uart2;
	boardDirect = new BoardDirect();
}
AllBoards::~AllBoards(){
	delete boardDirect;
}
static void execLoop(void* arg){
	((AllBoards*)arg)->ExecLoop();
}
void AllBoards::ExecLoop(){
	while (1){
		UdpCmdPacket* recv = &udpCom.recvs.Peek();
		ESP_LOGV(Tag(), "ExecLoop(): command %d received.", recv->command);
		if (CI_BOARD_INFO < recv->command && recv->command < CI_NCOMMAND) {
			//	send packet to allBoards
			ESP_LOGV(Tag(), "ExecLoop(): write cmd %d.", recv->command);
			WriteCmd(recv->command, *recv);
			udpCom.PrepareRetPacket(*recv);
			if (HasRet(recv->command)){
				ReadRet(recv->command, udpCom.send);
				ESP_LOGV(Tag(), "ExecLoop() read ret %d.", recv->command);
			}
			udpCom.SendReturn(*recv);
		}
		else {
			udpCom.ExecUdpCommand(*recv);
		}
		udpCom.recvs.Read();
	}
}
void AllBoards::Init() {
	assert(NUART == 2);	//NUART must be much to followings.
	logPrintf("Start allBoards");
	uart_config_t uconf;
	uconf.baud_rate = 2000000;
	uconf.data_bits = UART_DATA_8_BITS;
    uconf.parity = UART_PARITY_DISABLE;
    uconf.stop_bits = UART_STOP_BITS_1;
    uconf.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uconf.rx_flow_ctrl_thresh = 0;
    uconf.use_ref_tick = false;
	
	uart[0]->Init(uconf, U1TXPIN, U1RXPIN); // pin must be changed. IO6-11 are reserved. (RX=32 Yellow, TX=33 Green)
	logPrintf(".");
	uart[1]->Init(uconf, U2TXPIN, U2RXPIN);
	logPrintf(". done.\n");
	EnumerateBoard();
	xTaskCreate(execLoop, "ExecLoop", 8 * 1024, this, tskIDLE_PRIORITY, &taskExec);
}
void AllBoards::EnumerateBoard() {
	motorMap.clear();
	currentMap.clear();
	forceMap.clear();
	touchMap.clear();
	for(int m=0; m<boardDirect->GetNMotor(); ++m){
		boardDirect->motorMap.push_back((int)allBoards.motorMap.size());
		allBoards.motorMap.push_back(DeviceMap(-1, m));
	}
	for (int m = 0; m<boardDirect->GetNCurrent(); ++m) {
		boardDirect->currentMap.push_back((int)allBoards.currentMap.size());
		allBoards.currentMap.push_back(DeviceMap(-1, m));
	}
	for (int m = 0; m<boardDirect->GetNForce(); ++m) {
		boardDirect->forceMap.push_back((int)allBoards.forceMap.size());
		allBoards.forceMap.push_back(DeviceMap(-1, m));
	}
	for (int m = 0; m<boardDirect->GetNTouch(); ++m) {
		boardDirect->touchMap.push_back((int)allBoards.touchMap.size());
		allBoards.touchMap.push_back(DeviceMap(-1, m));
	}

	for (int i = 0; i < NUART; ++i) {
		uart[i]->EnumerateBoard();
	}
	nTargetMin = boardDirect->GetNTarget();
	nBoard = 1;
	for (int i = 0; i < NUART; ++i) {
		nBoard += (int)uart[i]->boards.size();
		for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
			int nt = uart[i]->boards[j]->GetNTarget();
			nTargetMin = nt < nTargetMin ? nt : nTargetMin;
		}
	}
}

bool AllBoards::HasRet(unsigned short id){
	if (boardDirect->retPacketLen[id]) return true;
	for (int i = 0; i < NUART; ++i) {
		for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
			if (uart[i]->boards[j]->retPacketLen[id]) return true;
		}
	}
	return false;
}

void AllBoards::WriteCmd(unsigned short commandId, BoardCmdBase& packet) {
	ESP_LOGV(Tag(), "WriteCmd() cmd=%d\r\n", commandId);
	//	Copy UDP command to the command buffers of each borad;
	boardDirect->WriteCmd(commandId, packet);
	for (int i = 0; i < NUART; ++i) {
		for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
			uart[i]->boards[j]->WriteCmd(commandId, packet);
		}
	}
	//	send command to borads via uart;
	for (int i = 0; i < NUART; ++i) {
		uart[i]->SendUart();
	}
	for (int i = 0; i < NUART; ++i) {
		uart[i]->RecvUart();
	}
}
inline void readAndGetMinMax(bool bFirst, BoardBase* board, unsigned short commandId, 
	BoardRetBase& packet, unsigned char& tcrMin, unsigned char& tcrMax, unsigned short& tickMin, unsigned short& tickMax){
	board->ReadRet(commandId, packet);
	if (bFirst){
		tcrMin = tcrMax = board->GetTargetCountRead();
		tickMin = tickMax = board->GetTick();
	}else{
		unsigned char tcr = board->GetTargetCountRead();
		if (tcr - tcrMin < 0) tcrMin = tcr;
		if (tcr - tcrMax > 0) tcrMax = tcr;
		unsigned short tick = board->GetTick();
		if (tick - tickMin < 0) tickMin = tick;
		if (tick - tickMax > 0) tickMax = tick;
	}
}
void AllBoards::ReadRet(unsigned short commandId, BoardRetBase& packet){
	if (commandId == CI_INTERPOLATE || commandId == CI_FORCE_CONTROL) {
		unsigned char tcrMin, tcrMax;
		unsigned short tickMin, tickMax;
		readAndGetMinMax(true, boardDirect, commandId, packet, tcrMin, tcrMax, tickMin, tickMax);
		for (int i = 0; i < NUART; ++i) {
			for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
				readAndGetMinMax(false, uart[i]->boards[j], commandId, packet, tcrMin, tcrMax, tickMin, tickMax);
			}
		}
		packet.SetTargetCountReadMin(tcrMin);
		packet.SetTargetCountReadMax(tcrMax);
		packet.SetTickMin(tickMin);
		packet.SetTickMax(tickMax);
		ESP_LOGV(Tag(), "ReadRet(): Cor:%d--%d", (int)tcrMin, (int) tcrMax);
	}else{
		boardDirect->ReadRet(commandId, packet);
		for (int i = 0; i < NUART; ++i) {
			for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
				uart[i]->boards[j]->ReadRet(commandId, packet);
			}
		}		
	}
}

