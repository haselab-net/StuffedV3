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
    SRWifiEventHandler srWifiEventHandler;
    void initInternal();
public:
    std::vector<WiFiAPRecord> scannedAPs;
    enum Status{
        WIFI_STA_DISCONNECTED,
        WIFI_STA_CONNECTING,
        WIFI_STA_CONNECTED,
        WIFI_STA_GOT_IP,
    } state;
    esp_netif_ip_info_t ipInfo;
    static SRWiFi wifi;
    static NVS* wifiNvs;
    enum {N_AP_RECORD_MAX = 10};
    SRWiFi();
    void init();        //  Init wifi and start WIFI_MODE_APSTA
    bool isAP();        //  is access point ?
	void startAP(const std::string& ssid, const std::string& passwd, wifi_auth_mode_t auth = WIFI_AUTH_OPEN);
	void startAP(const std::string& ssid, const std::string& passwd, wifi_auth_mode_t auth, uint8_t channel, bool ssid_hidden, uint8_t max_connection);
    void startAP();
    void stopAP();

    void connectAP(std::string ssid, std::string pass){
        connect(ssid, pass);
    }
    void connect(std::string ssid, std::string pass); //  connect to AP as an station (client).
    void disconnect();  //  disconnect from AP.

	void startScan();	//	Start scan. Wifi mode must be station or apSta. 
	void stopScan();	//	Stop scan and return ap list.
    std::string getStaPassword();
};
#endif
