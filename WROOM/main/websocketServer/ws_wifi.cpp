#include "ws_wifi.h"
#include <logging.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <GeneralUtils.h>
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
    wifi->state = SRWiFi::WIFI_STA_CONNECTED;
    return ESP_OK;
}
esp_err_t SRWifiEventHandler::staGotIp(system_event_sta_got_ip_t info) {
    LOGI("GOT IP: %s", ip4addr_ntoa(&info.ip_info.ip));
    wifi->state = SRWiFi::WIFI_STA_GOT_IP;
    memcpy(&wifi->ipInfo, &info.ip_info, sizeof(wifi->ipInfo));
    
    wifi_config_t wc;
	esp_wifi_get_config(WIFI_IF_STA, &wc);
    int pos = -1;
    for(int i=0; i<SRWiFi::N_AP_RECORD_MAX; ++i){
        char ssidKey[] = "ssid0";
        ssidKey[4] = '0' + i; 
        std::string ssid;
        SRWiFi::wifiNvs.get(ssidKey, ssid);
        if (ssid.compare((char*)wc.sta.ssid) == 0){
            pos = i;
            break;
        }
    }
    if (pos == -1){
        SRWiFi::wifiNvs.get("lastAP", pos);
        pos ++;
        if (pos < 0) pos = 0;
        if (pos >= SRWiFi::N_AP_RECORD_MAX) pos = 0;

        for(int i=0; i<SRWiFi::N_AP_RECORD_MAX; ++i){
            char ssidKey[] = "ssid0";
            ssidKey[4] = '0' + i; 
            std::string ssid;
            SRWiFi::wifiNvs.get(ssidKey, ssid);
            if (ssid.length() == 0){
                pos = i;
                break;
            }
        }    
    }
    char ssidKey[] = "ssid0"; ssidKey[4] = '0' + pos;
    char passKey[] = "pass0"; passKey[4] = '0' + pos;
    ESP_LOGI(tag, "WriteNVS %s=%s", ssidKey, wc.sta.ssid);
    SRWiFi::wifiNvs.set("lastAP", pos);
    SRWiFi::wifiNvs.set(ssidKey, std::string((char*)wc.sta.ssid));
    SRWiFi::wifiNvs.set(passKey, std::string((char*)wc.sta.password));
    SRWiFi::wifiNvs.commit();
    return ESP_OK;
}
esp_err_t SRWifiEventHandler::staDisconnected(system_event_sta_disconnected_t info) {
    wifi->state = SRWiFi::WIFI_STA_DISCONNECTED;
    switch (info.reason)
    {
        case WIFI_REASON_NO_AP_FOUND:
            LOGD("Unable to find AP %s, work as AP now", info.ssid);
            break;
        case WIFI_REASON_AUTH_FAIL:
            LOGD("Unable to connect to AP %s, work as AP now", info.ssid);
            break;
    
        default:
            LOGD("Unknown sta disconnected event: %i, work as AP now", info.reason);
            break;
    }
    return ESP_OK;
}
esp_err_t SRWifiEventHandler::staScanDone(system_event_sta_scan_done_t info){
    //  check nvs and try to connect
    wifi->stopScan();
    vTaskDelay(100);
    int lastAP;
    if (SRWiFi::wifiNvs.get("lastAP", lastAP) == ESP_OK){
        if (lastAP < 0) lastAP = 0;
        if (lastAP >= SRWiFi::N_AP_RECORD_MAX) lastAP = SRWiFi::N_AP_RECORD_MAX-1;
        int i=lastAP;
        std::string ssid, pass;
        do{
            char ssidKey[] = "ssid0"; ssidKey[4] = '0'+i;
            if (SRWiFi::wifiNvs.get(ssidKey, ssid) == ESP_OK){
                for(WiFiAPRecord& ap : wifi->scannedAPs){
                    ESP_LOGI(tag, "SRWifiEventHandler::staScanDone found=%s try=%s", ap.m_ssid.c_str(), ssid.c_str());
                    if (ap.m_ssid == ssid){
                        char passKey[] = "pass0"; passKey[4] = '0'+i;
                        SRWiFi::wifiNvs.get(passKey, pass);
                        ESP_LOGI(tag, "SRWifiEventHandler::staScanDone connect ssid=%s pass=%s", ssid.c_str(), pass.c_str());
                        wifi->connectAP(ssid, pass);
                        break;
                    }
                }
            }else{
                ESP_LOGI(tag, "Failed to get %s", ssidKey);
            }
            ESP_LOGI(tag, "staScannDone %d", i);
            i--;
            if (i<0) i = SRWiFi::N_AP_RECORD_MAX-1;
        }while(i!=lastAP);
    }
    return ESP_OK;
}

