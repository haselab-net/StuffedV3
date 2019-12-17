#include <stdlib.h>
#include <string.h>
#include <esp_log.h>
#include <esp_flash_encrypt.h>
#include <esp_ota_ops.h>
#include <esp_spiffs.h>
extern "C" {
    #include <esp_image_format.h>
}
#include "include/ota_flash.h"

#ifndef OTA_BUF_SIZE
#define OTA_BUF_SIZE 256
#endif

static const char *TAG = "ota_partition";

static void http_cleanup(esp_http_client_handle_t client)
{
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
}

esp_err_t esp_https_ota_partition(const esp_http_client_config_t *config, const partition_locator_t *partition_info)
{
    if (!config) {
        ESP_LOGE(TAG, "esp_http_client config not found");
        return ESP_ERR_INVALID_ARG;
    }

    if (!config->cert_pem && !config->use_global_ca_store) {
        ESP_LOGE(TAG, "Server certificate not found, either through configuration or global CA store");
        return ESP_ERR_INVALID_ARG;
    }

    printf(">>> esp_http_client_init \n");
    esp_http_client_handle_t client = esp_http_client_init(config);
    printf("<<< esp_http_client_init \n");
    if (client == NULL) {
        ESP_LOGE(TAG, "Failed to initialise HTTP connection");
        return ESP_FAIL;
    }

    if (esp_http_client_get_transport_type(client) != HTTP_TRANSPORT_OVER_SSL) {
        ESP_LOGE(TAG, "Transport is not over HTTPS");
        return ESP_FAIL;
    }

    printf(">>> esp_http_client_open \n");
    esp_err_t err = esp_http_client_open(client, 0);
    printf("<<< esp_http_client_open \n");
    if (err != ESP_OK) {
        esp_http_client_cleanup(client);
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
        return err;
    }
    esp_http_client_fetch_headers(client);

    const esp_partition_t *update_partition = NULL;
    ESP_LOGI(TAG, "Starting OTA on partition: %s...", partition_info->label);
    update_partition = esp_partition_find_first(partition_info->type, partition_info->subtype, partition_info->label);
    if (update_partition == NULL) {
        ESP_LOGE(TAG, "Partition %s not found", partition_info->label);
        http_cleanup(client);
        return ESP_FAIL;
    }
    err = esp_partition_erase_range(update_partition, 0, update_partition->size);
    ESP_LOGI(TAG, "Erase partition: %s, %d...", update_partition->label, update_partition->size);
    if (err != ESP_OK) {
        http_cleanup(client);
        ESP_LOGE(TAG, "Failed to erase partition %s. %s", partition_info->label, esp_err_to_name(err));
        return err;
    }
    ESP_LOGI(TAG, "Writing to partition subtype %d at offset 0x%x",
             update_partition->subtype, update_partition->address);

    esp_err_t ota_write_err = ESP_OK;
    char *upgrade_data_buf = (char *)malloc(OTA_BUF_SIZE);
    if (!upgrade_data_buf) {
        ESP_LOGE(TAG, "Couldn't allocate memory to upgrade data buffer");
        return ESP_ERR_NO_MEM;
    }
    int binary_file_len = 0;
    while (1) {
        int data_read = esp_http_client_read(client, upgrade_data_buf, OTA_BUF_SIZE);
        if (data_read == 0) {
            ESP_LOGI(TAG, "Connection closed, all data received");
            break;
        }
        if (data_read < 0) {
            ESP_LOGE(TAG, "Error: SSL data read error");
            break;
        }
        if (data_read > 0) {
            // if (binary_file_len == 0 && upgrade_data_buf[0] != ESP_IMAGE_HEADER_MAGIC) {
            //     ESP_LOGE(TAG, "Downloaded image has invalid magic byte (expected 0xE9, saw 0x%02x", upgrade_data_buf[0]);
            //     return ESP_ERR_OTA_VALIDATE_FAILED;
            // }
            if (esp_flash_encryption_enabled()) {
                ESP_LOGE(TAG, "Error: not able to handle encryped flash");
            }
            ota_write_err = esp_partition_write(update_partition, binary_file_len, (const void*)upgrade_data_buf, data_read);
            if (ota_write_err != ESP_OK) {
                ESP_LOGE(TAG, "Error: esp_partition_write failed");
                break;
            }
            binary_file_len += data_read;
            ESP_LOGD(TAG, "Written image length %d", binary_file_len);
        }
    }
    free(upgrade_data_buf);
    http_cleanup(client);
    ESP_LOGI(TAG, "Total binary data length writen: %d", binary_file_len);

    return ESP_OK;
}
