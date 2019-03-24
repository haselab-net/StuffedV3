#ifndef WEBSOCKETSERVER_WS_WS_H_
#define WEBSOCKETSERVER_WS_WS_H_

#include "WebSocket.h"

class SRWebSocketHandler: public WebSocketHandler {
    void onClose();
    void onMessage(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket);
	void onError(std::string error);
};

void wsOnConnected(WebSocket* pWS);

void wsOnMessage(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket);

void wsSendCommand(void* buffer, size_t buffer_size);

void printPacket(const void* pBuffer);

#endif
