#include "BoardDirect.h"
extern "C"{
#include "../../../PIC/control.h"
#include "../../../PIC/command.h"
}

BoardDirect::BoardDirect():Board(-1, cmdPacketLenBD0, retPacketLenBD0){
}
void BoardDirect::WriteCmd(unsigned short commandId, BoardCmdBase& packet){
    base::WriteCmd(commandId, packet);
    ExecCmd(&cmd, sizeof(cmd));
}
void BoardDirect::ReadRet(unsigned short cmd,  BoardRetBase& packet){
    ExecRet((void*)&ret, sizeof(ret));
    base::ReadRet(cmd, packet);
}
