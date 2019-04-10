﻿#pragma once

#ifndef __cplusplus

void UdpCom_OnReceiveServer(void* payload, int len);

#else

extern "C" void UdpCom_OnReceiveServer(void* payload, int len);

#include "ArrayRing.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "../WroomEnv.h"
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
	static const char* Tag(){ return "UdpCom"; }
	enum {
		HEADERLEN = 4,		//	does not include count. 
		MAXLEN = 512		//	hole packet size include count must equal or smaller than MAXLEN.
	};
	union {
		unsigned char bytes[MAXLEN];	//	hole packet
		struct {
			unsigned short count;		//	counter to detect packet drop.
			unsigned short length;		//	length of packet from here. i.e. without count.
			unsigned short command;		//	command id.
			short data[(MAXLEN-2*3)/2];	//	data of the command.
		}__attribute__((__packed__));
	};
};
class UdpCmdPacket: public UdpPacket, public BoardCmdBase{
public:
	ip_addr_t returnIp;	///<	IP address to send return packet, 0.0.0.0 means return to web server (duktape)
	int CommandLen();	///<	length of packet in bytes
	short GetControlMode(){
		if (command == CI_ALL){
			//	TBW hase
		}else{
		}
		ESP_LOGE("UdpComPacket", "Control mode is not included in a packet of command id %d", command);
		return -1;
	}
	short GetMotorPos(int i) { return data[i]; }
	void SetMotorPos(short p, int i) { data[i] = p; }
	short GetMotorVel(int i) { return data[allBoards.GetNTotalMotor() + i]; }
	void SetMotorVel(short v, int i) { data[allBoards.GetNTotalMotor() + i] = v; }
	unsigned short GetPeriod() { return data[allBoards.GetNTotalMotor()]; }
	void SetPeriod(unsigned short p) { data[allBoards.GetNTotalMotor()] = p; }
	unsigned short GetTargetCountWrite() { return data[allBoards.GetNTotalMotor() + 1]; }
	void SetTargetCountWrite(unsigned short c) { data[allBoards.GetNTotalMotor() + 1] = c; }
	short GetForceControlJacob(int j, int i) {	//	j: row, i: col,
	//	The matrix is 2 row x  3 col or 2*nBoard row x 3 col.
	//	int b = j / 2;
	//	int r = j % 2;
	//	return data[allBoards.GetNTotalMotor() + 2 + b*6 + r*3 + i];
		return data[allBoards.GetNTotalMotor() + 2 + j*3 + i];
	}
	short GetParamType() { return data[0]; }
	void SetParamType(short t) { data[0] = t; }
	SDEC GetControlK(int i) { return data[1 + i]; }
	void SetControlK(SDEC k, int i) { data[1 + i] = k; }
	SDEC GetControlB(int i) { return data[1 + allBoards.GetNTotalMotor() + i]; }
	void SetControlB(SDEC k, int i) { data[1 + allBoards.GetNTotalMotor() + i] = k; }
	SDEC GetControlA(int i) { return data[1 + i]; }
	void SetControlA(SDEC k, int i) { data[1 + i] = k; }
	SDEC GetTorqueMin(int i) { return data[1 + i]; }
	void SetTorqueMin(SDEC t, int i) { data[1 + i] = t; }
	SDEC GetTorqueMax(int i) { return data[1 + allBoards.GetNTotalMotor() + i]; }
	void SetTorqueMax(SDEC t, int i) { data[1 + allBoards.GetNTotalMotor() + i] = t; }
	short GetBoardId() { return data[1]; }
	void SetBoardId(short id) { data[1] = id; }
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
	void SetResetSensorFlags(short f) {
		if (command == CI_ALL) {
			//TBW hase
			data[0] = f;
		}
		else if (command == CI_RESET_SENSOR) {
			data[0] = f;
		}
	}
};
class UdpRetPacket:public UdpPacket, public BoardRetBase{
public:
	//	Set length of the packet based on command.
	void SetLength();
	void ClearData();
	void SetCommand(short cmd) { command = cmd; }
	virtual void SetAll(ControlMode controlMode, unsigned char targetCountReadMin, unsigned char targetCountReadMax,
		unsigned short tickMin, unsigned short tickMax, 
		SDEC* pos, SDEC* vel, SDEC* current, SDEC* force, SDEC* touch);
	short GetMotorPos(int i) { return data[i]; }
	void SetMotorPos(short p, int i) { data[i] = p; }
	short GetMotorVel(int i) { return data[allBoards.GetNTotalMotor() + i]; }
	void SetMotorVel(short v, int i) { data[allBoards.GetNTotalMotor() + i] = v; }
	//	for interpolate and force control
	unsigned char GetTargetCountReadMin() { return (unsigned char)data[allBoards.GetNTotalMotor()]; }
	void SetTargetCountReadMin(unsigned char c) { data[allBoards.GetNTotalMotor()] = c; }
	unsigned char GetTargetCountReadMax() { return (unsigned char)data[allBoards.GetNTotalMotor() + 1]; }
	void SetTargetCountReadMax(unsigned char c) { data[allBoards.GetNTotalMotor() + 1] = c; }
	short GetTickMin() { return data[allBoards.GetNTotalMotor() + 2]; }
	void SetTickMin(unsigned short t) { data[allBoards.GetNTotalMotor() + 2] = t; }
	short GetTickMax() { return data[allBoards.GetNTotalMotor() + 3]; }
	void SetTickMax(unsigned short t) { data[allBoards.GetNTotalMotor() + 3] = t; }
	//	sense
	short GetCurrent(int i) { return data[allBoards.GetNTotalMotor() + i]; }
	void SetCurrent(short c, int i) { data[allBoards.GetNTotalMotor() + i] = c; }
	short GetForce(int i) { return data[allBoards.GetNTotalMotor() + allBoards.GetNTotalCurrent() + i]; }
	void SetForce(short f, int i) { data[allBoards.GetNTotalMotor() + allBoards.GetNTotalCurrent() + i] = f; }
	short GetTouch(int i) { return data[allBoards.GetNTotalMotor() + allBoards.GetNTotalCurrent() + allBoards.GetNTotalForce() + i]; }
	void SetTouch(short t, int i) { data[allBoards.GetNTotalMotor() + allBoards.GetNTotalCurrent() + allBoards.GetNTotalForce() + i] = t; }
	void SetBoardInfo(int systemId, int nTarget, int nMotor, int nCurrent, int nForce, int nTouch) {
		data[0] = systemId;
		data[1] = nTarget;
		data[2] = nMotor;
		data[3] = nCurrent;
		data[4] = nForce;
		data[5] = nTouch;
#ifndef _WIN32
		esp_read_mac((uint8_t*)(data+6), ESP_MAC_WIFI_STA);	// 6 bytes
#endif
	}
};

