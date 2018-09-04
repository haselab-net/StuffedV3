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
	volatile RetPacket ret;
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
	volatile unsigned char* RetStart() { return ret.bytes; }
	int RetLen() { return retPacketLen[ret.commandId]; }
	int RetLenForCommand() { return retPacketLen[cmd.commandId]; }
	unsigned char GetTargetCountOfRead(){
		return ret.interpolate.countOfRead;
	}
	unsigned short GetTick(){
		return ret.interpolate.tick;
	}
	void WriteCmd(UdpCmdPacket& packet) {
		cmd.commandId = packet.command;
		switch (packet.command){
		case CI_DIRECT:
			for (int i = 0; i < GetNMotor(); ++i) {
				cmd.direct.pos[i] = packet.GetMotorPos(motorMap[i]);
				cmd.direct.vel[i] = packet.GetMotorVel(motorMap[i]);
			}
			break;
		case CI_INTERPOLATE:
			for (int i = 0; i < GetNMotor(); ++i) {
				cmd.interpolate.pos[i] = packet.GetMotorPos(motorMap[i]);
			}
			cmd.interpolate.period = packet.GetPeriod();
			cmd.interpolate.count = packet.GetTargetCount();
			break;
		case CI_FORCE_CONTROL:
			for (int i = 0; i < GetNMotor(); ++i) {
				cmd.forceControl.pos[i] = packet.GetMotorPos(motorMap[i]);
				cmd.interpolate.period = packet.GetPeriod();
				cmd.interpolate.count = packet.GetTargetCount();
				for (int j = 0; j < GetNForce(); ++j) {
					cmd.forceControl.Jacob[j][i] = packet.GetForceControlJacob(forceMap[j], i);
				}
			}
			break;
		case CI_PDPARAM:
			for (int i = 0; i < GetNMotor(); ++i) {
				cmd.pdParam.k[i] = packet.GetControlK(motorMap[i]);
				cmd.pdParam.b[i] = packet.GetControlB(motorMap[i]);
			}
			break;
		case CI_TORQUE_LIMIT:
			for (int i = 0; i < GetNMotor(); ++i) {
				cmd.torqueLimit.min[i] = packet.GetTorqueMin(motorMap[i]);
				cmd.torqueLimit.max[i] = packet.GetTorqueMax(motorMap[i]);
			}
			break;
		case CI_RESET_SENSOR:
			cmd.resetSensor.flags = packet.GetResetSensorFlags();
			break;
		}
	}
	void ReadRet(UdpRetPacket& packet) {
		switch (packet.command) {
		case CI_DIRECT:
			for (int i = 0; i < GetNMotor(); ++i) {
				packet.SetMotorPos(ret.direct.pos[i], motorMap[i]);
				packet.SetMotorVel(ret.direct.vel[i], motorMap[i]);
			}
			//ESP_LOGI("Board", "Direct Motor Pos: %d %d %d %d\n", packet.MotorPos(0),  packet.MotorPos(1), packet.MotorPos(2),  packet.MotorPos(3));
			break;
		case CI_INTERPOLATE:
		case CI_FORCE_CONTROL:
			for (int i = 0; i < GetNMotor(); ++i) {
				packet.SetMotorPos(ret.interpolate.pos[i], motorMap[i]);
			}
			//ESP_LOGI("Board", "Motor Pos: %d %d %d %d\n", packet.MotorPos(0),  packet.MotorPos(1), packet.MotorPos(2),  packet.MotorPos(3));
			break;
		case CI_SENSOR:
			//ESP_LOGI("UART", "M0:%x", (int)ret.sensor.pos[0]);
			for (int i = 0; i < GetNMotor(); ++i) {
				packet.SetMotorPos(ret.sensor.pos[i], motorMap[i]);
			}
			for (int i = 0; i < GetNForce(); ++i) {
				packet.SetForce(ret.sensor.force[i], forceMap[i]);
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
