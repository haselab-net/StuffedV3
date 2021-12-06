#include "SRWifi.h"
#include <logging.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <GeneralUtils.h>
#include <string.h>

LOG_TAG("SRWiFi");

inline uint32_t ipv4addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d){
    return d << 24 | c << 16 | b << 8 | a;
}

const char* ipEventString[] = {
    "IP_EVENT_STA_GOT_IP",               /*!< station got IP from connected AP */
    "IP_EVENT_STA_LOST_IP",              /*!< station lost IP and the IP is reset to 0 */
    "IP_EVENT_AP_STAIPASSIGNED",         /*!< soft-AP assign an IP to a connected station */
    "IP_EVENT_GOT_IP6",                  /*!< station or ap or ethernet interface v6IP addr is preferred */
    "IP_EVENT_ETH_GOT_IP",               /*!< ethernet got IP from connected AP */
    "IP_EVENT_PPP_GOT_IP",               /*!< PPP interface got IP */
    "IP_EVENT_PPP_LOST_IP",              /*!< PPP interface lost IP */
};

const char* wifiEventString[] = {
    "WIFI_EVENT_WIFI_READY",               /**< ESP32 WiFi ready */
    "WIFI_EVENT_SCAN_DONE",                /**< ESP32 finish scanning AP */
    "WIFI_EVENT_STA_START",                /**< ESP32 station start */
    "WIFI_EVENT_STA_STOP",                 /**< ESP32 station stop */
    "WIFI_EVENT_STA_CONNECTED",            /**< ESP32 station connected to AP */
    "WIFI_EVENT_STA_DISCONNECTED",         /**< ESP32 station disconnected from AP */
    "WIFI_EVENT_STA_AUTHMODE_CHANGE",      /**< the auth mode of AP connected by ESP32 station changed */

    "WIFI_EVENT_STA_WPS_ER_SUCCESS",       /**< ESP32 station wps succeeds in enrollee mode */
    "WIFI_EVENT_STA_WPS_ER_FAILED",        /**< ESP32 station wps fails in enrollee mode */
    "WIFI_EVENT_STA_WPS_ER_TIMEOUT",       /**< ESP32 station wps timeout in enrollee mode */
    "WIFI_EVENT_STA_WPS_ER_PIN",           /**< ESP32 station wps pin code in enrollee mode */
    "WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP",   /**< ESP32 station wps overlap in enrollee mode */

    "WIFI_EVENT_AP_START",                 /**< ESP32 soft-AP start */
    "WIFI_EVENT_AP_STOP",                  /**< ESP32 soft-AP stop */
    "WIFI_EVENT_AP_STACONNECTED",          /**< a station connected to ESP32 soft-AP */
    "WIFI_EVENT_AP_STADISCONNECTED",       /**< a station disconnected from ESP32 soft-AP */
    "WIFI_EVENT_AP_PROBEREQRECVED",        /**< Receive probe request packet in soft-AP interface */

    "WIFI_EVENT_FTM_REPORT",               /**< Receive report of FTM procedure */

    /* Add next events after this only */
    "WIFI_EVENT_STA_BSS_RSSI_LOW",         /**< AP's RSSI crossed configured threshold */
    "WIFI_EVENT_ACTION_TX_STATUS",         /**< Status indication of Action Tx operation */
    "WIFI_EVENT_ROC_DONE",                 /**< Remain-on-Channel operation complete */

    "WIFI_EVENT_STA_BEACON_TIMEOUT",       /**< ESP32 station beacon timeout */
};

void SRWiFi::ip_event_handler(void* ctx, esp_event_base_t event_base, int32_t event_id, void* event_data){
    SRWiFi* wifi = (SRWiFi*)ctx;
    LOGI("IP event %s", ipEventString[event_id]);
    switch(event_id){
        case IP_EVENT_STA_GOT_IP: {
            wifi->handleStaGotIp((ip_event_got_ip_t*) event_data);
            break;
        }
    }
}

