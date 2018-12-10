#pragma once

#include "ArrayRing.h"
#include "esp_event_loop.h"
#include "UartForBoards.h"
#include "AllBoards.h"


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
};
class UdpCmdPacket: public UdpPacket{
public:
	ip_addr_t returnIp;
	int CommandLen();	///<	length of packet in bytes
	short GetMotorPos(int i) {
		return data[i];
	}
	short GetMotorVel(int i) {
		return data[allBoards.GetNTotalMotor() + i];
	}
	short GetPeriod() const {
		return data[allBoards.GetNTotalMotor()];
	}
	short GetTargetCount() const {
		return data[allBoards.GetNTotalMotor()+1];
	}
	short GetForceControlJacob(int j, int i) const {	//	j: row, i: col,
		//	The matrix is 2 row x  3 col or 2*nBoard row x 3 col.
	//	int b = j / 2;
	//	int r = j % 2;
	//	return data[allBoards.GetNTotalMotor() + 2 + b*6 + r*3 + i];
		return data[allBoards.GetNTotalMotor() + 2 + j*3 + i];
	}
	short GetControlK(int i) const {
		return data[i];
	}
	short GetControlB(int i) const {
		return data[allBoards.GetNTotalMotor() + i];
	}
	short GetTorqueMin(int i) const {
		return data[i];
	}
	short GetTorqueMax(int i) const {
		return data[allBoards.GetNTotalMotor() + i];
	}
	short GetResetSensorFlags() const {
		return data[0];
	}
};
class UdpRetPacket:public UdpPacket{
public:
	//	Set length of the packet based on command.
	void SetLength();
	void ClearData();
	void SetCommand(short cmd) { command = cmd; }
	void SetMotorPos(short p, int i) {
		data[i] = p;
	}
	void SetMotorVel(short v, int i) {
		data[allBoards.GetNTotalMotor() + i] = v;
	}
	//	for interpolate and force control
	void SetTargetCountRead(short c) {
		data[allBoards.GetNTotalMotor()] = c;
	}
	void SetTickMin(short t) {
		data[allBoards.GetNTotalMotor()+1] = t;
	}
	void SetTickMax(short t) {
		data[allBoards.GetNTotalMotor()+2] = t;
	}
	void SetNTargetRemain(short t){
		data[allBoards.GetNTotalMotor()+3] = t;		
	}
	void SetNTargetVacancy(short t){
		data[allBoards.GetNTotalMotor()+4] = t;		
	}
	//	sense
	void SetForce(short f, int i) {
		data[allBoards.GetNTotalMotor() + i] = f;
	}
	void SetBoardInfo(int systemId, int nTarget, int nMotor, int nForce) {
		data[0] = systemId;
		data[1] = nTarget;
		data[2] = nMotor;
		data[3] = nForce;
		esp_read_mac((uint8_t*)(data+4), ESP_MAC_WIFI_STA);	// 6 bytes
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
	TaskHandle_t taskExeCmd; 

#if 0 
	void ConnectWifi();
	void OnWifi(system_event_t* event);
#endif
	void Init();
	void Start();
	void OnReceive(struct udp_pcb * upcb, struct pbuf * p, const ip_addr_t* addr, u16_t port);
	void ExecCommandLoop();
	void PrepareRetPacket(int cmd);
	void SendRetPacket(ip_addr_t& returnIp);
	void ExecUdpCommand(UdpCmdPacket& recv);
	void SendText(char* text, short errorlevel=0);
};
extern UdpCom udpCom;
