/**
 * Websocket server to communicate with browser
 */

#include "ws_ws.h"

#include <string>
#include <sstream>
#include <fstream>

#include "esp_log.h"
extern "C" {
#include "module_jslib.h"
#include "duktape_jsfile.h"
}
#include "../SoftRobot/UdpCom.h"
#include "module_srcommand.h"

#include "ws_command.h"
#include "ws_task.h"
#include "ws_fs.h"

static char LOG_TAG[] = "ws_ws";

static WebSocket* pWebSocket = NULL;
static SRWebSocketHandler webSocketHandler = SRWebSocketHandler();

static bool development_mode = false;

void SRWebSocketHandler::onClose() {
    ESP_LOGD(LOG_TAG, "on close");
    pWebSocket = NULL;
}
void SRWebSocketHandler::onMessage(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket){
    ESP_LOGD(LOG_TAG, "on message");
    wsOnMessageWs(pWebSocketInputStreambuf, pWebSocket);
}
void SRWebSocketHandler::onError(std::string error){
    ESP_LOGD(LOG_TAG, "on error");
    pWebSocket = NULL;
}

void wsOnConnected(WebSocket* pWS){
    ESP_LOGD(LOG_TAG, "Opened a Websocket connenction");
    pWebSocket = pWS;
    pWebSocket->setHandler(&webSocketHandler);
}

/*
static void saveToMainJsStream(const WebSocketInputStreambuf *content) {
    std::ofstream m_ofStream;

    std::string root_path = SPIFFS_MOUNTPOINT;
    m_ofStream.open(root_path + "/main/main.js", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    if (!m_ofStream.is_open()) {
        ESP_LOGD(LOG_TAG, "Failed to open file /spiffs/main/main.js for writing");
        return;
    }

    m_ofStream << content;

    m_ofStream.close();
}
*/

