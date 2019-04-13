/**
 * Http server of 
 * 1. wifi connection web page
 * 2. handshake for websocket 
 */

#include "ws_http.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
// #include <freertos/projdefs.h>
#include <fstream>

#include "logging.h"
#include "JSON.h"
#include "CPPNVS.h"
#include "FreeRTOSTimer.h"

#include "ws_ws.h"
#include "ws_fs.h"
#include "ws_wifi.h"
#include "ws_urlParser.h"

LOG_TAG("ws_http");

static HttpServer* pHttpServer;

// static void restartin5s(FreeRTOSTimer* pTimer) {
//     LOGD("restart in 5s");
//     esp_restart();
// }

static void wsHandshakeHandler(HttpRequest* pRequest, HttpResponse* pResponse) {
    if(pRequest->isWebsocket()) {
        wsOnConnected(pRequest->getWebSocket());
    }
}

static void httpWifiHtmlHandler(HttpRequest* pRequest, HttpResponse* pResponse) {
    std::ifstream fr;
    std::string root_path = SPIFFS_MOUNTPOINT;
    fr.open(root_path+"/web/selectAP.html");

    if(!fr.is_open()) {
        LOGD("Failed to open html file");
        return;
    }

    std::stringstream html_content;
    html_content << fr.rdbuf();
    pResponse->setStatus(200, "OK");
    pResponse->sendData(html_content.str());
    pResponse->close();

    fr.close();
}

static void httpWifiSetHandler(HttpRequest* pRequest, HttpResponse* pResponse) {
    std::string body = pRequest->getBody();
    urlParser up(body);

    printf("body: %s", body.c_str());
    printf("ssif: %s", up.getString("ssid").c_str());

    wifiNvs.set("ssid", up.getString("ssid"));
    wifiNvs.set("password", up.getString("password"));
    wifiNvs.set("ip", up.getString("ip"));
    wifiNvs.set("gw", up.getString("gw"));
    wifiNvs.set("netmask", up.getString("netmask"));

    pResponse->setStatus(200, "OK");
    std::string return_message = "Got data - try to connect to AP: " + up.getString("ssid") + ", with password: " + up.getString("password");
    pResponse->sendData(return_message);
    pResponse->close();

    wifi.connectAP(up.getString("ssid"), up.getString("password"), false);

    //esp_restart();

    // char timer_name[] = "rebootin5s";
    // FreeRTOSTimer timer(timer_name, (TickType_t)5000/10, false, NULL, restartin5s);
    // timer.start();
}

void createHttpServer() {
    pHttpServer = new HttpServer();
    pHttpServer->addPathHandler(
        HttpRequest::HTTP_METHOD_GET,
        "/",
        wsHandshakeHandler
    );
    pHttpServer->addPathHandler(
        HttpRequest::HTTP_METHOD_GET,
        "/wifi.html",
        httpWifiHtmlHandler
    );
    pHttpServer->addPathHandler(
        HttpRequest::HTTP_METHOD_POST,
        "/ssidSelected",
        httpWifiSetHandler
    );
    pHttpServer->start(8002);       // listen http handshake at port 8000
}


