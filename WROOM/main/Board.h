#pragma once

#include "BoardBase.h"
#include "UdpCom.h"
#include "esp_log.h"

#define CMDWAITMAXLEN	80
template <class CMD, class RET>
class Board: public BoardBase{
public:
	typedef CMD CmdPacket;
	typedef RET RetPacket;
#ifdef _WIN32
	CommandPacketB1M cmd;
	ReturnPacketB1M ret;
#else
	CmdPacket cmd;
	uint8_t zero[CMDWAITMAXLEN];
	RetPacket ret;
#endif
	Board(int bid, const unsigned char * c, const unsigned char * r) {
		cmd.boardId = bid;
		cmdPacketLen = c;
		retPacketLen = r;
	}
	const char* GetName() { return CMD::GetBoardName(); }
	int GetModelNumber() { return CMD::GetModelNumber(); }
	int GetNTarget() { return CMD::GetNTarget();  }
	int GetNMotor() { return CMD::GetNMotor(); }
	int GetNForce() { return CMD::GetNForce(); }
	int GetBoardId() { return cmd.boardId;  }
	int GetRetCommand() { return ret.commandId; }
	unsigned char* CmdStart() { return cmd.bytes;  }
	int CmdLen() { return cmdPacketLen[cmd.commandId]; }
	unsigned char* RetStart() { return ret.bytes; }
	int RetLen() { return retPacketLen[ret.commandId]; }
	int RetLenForCommand() { return retPacketLen[cmd.commandId]; }
	void WriteCmd(UdpCmdPacket& packet) {
		cmd.commandId = packet.command;
		switch (packet.command){
		case CI_DIRECT:
			for (int i = 0; i < GetNMotor(); ++i) {
				cmd.direct.pos[i] = packet.MotorPos(motorMap[i]);
				cmd.direct.vel[i] = packet.MotorVel(motorMap[i]);
			}
			break;
		case CI_INTERPOLATE:
			for (int i = 0; i < GetNMotor(); ++i) {
				cmd.interpolate.pos[i] = packet.MotorPos(motorMap[i]);
				cmd.interpolate.period = packet.Period();
			}
			break;
		case CI_FORCE_CONTROL:
			for (int i = 0; i < GetNMotor(); ++i) {
				cmd.forceControl.pos[i] = packet.MotorPos(motorMap[i]);
				for (int j = 0; j < GetNForce(); ++j) {
					cmd.forceControl.JK[j][i] = packet.ForceControlJK(forceMap[j], i);
				}
				cmd.interpolate.period = packet.Period();
			}
			break;
		case CI_PDPARAM:
			for (int i = 0; i < GetNMotor(); ++i) {
				cmd.pdParam.k[i] = packet.K(motorMap[i]);
				cmd.pdParam.b[i] = packet.B(motorMap[i]);
			}
			break;
		case CI_TORQUE_LIMIT:
			for (int i = 0; i < GetNMotor(); ++i) {
				cmd.torqueLimit.min[i] = packet.TorqueMin(motorMap[i]);
				cmd.torqueLimit.max[i] = packet.TorqueMax(motorMap[i]);
			}
			break;
		}
	}
	void ReadRet(UdpRetPacket& packet) {
		switch (packet.command) {
		case CI_DIRECT:
			for (int i = 0; i < GetNMotor(); ++i) {
				packet.MotorPos(motorMap[i]) = ret.direct.pos[i];
				packet.MotorVel(motorMap[i]) = ret.direct.vel[i];
			}
			//ESP_LOGI("Board", "Direct Motor Pos: %d %d %d %d\n", packet.MotorPos(0),  packet.MotorPos(1), packet.MotorPos(2),  packet.MotorPos(3));
			break;
		case CI_INTERPOLATE:
		case CI_FORCE_CONTROL:
			for (int i = 0; i < GetNMotor(); ++i) {
				packet.MotorPos(motorMap[i]) = ret.interpolate.pos[i];
			}
			packet.SetVacancy(ret.interpolate.vacancy);
			packet.SetRemain(ret.interpolate.remain);
			packet.SetTick(ret.interpolate.tick);
			//ESP_LOGI("Board", "Motor Pos: %d %d %d %d\n", packet.MotorPos(0),  packet.MotorPos(1), packet.MotorPos(2),  packet.MotorPos(3));
			break;
		case CI_SENSOR:
			for (int i = 0; i < GetNMotor(); ++i) {
				packet.MotorPos(motorMap[i]) = ret.sensor.pos[i];
			}
			for (int i = 0; i < GetNForce(); ++i) {
				packet.Force(forceMap[i]) = ret.sensor.force[i];
			}
			break;
		}
	}
};

template <class BOARD> class BoardFactory:public BoardFactoryBase{
public:
	BoardFactory(const unsigned char * c, const unsigned char * r) : BoardFactoryBase(c, r) {}
	virtual BoardBase* Create(int id) {
		return new BOARD(id, cmdPacketLen, retPacketLen);
	}
	virtual const char* GetName() {
		return BOARD::CmdPacket::GetBoardName();
	}
	virtual int GetModelNumber() {
		return BOARD::CmdPacket::GetModelNumber();
	}
};
#define BOARD_FACTORY(BOARD)	BoardFactory< Board<CommandPacket##BOARD, ReturnPacket##BOARD> >(cmdPacketLen##BOARD, retPacketLen##BOARD)
