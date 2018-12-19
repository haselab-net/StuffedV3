#pragma once

#include "Board.h"
#include "esp_log.h"
#include "MotorDriver.h"

class BoardDirect: public Board<CommandPacketBD0, ReturnPacketBD0>{
public:
	typedef Board<CommandPacketBD0, ReturnPacketBD0> base;
	BoardDirect();
	void WriteCmd(UdpCmdPacket& packet);
	void ReadRet(UdpRetPacket& packet);
};