#define NUDPCMDPACKETS	10
class UdpCmdPackets:public ArrayRing<UdpCmdPacket, NUDPCMDPACKETS>{
	xSemaphoreHandle smAvail, smFree;
public:
	typedef ArrayRing<UdpCmdPacket, NUDPCMDPACKETS> base;
	UdpCmdPackets();
	//	blocking read, write peek poke
	void Read();
	void Write();
	UdpCmdPacket& Peek();
	UdpCmdPacket& Poke();
};

class UdpCom {
public:
	static const char* Tag() { return UdpPacket::Tag(); }
	const int port = 9090;
	struct udp_pcb* udp;
	ip_addr_t ownerIp;

	UdpCmdPackets recvs;
	unsigned short commandCount;
	UdpRetPacket send;
#if 0 
	void ConnectWifi();
	void OnWifi(system_event_t* event);
#endif
	void Init();
	void Start();
	UdpCmdPacket* PrepareCommand(CommandId cid);
	void WriteCommand();

	void OnReceiveUdp(struct udp_pcb * upcb, struct pbuf * top, const ip_addr_t* addr, u16_t port);
	void OnReceiveServer(void* payload, int len);
	///	execute udp command
	void ExecUdpCommand(UdpCmdPacket& recv);
	///	send return packet correspond to UdpCmdPacket recv.
	void SendReturn(UdpCmdPacket& recv);
	///	send return packet to web server (duktape)
	void SendReturnServer();
	///	send return packet to udp
	void SendReturnUdp(UdpCmdPacket& recv);
	///	prepare return packet for command cmd
	void PrepareRetPacket(UdpCmdPacket& recv);
	void SendText(char* text, short errorlevel=0);
};
extern UdpCom udpCom;
#endif