SRWiFi SRWiFi::wifi;
NVS SRWiFi::wifiNvs("wifinvs");
SRWiFi::SRWiFi():srWifiEventHandler(this){
    memset(&ipInfo, 0, sizeof(ipInfo));
    state = WIFI_STA_DISCONNECTED;
}
void SRWiFi::init() {
    //  set SREventHandler
    setWifiEventHandler(&srWifiEventHandler);

    //  make ssid
    uint8_t mac[6];
	esp_read_mac(mac, ESP_MAC_WIFI_STA);	// 6 bytes
    char ssid[33];
    strcpy(ssid, "Nuibot ");
    for(int i=0; i<6; ++i){
        sprintf(ssid+strlen(ssid), "%02X", mac[i]);
    }
    startAP(ssid, "");
    esp_wifi_set_mode(WIFI_MODE_APSTA);
    startScan();
}
void SRWiFi::connectAP(std::string ssid, std::string pass){
    state = WIFI_STA_CONNECTING;
	m_apConnectionStatus = UINT8_MAX;
    wifi_config_t sta_config;
    ::memset(&sta_config, 0, sizeof(sta_config));
    ::memcpy(sta_config.sta.ssid, ssid.data(), ssid.size());
    ::memcpy(sta_config.sta.password, pass.data(), pass.size());
    sta_config.sta.bssid_set = 0;
    esp_err_t errRc = ::esp_wifi_set_config(WIFI_IF_STA, &sta_config);
    if (errRc != ESP_OK) {
        ESP_LOGE(tag, "esp_wifi_set_config: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
        abort();
    }
    errRc = ::esp_wifi_connect();
    if (errRc != ESP_OK) {
        ESP_LOGE(tag, "esp_wifi_connect: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
        abort();
    }
}
void SRWiFi::startScan(){
	wifi_scan_config_t scan_config;
    memset(&scan_config, 0, sizeof(scan_config));
    scan_config.show_hidden = true;
    scan_config.scan_type = WIFI_SCAN_TYPE_ACTIVE;
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, false));   //  start non blocking ap scan.
}
void SRWiFi::stopScan(){
    uint16_t apCount;  // Number of access points available.
	esp_err_t rc = ::esp_wifi_scan_get_ap_num(&apCount);
	if (rc != ESP_OK) {
		ESP_LOGE(tag, "esp_wifi_scan_get_ap_num: %d", rc);
		return;
	} else {
		ESP_LOGD(tag, "Count of found access points: %d", apCount);
	}
	wifi_ap_record_t* list = (wifi_ap_record_t*) malloc(sizeof(wifi_ap_record_t) * apCount);
	if (list == nullptr) {
		ESP_LOGE(tag, "Failed to allocate memory");
		return;
	}
	esp_err_t errRc = ::esp_wifi_scan_get_ap_records(&apCount, list);
	if (errRc != ESP_OK) {
		ESP_LOGE(tag, "esp_wifi_scan_get_ap_records: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
		abort();
	}
    scannedAPs.clear();
    scannedAPs.reserve(apCount);
	for (uint16_t i = 0; i < apCount; i++) {
		WiFiAPRecord wifiAPRecord;
		memcpy(wifiAPRecord.m_bssid, list[i].bssid, 6);
		wifiAPRecord.m_ssid	 = std::string((char*) list[i].ssid);
		wifiAPRecord.m_authMode = list[i].authmode;
		wifiAPRecord.m_rssi	 = list[i].rssi;
        scannedAPs.push_back(wifiAPRecord);
	}
	free(list);   // Release the storage allocated to hold the records.
	std::sort(scannedAPs.begin(),
		scannedAPs.end(),
		[](const WiFiAPRecord& lhs, const WiFiAPRecord& rhs){ return lhs.m_rssi > rhs.m_rssi; });
}
