#ifndef WEBSOCKETSERVER_WS_WS_H_
#define WEBSOCKETSERVER_WS_WS_H_

#include "WebSocket.h"
#include "UdpCom.h"
#include "../../main/WroomEnv.h"
#include "Utils.h"

extern bool offline_mode;

class SRWebSocketHandler: public WebSocketHandler {
    void onClose();
    void onMessage(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket);
	void onError(std::string error);
};

void wsOnConnected(WebSocket* pWS);

void switchOfflineModeSuccess();
void wsOnMessageWs(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket);

void wsOnMessageSr(UdpRetPacket& ret);

void printPacketJsfile(const void* pBuffer, size_t len);
void printPacketCommand(const void* pBuffer, size_t len);
void printPacket(const void* pBuffer, size_t len);
void printDTPacket(const void* pBuffer, size_t len);

#endif
