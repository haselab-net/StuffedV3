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

RobotState::RobotState(){
	nTargetMin = 0;
	mode = CM_DIRECT;
}
RobotCommand::RobotCommand(){
	mode = CM_SKIP;
}


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
#if UDP_UART_ASYNC
static void execLoop(void* arg){
	((AllBoards*)arg)->ExecLoop();
}
#endif
void AllBoards::ExecLoop(){
	bool& bDebug = UartForBoards::bDebug;
	while (1){
		if (udpCom.recvs.ReadAvail()) {	//	if receive packet from udp
			UdpCmdPacket* recv = &udpCom.recvs.Peek();
			if (bDebug) ESP_LOGI("AllBoards::ExecLoop", "command %d received.", recv->command);
			if (CI_BOARD_INFO < recv->command && recv->command < CI_NCOMMAND) {
				//	send packet to allBoards
				if (bDebug) ESP_LOGI("AllBoards::ExecLoop", "write cmd %d.", recv->command);
				allBoards.WriteCmd(recv->command, *recv);
				udpCom.PrepareRetPacket(*recv);
				if (HasRet(recv->command)){
					ReadRet(recv->command, udpCom.send);
					ReadRet(recv->command, state);
					if (bDebug) ESP_LOGI("AllBoards::ExecLoop", "read ret %d.", recv->command);
				}
				udpCom.SendReturn(*recv);
			}
			else {
				udpCom.ExecUdpCommand(*recv);
			}
			udpCom.recvs.Read();
		}else{
			static int count = 0;
			count ++;
			if (!bDebug || count > 1000){
				count = 0;
				static int last;
				last = state.position[3];
				WriteCmd(CI_ALL, command);
				command.mode = CM_SKIP;
				ReadRet(CI_ALL, state);
				int diff = state.position[3] - last;
				if (diff < 0) diff = -diff;
				if (diff > 100){
					ESP_LOGW("AllBoards", "M3 diff=%d pos=%d last=%d", diff, state.position[3], last);
				}
			}
		}
		//vTaskDelay(4);
		//vTaskDelay(100);	//	When PIC is heavy this delay give time to PIC  
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
	#if UDP_UART_ASYNC
	xTaskCreate(execLoop, "ExecLoop", 8 * 1024, this, tskIDLE_PRIORITY, &taskExec);
#endif
}
void AllBoards::EnumerateBoard() {
	motorMap.clear();
	currentMap.clear();
	forceMap.clear();
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

	for (int i = 0; i < NUART; ++i) {
		uart[i]->EnumerateBoard();
	}
	state.nTargetMin = boardDirect->GetNTarget();
	nBoard = 1;
	for (int i = 0; i < NUART; ++i) {
		nBoard += (int)uart[i]->boards.size();
		for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
			int nt = uart[i]->boards[j]->GetNTarget();
			state.nTargetMin = nt < state.nTargetMin ? nt : state.nTargetMin;
		}
	}
	state.position.resize(motorMap.size());
	state.velocity.resize(motorMap.size());
	state.current.resize(currentMap.size());
	state.force.resize(forceMap.size());
	command.forceControlJacobian.resize(forceMap.size() * 3);
	command.targetPosition.resize(motorMap.size());
	command.targetVelocity.resize(motorMap.size());
	command.torqueMin.resize(motorMap.size());
	command.torqueMax.resize(motorMap.size());
	command.controlK.resize(motorMap.size());
	command.controlB.resize(motorMap.size());
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
	if (UartForBoards::bDebug) ESP_LOGI("AllBorads::WriteCmd", "cmd=%d\r\n", commandId);
	//	Update state based on packet
	if (commandId == CI_INTERPOLATE){
		state.targetCountWrite = (unsigned char)packet.GetTargetCount();
		state.mode = CM_INTERPOLATE;
	}else if(commandId == CI_FORCE_CONTROL){
		state.targetCountWrite = (unsigned char)packet.GetTargetCount();
		state.mode = CM_FORCE_CONTROL;
	}else if(commandId == CI_DIRECT){
		state.mode = CM_DIRECT;
	}else if(commandId == CI_CURRENT){
		state.mode = CM_CURRENT;
	}
	//	Write command to borads via uart;
	boardDirect->WriteCmd(commandId, packet);
	for (int i = 0; i < NUART; ++i) {
		for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
			uart[i]->boards[j]->WriteCmd(commandId, packet);
		}
	}
	for (int i = 0; i < NUART; ++i) {
		uart[i]->SendUart();
	}
	for (int i = 0; i < NUART; ++i) {
		uart[i]->RecvUart();
	}
}
inline void readAndGetMinMax(BoardBase* board, unsigned short commandId, 
	BoardRetBase& packet, RobotState& state,
	int& diffMin, int& diffMax, unsigned short& tickMin, unsigned short& tickMax){
	board->ReadRet(commandId, packet);
	int diff = ((int)state.targetCountWrite - (int)board->GetTargetCountOfRead() + 0x100) & 0xFF;
	if (diff < diffMin) diffMin = diff;
	if (diff > diffMax) diffMax = diff;
	unsigned short tick = board->GetTick();
	if (tick < tickMin) tickMin = tick;
	if (tick > tickMax) tickMax = tick;
}
void AllBoards::ReadRet(unsigned short commandId, BoardRetBase& packet){
	if (commandId == CI_INTERPOLATE || commandId == CI_FORCE_CONTROL) {
		int diffMin = 0x100;
		int diffMax = -0x100;
		unsigned short tickMin = 0xFFFF;
		unsigned short tickMax = 0;
		int countOfRead[20];
		int nCoR = 0;
		memset(countOfRead, 0, sizeof(countOfRead));

		readAndGetMinMax(boardDirect, commandId, packet, state, diffMin, diffMax, tickMin, tickMax);
		countOfRead[nCoR++] = (int)boardDirect->GetTargetCountOfRead();
		for (int i = 0; i < NUART; ++i) {
			for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
				readAndGetMinMax(uart[i]->boards[j], commandId, packet, state, diffMin, diffMax, tickMin, tickMax);
				countOfRead[nCoR++] = (int)uart[i]->boards[j]->GetTargetCountOfRead();
			}
		}		
		state.targetCountReadMax = state.targetCountWrite - diffMin;
		state.nTargetVacancy = state.nTargetMin - diffMax;
		state.nTargetRemain = diffMin;
		if (tickMax - tickMin > 0x7FFF){
			unsigned short temp = tickMin;
			tickMin = tickMax;
			tickMax = temp;
		}
#if 0
		ESP_LOGI("TGT", "remain:%d vac:%d cor%d %d %d  cow%d  diff%d",
			 (int)state.nTargetRemain, (int)state.nTargetVacancy, countOfRead[0], countOfRead[1], countOfRead[2], state.targetCountWrite
			 , diffMax);
#endif
		packet.SetTargetCountRead(state.targetCountReadMax);
		packet.SetTickMin(tickMin);
		packet.SetTickMax(tickMax);
		packet.SetNTargetRemain(state.nTargetRemain);
		packet.SetNTargetVacancy(state.nTargetVacancy);
	}else{
		boardDirect->ReadRet(commandId, packet);
		for (int i = 0; i < NUART; ++i) {
			for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
				uart[i]->boards[j]->ReadRet(commandId, packet);
			}
		}		
	}
}

