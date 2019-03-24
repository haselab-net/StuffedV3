#include "ws_wifi.h"

#include "logging.h"

LOG_TAG("ws_wifi");

static WiFi wifi = WiFi();
static SRWifiEventHandler* wifiEventHandler;
NVS wifiNvs = NVS("wifinvs");

esp_err_t SRWifiEventHandler::apStart() {
    LOGD("Now serve as an access point");
    return ESP_OK;
}
esp_err_t SRWifiEventHandler::staConnected(system_event_sta_connected_t info) {
    LOGD("Now serve as a station");
    return ESP_OK;
}
esp_err_t SRWifiEventHandler::staGotIp(system_event_sta_got_ip_t info) {
    LOGD("GOT IP: %s", ip4addr_ntoa(&info.ip_info.ip));
    return ESP_OK;
}

void initWifi() {
    std::string ssid, password, ip, gw, netmask;
    esp_err_t rc = ESP_OK;
    rc = rc || wifiNvs.get("ssid",     &ssid);
    rc = rc || wifiNvs.get("password", &password);
    rc = rc || wifiNvs.get("ip",       &ip);
    rc = rc || wifiNvs.get("gw",       &gw);  
    rc = rc || wifiNvs.get("netmask",  &netmask);

    wifiEventHandler = new SRWifiEventHandler();
    wifi.setWifiEventHandler(wifiEventHandler);
    
    if(!rc) wifi.startAP("esp32-duktape", "");     // become AP
    else wifi.connectAP("haselabS", "2human2human2");           // become STA
}