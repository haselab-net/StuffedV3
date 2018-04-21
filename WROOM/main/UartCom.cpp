#include "UartCom.h"
#include "UdpCom.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"

static const char* Tag = "Uart";

void uartEvent(void* a){
    uart_event_t event;
	Uart* u = (Uart*)a;
    for(;;) {
        //Waiting for UART event.
        if(xQueueReceive(u->eventQueue, (void *)&event, (portTickType)portMAX_DELAY)) {
			ESP_LOGI(Tag, "Event %x, Size %d", event.type, event.size);
			u->Event(event);
		}
	}
} 
void Uart::Init(uart_config_t conf, int rxPin, int txPin){
	uart_param_config(port, &conf);
	uart_set_pin(port, txPin, rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	uart_driver_install(port, 256, 256, 20, &eventQueue, 0);
}
void Uart::EventStart(){
#if 0
	/*
	UART_TX_DONE_INT: Triggered when the transmitter has sent out all FIFO data.
	UART_TXFIFO_EMPTY_INT: Triggered when the amount of data in the transmit-FIFO is less
	 than what tx_mem_cnttxfifo_cnt specifies.
	UART_RXFIFO_FULL_INT: Triggered when the receiver gets more data than 
	 what (rx_flow_thrhd_h3, rx_flow_thrhd) specifies.	*/
	uart_intr_config_t cfg={
	/*!< UART interrupt enable mask, choose from UART_XXXX_INT_ENA_M under UART_INT_ENA_REG(i), connect with bit-or operator*/
    	.intr_enable_mask = UART_TX_DONE_INT_ENA_M | UART_TXFIFO_EMPTY_INT_ENA_M | UART_RXFIFO_FULL_INT_CLR_M,
		.rx_timeout_thresh = 10,
    	.txfifo_empty_intr_thresh = 20,	//	200kHz/20 = 10kHz, UART_FIFO_LEN=128
    	.rxfifo_full_thresh = 1,
	};
	uart_intr_config(port, &cfg);
#endif
	uart_enable_rx_intr(port);
	uart_enable_tx_intr(port, 1, 20);
	xTaskCreate(uartEvent, "UartEvent", 8*1024, this, 12, NULL);
}

void Uart::Event(uart_event_t& ev){
	switch(ev.type){
		case UART_DATA:              /*!< UART data event*/
			Loop();
		break;
		default:
		ESP_LOGE(Tag, "Unexpected event type %x occured.", ev.type);
		break;
	}
}
void Uart::RecvTask(){
	while(1){
		ulTaskNotifyTake(, portMAX_DELAY);	//	given when udp sent.
		for (retCur.board=0; retCur.board < boards.size(); retCur.board++) {
			//	read 1 byte tentatively. this blocks the thread.
			uart_read_bytes(port, boards[0]->RetStart()+retCur.cur, 1, portMAX_DELAY);
			//	receive rest.
			uart_read_bytes(port, boards[retCur.board]->RetStart()+retCur.cur,
				boards[retCur.board]->RetLen()-1, portMAX_DELAY);
			//	read 1 byte from the next board
			uart_read_bytes(port, boards[retCur.board+1]->RetStart()+retCur.cur, 1, portMAX_DELAY);
			xTaskNotifyGive(taskSend);		//	notify to send to next borad.
		}
	}
}
void Uart::SendTask(){
	while(1){
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);	//	given by ExecCmd
		for(cmdCur.board=0; cmdCur.board<boards.size(); cmdCur.board++){
			int retLen = boards[cmdCur.board]->RetLenForCommand();
			if (retLen != 0){
				//	if command has return packet, wait return before sending command for the next board.
				ulTaskNotifyTake(, portMAX_DELAY);
			}
			uart_write_bytes(port, (char*)boards[cmdCur.board]->CmdStart(),
				(size_t)boards[cmdCur.board]->CmdLen());
		}
	}
}
void Uart::Loop() {
	//	receive first
	size_t rxLen;
	uart_get_buffered_data_len(port, &rxLen);
	while (rxLen && retCur.board < boards.size()) {
#if 1
		ESP_LOGI(Tag, "rx%d B%dR%d %d \n", rxLen, retCur.board, retCur.cur, boards[retCur.board]->RetStart()[retCur.cur]);
#endif
		rxLen -= uart_read_bytes(port, boards[retCur.board]->RetStart()+retCur.cur, 1, 0);
		retCur.cur++;
		if (retCur.cur == boards[retCur.board]->RetLen()) {
			retCur.cur = 0;
			retCur.board++;
		}
	}
	//	then send
	if (cmdCur.board < boards.size()) {
		int retLen = boards[cmdCur.board]->RetLenForCommand();
		if (retLen == 0 || cmdCur.board <= retCur.board) {
			//	if command has return packet, wait return before sending command for the next board.
			//	otherwise
			cmdCur.cur += uart_write_bytes(port, (char*)boards[cmdCur.board]->CmdStart()+cmdCur.cur,
			 	(size_t)boards[cmdCur.board]->CmdLen() - cmdCur.cur);
			if (cmdCur.cur == boards[cmdCur.board]->CmdLen()) {
				cmdCur.cur = 0;
				cmdCur.board++;
			}
		}
		else {
			printf("Wait c: %d-%d r:%d-%d rl%d\r\n",cmdCur.board, cmdCur.cur, 
				retCur.board, retCur.cur, boards[retCur.board]->RetLenForCommand());
		}
	}
}

