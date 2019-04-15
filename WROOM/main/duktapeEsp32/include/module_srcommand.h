#ifndef MAIN_INCLUDE_MODULE_SRCOMMAND_H_
#define MAIN_INCLUDE_MODULE_SRCOMMAND_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <duktape.h>
duk_ret_t ModuleSRCommand(duk_context *ctx);

#ifdef __cplusplus
}
#include "../../softRobot/UdpCom.h"
void commandMessageHandler(UdpRetPacket& ret);
#endif

#endif /* MAIN_INCLUDE_MODULE_SRCOMMAND_H_ */
