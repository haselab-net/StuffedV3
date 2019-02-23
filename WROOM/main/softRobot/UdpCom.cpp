#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event_loop.h"
#include "esp_log.h"

#include "lwip/opt.h"
#include "lwip/tcpip.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#ifndef _WIN32
#include "esp_system.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#endif

#include <algorithm>
#include <string.h>

#include "AllBoards.h"
#include "UdpCom.h"
#include "UartForBoards.h"
#include "CommandWROOM.h"


UdpCom udpCom;
bool UdpCom::bDebug = false;

static const char* Tag = "UdpCom";

static const int NHEADER = UdpPacket::HEADERLEN/2;
int UdpCmdPacket::CommandLen() {
	switch (command)
	{
	case CI_BOARD_INFO:		//	
		return NHEADER * 2;
	//	case CI_SET_CMDLEN is only for uart
	case CI_ALL:			// direct/interpolate/forceControl + mode 
	 	return (NHEADER + allBoards.GetNTotalMotor()*3 + 2 + 1) * 2; 
	case CI_SENSOR:			//	
		return NHEADER * 2;
	case CI_DIRECT:			//	pos vel
		return (NHEADER + allBoards.GetNTotalMotor() * 2) * 2;
	case CI_INTERPOLATE: 	//	pos period targetCount
		return (NHEADER + allBoards.GetNTotalMotor() + 2) * 2;
	case CI_FORCE_CONTROL: 	//	pos JK period targetCount
		return (NHEADER + allBoards.GetNTotalMotor() + allBoards.GetNTotalForce()*3 + 2) * 2;	
	case CI_PDPARAM: 		//	K B
		return (NHEADER + allBoards.GetNTotalMotor() * 2) * 2;
	case CI_TORQUE_LIMIT:	//  min max.
		return (NHEADER + allBoards.GetNTotalMotor() * 2) * 2;
	case CI_RESET_SENSOR:
		return (NHEADER + 1) * 2;	//	flags
	case CIU_SET_IPADDRESS:	//  Set ip address to return the packet: command only
		return NHEADER * 2;
	case CIU_GET_IPADDRESS:	//  Get ip address to return the packet: command only
		return NHEADER * 2;
	}
	return 0;
}
void UdpRetPacket::SetLength() {
	switch (command){
	case CI_BOARD_INFO:		//	model nTarget nMotor nCurrent nForce macAddress
		length = (NHEADER + 5) * 2 + 6; break;
	//	case CI_SET_CMDLEN is only for uart
	case CI_ALL:			//	pos vel current force
		length = (NHEADER + allBoards.GetNTotalMotor()*2 + allBoards.GetNTotalCurrent() + allBoards.GetNTotalForce()) * 2; break;
	break;
	case CI_SENSOR:			//	pos force
		length = (NHEADER + allBoards.GetNTotalMotor() + allBoards.GetNTotalCurrent() + allBoards.GetNTotalForce()) * 2; break;
	case CI_DIRECT:			//	pos vel
		length = (NHEADER + allBoards.GetNTotalMotor() * 2) * 2; break;
	case CI_INTERPOLATE:	//	pos targetCountRead tickMin tickMax remain vacancy
	case CI_FORCE_CONTROL: 
		length = (NHEADER + allBoards.GetNTotalMotor() + 5) * 2; break;
	case CI_PDPARAM:
	case CI_TORQUE_LIMIT:
	case CI_RESET_SENSOR:
		length = NHEADER*2; break;
	case CIU_TEXT:			//	return text message: cmd, type, length, bytes
		length = (NHEADER + 1 + 1) * 2 + data[1]; break;
	case CIU_SET_IPADDRESS:	//  Set ip address to return the packet
		length = NHEADER * 2; break;
	case CIU_GET_IPADDRESS:	//  Get ip address to return the packet
		length = (NHEADER + 16) * 2; break;
	default:				//	error
		ESP_LOGE("UdpRetPacket", "Undefined command %d set lentgh to 0", command);
		length = 0;
		break;
	}
}
void UdpRetPacket::ClearData() {
	SetLength();
	memset(data, 0, length);
}

UdpCmdPackets::UdpCmdPackets() {
	mutex = xSemaphoreCreateMutex();
}
void UdpCmdPackets::Lock() {
	xSemaphoreTake(mutex, portMAX_DELAY);
}
void UdpCmdPackets::Unlock() {
	xSemaphoreGive(mutex);
}

static void onReceiveUdp(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	((UdpCom*)arg)->OnReceiveUdp(pcb, p, addr, port);
}
#if !UDP_UART_ASYNC
static void execCommand(void* udpCom){
	((UdpCom*) udpCom)->ExecCommandLoop();
}
#endif
void UdpCom::Init() {
	udp = NULL;
	recvRest = 0;
	commandCount = 0;
	sendStart = sendLast = NULL;
	sendLen = 0;
	#if !UDP_UART_ASYNC
    xTaskCreate(execCommand, "ExeCmd", 8*1024, &udpCom, tskIDLE_PRIORITY, &taskExeCmd);
	#endif
}
void UdpCom::Start(){
	udp_init();
	if (udp) udp_remove(udp);
	udp = udp_new();
	udp_bind(udp, (ip_addr_t*)IP4_ADDR_ANY, port);
	udp_recv(udp, onReceiveUdp, this);
}

