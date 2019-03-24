/**
 * Create Http and Websocket Server
 */

#include "ws_server.h"

#include "logging.h"
#include "HttpServer.h"

LOG_TAG("ws_server");

static HttpServer* pHttpServer;
static WebSocket* pWebSocket;

class SRWebSocketHandler: public WebSocketHandler {
    void onClose() {
        LOGD("on close");
    }
    void onMessage(WebSocketInputStreambuf* pWebSocketInputStreambuf, WebSocket* pWebSocket){
        LOGD("on message");
    }
	void onError(std::string error){
        LOGD("on error");
    }
};

static void establishWsConnection(WebSocket* pWS) {
    pWebSocket = pWS;
}

static void wsHandshakeHandler(HttpRequest* pRequest, HttpResponse* pResponse) {
    if(pRequest->isWebsocket()) {
        establishWsConnection(pRequest->getWebSocket());
    }
}

static void createHttpServer() {
    pHttpServer = new HttpServer();
    pHttpServer->addPathHandler(
        HttpRequest::HTTP_METHOD_GET,
        "",
        wsHandshakeHandler
    );
    pHttpServer->start(8002);       // listen http handshake at port 8000
}

void createServer() {
    createHttpServer();
    LOGD("WebSocket server running on port 8002");
}