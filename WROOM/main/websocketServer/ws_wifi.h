#ifndef WEBSOCKETSERVER_WS_WIFI_H_
#define WEBSOCKETSERVER_WS_WIFI_H_

#include "WiFiEventHandler.h"
#include "WiFi.h"
#include "CPPNVS.h"

class SRWiFi;
class SRWifiEventHandler: public WiFiEventHandler {
protected:
    SRWiFi* wifi;
	virtual esp_err_t staScanDone(system_event_sta_scan_done_t info);
	virtual esp_err_t apStaConnected(system_event_ap_staconnected_t info);
    virtual esp_err_t staConnected(system_event_sta_connected_t info);
    virtual esp_err_t staGotIp(system_event_sta_got_ip_t info);
    virtual esp_err_t staDisconnected(system_event_sta_disconnected_t info);
public:
    SRWifiEventHandler(SRWiFi* w);
    virtual ~SRWifiEventHandler(){}
};

class SRWiFi: public WiFi{
protected:
    SRWifiEventHandler eventHandler;
public:
    static SRWiFi wifi;
    static NVS wifiNvs;

    SRWiFi():eventHandler(this){}
    void init();
	void					  startScan();	//	Start scan. Wifi mode must be station or apSta. 
	std::vector<WiFiAPRecord> stopScan();	//	Stop scan and return ap list.

    void startAccessPoint();
};
#endif
