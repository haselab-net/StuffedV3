#pragma once

#include "CommandWROOM.h"
#include "UTRef.h"
#include "TinyContainer.h"
extern "C"{
#include "../../PIC/fixed.h"
}

class BoardCmdBase{
public:
	virtual short GetControlMode()=0;
	virtual short GetMotorPos(int i)=0;
	virtual short GetMotorVel(int i)=0;
	virtual short GetPeriod()=0;
	virtual short GetTargetCount()=0;
	virtual short GetForceControlJacob(int j, int i)=0;
	virtual short GetControlK(int i)=0;
	virtual short GetControlB(int i)=0;
	virtual short GetTorqueMin(int i)=0;
	virtual short GetTorqueMax(int i)=0;
	typedef ::ResetSensorFlags ResetSensorFlags;		//	in CommandIDs.cs
	virtual short GetResetSensorFlags()=0;	//	
};
class BoardRetBase{
public:
	virtual void SetControlMode(short cm)=0;
	virtual void SetMotorPos(short p, int i)=0;
	virtual void SetMotorVel(short v, int i)=0;
	virtual void SetTargetCountRead(unsigned char c)=0;
	virtual void SetTickMin(short t)=0;
	virtual void SetTickMax(short t)=0;
	virtual void SetNTargetRemain(unsigned char t)=0;
	virtual void SetNTargetVacancy(unsigned char t)=0;
	virtual void SetCurrent(short c, int i)=0;
	virtual void SetForce(short f, int i)=0;
	virtual void SetBoardInfo(int systemId, int nTarget, int nMotor, int nCurrent, int nForce)=0;
};

struct RobotState;
class UdpCmdPacket;
class UdpRetPacket;
class BoardBase:public UTRefCount{
public:
	const unsigned char * cmdPacketLen;
	const unsigned char * retPacketLen;
	tiny::vector<int> motorMap;
	tiny::vector<int> currentMap;
	tiny::vector<int> forceMap;
	virtual ~BoardBase(){}
	virtual const char* GetName() = 0;
	virtual int GetModelNumber() = 0;
	virtual int GetNTarget() = 0;
	virtual int GetNMotor() = 0;
	virtual int GetNCurrent() = 0;
	virtual int GetNForce() = 0;
	virtual int GetBoardId() = 0;
	virtual unsigned char GetTargetCountOfRead() = 0;
	virtual unsigned short GetTick() = 0;
	virtual void WriteCmd(unsigned short command, BoardCmdBase& packet) = 0;
	virtual void ReadRet(unsigned short command, BoardRetBase& packet) = 0;
	virtual int GetRetCommand() = 0;
	virtual unsigned char* CmdStart() = 0;
	virtual int CmdLen() = 0;
	virtual volatile unsigned char* RetStart() = 0;
	virtual int RetLen() = 0;
	virtual int RetLenForCommand() = 0;
};

class BoardFactoryBase :public UTRefCount {
public:
	const unsigned char * cmdPacketLen;
	const unsigned char * retPacketLen;
	BoardFactoryBase(const unsigned char * c, const unsigned char * r) : cmdPacketLen(c), retPacketLen(r) {}
	virtual ~BoardFactoryBase(){}
	virtual const char* GetName() = 0;
	virtual int GetModelNumber() = 0;
	virtual BoardBase* Create(int id) = 0;
};
class BoardFactories :public tiny::vector< UTRef<BoardFactoryBase> > {
public:
	BoardFactories();
	BoardFactoryBase* Find(const char* name);
	BoardFactoryBase* Find(int modelNum);
};

class Boards :public tiny::vector< UTRef<BoardBase> > {	
	static BoardFactories factories;
public:
	BoardBase* Create(const char* name, int boardId);
	BoardBase* Create(int modelNum, int boardId);
};
