#include "module_ifttt.h"

extern "C" {
    #include "esp_http_client.h"
    #include "esp_log.h"
}
#include <string>
#include <cJSON.h>

static char LOG_TAG[] = "module_ifttt";

extern const char ifttt_com_root_cert_pem_start[] asm("_binary_ifttt_server_root_cert_pem_start");
extern const char ifttt_com_root_cert_pem_end[] asm("_binary_ifttt_server_root_cert_pem_end");

static esp_err_t _ifttt_https_event_handle(esp_http_client_event_t *evt) {
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGI(LOG_TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI(LOG_TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI(LOG_TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI(LOG_TAG, "HTTP_EVENT_ON_HEADER");
            printf("%.*s", evt->data_len, (char*)evt->data);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(LOG_TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                printf("%.*s", evt->data_len, (char*)evt->data);
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(LOG_TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(LOG_TAG, "HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}

// function triggerEvent(key: string, event: string, value1?: string, value2?: string, value3?: string)
duk_ret_t triggerEvent(duk_context* ctx) {
    int id = -5;

    const char* key;
    key = duk_get_string(ctx, id);
    id++;

    const char* event;
    event = duk_get_string(ctx, id);
    id++;

    const char* value1;
    if (duk_is_string(ctx, id)) value1 = duk_get_string(ctx, id);
    else value1 = "";
    id++;

    const char* value2;
    if (duk_is_string(ctx, id)) value2 = duk_get_string(ctx, id);
    else value2 = "";
    id++;

    const char* value3;
    if (duk_is_string(ctx, id)) value3 = duk_get_string(ctx, id);
    else value3 = "";
    id++;

    cJSON* json;
	json = cJSON_CreateObject();

	cJSON_AddStringToObject(json, "value1", value1);
	cJSON_AddStringToObject(json, "value2", value2);
	cJSON_AddStringToObject(json, "value3", value3);

    char* json_str = cJSON_Print(json);

    printf("before get");

    std::string url = "http://maker.ifttt.com/trigger/" + std::string(event) + "/with/key/" + std::string(key);
    printf("url: %s", url.c_str());

    esp_http_client_config_t config = { };
    config.url = url.c_str();
    config.event_handler = _ifttt_https_event_handle;
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_post_field(client, json_str, strlen(json_str));

    esp_err_t err = esp_http_client_perform(client);

    printf("after get");

    if (err == ESP_OK) {
        ESP_LOGI(LOG_TAG, "Status = %d, content_length = %d",
        esp_http_client_get_status_code(client),
        esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(LOG_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);

    return 0;
}

extern "C" duk_ret_t ModuleIFTTT(duk_context *ctx) {
    ADD_FUNCTION("triggerEvent", triggerEvent, 5);

    return 0;
}