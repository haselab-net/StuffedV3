#include "ws_wifi.h"
#include "logging.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "GeneralUtils.h"
#include <string.h>

LOG_TAG("ws_wifi");

SRWifiEventHandler::SRWifiEventHandler(SRWiFi* w):wifi(w){

}

esp_err_t SRWifiEventHandler::apStaConnected(system_event_ap_staconnected_t info){
    LOGD("SoftAP got connection");
    
    return ESP_OK;
}

esp_err_t SRWifiEventHandler::staConnected(system_event_sta_connected_t info) {
    LOGD("Now serve as a station");
    return ESP_OK;
}
esp_err_t SRWifiEventHandler::staGotIp(system_event_sta_got_ip_t info) {
    LOGI("GOT IP: %s", ip4addr_ntoa(&info.ip_info.ip));
    return ESP_OK;
}
esp_err_t SRWifiEventHandler::staDisconnected(system_event_sta_disconnected_t info) {
    switch (info.reason)
    {
        case WIFI_REASON_NO_AP_FOUND:
            LOGD("Unable to find AP %s, work as AP now", info.ssid);
            wifi->startAccessPoint();
            break;
        case WIFI_REASON_AUTH_FAIL:
            LOGD("Unable to connect to AP %s, work as AP now", info.ssid);
            wifi->startAccessPoint();
            break;
    
        default:
            LOGD("Unknown sta disconnected event: %i, work as AP now", info.reason);
            wifi->startAccessPoint();
            break;
    }
    return ESP_OK;
}
esp_err_t SRWifiEventHandler::staScanDone(system_event_sta_scan_done_t info){
    return ESP_OK;
}



SRWiFi SRWiFi::wifi;
NVS SRWiFi::wifiNvs("wifinvs");
void SRWiFi::startAccessPoint() {
    //  Set ssid and start access point
    uint8_t mac[6];
	esp_read_mac(mac, ESP_MAC_WIFI_STA);	// 6 bytes
    char buf[33];
    strcpy(buf, "Nuibot ");
    for(int i=0; i<6; ++i){
        sprintf(buf+strlen(buf), "%02X", mac[i]);
    }
    startAP(buf, "");
}


void SRWiFi::init() {
    std::string ssid="", password="", ip="", gw="", netmask="";
    wifiNvs.get("ssid",     &ssid);
    wifiNvs.get("password", &password);
    wifiNvs.get("ip",       &ip);
    wifiNvs.get("gw",       &gw);  
    wifiNvs.get("netmask",  &netmask);
    wifiNvs.commit();

    setWifiEventHandler(&eventHandler);    
    if (ssid.size()==0||password.size()==0){
        startAccessPoint();     // start AP
    }
    else{
        startAccessPoint();     // start AP and 
        connectAP(ssid, password, false, WIFI_MODE_APSTA);     // move to APSTA
    } 
}


void SRWiFi::startScan(){
	wifi_scan_config_t scan_config;
    memset(&scan_config, 0, sizeof(scan_config));
    scan_config.show_hidden = true;
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, false));   //  start non blocking ap scan.
}
std::vector<WiFiAPRecord> SRWiFi::stopScan(){
	std::vector<WiFiAPRecord> apRecords;
    uint16_t apCount;  // Number of access points available.
	esp_err_t rc = ::esp_wifi_scan_get_ap_num(&apCount);
	if (rc != ESP_OK) {
		ESP_LOGE(tag, "esp_wifi_scan_get_ap_num: %d", rc);
		return apRecords;
	} else {
		ESP_LOGD(tag, "Count of found access points: %d", apCount);
	}

	wifi_ap_record_t* list = (wifi_ap_record_t*) malloc(sizeof(wifi_ap_record_t) * apCount);
	if (list == nullptr) {
		ESP_LOGE(tag, "Failed to allocate memory");
		return apRecords;
	}

	esp_err_t errRc = ::esp_wifi_scan_get_ap_records(&apCount, list);
	if (errRc != ESP_OK) {
		ESP_LOGE(tag, "esp_wifi_scan_get_ap_records: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
		abort();
	}

	for (uint16_t i = 0; i < apCount; i++) {
		WiFiAPRecord wifiAPRecord;
		memcpy(wifiAPRecord.m_bssid, list[i].bssid, 6);
		wifiAPRecord.m_ssid	 = std::string((char*) list[i].ssid);
		wifiAPRecord.m_authMode = list[i].authmode;
		wifiAPRecord.m_rssi	 = list[i].rssi;
		apRecords.push_back(wifiAPRecord);
	}
	free(list);   // Release the storage allocated to hold the records.
	std::sort(apRecords.begin(),
		apRecords.end(),
		[](const WiFiAPRecord& lhs, const WiFiAPRecord& rhs){ return lhs.m_rssi > rhs.m_rssi; });
	return apRecords;
}

