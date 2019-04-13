#include "ws_wifi.h"

#include "logging.h"

LOG_TAG("ws_wifi");

static WiFi wifi = WiFi();
static SRWifiEventHandler* wifiEventHandler;
NVS wifiNvs = NVS("wifinvs");

static void becomeAccessPoint() {
    wifi.startAP("esp32-duktape-gzl", "");
}

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
esp_err_t SRWifiEventHandler::staDisconnected(system_event_sta_disconnected_t info) {
    switch (info.reason)
    {
        case WIFI_REASON_NO_AP_FOUND || WIFI_REASON_AUTH_FAIL:
            LOGD("Unable to connect to AP %s, work as AP now", info.ssid);
            becomeAccessPoint();
            break;
    
        default:
            LOGD("Unknown sta disconnected event: %i, work as AP now", info.reason);
            becomeAccessPoint();
            break;
    }
    return ESP_OK;
}

void initWifi() {
    std::string ssid="", password="", ip="", gw="", netmask="";

    wifiNvs.get("ssid",     &ssid);
    wifiNvs.get("password", &password);
    wifiNvs.get("ip",       &ip);
    wifiNvs.get("gw",       &gw);  
    wifiNvs.get("netmask",  &netmask);
    wifiNvs.commit();

    wifiEventHandler = new SRWifiEventHandler();
    wifi.setWifiEventHandler(wifiEventHandler);
    
    if(ssid.size()==0||password.size()==0) becomeAccessPoint();    // become AP
    else wifi.connectAP(ssid, password, false);           // become STA
}