static void saveToMainJs(const char *content, size_t length){
    std::ofstream m_ofStream;

    m_ofStream.open(std::string(SPIFFS_MOUNTPOINT) + "/main/main.js", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    if (!m_ofStream.is_open()) {
        ESP_LOGD(LOG_TAG, "Failed to open file /spiffs/main/main.js for writing");
        return;
    }

    m_ofStream.write(content, length);
    m_ofStream.close();

    ESP_LOGD(LOG_TAG, "File main.js written to /spiffs/main/main.js");
}

static void combineMainFiles() {
    std::ifstream m_ifStream;
    std::ofstream m_ofStream;

    m_ofStream.open(std::string(SPIFFS_MOUNTPOINT) + "/main/runtime.js", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

    m_ifStream.open(std::string(SPIFFS_MOUNTPOINT) + "/main/maininit.js", std::ofstream::in | std::ofstream::binary);
    m_ofStream << m_ifStream.rdbuf() << std::endl;
    m_ifStream.close();
    m_ifStream.open(std::string(SPIFFS_MOUNTPOINT) + "/main/main.js", std::ofstream::in | std::ofstream::binary);
    m_ofStream << m_ifStream.rdbuf() << std::endl;
    m_ifStream.close();
    m_ifStream.open(std::string(SPIFFS_MOUNTPOINT) + "/main/mainend.js", std::ofstream::in | std::ofstream::binary);
    m_ofStream << m_ifStream.rdbuf() << std::endl;
    m_ifStream.close();

    m_ofStream.close();
}

static void wsSend(void* data, size_t length) {
    if(!pWebSocket) {
        ESP_LOGD(LOG_TAG, "Unable to send packet, websocket is not connected");
        return;
    }
    pWebSocket->send((uint8_t*)data, length , WebSocket::SEND_TYPE_BINARY);
}

/**
 * Handle message from websocket
 */
void wsOnMessageWs(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket) {
    printf("before wsOnMessageWs heap size: %d \n", esp_get_free_heap_size());

    int16_t packetId = pWebSocketInputStreambuf->sgetc();
    ESP_LOGD(LOG_TAG, "type: %i", packetId);

    size_t bufferSize = 4096;
    char* pBuffer = new char[bufferSize];
    std::streamsize ssize = pWebSocketInputStreambuf->sgetn(pBuffer, bufferSize);
    if(ssize>=bufferSize) {
        ESP_LOGD(LOG_TAG ,"File main.js to large!!!!!!!!!");
        return;
    }

    pWebSocketInputStreambuf->discard();

    printf("+ WS packet \n");
    printPacket((const void*)pBuffer, ssize);

    switch (packetId)
    {
        case PacketId::PI_JSFILE: {
            wsDeleteJsfileTask();
            
            saveToMainJs(pBuffer+2, ssize-2);
            combineMainFiles();

            delete[] pBuffer;       // delete buffer to provide more space for jsfile task
            pBuffer = NULL;

            if(development_mode) {  // do not run file in development mode
                break;
            }
            else {                  // run file
                std::ifstream m_ifstream("/spiffs/main/runtime.js");
                std::string str((std::istreambuf_iterator<char>(m_ifstream)),
                    std::istreambuf_iterator<char>());
                printf("Start runtime file: \n %s", str.c_str());
                m_ifstream.close();

                printf("before wsCreateJsfileTask heap size: %d \n", esp_get_free_heap_size());

                wsCreateJsfileTask();
            }
            
            break;
        }

        case PacketId::PI_COMMAND: {
            UdpCom_OnReceiveServer((void*)(pBuffer+2), *(int16_t*)(&pBuffer[2]));
            break;
        }

        case PacketId::PI_SETTINGS: {
            uint16_t* pBufferI16 = (uint16_t*)pBuffer;
            uint16_t id = pBufferI16[1];
            switch (id)
            {
                case PacketSettingsId::DEVELOPMENT_MODE:
                    development_mode = pBufferI16[2];
                    if(development_mode) {
                        ESP_LOGD(LOG_TAG, "switch to development mode, stop running jsfile task");
                        wsDeleteJsfileTask();
                    }else if(!wsIsJsfileTaskRunning()){
                        ESP_LOGD(LOG_TAG, "switch to jsfile mode, start running jsfile task");
                        wsDeleteJsfileTask();
                        wsCreateJsfileTask();
                    }
                    break;
            
                default:
                    ESP_LOGD(LOG_TAG, "Unknown packet settings id (%i)", pBufferI16[1]);
                    break;
            }
            break;
        }
    
        default:
            break;
    }

    if(pBuffer) delete[] pBuffer;
}

/**
 * Handle message from softrobot
 * send command to browser and jsfile task
 */
void wsOnMessageSr(UdpRetPacket& ret) {
    printf("+ SR Packet \n");
    printPacketCommand(ret.bytes + 2, ret.length);
    
    ret.count = PacketId::PI_COMMAND;     //  add packet id at the previous position.
    // send packet to browser
    wsSend(ret.bytes, ret.length+2);
    ESP_LOGD(LOG_TAG, "Packet softrobot -> websocket");

    // send packet to jsfile task
    // return_packet_to_jsfile(buffer, buffer_size);
    if(!esp32_duk_context) return;
    commandMessageHandler(ret);
    ESP_LOGD(LOG_TAG, "Packet softrobot -> jsfile");
}

void printPacketJsfile(const void* pBuffer, size_t len) {
    printf("|- PacketId: PI_JSFILE \r\n");
    const char* pBufferChar = (const char*)pBuffer;
    printf("|- Content: \r\n");
    for(int i=0; i<len; i++) {
        std::cout << pBufferChar[i];
    }
    printf("\r\n");
}

void printPacketCommand(const void* pBuffer, size_t len) {
    int16_t* pBufferI16 = (int16_t*)pBuffer;
    printf("|- PacketId: PI_COMMAND \r\n");

    uint16_t length = pBufferI16[0];
    printf("|- Content: \r\n");
    printf("   |- Length: %i \r\n", length);
    printf("   |- CommandId: %i \r\n", pBufferI16[1]);

    printf("   |- Command: ");
    for(size_t i = 2; i < len/2; i++)
    {
        printf("%i, ", pBufferI16[i]);
    }
    printf("\r\n");
}

void printPacketSettings(const void* pBuffer, size_t len) {
    int16_t* pBufferI16 = (int16_t*)pBuffer;
    printf("|- PacketId: PI_SETTINGS \r\n");

    uint16_t id = pBufferI16[0];
    printf("   |- Setting type: %s \r\n", getPacketSettingsIdStr(id).c_str());

    printf("   |- Value: ");
    switch (id)
    {
        case PacketSettingsId::DEVELOPMENT_MODE:
            printf("%i ", pBufferI16[1]);
            break;
    
        default:
            break;
    }
    printf("\r\n");
}

void printPacket(const void* pBuffer, size_t len) {
    const int16_t* pBufferI16 = (const int16_t*)pBuffer;
    switch (*pBufferI16)
    {
        case PacketId::PI_JSFILE: {
            printPacketJsfile((char*)pBuffer+2, len-2);
            break;
        }

        case PacketId::PI_COMMAND: {
            printPacketCommand((char*)pBuffer+2, len-2);
            break;
        }

        case PacketId::PI_SETTINGS: {
            printPacketSettings((char*)pBuffer+2, len-2);
            break;
        }
    
        default: {
            printf("- PacketId: UNRECOGNIZED (%i) \r\n", pBufferI16[0]);
            break;
        }
    }
}