void SRWiFi::wifi_event_handler(void* ctx, esp_event_base_t event_base, int32_t event_id, void* event_data){
    //  LOGI("Wifi event %s", wifiEventString[event_id]);
    SRWiFi* wifi = (SRWiFi*)ctx;
    switch(event_id){
        case WIFI_EVENT_AP_START: {
            //wifi->handleApStart();
            break;
        }

        case WIFI_EVENT_AP_STOP: {
            //wifi->handleApStop();
            break;
        }

        case WIFI_EVENT_AP_STACONNECTED: {
            //wifi->handleApStaConnected((wifi_event_ap_staconnected_t*) event_data);
            break;
        }

        case WIFI_EVENT_AP_STADISCONNECTED: {
            //wifi->handleApStaDisconnected((wifi_event_sta_disconnected_t*)event_data);
            break;
        }

        case WIFI_EVENT_SCAN_DONE: {
            wifi->handleStaScanDone((wifi_event_sta_scan_done_t*)event_data);
            break;
        }

        case WIFI_EVENT_STA_AUTHMODE_CHANGE: {
            //wifi->handleStaAuthChange((wifi_event_sta_authmode_change_t)*event_data);
            break;
        }

        case WIFI_EVENT_STA_CONNECTED: {
            //wifi->handleStaConnected((wifi_event_sta_connected_t)* event_data);
            break;
        }

        case WIFI_EVENT_STA_DISCONNECTED: {
            wifi->handleStaDisconnected((wifi_event_sta_disconnected_t*) event_data);
            break;
        }

        case WIFI_EVENT_STA_START: {
            //wifi->handleStaStart();
            break;
        }

        case WIFI_EVENT_STA_STOP: {
            //wifi->handleStaStop();
            break;
        }

        case WIFI_EVENT_WIFI_READY: {
            //wifi->handleWifiReady();
            break;
        }
    }
}

esp_err_t SRWiFi::handleStaGotIp(ip_event_got_ip_t* info) {
    LOGI("WiFi got IP as a station: %s", ip4addr_ntoa((ip4_addr_t*)&info->ip_info.ip));
    this->state = SRWiFi::WIFI_STA_GOT_IP;
    memcpy(&this->ipInfo, &info->ip_info, sizeof(this->ipInfo));

    wifi_config_t wc;
	esp_wifi_get_config(WIFI_IF_STA, &wc);
    int pos = -1;
    for(int i=0; i<SRWiFi::N_AP_RECORD_MAX; ++i){
        char ssidKey[] = "ssid0";
        ssidKey[4] = '0' + i;
        std::string ssid;
        SRWiFi::wifiNvs->get(ssidKey, ssid);
        if (ssid.compare((char*)wc.sta.ssid) == 0){
            pos = i;
            break;
        }
    }
    if (pos == -1){
        SRWiFi::wifiNvs->get("lastAP", pos);
        pos ++;
        if (pos < 0) pos = 0;
        if (pos >= SRWiFi::N_AP_RECORD_MAX) pos = 0;

        for(int i=0; i<SRWiFi::N_AP_RECORD_MAX; ++i){
            char ssidKey[] = "ssid0";
            ssidKey[4] = '0' + i;
            std::string ssid;
            SRWiFi::wifiNvs->get(ssidKey, ssid);
            if (ssid.length() == 0){
                pos = i;
                break;
            }
        }
    }
    char ssidKey[] = "ssid0"; ssidKey[4] = '0' + pos;
    char passKey[] = "pass0"; passKey[4] = '0' + pos;
    //LOGI("WriteNVS %s=%s", ssidKey, wc.sta.ssid);
    SRWiFi::wifiNvs->set("lastAP", pos);
    SRWiFi::wifiNvs->set(ssidKey, std::string((char*)wc.sta.ssid));
    SRWiFi::wifiNvs->set(passKey, std::string((char*)wc.sta.password));
    SRWiFi::wifiNvs->commit();

    SRWiFi::wifi.scannedAPs.clear();
    SRWiFi::wifi.scannedAPs.shrink_to_fit();
    return ESP_OK;
}
esp_err_t SRWiFi::handleStaDisconnected(wifi_event_sta_disconnected_t* info) {
    this->state = SRWiFi::WIFI_STA_DISCONNECTED;
    switch (info->reason)
    {
        case WIFI_REASON_NO_AP_FOUND:
            LOGD("Unable to find AP %s, work as AP now", info->ssid);
            break;
        case WIFI_REASON_AUTH_FAIL:
            LOGD("Unable to connect to AP %s, work as AP now", info->ssid);
            break;

        default:
            LOGD("Unknown sta disconnected event: %i, work as AP now", info->reason);
            break;
    }
    return ESP_OK;
}
esp_err_t SRWiFi::handleStaScanDone(wifi_event_sta_scan_done_t* info){
    //  check nvs and try to connect
    this->stopScan();
    vTaskDelay(100);
    int lastAP;
    if (SRWiFi::wifiNvs->get("lastAP", lastAP) == ESP_OK){
        if (lastAP < 0) lastAP = 0;
        if (lastAP >= SRWiFi::N_AP_RECORD_MAX) lastAP = SRWiFi::N_AP_RECORD_MAX-1;
        int i=lastAP;
        std::string ssid, pass;
        do{
            char ssidKey[] = "ssid0"; ssidKey[4] = '0'+i;
            if (SRWiFi::wifiNvs->get(ssidKey, ssid) == ESP_OK){
                for(WiFiAPRecord& ap : this->scannedAPs){
                    //LOGI("SRWifiEventHandler::staScanDone found=%s try=%s", ap.m_ssid.c_str(), ssid.c_str());
                    if (ap.ssid == ssid){
                        char passKey[] = "pass0"; passKey[4] = '0'+i;
                        SRWiFi::wifiNvs->get(passKey, pass);
                        //LOGI("SRWifiEventHandler::staScanDone connect ssid=%s pass=%s", ssid.c_str(), pass.c_str());
                        this->connect(ssid, pass);
                        break;
                    }
                }
            }
            i--;
            if (i<0) i = SRWiFi::N_AP_RECORD_MAX-1;
        }while(i!=lastAP);
    }
    return ESP_OK;
}

