/**
 * Websocket server to communicate with browser
 */

#include "ws_ws.h"

#include <string>
#include <sstream>
#include <fstream>
#include <cstring>

#include "esp_heap_trace.h"
#include "esp_log.h"
#include "assert.h"
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

bool offline_mode = false;   // offline: 1, synchronization || development: 0

void SRWebSocketHandler::onClose() {
    ESP_LOGV(LOG_TAG, "on close");
    pWebSocket = NULL;
}
void SRWebSocketHandler::onMessage(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket){
    ESP_LOGV(LOG_TAG, "on message");
    wsOnMessageWs(pWebSocketInputStreambuf, pWebSocket);
}
void SRWebSocketHandler::onError(std::string error){
    ESP_LOGV(LOG_TAG, "on error");
    pWebSocket = NULL;
}

void wsOnConnected(WebSocket* pWS){
    ESP_LOGV(LOG_TAG, "Opened a Websocket connenction");
    pWebSocket = pWS;
    pWebSocket->setHandler(&webSocketHandler);
}

/*
static void saveToMainJsStream(const WebSocketInputStreambuf *content) {
    std::ofstream m_ofStream;

    std::string root_path = SPIFFS_MOUNTPOINT;
    m_ofStream.open(root_path + "/main/main.js", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    if (!m_ofStream.is_open()) {
        ESP_LOGV(LOG_TAG, "Failed to open file /spiffs/main/main.js for writing");
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
        ESP_LOGV(LOG_TAG, "Failed to open file /spiffs/main/main.js for writing");
        return;
    }

    m_ofStream.write(content, length);
    m_ofStream.close();

    ESP_LOGV(LOG_TAG, "File main.js written to /spiffs/main/main.js");
}

static void wsSend(void* data, size_t length) {
    if(!pWebSocket) {
        ESP_LOGV(LOG_TAG, "Unable to send packet, websocket is not connected");
        return;
    }
    pWebSocket->send((uint8_t*)data, length , WebSocket::SEND_TYPE_BINARY);
}

/**
 * Handle message from websocket
 */
