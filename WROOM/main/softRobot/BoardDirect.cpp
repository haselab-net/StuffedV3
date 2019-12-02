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
#if 0
    if (cmd.commandId == CI_SETPARAM && (cmd.param.type == PT_PD || cmd.param.type == PT_CURRENT)){
        allBoards.SaveMotorParam();
    }
#endif
}
void BoardDirect::ReadRet(unsigned short cmd,  BoardRetBase& packet){
    ExecRet((void*)&ret, sizeof(ret));
    base::ReadRet(cmd, packet);
}
