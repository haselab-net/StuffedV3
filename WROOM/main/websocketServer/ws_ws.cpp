/**
 * Websocket server to communicate with browser
 */

#include "ws_ws.h"

#include <string>
#include <sstream>
#include <fstream>

#include "logging.h"
#include "WebSocket.h"

#include "ws_command.h"

extern void UdpCom_OnReceiveServer(void* payload, int len);

LOG_TAG("ws_ws");

static WebSocket* pWebSocket = NULL;

class SRWebSocketHandler: public WebSocketHandler {
    void onClose() {
        LOGD("on close");
        pWebSocket = NULL;
    }
    void onMessage(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket){
        LOGD("on message");
        wsOnMessage(pWebSocketInputStreambuf, pWebSocket);
    }
	void onError(std::string error){
        LOGD("on error");
        pWebSocket = NULL;
    }
};

void wsOnConnected(WebSocket* pWS){
    pWebSocket = pWS;
}

void wsOnMessage(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket) {
    std::stringstream buffer;
    buffer << pWebSocketInputStreambuf;
    const char* pBuffer = buffer.str().c_str();
    printPacket((const void*)pBuffer);

    const int16_t* pBufferI16 = (const int16_t*)pBuffer;

    switch (*pBufferI16)
    {
        case PacketId::PI_JSFILE:
            // TODO run JSFILE
            break;

        case PacketId::PI_COMMAND:
            UdpCom_OnReceiveServer((void*)(pBuffer+1), pBuffer[1]);
            break;
    
        default:
            break;
    }
}

void wsSend(std::string data) {
    if(!pWebSocket) return;
    pWebSocket->send(data, WebSocket::SEND_TYPE_BINARY);
}

void printPacket(const void* pBuffer) {
    const int16_t* pBufferI16 = (const int16_t*)pBuffer;
    switch (*pBufferI16)
    {
        case PacketId::PI_JSFILE:
            printf("- PacketId: PI_JSFILE \r\n");
            const char* pBufferChar = (const char*)pBuffer;
            printf("- Content: \r\n");
            printf("%s", pBufferChar);
            break;

        case PacketId::PI_COMMAND:
            printf("- PacketId: PI_COMMAND \r\n");

            pBufferI16 = pBufferI16+1;
            uint16_t length = pBufferI16[1];
            printf("- Content: \r\n");
            printf("   |- Length: %i \r\n", pBufferI16[0]);
            printf("   |- CommandId: %i \r\n", pBufferI16[1]);

            printf("   |- Command: ");
            for(size_t i = 0; i < length; i++)
            {
                printf("%i ", pBufferI16[2+i]);
            }
            printf("\r\n");
            break;
    
        default:
            printf("- PacketId: UNRECOGNIZED");
            break;
    }
}
