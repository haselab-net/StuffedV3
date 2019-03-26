/**
 * Http server of 
 * 1. wifi connection web page
 * 2. handshake for websocket 
 */

#include "ws_http.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <fstream>

#include "logging.h"
#include "JSON.h"
#include "CPPNVS.h"
#include "FreeRTOSTimer.h"

#include "ws_ws.h"
#include "ws_fs.h"
#include "ws_wifi.h"

LOG_TAG("ws_http");

static HttpServer* pHttpServer;

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

    std::cout << "html_file: " << html_content.str() << std::endl;
}

static void httpWifiSetHandler(HttpRequest* pRequest, HttpResponse* pResponse) {
    std::string body = pRequest->getBody();
    JsonObject jo = JSON::parseObject(body);

    wifiNvs.set("ssid", jo.getString("ssid"));
    wifiNvs.set("password", jo.getString("password"));
    wifiNvs.set("ip", jo.getString("ip"));
    wifiNvs.set("gw", jo.getString("gw"));
    wifiNvs.set("netmask", jo.getString("netmask"));

    pResponse->setStatus(200, "Got data - rebooting in 5s");
    pResponse->close();

    // TODO fix reboot
    vTaskDelay(500000);
    esp_restart();
    // FreeRTOSTimer timer("rebootin5s", pdMs_TO_TICKS(5000), false, NULL, esp_restart);
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


