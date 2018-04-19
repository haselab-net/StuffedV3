#pragma once

#include "VCEdit.h"
#include "ArrayRing.h"
#include "UartCom.h"
#include "esp_event_loop.h"

/**	Udp packet from PC
	Each command has sequential counter to detect packet drop.
	Counters in return packets indicate that of lastly received command packet.
	PC side keep commands until receive the counter;
	Not all commands return packet. So, PC side must send commmand with return to check the counter.
	It will be occurr when the commands in keeping buffer exceed some threshold.
*/
class UdpPacket {
public:
	enum { MAXLEN=1500, HEADERLEN=6};	//	packet/command size must smaller than 1500
	union {
		unsigned char bytes[MAXLEN];
		struct {
			unsigned short length;	//	length of this command
			unsigned short count;	//	counter to detect packet drop.
			unsigned short command;	//	command id
			short data[(MAXLEN-2*3)/2];
		}__attribute__((__packed__));
	};
	short& MotorPos(int i) {
		return data[i];
	}
	short& MotorVel(int i) {
		return data[uarts.GetNTotalMotor() + i];
	}
	short ForceControlJK(int j, int i) {	//	2 forces x 3 motors,
		int b = j / 2;
		int r = j % 2;
		return data[uarts.GetNTotalMotor() + b*6 + r*3 + i];
	}
};
class UdpCmdPacket: public UdpPacket{
public:
	ip_addr_t returnIp;
	int CommandLen();	///<	length of packet in bytes
	short& Period() {
		return data[uarts.GetNTotalMotor()];
	}
	short& K(int i) {
		return data[i];
	}
	short& B(int i) {
		return data[uarts.GetNTotalMotor() + i];
	}
	short& TorqueMin(int i) {
		return data[i];
	}
	short& TorqueMax(int i) {
		return data[uarts.GetNTotalMotor() + i];
	}
};
class UdpRetPacket:public UdpPacket{
public:
	void SetLength();
	void ClearData();
	void SetCommand(short cmd) {
		command = cmd;
		if (cmd == CI_INTERPOLATE) {
			short &pv = data[uarts.GetNTotalMotor()];
			short &pr = data[uarts.GetNTotalMotor() + 1];
			pv = pr = 0x7FFF;
		}
	}
	short GetVacancy() {
		return data[uarts.GetNTotalMotor()];
	}
	void SetVacancy(short v) {
		short &pv = data[uarts.GetNTotalMotor()];
		pv = pv < v ? pv : v;
	}
	void SetRest(short r) {
		short &pr = data[uarts.GetNTotalMotor() + 1];
		pr = pr < r ? pr : r;
	}
	void SetTick(short t) {
		data[uarts.GetNTotalMotor() + 2] = t;
	}
	void InitInterpolate() {
		short &pv = data[uarts.GetNTotalMotor()];
		short &pr = data[uarts.GetNTotalMotor() + 1];
		pv = pr = 1000;
	}
	short& Force(int i) {
		return data[uarts.GetNTotalMotor() + i];
	}
	void SetBoardInfo(int systemId, int nTarget, int nMotor, int nForce) {
		data[0] = systemId;
		data[1] = nTarget;
		data[2] = nMotor;
		data[3] = nForce;
	}
};

class UdpCmdPackets:public ArrayRing<UdpCmdPacket, 20>{
};

class UdpCom {
public:
	const int port = 9090;
	struct udp_pcb* udp;
	ip_addr_t ownerIp;

	UdpCmdPackets recvs;
	unsigned short commandCount;
	int recvRest;
	UdpRetPacket send;

	void ConnectWifi();
	void OnWifi(system_event_t* event);
	void Init();
	void OnReceive(struct udp_pcb * upcb, struct pbuf * p, const ip_addr_t* addr, u16_t port);
	void ExecCommand();
	void PrepareRetPacket(int cmd);
	void SendRetPacket(ip_addr_t& returnIp);
	void ExecUdpCommand(UdpCmdPacket& recv);
	void SendText(char* text, short errorlevel=0);
};
extern UdpCom udpCom;
