#include "VCEdit.h"
#include "UdpCom.h"
#include "UartCom.h"
#include "command.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event_loop.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/udp.h"
#include "esp_system.h"
#include "esp_wifi.h"

#include <algorithm>
#include <string.h>


UdpCom udpCom;


int UdpCmdPacket::CommandLen() {
	switch (command)
	{
	case CI_BOARD_INFO: return 3 * 2;								//	model nTarget nMotor nForce
	case CI_DIRECT: return (3 + uarts.GetNTotalMotor() * 2) * 2;	//	vel pos
	case CI_INTERPOLATE: return (3 + uarts.GetNTotalMotor() + 1) * 2;	//	pos period
	case CI_FORCE_CONTROL: return (3 + uarts.GetNTotalMotor() + uarts.GetNTotalForce()*3 + 1) * 2;	//	pos period
	case CI_PDPARAM: return (3 + uarts.GetNTotalMotor() * 2) * 2;	//  K B.
	case CI_TORQUE_LIMIT: return (3 + uarts.GetNTotalMotor() * 2) * 2;		//  min max.
	case CI_SENSOR: return (1 + uarts.GetNTotalMotor() + uarts.GetNTotalForce()) * 2;
	case CIU_TEXT:	return (3 + 1 + 1) * 2 + data[1];		//	return text message: cmd, type, len, bytes
	case CIU_SET_IPADDRESS:	return 3 * 2;					//  Set ip address to return the packet
	case CIU_GET_IPADDRESS: return 3 * 2;					//  Get ip address to return the packet
	}
	return 0;
}
void UdpRetPacket::SetLength() {	//	length in short (per 2bytes)
	switch (command)
	{
	case CI_BOARD_INFO: length = (3 + 4) * 2; break;							//	model nTarget nMotor nForce
	case CI_DIRECT: length = (3 + uarts.GetNTotalMotor() * 2) * 2; break;		//	vel pos
	case CI_INTERPOLATE: length = (3 + uarts.GetNTotalMotor() + 3) * 2; break;	//	pos vacancy avail tick
	case CI_FORCE_CONTROL: length = (3 + uarts.GetNTotalMotor() + 3) * 2; break;	//	pos vacancy avail tick
	case CI_SENSOR: length = (1 + uarts.GetNTotalMotor() + uarts.GetNTotalForce()) * 2; break;
	case CIU_TEXT:	length = (3 + 1 + 1) * 2 + data[1]; break;	//	return text message: cmd, type, length, bytes
	case CIU_GET_IPADDRESS: length = (3 + 16) * 2; break;		//  Get ip address to return the packet
	default:
		length = 3 * 2;											//	Ack
		break;
	}
}
void UdpRetPacket::ClearData() {
	SetLength();
	memset(data, 0, length);
}

void UdpCom::Init() {
	recvRest = 0;
	commandCount = 0;
	ConnectWifi();
}

void UdpCom::OnReceive(struct udp_pcb * upcb, struct pbuf * top,
	ip_addr_t* addr, u16_t port) {
	if (!recvs.WriteAvail()){
		printf("Udp recv buffer full.\n");
		pbuf_free(top);
		return;
	}
	struct pbuf* p = top;
	int readLen = 0; 
	int cur = 0;
	int cmdLen = UdpPacket::HEADERLEN;
	UdpCmdPacket& recv = recvs.Poke();
	while(1){
		int l = p->len - cur;
		if (l > cmdLen-readLen) l = cmdLen-readLen;
		memcpy(recv.bytes + readLen, ((char*)p->payload)+cur, l);
		readLen += l;
		cur += l;
		if (readLen == cmdLen){
			if (cmdLen == UdpPacket::HEADERLEN){
				cmdLen = recv.CommandLen();
#ifdef DEBUG
				printf("L=%d Cm=%d Ct=%d", recv.length, recv.command, recv.count);
#endif
			}
			if (readLen == cmdLen){
				recv.returnIp = *addr;
				if (recv.length != cmdLen) {
					printf("cmdLen %d != recvLen %d\n", cmdLen, recv.length);
				}
				if (recv.command == CIU_GET_IPADDRESS) {
					recvs.Write();
				}
				else if (recv.count == commandCount + 1) {		// check and update counter
					recvs.Write();
					commandCount++;
				}
				else {
					printf(" ignore %d", recv.count);
				}
				if (!recvs.WriteAvail()){
					printf("Udp recv buffer full.\n");
					pbuf_free(top);
					return;
				}
				recv = recvs.Poke();
				readLen = 0;
			}
		}
		if (p->len == cur){
			if (p->len != p->tot_len){
				p = p->next;
				cur = 0;
			}else{
				break;
			}
		}
	}
	pbuf_free(top);
}

