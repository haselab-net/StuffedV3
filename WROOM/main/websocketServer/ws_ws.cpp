/**
 * Websocket server to communicate with browser
 */

#include "ws_ws.h"

#include <string>
#include <sstream>
#include <fstream>

#include "logging.h"

#include "ws_command.h"
#include "ws_task.h"

extern void UdpCom_OnReceiveServer(void* payload, int len);

LOG_TAG("ws_ws");

static WebSocket* pWebSocket = NULL;

void SRWebSocketHandler::onClose() {
    LOGD("on close");
    pWebSocket = NULL;
}
void SRWebSocketHandler::onMessage(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket){
    LOGD("on message");
    wsOnMessage(pWebSocketInputStreambuf, pWebSocket);
}
void SRWebSocketHandler::onError(std::string error){
    LOGD("on error");
    pWebSocket = NULL;
}

void wsOnConnected(WebSocket* pWS){
    LOGD("Opened a Websocket connenction");
    pWebSocket = pWS;
}

static void saveToMainJs(const WebSocketInputStreambuf *content) {
    std::ofstream m_ofStream;

    m_ofStream.open("/main/main.js", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    if (!m_ofStream.is_open()) {
        LOGD("Failed to open file /main.main,js for writing");
        return;
    }

    m_ofStream << content;

    m_ofStream.close();
}

void wsOnMessage(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket) {
    std::stringstream buffer;
    buffer << pWebSocketInputStreambuf;
    const char* pBuffer = buffer.str().c_str();
    LOGD("Received a ws packet");
    printPacket((const void*)pBuffer);

    const int16_t* pBufferI16 = (const int16_t*)pBuffer;

    switch (*pBufferI16)
    {
        case PacketId::PI_JSFILE:
            wsDeleteJsfileTask();
            
            saveToMainJs(pWebSocketInputStreambuf);
            wsCreateJsfileTask();
            
            break;

        case PacketId::PI_COMMAND:
            UdpCom_OnReceiveServer((void*)(pBuffer+1), pBuffer[1]);
            break;
    
        default:
            break;
    }
}

static void wsSend(std::string data) {
    if(!pWebSocket) return;
    LOGD("Prepare to send a ws packet");
    printPacket((const void*)data.c_str());
    pWebSocket->send(data, WebSocket::SEND_TYPE_BINARY);
}

void wsSendCommand(void* buffer, size_t buffer_size) {
    void* data_buffer = (void*)malloc(sizeof(int16_t)+buffer_size);
    *(int16_t*)data_buffer = PacketId::PI_COMMAND;
    memcpy((int16_t*)data_buffer+1, buffer, buffer_size);

    std::string* sp = static_cast<std::string*>(data_buffer);
    std::string s = *sp;
    
    free(data_buffer);

    wsSend(s);
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
