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
#include "nvs_flash.h"

#include <algorithm>
#include <string.h>


UdpCom udpCom;
static const char* Tag = "UdpCom";

static const int NHEADER = UdpPacket::HEADERLEN/2;
int UdpCmdPacket::CommandLen() {
	switch (command)
	{
	case CI_BOARD_INFO:		//	
		return NHEADER * 2;
	//	case CI_SET_CMDLEN is only for uart
	case CI_SENSOR:			//	
		 return NHEADER * 2;
	case CI_DIRECT:			//	vel pos
		return (NHEADER + uarts.GetNTotalMotor() * 2) * 2;
	case CI_INTERPOLATE: 	//	pos period targetCount
		return (NHEADER + uarts.GetNTotalMotor() + 2) * 2;
	case CI_FORCE_CONTROL: 	//	pos JK period targetCount
		return (NHEADER + uarts.GetNTotalMotor() + uarts.GetNTotalForce()*3 + 2) * 2;	
	case CI_PDPARAM: 		//	K B
		return (NHEADER + uarts.GetNTotalMotor() * 2) * 2;
	case CI_TORQUE_LIMIT:	//  min max.
		return (NHEADER + uarts.GetNTotalMotor() * 2) * 2;
	case CIU_SET_IPADDRESS:	//  Set ip address to return the packet: command only
		return NHEADER * 2;
	case CIU_GET_IPADDRESS:	//  Get ip address to return the packet: command only
		return NHEADER * 2;
	}
	return 0;
}
void UdpRetPacket::SetLength() {
	switch (command){
	case CI_BOARD_INFO:		//	model nTarget nMotor nForce
		length = (NHEADER + 4) * 2; break;
	//	case CI_SET_CMDLEN is only for uart
	case CI_SENSOR:
		length = (NHEADER + uarts.GetNTotalMotor() + uarts.GetNTotalForce()) * 2; break;
	case CI_DIRECT:			//	vel pos
		length = (NHEADER + uarts.GetNTotalMotor() * 2) * 2; break;
	case CI_INTERPOLATE:	//	pos targetCountRead tickMin tickMax remain vacancy
	case CI_FORCE_CONTROL: 
		length = (NHEADER + uarts.GetNTotalMotor() + 5) * 2; break;
	case CI_PDPARAM:
	case CI_TORQUE_LIMIT:
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

static void onReceive(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	((UdpCom*)arg)->OnReceive(pcb, p, addr, port);
}
static void execCommand(void* udpCom){
	((UdpCom*) udpCom)->ExecCommandLoop();
}
void UdpCom::Init() {
	recvRest = 0;
	commandCount = 0;
	//ConnectWifi();
    xTaskCreate(execCommand, "ExeCmd", 8*1024, &udpCom, tskIDLE_PRIORITY, &taskExeCmd);
}
void UdpCom::Start(){
	udp_init();
	if (udp) udp_remove(udp);
	udp = udp_new();
	udp_bind(udp, (ip_addr_t*)IP4_ADDR_ANY, port);
	udp_recv(udp, onReceive, this);
}
void UdpCom::OnReceive(struct udp_pcb * upcb, struct pbuf * top, const ip_addr_t* addr, u16_t port) {
	if (!recvs.WriteAvail()){
		printf("Udp recv buffer full.\n");
		pbuf_free(top);
		return;
	}
	struct pbuf* p = top;
	int readLen = 0; 
	int cur = 0;
	int cmdLen = UdpPacket::HEADERLEN;
	UdpCmdPacket* recv = &recvs.Poke();
	while(1){
		int l = p->len - cur;
		if (l > cmdLen-readLen) l = cmdLen-readLen;
		memcpy(recv->bytes + readLen, ((char*)p->payload)+cur, l);
		readLen += l;
		cur += l;
		if (readLen == cmdLen){
			if (cmdLen == UdpPacket::HEADERLEN){
				cmdLen = recv->CommandLen();
#if 0
				printf("L=%d Cm=%d Ct=%d received from %s.\n", recv->length, recv->command, recv->count, ipaddr_ntoa(addr));
#endif
			}
			if (readLen == cmdLen){
				recv->returnIp = *addr;
				if (recv->length != cmdLen) {
					ESP_LOGE(Tag, "cmdLen %d != recvLen %d\n", cmdLen, recv->length);
				}
				if (recv->command == CIU_GET_IPADDRESS) {
					recvs.Write();
					xTaskNotifyGive(taskExeCmd);
				}
				else if (recv->count == commandCount + 1) {		// check and update counter
					commandCount++;
					recvs.Write();
					xTaskNotifyGive(taskExeCmd);
				}
				else {
					ESP_LOGI(Tag, "ignore Ct:%d|%d Cm:%d\n", recv->count, commandCount, recv->command);
				}
				if (!recvs.WriteAvail()){
					ESP_LOGE(Tag, "Udp recv buffer full.\n");
					pbuf_free(top);
					return;
				}
				recv = &recvs.Poke();
				cmdLen = UdpPacket::HEADERLEN;
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

void UdpCom::ExecCommandLoop(){
    while(1){
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		while (recvs.ReadAvail()) {
			UdpCmdPacket* recv = &recvs.Peek();
			if (CI_BOARD_INFO < recv->command && recv->command < CI_NCOMMAND) {
				//	send packet to uarts
				uarts.WriteCmd(*recv);
				PrepareRetPacket(recv->command);
				if (uarts.HasRet(recv->command)){
					uarts.ReadRet(send);
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
void UdpCom::PrepareRetPacket(int cmd) {
	send.command = cmd;
	send.count = commandCount;
	send.ClearData();
}
void UdpCom::SendRetPacket(ip_addr_t& returnIp) {
	struct pbuf* pb = pbuf_alloc(PBUF_TRANSPORT, send.length, PBUF_RAM);
    memcpy (pb->payload, send.bytes, send.length);
	udp_sendto(udp, pb, &returnIp, port);
    pbuf_free(pb); //De-allocate packet buffer
//	ESP_LOGI(Tag, "Ret%d C%d L%d to %s\n", send.command, send.count, send.length, ipaddr_ntoa(&returnIp));
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
		ESP_LOGI(Tag, "Invalid command %d count %d received from %s at %x.\n", 
			(int)recv.command, (int)recv.count, ipaddr_ntoa(&recv.returnIp), (unsigned)&recv);
		break;
	}
}


#if 0
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
    ((UdpCom*)ctx)->OnWifi(event);
	return ESP_OK;	
}
void UdpCom::OnWifi(system_event_t* event){
	switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
		udp_init();
		if (udp) udp_remove(udp);
		udp = udp_new();
		udp_bind(udp, (ip_addr_t*)IP4_ADDR_ANY, port);
		udp_recv(udp, onReceive, this);
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
}

void UdpCom::ConnectWifi() {
	nvs_flash_init();
    tcpip_adapter_init();
	wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(onWifiEvent, this) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config;
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
#if 1
	strcpy((char*)wifi_config.sta.ssid, "hasefone");
	strcpy((char*)wifi_config.sta.password, "hasevr@gmail.com");
#elif 0
	strcpy((char*)wifi_config.sta.ssid, "HOME");
	strcpy((char*)wifi_config.sta.password, "2human2human2");
#else
	strcpy((char*)wifi_config.sta.ssid, "haselab_pi_G");
	strcpy((char*)wifi_config.sta.password, "2human2human2");
#endif
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:%s password:%s",
             wifi_config.sta.ssid, wifi_config.sta.password);
}
#endif
