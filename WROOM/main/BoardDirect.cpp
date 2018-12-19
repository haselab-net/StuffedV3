#include "BoardDirect.h"
extern "C"{
#include "../../PIC/control.h"
#include "../../PIC/command.h"
}

BoardDirect::BoardDirect():Board(-1, cmdPacketLenBD0, retPacketLenBD0){
}
void BoardDirect::WriteCmd(UdpCmdPacket& packet){
    base::WriteCmd(packet);
    ExecCmd(&cmd, sizeof(cmd));
}
void BoardDirect::ReadRet(UdpRetPacket& packet){
    ExecRet((void*)&ret, sizeof(ret));
    base::ReadRet(packet);
}
