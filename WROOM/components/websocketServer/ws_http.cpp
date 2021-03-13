/**
 * Http server of 
 * 1. wifi connection web page
 * 2. handshake for websocket 
 */

#include "ws_http.h"
#include "ws_form.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
// #include <freertos/projdefs.h>
#include <fstream>

#include "logging.h"
#include "JSON.h"
#include "CPPNVS.h"
#include "FreeRTOSTimer.h"

#include "WebSocketFileTransfer.h"

#include "ws_ws.h"
#include "ws_fs.h"
#include "ws_wifi.h"
#include "ws_urlParser.h"

static const char tag[] = "ws_form";

HttpServer* pHttpServer;

// static void restartin5s(FreeRTOSTimer* pTimer) {
//     LOGD("restart in 5s");
//     esp_restart();
// }

static void wsHandshakeHandler(HttpRequest* pRequest, HttpResponse* pResponse) {
    if(pRequest->isWebsocket()) {
        wsOnConnected(pRequest->getWebSocket());
    }
}

WebSocketFileTransfer webSocketJsfileTransfer("/main");
static void wsJsfileHandshakeHandler(HttpRequest* pRequest, HttpResponse* pResponse) {
    if(pRequest->isWebsocket()) {
        webSocketJsfileTransfer.start(pRequest->getWebSocket(), true);
    }
}

extern void addWifiForm();
void createHttpServer() {
    pHttpServer = new HttpServer();
    pHttpServer->setRootPath(std::string(SPIFFS_MOUNTPOINT) + "/web");
    pHttpServer->setDirectoryListing(true);
    pHttpServer->addPathHandler(            // handler for ws commands from pxt
        HttpRequest::HTTP_METHOD_GET,
        "/ws",
        wsHandshakeHandler
    );
    pHttpServer->addPathHandler(            // handler for jsfile from pxt
        HttpRequest::HTTP_METHOD_GET,
        "/ws_jsfile",
        wsJsfileHandshakeHandler
    );
    addWifiForm();
    SRFormHandler::registerToServer(pHttpServer);
    pHttpServer->start(80);       // listen http handshake at port 80
}
