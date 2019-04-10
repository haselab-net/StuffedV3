#include "ws_fs.h"

#include <fstream>

#include "logging.h"
#include "duktape_spiffs.h"

LOG_TAG("ws_fs");

/**
 * Mount & register virtual filesystem.
 */
void esp32_spiffs_mount() {
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = false
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            LOGE("Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            LOGE("Failed to find SPIFFS partition");
        } else {
            LOGE("Failed to initialize SPIFFS (%d)", ret);
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        LOGE("Failed to get SPIFFS partition information");
    } else {
        LOGI("Partition size: total: %d, used: %d", total, used);
    }

} // esp32_duktape_spiffs_mount

void combineMainFiles() {
    std::ifstream m_ifStream;
    std::ofstream m_ofStream;

    m_ofStream.open(std::string(SPIFFS_MOUNTPOINT) + "/main/runtime.js", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

    m_ifStream.open(std::string(SPIFFS_MOUNTPOINT) + "/main/maininit.js", std::ofstream::in | std::ofstream::binary);
    m_ofStream << m_ifStream.rdbuf() << std::endl;
    m_ifStream.close();
    m_ifStream.open(std::string(SPIFFS_MOUNTPOINT) + "/main/main.js", std::ofstream::in | std::ofstream::binary);
    m_ofStream << m_ifStream.rdbuf() << std::endl;
    m_ifStream.close();
    m_ifStream.open(std::string(SPIFFS_MOUNTPOINT) + "/main/mainend.js", std::ofstream::in | std::ofstream::binary);
    m_ofStream << m_ifStream.rdbuf() << std::endl;
    m_ifStream.close();

    m_ofStream.close();
}