void UdpCom::ExecCommand(){
	if (recvs.ReadAvail()) {
		UdpCmdPacket& recv = recvs.Peek();
		if (CI_BOARD_INFO < recv.command && recv.command < CI_NCOMMAND) {
			if (uarts.IsIdle()) {
				uarts.WriteCmd(recv);
				if (!uarts.StartCmd()) {
					PrepareRetPacket(recv.command);
					SendRetPacket(recv.returnIp);
				}
				recvs.Read();
			}
		}
		else {
			ExecUdpCommand(recvs.Peek());
			recvs.Read();
		}
	}
	if (uarts.RetReady()) {	//	Send udp packet when uarts ready
		printf("URet");
		PrepareRetPacket(uarts.RetCommand());
		uarts.ReadRet(send);
		uarts.RetEnd();		//	release uarts
		SendRetPacket(uarts.returnIp);
	}
}

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
	struct pbuf pb;
	pb.len = pb.tot_len = send.length;
	pb.payload = send.bytes;
	udp_sendto(udp, &pb, &ownerIp, port);
	printf("Ret%d C%d L%d\n", send.command, send.count, send.length);
}
void UdpCom::PrepareRetPacket(int cmd) {
	send.command = cmd;
	send.count = commandCount;
	send.SetLength();
	send.ClearData();
	if (cmd == CI_INTERPOLATE || cmd == CI_FORCE_CONTROL) {
		send.InitInterpolate();
	}

}
void UdpCom::SendRetPacket(ip_addr_t& returnIp) {
	pbuf pb;
	pb.len = pb.tot_len = send.length;
	pb.payload = send.bytes;
	udp_sendto(udp, &pb, &returnIp, port);
	printf("Ret%d C%d L%d\n", send.command, send.count, send.length);
}
void UdpCom::ExecUdpCommand(UdpCmdPacket& recv) {
	switch (recv.command)
	{
	case CI_BOARD_INFO: 
		PrepareRetPacket(recv.command);
		send.SetBoardInfo(uarts.GetSystemId(), uarts.GetNTarget(), uarts.GetNTotalMotor(), uarts.GetNTotalForce());
		SendRetPacket(recv.returnIp);
		break;
	case CIU_SET_IPADDRESS:
		ownerIp = recv.returnIp;
		PrepareRetPacket(recv.command);
		SendRetPacket(recv.returnIp);
		break;
	case CIU_GET_IPADDRESS:
		PrepareRetPacket(recv.command);
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
#ifdef DEBUG
		printf("GetIPAddress send to ");
		Serial.print(recv.returnIp);
		Serial.print("  ");
		Serial.print(port);
		Serial.print(" Len:");
		Serial.print(send.length);
		Serial.println(".");
		Serial.println();
#endif
		SendRetPacket(recv.returnIp);
		break;
	default:
		printf("Invalid command %d count %d received.\n", send.command, send.count);
		break;
	}
}

static char* mac2Str(uint8_t* m){
	static char buf[256];
	sprintf(buf, "%02x%02x %02x%02x %02x%02x", MAC2STR(m));
	return buf;
}

static const char *TAG = "Wifi";
/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t wifi_event_group;
const int WIFI_CONNECTED_BIT = BIT0;

static esp_err_t onWifiEvent(void *ctx, system_event_t *event){
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "station:'%s' join, AID=%d",
                 mac2Str(event->event_info.sta_connected.mac),
                 event->event_info.sta_connected.aid);
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        {
			ESP_LOGI(TAG, "station:'%s'leave, AID=%d",
                 mac2Str(event->event_info.sta_disconnected.mac),
                 event->event_info.sta_disconnected.aid);
		}
		break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;	
}

void UdpCom::ConnectWifi() {
    wifi_event_group = xEventGroupCreate();
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(onWifiEvent, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config;
	strcpy((char*)wifi_config.sta.ssid, "hasefone");
	strcpy((char*)wifi_config.sta.password, "hasevr@gmail.com");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:%s password:%s",
             wifi_config.sta.ssid, wifi_config.sta.password);
}