SRWiFi SRWiFi::wifi;
NVS* SRWiFi::wifiNvs = NULL;
SRWiFi::SRWiFi(){
    memset(&ipInfo, 0, sizeof(ipInfo));
}
void SRWiFi::init() {
    initInternal();
    //  set SREventHandler
    LOGD("Free heap after setEventHandler: %d", esp_get_free_heap_size());
    startAP();
    LOGD("Free heap after startAP: %d", esp_get_free_heap_size());
    startScan();
    LOGD("Free heap after scan: %d", esp_get_free_heap_size());
}

void SRWiFi::initInternal(){
    if (wifiNvs) return;

    wifiNvs = new NVS("wifinvs");
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_err_t errRc = ::esp_wifi_init(&cfg);
    if (errRc != ESP_OK) {
        LOGE("esp_wifi_init: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
        abort();
    }

    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, this, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        IP_EVENT, ESP_EVENT_ANY_ID, &ip_event_handler, this, NULL));

    errRc = ::esp_wifi_set_storage(WIFI_STORAGE_RAM);
    if (errRc != ESP_OK) {
        LOGE("esp_wifi_set_storage: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
        abort();
    }

    if (!netifAp){
		this->netifAp = esp_netif_create_default_wifi_ap();
	}
    if (!netifSta){
		this->netifSta = esp_netif_create_default_wifi_sta();
	}
}

