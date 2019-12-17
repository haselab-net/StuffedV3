#ifndef _OTA_FLASH_H_
#define _OTA_FLASH_H_

#include <stdio.h>
#include <esp_partition.h>
#include <esp_http_client.h>

struct partition_locator_t {
    esp_partition_type_t type;
    esp_partition_subtype_t subtype;
    char* label;
};

esp_err_t esp_https_ota_partition(const esp_http_client_config_t *config, const partition_locator_t *parititon_info);

#endif