void UdpCom::OnReceiveUdp(struct udp_pcb * upcb, struct pbuf * top, const ip_addr_t* addr, u16_t port) {
	if (!recvs.WriteAvail()) {
		ESP_LOGE("UdpCom::OnReceiveUdp", "Udp command receive buffer is full.");
		pbuf_free(top);
		return;
	}
	//	 read buffer and put it on recvs.
	struct pbuf* p = top;
	int readLen = 0;
	int cur = 0;
	int cmdLen = UdpPacket::HEADERLEN;

	recvs.Lock();
	UdpCmdPacket* recv = &recvs.Poke();
	int countDiffMax = 0;
	while (1) {
		int l = p->len - cur;
		if (l > cmdLen - readLen) l = cmdLen - readLen;
		memcpy(recv->bytes + readLen, ((char*)p->payload) + cur, l);
		readLen += l;
		cur += l;
		if (readLen == cmdLen) {
			if (cmdLen == UdpPacket::HEADERLEN) {
				cmdLen = recv->CommandLen();
				if (bDebug) {
					ESP_LOGI(Tag, "L=%d Cm=%d Ct=%d received from %s.\n", recv->length, recv->command, recv->count, ipaddr_ntoa(addr));
				}
}
			if (readLen == cmdLen) {
				recv->returnIp = *addr;
				if (recv->length != cmdLen - 2) {
					ESP_LOGE(Tag, "cmdLen %d != recvLen %d - 2 in cmd:%d \n", cmdLen, recv->length, recv->command);
				}
				if (recv->command == CIU_GET_IPADDRESS) {
					recvs.Write();
#if !UDP_UART_ASYNC
					xTaskNotifyGive(taskExeCmd);
#endif
				}
#if 1			//	check command counter exactly.
				else if (recv->count == commandCount + 1) {		// check and update counter
					commandCount++;
#else			//	Only check received command counter > last command counter.
				//				else if (short(recv->count - commandCount) > 0) {		// check and update counter
				else if (1) {
					commandCount = recv->count;
#endif
					recvs.Write();
#if !UDP_UART_ASYNC
					xTaskNotifyGive(taskExeCmd);
#endif
					if (countDiffMax > 0) {
						ESP_LOGI(Tag, "ignored %d packets Ct:%d Cm:%d", countDiffMax, commandCount, recv->command);
						countDiffMax = 0;
					}
				}
				else {
					int diff = (short)((short)commandCount - (short)recv->count);
					if (countDiffMax < diff) countDiffMax = diff;
					//	Command count is not matched. There was some packet losses or delay. 
					//ESP_LOGI(Tag, "ignore Ct:%d<%d Cm:%d\n", recv->count, commandCount+1, recv->command);
					//ESP_LOGI(Tag, "ignore %d packets Ct:%d Cm:%d", countDiffMax, commandCount+1, recv->command);
				}
				if (!recvs.WriteAvail()) {
					ESP_LOGE(Tag, "Udp recv buffer full.\n");
					pbuf_free(top);
					recvs.Unlock();
					return;
				}
				recv = &recvs.Poke();
				cmdLen = UdpPacket::HEADERLEN;
				readLen = 0;
				}
			}
		if (p->len == cur) {
			if (p->len != p->tot_len) {
				p = p->next;
				cur = 0;
			}
			else {
				break;
			}
		}
	}
	recvs.Unlock();
	pbuf_free(top);
}
void UdpCom::OnReceiveServer(void* payload, int len) {
	if (!recvs.WriteAvail()) {
		ESP_LOGE("UdpCom::OnReceiveServer", "Udp command receive buffer is full.");
		return;
	}
	recvs.Lock();
	UdpCmdPacket* recv = &recvs.Poke();
	memcpy(recv->bytes + 2, payload, len);
	recv->count = commandCount;
	recvs.Write();
	recvs.Unlock();
}

#if !UDP_UART_ASYNC
void UdpCom::ExecCommandLoop(){
    while(1){
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		while (recvs.ReadAvail()) {
			UdpCmdPacket* recv = &recvs.Peek();
			if (CI_BOARD_INFO < recv->command && recv->command < CI_NCOMMAND) {
				//	send packet to allBoards
				allBoards.WriteCmd(recv->command, *recv);
				PrepareRetPacket(recv->command);
				if (allBoards.HasRet(recv->command)){
					allBoards.ReadRet(recv->command, send);
				}
				SendRetPacket(recv->returnIp);
			}
			else {
				ExecUdpCommand(*recv);
			}
			recvs.Read();
		}
	}
}
#endif

void UdpCom::SendText(char* text, short errorlevel) {
	send.command = CIU_TEXT;
	send.count = commandCount;
	send.data[0] = errorlevel;
	int len = strlen(text);
	if (len > 1000) len = 1000;
	send.data[1] = len;
	send.SetLength();
	char* str = (char*)(send.data + 2);
	memcpy(str, text, len);
	struct pbuf* pb = pbuf_alloc(PBUF_TRANSPORT, send.length, PBUF_RAM);
    memcpy (pb->payload, send.bytes, send.length);
	udp_sendto(udp, pb, &ownerIp, port);
    pbuf_free(pb); //De-allocate packet buffer
//	ESP_LOGI(Tag, "Ret%d C%d L%d to %s\n", send.command, send.count, send.length, ipaddr_ntoa(&ownerIp));
}
void UdpCom::PrepareRetPacket(UdpCmdPacket& recv) {
	send.command = recv.command;
	send.count = commandCount;
	send.ClearData();
}
void UdpCom::SendReturn(UdpCmdPacket& recv) {
	if (recv.returnIp.u_addr.ip4.addr == 0) {
		SendReturnServer(recv);
	}
	else {
		SendReturnUdp(recv);
	}
}
void UdpCom::SendReturnServer(UdpCmdPacket& recv) {
	//	TBW		hase
}
void UdpCom::SendReturnUdp(UdpCmdPacket& recv) {
	if (!udp) return;
	static char sendBuf[1000];
	if (sendLen + send.length >= 1000){	//	UDP's MTU < 1500, but usually > 1000. 
		struct pbuf* pb = pbuf_alloc(PBUF_TRANSPORT, sendLen, PBUF_RAM);
		memcpy(pb->payload, sendBuf, sendLen);
		udp_sendto(udp, pb, &recv.returnIp, port);
    	pbuf_free(pb); //De-allocate packet buffer
		sendLen = 0;
	}
    memcpy(sendBuf+sendLen, send.bytes, send.length);
	sendLen += send.length;
	if (recvs.ReadAvail() <= 1){	//	Read() will call after sent. So 1 means no command remaining.
		struct pbuf* pb = pbuf_alloc(PBUF_TRANSPORT, sendLen, PBUF_RAM);
		memcpy(pb->payload, sendBuf, sendLen);
		udp_sendto(udp, pb, &recv.returnIp, port);
    	pbuf_free(pb); //De-allocate packet buffer
		sendLen = 0;
	}
//	ESP_LOGI(Tag, "Ret%d C%d L%d to %s\n", send.command, send.count, send.length, ipaddr_ntoa(&returnIp));
}
void UdpCom::ExecUdpCommand(UdpCmdPacket& recv) {
	switch (recv.command)
	{
	case CI_BOARD_INFO: 
		PrepareRetPacket(recv);
		send.SetBoardInfo(allBoards.GetSystemId(), allBoards.GetNTarget(), allBoards.GetNTotalMotor(), allBoards.GetNTotalCurrent(), allBoards.GetNTotalForce());
		SendReturn(recv);
		break;
	case CIU_SET_IPADDRESS:
		ownerIp = recv.returnIp;
		PrepareRetPacket(recv);
		SendReturn(recv);
		break;
	case CIU_GET_IPADDRESS:
		PrepareRetPacket(recv);
#ifndef _WIN32
		if (ownerIp.type ==IPADDR_TYPE_V4){
			send.data[0] = (ownerIp.u_addr.ip4.addr>>3*8) &0xFF;
			send.data[1] = (ownerIp.u_addr.ip4.addr>>2*8) &0xFF;
			send.data[2] = (ownerIp.u_addr.ip4.addr>>1*8) &0xFF;
			send.data[3] = ownerIp.u_addr.ip4.addr&0xFF;
		}else if (ownerIp.type ==IPADDR_TYPE_V6){
			for(int i=0; i<4; ++i){
				u32_t a = ownerIp.u_addr.ip6.addr[i];
				send.data[0+4*i] = (a>>3*8) &0xFF;
				send.data[1+4*i] = (a>>2*8) &0xFF;
				send.data[2+4*i] = (a>>1*8) &0xFF;
				send.data[3+4*i] = a&0xFF;
			}
		}
#else
		send.data[0] = (ownerIp.addr >> 3 * 8) & 0xFF;
		send.data[1] = (ownerIp.addr >> 2 * 8) & 0xFF;
		send.data[2] = (ownerIp.addr >> 1 * 8) & 0xFF;
		send.data[3] = ownerIp.addr & 0xFF;
#endif
#ifdef DEBUG
		logPrintf("GetIPAddress send to ");
		Serial.print(recv.returnIp);
		Serial.print("  ");
		Serial.print(port);
		Serial.print(" Len:");
		Serial.print(send.length);
		Serial.println(".");
		Serial.println();
#endif
		SendReturn(recv);
		break;
	default:
		ESP_LOGE(Tag, "Invalid command %d count %d received from %s at %x.\n", 
			(int)recv.command, (int)recv.count, ipaddr_ntoa(&recv.returnIp), (unsigned)&recv);
		break;
	}
}