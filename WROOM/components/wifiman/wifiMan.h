
#pragma once

#ifdef __cplusplus
extern "C" void wifiMan();
#else 
void wifiMan();
#endif

extern EventGroupHandle_t wifi_manager_event_group;
/* @brief indicate that the ESP32 is currently connected. */
extern const int WIFI_MANAGER_WIFI_CONNECTED_BIT;
extern const int WIFI_MANAGER_AP_STA_CONNECTED_BIT;
/* @brief Set automatically once the SoftAP is started */
extern const int WIFI_MANAGER_AP_STARTED;
/* @brief When set, means a client requested to connect to an access point.*/
extern const int WIFI_MANAGER_REQUEST_STA_CONNECT_BIT;
/* @brief This bit is set automatically as soon as a connection was lost */
extern const int WIFI_MANAGER_STA_DISCONNECT_BIT;
/* @brief When set, means a client requested to scan wireless networks. */
extern const int WIFI_MANAGER_REQUEST_WIFI_SCAN;
/* @brief When set, means a client requested to disconnect from currently connected AP. */
extern const int WIFI_MANAGER_REQUEST_WIFI_DISCONNECT;

