#pragma once
#include "UdpCom.h"


class IpCom: public UdpCom {
public:
	const int tcpPort = 9091;
	void Init();
	void Start();
	void OnReceiveTcp(struct udp_pcb * upcb, struct pbuf * p, const ip_addr_t* addr, u16_t port);
#if !UDP_UART_ASYNC
	void ExecCommandLoop();
#endif
	void PrepareRetPacket(int cmd);
	void SendRetPacket(ip_addr_t& returnIp);
	void ExecUdpCommand(UdpCmdPacket& recv);
};
extern UdpCom udpCom;