void Uart::EnumerateBoard(Uarts* uarts) {
	boards.clear();
	CommandPacketBD0 cmd;
	ReturnPacketBD0 ret;
	for (int i = 0; i <= MAXBOARDID; ++i) {
		printf("Enumerate borad on uart #%d.", i);
		cmd.commandId = CI_BOARD_INFO;
		cmd.boardId = i;
		uart_flush_input(port);	//	clear input buffer
		uart_write_bytes(port, (char*)cmd.bytes, BD0_CLEN_BOARD_INFO);	//	send board info command
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
	cmdCur.cur = 0;
	retCur.board = 0;
	retCur.cur = 0;
	//	set command length for all boards
	for (int i = 0; i < boards.size(); ++i) {
		printf("Board %d CLEN:", boards[i]->GetBoardId());
		for (int c = 0; c < CI_NCOMMAND; ++c) {
			cmd.cmdLen.len[c] = boards[i]->cmdPacketLen[c];
			printf(" %d", (int) boards[i]->cmdPacketLen[c]);
		}
		printf("\n");
		cmd.commandId = CI_SET_CMDLEN;
		cmd.boardId = boards[i]->GetBoardId();
		uart_flush_input(port);												//	clear input buffer
		uart_write_bytes(port, (char*)cmd.bytes, BD0_CLEN_SET_CMDLEN);		//	send board info command
	}
}
void Uarts::EnumerateBoard() {
	motorMap.clear();
	forceMap.clear();
	for (int i = 0; i < NUART; ++i) {
		uart[i]->EnumerateBoard(this);
	}
#ifdef DEBUG
	Serial.print("Motors:");
	for (int i = 0; i<motorMap.size(); ++i){
		Serial.print(" ");
		Serial.print(motorMap[i].board);
		Serial.print("-");
		Serial.print(motorMap[i].id);
	}
	Serial.println();
	for (int i = 0; i < NUART; ++i) {
		for (int j = 0; j < uart[i]->boards.size(); ++j) {
			Serial.print("U");
			Serial.print(i);
			Serial.print("B");
			Serial.print(j);
			Serial.print(" =");
			for(int k=0; k< uart[i]->boards[j]->motorMap.size(); ++k){
				Serial.print(" ");
				Serial.print(uart[i]->boards[j]->motorMap[k]);
			}
			Serial.println();
		}
	}
#endif
	nTargetMin = 0xFFFF;
	nBoard = 0;
	for (int i = 0; i < NUART; ++i) {
		nBoard += uart[i]->boards.size();
		for (int j = 0; j < uart[i]->boards.size(); ++j) {
			int nt = uart[i]->boards[j]->GetNTarget();
			nTargetMin = nt < nTargetMin ? nt : nTargetMin;
		}
	}
}
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
	uart[0]->Init(uconf, 32, 33); // pin must be changed. IO6-11 are reserved. (RX=32 Yellow, TX=33 Green)
	printf(".");
	uart[1]->Init(uconf, 16, 17);
	printf(". done.\n");
	EnumerateBoard();
	uart[0]->EventStart();
	uart[1]->EventStart();
}

Uarts uarts;
Uart uart1(UART_NUM_1);
Uart uart2(UART_NUM_2);
Uarts::Uarts(){
	uart[0] = &uart1;
	uart[1] = &uart2;
	nBoard = 0;
	nTargetMin = 0;
}
void Uarts::WriteCmd(UdpCmdPacket& packet) {
	for (int i = 0; i < NUART; ++i) {
		for (int j = 0; j < uart[i]->boards.size(); ++j) {
			uart[i]->boards[j]->WriteCmd(packet);
		}
	}
	returnIp = packet.returnIp;
}
void Uarts::ReadRet(UdpRetPacket& packet){
	for (int i = 0; i < NUART; ++i) {
		for (int j = 0; j < uart[i]->boards.size(); ++j) {
			uart[i]->boards[j]->ReadRet(packet);
		}
	}
	if (packet.command == CI_INTERPOLATE || packet.command == CI_FORCE_CONTROL) {
		nTargetVacancy = packet.GetVacancy();
	}
}
