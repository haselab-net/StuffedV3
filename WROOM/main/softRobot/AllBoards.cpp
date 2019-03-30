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
	state.touch.resize(touchMap.size());
	command.forceControlJacobian.resize(forceMap.size() * 3);
	command.targetPosition.resize(motorMap.size());
	command.targetVelocity.resize(motorMap.size());
	command.torqueMin.resize(motorMap.size());
	command.torqueMax.resize(motorMap.size());
	command.controlK.resize(motorMap.size());
	command.controlB.resize(motorMap.size());
	command.controlA.resize(motorMap.size());
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
		//ESP_LOGI("AllBoards_RecvCmd", "Peri:%d  tcw:%d", packet.GetPeriod(), packet.GetTargetCountWrite());
		if (packet.GetPeriod() > 0){
			state.targetCountWrite = (unsigned char)packet.GetTargetCountWrite();
		} 
		state.mode = CM_INTERPOLATE;
	}else if(commandId == CI_FORCE_CONTROL){
		if (packet.GetPeriod() > 0){
			state.targetCountWrite = (unsigned char)packet.GetTargetCountWrite();
		}
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
inline void readAndGetMinMax(bool bFirst, BoardBase* board, unsigned short commandId, 
	BoardRetBase& packet, RobotState& state,
	unsigned char& tcrMin, unsigned char& tcrMax, unsigned short& tickMin, unsigned short& tickMax){
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
		readAndGetMinMax(true, boardDirect, commandId, packet, state, tcrMin, tcrMax, tickMin, tickMax);
		for (int i = 0; i < NUART; ++i) {
			for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
				readAndGetMinMax(false, uart[i]->boards[j], commandId, packet, state, tcrMin, tcrMax, tickMin, tickMax);
			}
		}
		packet.SetTargetCountReadMin(tcrMin);
		packet.SetTargetCountReadMax(tcrMax);
		packet.SetTickMin(tickMin);
		packet.SetTickMax(tickMax);
		/*		
		if (&packet == &state){
			ESP_LOGI("ReadRet", "Cor:%d--%d, tcw:%d", (int)tcrMin, (int) tcrMax, state.targetCountWrite);
		}
		*/
	}else{
		boardDirect->ReadRet(commandId, packet);
		for (int i = 0; i < NUART; ++i) {
			for (int j = 0; j < (int)uart[i]->boards.size(); ++j) {
				uart[i]->boards[j]->ReadRet(commandId, packet);
			}
		}		
	}
}

