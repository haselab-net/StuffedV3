#ifndef WEBSOCKETSERVER_WS_WIFI_H_
#define WEBSOCKETSERVER_WS_WIFI_H_

#include <esp_netif.h>
#include <vector>
#include "CPPNVS.h"

struct WiFiAPRecord {
	uint8_t        bssid[6];
	int8_t         rssi;
	std::string    ssid;
	wifi_auth_mode_t authMode;
};

class SRWiFi{
protected:
    void initInternal();
    esp_netif_t* netifAp = NULL;
    esp_netif_t* netifSta = NULL;

    static void wifi_event_handler(void* ctx, esp_event_base_t event_base, int32_t event_id, void* event_data);
    static void ip_event_handler(void* ctx, esp_event_base_t event_base, int32_t event_id, void* event_data);

    esp_err_t handleStaGotIp(ip_event_got_ip_t* info);
    esp_err_t handleStaDisconnected(wifi_event_sta_disconnected_t* info);
    esp_err_t handleStaScanDone(wifi_event_sta_scan_done_t* info);

public:
    static NVS* wifiNvs;
    static SRWiFi wifi;
    esp_netif_ip_info_t ipInfo; //  Current station ip info. 
    enum Status{
        WIFI_STA_DISCONNECTED,
        WIFI_STA_CONNECTING,
        WIFI_STA_CONNECTED,
        WIFI_STA_GOT_IP,
    } state = WIFI_STA_DISCONNECTED;
    std::vector<WiFiAPRecord> scannedAPs;   //  access point list

    enum {N_AP_RECORD_MAX = 10};
    SRWiFi();
    void init();        //  Init wifi and start WIFI_MODE_APSTA
    bool isAP();        //  is access point ?
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
    std::string getStaSSID();
};
#endif
