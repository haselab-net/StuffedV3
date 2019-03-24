/**
 * Http server of 
 * 1. wifi connection web page
 * 2. handshake for websocket 
 */

#include "ws_http.h"

#include "logging.h"

#include "ws_ws.h"

static HttpServer* pHttpServer;

static void wsHandshakeHandler(HttpRequest* pRequest, HttpResponse* pResponse) {
    if(pRequest->isWebsocket()) {
        wsOnConnected(pRequest->getWebSocket());
    }
}

void createHttpServer() {
    pHttpServer = new HttpServer();
    pHttpServer->addPathHandler(
        HttpRequest::HTTP_METHOD_GET,
        "",
        wsHandshakeHandler
    );
    pHttpServer->start(8002);       // listen http handshake at port 8000
}


