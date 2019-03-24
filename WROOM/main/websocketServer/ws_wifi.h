#ifndef WEBSOCKETSERVER_WS_WIFI_H_
#define WEBSOCKETSERVER_WS_WIFI_H_

#include "WiFiEventHandler.h"
#include "WiFi.h"
#include "CPPNVS.h"

void initWifi();

class SRWifiEventHandler: public WiFiEventHandler {
    esp_err_t apStart();
    esp_err_t staConnected(system_event_sta_connected_t info);
    esp_err_t staGotIp(system_event_sta_got_ip_t info);
};

extern NVS wifiNvs;

#endif