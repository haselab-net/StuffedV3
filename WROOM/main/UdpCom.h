#pragma once

#include "ArrayRing.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "WroomEnv.h"
#include "BoardBase.h"
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
			unsigned short count;	//	counter to detect packet drop.
			unsigned short length;	//	length of this command
			unsigned short command;	//	command id
			short data[(MAXLEN-2*3)/2];
		}__attribute__((__packed__));
	};
};
class UdpCmdPacket: public UdpPacket, public BoardCmdBase{
public:
	ip_addr_t returnIp;
	int CommandLen();	///<	length of packet in bytes
	short GetControlMode(){
		if (command == CI_ALL){
			//	TBW hase
		}else{
		}
		ESP_LOGE("UdpComPacket", "Control mode is not included in a packet of command id %d", command);
		return -1;
	}
	short GetMotorPos(int i) {
		return data[i];
	}
	short GetMotorVel(int i) {
		return data[allBoards.GetNTotalMotor() + i];
	}
	short GetPeriod() {
		return data[allBoards.GetNTotalMotor()];
	}
	short GetTargetCount() {
		return data[allBoards.GetNTotalMotor()+1];
	}
	short GetForceControlJacob(int j, int i) {	//	j: row, i: col,
		//	The matrix is 2 row x  3 col or 2*nBoard row x 3 col.
	//	int b = j / 2;
	//	int r = j % 2;
	//	return data[allBoards.GetNTotalMotor() + 2 + b*6 + r*3 + i];
		return data[allBoards.GetNTotalMotor() + 2 + j*3 + i];
	}
	short GetControlK(int i) {
		return data[i];
	}
	short GetControlB(int i) {
		return data[allBoards.GetNTotalMotor() + i];
	}
	short GetTorqueMin(int i) {
		return data[i];
	}
	short GetTorqueMax(int i) {
		return data[allBoards.GetNTotalMotor() + i];
	}
	short GetResetSensorFlags() {
		if (command == CI_ALL){
			//TBW hase
			return data[0];
		}else if (command == CI_RESET_SENSOR){
			return data[0];
		}else{
			return RSF_NONE;
		}
	}
};
class UdpRetPacket:public UdpPacket, public BoardRetBase{
public:
	//	Set length of the packet based on command.
	void SetLength();
	void ClearData();
	void SetCommand(short cmd) { command = cmd; }
	void SetControlMode(short p){
		if (command == CI_ALL){
			//TBW hase	ALLの場合だけ、パケットの中身もずれるので、Robokeyを含めて直す必要あり
		}
	}
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
	void SetCurrent(short c, int i) {
		data[allBoards.GetNTotalMotor() + i] = c;
	}
	void SetForce(short f, int i) {
		data[allBoards.GetNTotalMotor() + allBoards.GetNTotalCurrent() + i] = f;
	}
	void SetBoardInfo(int systemId, int nTarget, int nMotor, int nCurrent, int nForce) {
		data[0] = systemId;
		data[1] = nTarget;
		data[2] = nMotor;
		data[3] = nCurrent;
		data[4] = nForce;
#ifndef _WIN32
		esp_read_mac((uint8_t*)(data+5), ESP_MAC_WIFI_STA);	// 6 bytes
#endif
	}
};

class UdpCmdPackets:public ArrayRing<UdpCmdPacket, 20>{
	xSemaphoreHandle mutex;
public:
	UdpCmdPackets();
	void Lock();
	void Unlock();
};

class UdpCom {
public:
	static bool bDebug;

	const int port = 9090;
	struct udp_pcb* udp;
	ip_addr_t ownerIp;

	UdpCmdPackets recvs;
	unsigned short commandCount;
	int recvRest;
	UdpRetPacket send;
	struct pbuf* sendStart;	//	The first udp buffer to send.
	struct pbuf* sendLast;	//	The last udp buffer to send.
	int sendLen;			//	total bytes of send buffers.
	#if !UDP_UART_ASYNC
	TaskHandle_t taskExeCmd; 
	#endif
#if 0 
	void ConnectWifi();
	void OnWifi(system_event_t* event);
#endif
	void Init();
	void Start();
	void OnReceive(struct udp_pcb * upcb, struct pbuf * p, const ip_addr_t* addr, u16_t port);
#if !UDP_UART_ASYNC
	void ExecCommandLoop();
#endif
	void PrepareRetPacket(int cmd);
	void SendRetPacket(ip_addr_t& returnIp);
	void ExecUdpCommand(UdpCmdPacket& recv);
	void SendText(char* text, short errorlevel=0);
};
extern UdpCom udpCom;