void wsOnMessageWs(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket) {
    ESP_LOGD(LOG_TAG, "before wsOnMessageWs heap size: %d", esp_get_free_heap_size());

    int16_t packetId = pWebSocketInputStreambuf->sgetc();
    ESP_LOGD(LOG_TAG, "packet type: %i", packetId);


    size_t bufferSize = 4096;
    char* pBuffer = new char[bufferSize];
    std::streamsize ssize = pWebSocketInputStreambuf->sgetn(pBuffer, bufferSize);
    if(ssize>=bufferSize) {
        ESP_LOGD(LOG_TAG ,"File main.js to large!!!!!!!!!");
        delete [] pBuffer;
        return;
    }

    pWebSocketInputStreambuf->discard();

    ESP_LOGD(LOG_TAG, "+ WS packet");
    printPacket((const void*)pBuffer, ssize);

    switch (packetId)
    {
        case PacketId::PI_JSFILE: {
            // stop current running js task
            wsDeleteJsfileTask();
            
            saveToMainJs(pBuffer+2, ssize-2);
            //combineMainFiles();

            delete[] pBuffer;       // delete buffer to provide more space for jsfile task
            pBuffer = NULL;

            // return packet to pxt
            short* retBuffer = (short*)malloc(2 * sizeof(short));        // return packet for download success
            *retBuffer = PacketId::PI_JSFILE;
            *(retBuffer+1) = 1;
            wsSend((void*)retBuffer, 4);
            delete[] retBuffer;
            retBuffer = NULL;

            // run file or not
            if(!offline_mode) {  // do not run file in development mode
                break;
            }
            else {                  // run file
                // std::ifstream m_ifstream("/spiffs/main/runtime.js");
                // std::string str((std::istreambuf_iterator<char>(m_ifstream)),
                //     std::istreambuf_iterator<char>());
                // ESP_LOGD(LOG_TAG, "Start runtime file: %s", str.c_str());
                // m_ifstream.close();

                ESP_LOGD(LOG_TAG, "before wsCreateJsfileTask heap size: %d", esp_get_free_heap_size());

                wsCreateJsfileTask();
            }
            
            break;
        }

        case PacketId::PI_COMMAND: {
            UdpCom_ReceiveCommand((void*)(pBuffer+2), *(int16_t*)(&pBuffer[2]), 0);
            break;
        }

        case PacketId::PI_SETTINGS: {
            uint16_t* pBufferI16 = (uint16_t*)pBuffer;
            uint16_t id = pBufferI16[1];
            switch (id)
            {
                case PacketSettingsId::OFFLINE_MODE: {
                    bool new_offline_mode = pBufferI16[2];
                    if (new_offline_mode == offline_mode) break;
                    else offline_mode = new_offline_mode;
                    if(!offline_mode) {
                        ESP_LOGD(LOG_TAG, "switch to development mode, stop running jsfile task");
                        wsDeleteJsfileTask();
                        heap_trace_dump();
                        heap_trace_start(HEAP_TRACE_LEAKS);                        
                        printf("delete success");
                    }else if(!wsIsJsfileTaskRunning()){
                        ESP_LOGI(LOG_TAG, "before wsCreateJsfileTask heap size: %d", esp_get_free_heap_size());
                        ESP_LOGD(LOG_TAG, "switch to offline mode, start running jsfile task");
                        wsCreateJsfileTask();
                    }
                    break;
                }
                default:
                    ESP_LOGV(LOG_TAG, "Unknown packet settings id (%i)", pBufferI16[1]);
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
    ESP_LOGD(LOG_TAG, "+ SR Packet");
    printPacketCommand(ret.bytes + 2, ret.length);
    
    if (ret.count == 0) {
        // send packet to browser
        char* buf = (char*)malloc(ret.length+2);
        std::memcpy(buf+2, ret.bytes+2, ret.length);
        *(short*)buf = 2;
        wsSend(buf, ret.length+2);
        free(buf);
        ESP_LOGV(LOG_TAG, "Packet softrobot -> websocket");
    } else if (ret.count == 1) {
        // send packet to jsfile task
        // return_packet_to_jsfile(buffer, buffer_size);
        if(!wsIsJsfileTaskRunning()) return;
        if(!esp32_duk_context) return;
        
        lock_heap();
        if(!wsIsJsfileTaskRunning() || !esp32_duk_context) {
            unlock_heap();
            return;
        }

        commandMessageHandler(ret);
        ESP_LOGD(LOG_TAG, "Packet softrobot -> jsfile");
        
        unlock_heap();
    } else {
        ESP_LOGV(LOG_TAG, "Cannot find destination: %i", ret.count);
    }
}

void printPacketJsfile(const void* pBuffer, size_t len) {
    ESP_LOGD(LOG_TAG, "|- PacketId: PI_JSFILE");
    char buf[1024];
    memcpy(buf, pBuffer, len);
    buf[len] = '\0';
    ESP_LOGD(LOG_TAG, "|- Content: %s", buf);
}

void printPacketCommand(const void* pBuffer, size_t len) {
    int16_t* pBufferI16 = (int16_t*)pBuffer;
    ESP_LOGD(LOG_TAG, "|- PacketId: PI_COMMAND");

    uint16_t length = pBufferI16[0];
    assert(length == len);
    ESP_LOGD(LOG_TAG, "|- Content:");
    ESP_LOGD(LOG_TAG, "   |- Length: %i", length);
    ESP_LOGD(LOG_TAG, "   |- CommandId: %i", pBufferI16[1]);
    char buf[1024]={'\0'};
    for(size_t i = 2; i < len/2; i++){
        sprintf(buf+strlen(buf), "%i, ", pBufferI16[i]);
    }
    ESP_LOGD(LOG_TAG, "   |- Command: %s", buf);
}

void printPacketSettings(const void* pBuffer, size_t len) {
    int16_t* pBufferI16 = (int16_t*)pBuffer;
    ESP_LOGD(LOG_TAG, "|- PacketId: PI_SETTINGS");
    uint16_t id = pBufferI16[0];
    ESP_LOGD(LOG_TAG, "   |- Setting type: %s", getPacketSettingsIdStr(id).c_str());
    char buf[1024]={'\0'};
    switch (id)
    {
        case PacketSettingsId::OFFLINE_MODE:
            sprintf(buf, "%i ", pBufferI16[1]);
            break;
    
        default:
            break;
    }
    ESP_LOGD(LOG_TAG, "   |- Value: %s", buf);
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
            ESP_LOGD(LOG_TAG, "- PacketId: UNRECOGNIZED (%i)", pBufferI16[0]);
            break;
        }
    }
}

void printDTPacket(const void* pBuffer, size_t len) {
    ESP_LOGD(LOG_TAG, "+ DT packet");
    printPacketCommand(pBuffer, len);
}
