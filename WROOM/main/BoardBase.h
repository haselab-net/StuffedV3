#pragma once

#include "CommandWROOM.h"
#include "UTRef.h"
#include "TinyContainer.h"

class UdpCmdPacket;
class UdpRetPacket;
class BoardBase:public UTRefCount{
public:
	const unsigned char * cmdPacketLen;
	const unsigned char * retPacketLen;
	tiny::vector<int> motorMap;
	tiny::vector<int> forceMap;
	virtual ~BoardBase(){}
	virtual const char* GetName() = 0;
	virtual int GetModelNumber() = 0;
	virtual int GetNTarget() = 0;
	virtual int GetNMotor() = 0;
	virtual int GetNForce() = 0;
	virtual int GetBoardId() = 0;
	virtual unsigned char GetTargetCountOfRead() = 0;
	virtual unsigned short GetTick() = 0;
	virtual void WriteCmd(UdpCmdPacket& packet) = 0;
	virtual void ReadRet(UdpRetPacket& packet) = 0;
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
