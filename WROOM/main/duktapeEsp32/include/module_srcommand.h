#ifndef MAIN_INCLUDE_MODULE_SRCOMMAND_H_
#define MAIN_INCLUDE_MODULE_SRCOMMAND_H_

#include <duktape.h>

#ifdef __cplusplus
class UdpRetPacket;
void commandMessageHandler(UdpRetPacket& ret);
#endif

duk_ret_t ModuleSRCommand(duk_context *ctx);

#endif /* MAIN_INCLUDE_MODULE_SRCOMMAND_H_ */