bool SRWiFi::isAP(){
    wifi_mode_t mode;
    esp_wifi_get_mode(&mode);
    if (mode == WIFI_MODE_AP || mode == WIFI_MODE_APSTA){
        return true;
    }
    return false;
}
void SRWiFi::startAP(){
    //  make ssid
    uint8_t mac[6];
	esp_read_mac(mac, ESP_MAC_WIFI_STA);	// 6 bytes
    char ssid[33];
    strcpy(ssid, "Nuibot ");
    for(int i=3; i<6; ++i){ //  0-2 is the same 30AEA4
        sprintf(ssid+strlen(ssid), "%02X", mac[i]);
    }
    startAP(ssid, "", WIFI_AUTH_OPEN, 0, false, 4);
}
void SRWiFi::startAP(const std::string& ssid, const std::string& password, wifi_auth_mode_t auth, uint8_t channel, bool ssid_hidden, uint8_t max_connection) {
	initInternal();
    esp_wifi_set_mode(WIFI_MODE_APSTA);
    LOGD(">> startAP: ssid: %s", ssid.c_str());
	esp_err_t errRc = ::esp_wifi_set_mode(WIFI_MODE_APSTA);
	if (errRc != ESP_OK) {
		LOGE("esp_wifi_set_mode: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
		abort();
	}
	// Build the apConfig structure.
	wifi_config_t apConfig;
	::memset(&apConfig, 0, sizeof(apConfig));
	::memcpy(apConfig.ap.ssid, ssid.data(), ssid.size());
	apConfig.ap.ssid_len = ssid.size();
	::memcpy(apConfig.ap.password, password.data(), password.size());
	apConfig.ap.channel         = channel;
	apConfig.ap.authmode        = auth;
	apConfig.ap.ssid_hidden     = (uint8_t) ssid_hidden;
	apConfig.ap.max_connection  = max_connection;
	apConfig.ap.beacon_interval = 100;
	errRc = ::esp_wifi_set_config(WIFI_IF_AP, &apConfig);
	if (errRc != ESP_OK) {
		LOGE("esp_wifi_set_config: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
		abort();
	}

	errRc = ::esp_wifi_start();
	if (errRc != ESP_OK) {
		LOGE("esp_wifi_start: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
		abort();
	}

    ESP_ERROR_CHECK(esp_netif_dhcps_stop(netifAp));
    esp_netif_ip_info_t ipInfoAp;
    ipInfoAp.ip.addr = ipv4addr(192,168,4,1);
    ipInfoAp.netmask.addr = ipv4addr(255,255,255,0);
    ipInfoAp.gw.addr = ipInfoAp.ip.addr;
    errRc = esp_netif_set_ip_info(this->netifAp, &ipInfoAp);
	if (errRc != ESP_OK) {
		LOGE("esp_netif_set_ip_info: rc=0x%x %s", errRc, GeneralUtils::errorToString(errRc));
	}
    ESP_ERROR_CHECK(esp_netif_dhcps_start(netifAp));

	LOGD("<< startAP");
}
void SRWiFi::stopAP(){
	esp_err_t errRc = esp_netif_dhcps_stop(this->netifAp);
	if (errRc != ESP_OK) {
		LOGE("tcpip_adapter_dhcps_stop: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
	}
    esp_wifi_set_mode(WIFI_MODE_STA);
}
void SRWiFi::connect(std::string ssid, std::string pass){
    state = WIFI_STA_CONNECTING;
    wifi_config_t sta_config;
    ::memset(&sta_config, 0, sizeof(sta_config));
    ::memcpy(sta_config.sta.ssid, ssid.data(), ssid.size());
    ::memcpy(sta_config.sta.password, pass.data(), pass.size());
    sta_config.sta.bssid_set = 0;
    esp_err_t errRc = ::esp_wifi_set_config(WIFI_IF_STA, &sta_config);
    if (errRc != ESP_OK) {
        LOGE("esp_wifi_set_config: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
    }
    errRc = ::esp_wifi_connect();
    if (errRc != ESP_OK) {
        LOGE("esp_wifi_connect: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
    }
}
void SRWiFi::disconnect(){
    esp_err_t errRc = esp_wifi_disconnect();
    state = WIFI_STA_DISCONNECTED;
    if (errRc != ESP_OK) {
        LOGE("esp_wifi_disconnect: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
        abort();
    }
}


void SRWiFi::startScan(){
	wifi_scan_config_t scan_config;
    memset(&scan_config, 0, sizeof(scan_config));
    scan_config.show_hidden = true;
    scan_config.scan_type = WIFI_SCAN_TYPE_ACTIVE;
    esp_err_t rv = esp_wifi_scan_start(&scan_config, false);   //  start non blocking ap scan.
    if (rv != ESP_OK){
        LOGE("esp_wifi_scan_start() failed. returns %x.", rv);
    }
}
void SRWiFi::stopScan(){
    uint16_t apCount = 0;  // Number of access points available.
	esp_err_t rc = ::esp_wifi_scan_get_ap_num(&apCount);
	if (rc != ESP_OK) {
		LOGE("esp_wifi_scan_get_ap_num: %d", rc);
		return;
	} else {
		LOGD("Count of found access points: %d", apCount);
	}
    scannedAPs.clear();
    if (apCount){
        wifi_ap_record_t* list = (wifi_ap_record_t*) malloc(sizeof(wifi_ap_record_t) * apCount);
        if (list == nullptr) {
            LOGE("Failed to allocate memory");
            return;
        }
        esp_err_t errRc = ::esp_wifi_scan_get_ap_records(&apCount, list);
        if (errRc != ESP_OK) {
            LOGE("esp_wifi_scan_get_ap_records: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
            abort();
        }
        scannedAPs.reserve(apCount);
        for (uint16_t i = 0; i < apCount; i++) {
            WiFiAPRecord wifiAPRecord;
            memcpy(wifiAPRecord.bssid, list[i].bssid, 6);
            wifiAPRecord.ssid	 = std::string((char*) list[i].ssid);
            wifiAPRecord.authMode = list[i].authmode;
            wifiAPRecord.rssi	 = list[i].rssi;
            scannedAPs.push_back(wifiAPRecord);
        }
        free(list);   // Release the storage allocated to hold the records.
        std::sort(scannedAPs.begin(),
            scannedAPs.end(),
            [](const WiFiAPRecord& lhs, const WiFiAPRecord& rhs){ return lhs.rssi > rhs.rssi; });
    }
}

std::string SRWiFi::getStaPassword() {
    wifi_config_t conf;
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    return std::string((char*) conf.ap.password);
}
std::string SRWiFi::getStaSSID() {
	wifi_config_t conf;
	esp_wifi_get_config(WIFI_IF_STA, &conf);
	return std::string((char*) conf.ap.ssid);
} // getStaSSID
