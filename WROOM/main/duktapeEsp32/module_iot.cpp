#include "module_iot.h"

#include <string>

extern "C" {
    #include <esp_http_client.h>
    #include <esp_log.h>
    #include <esp_system.h>
    #include <cJSON.h>

    #include <freertos/task.h>

    #include "duktape_event.h"
}

#include "WebSocket.h"
#include "Task.h"
#include "FreeRTOS.h"
#include "Socket.h"

static char LOG_TAG[] = "module_iot";

static uint32_t mqtt_callback = 0;

static char mqtt_key[7];
esp_mqtt_client_handle_t mqtt_client = NULL;

/////////////////////////////////////////
////////// Send Event ///////////////////
/////////////////////////////////////////

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
// trigger remote event through IFTTT
static duk_ret_t triggerIFTTTEvent(duk_context* ctx) {
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

/////////////////////////////////////////
////////// Receive Event ////////////////
/////////////////////////////////////////
int mqtt_callback_push_values(duk_context* ctx, void* data) {
    size_t offset;
    char* p_str = (char*)data;

    // event
    duk_push_string(ctx, p_str);
    offset = strlen(p_str)+1;
    p_str += offset;
    
    // value1
    duk_push_string(ctx, p_str);
    offset = strlen(p_str)+1;
    p_str += offset;

    // value2
    duk_push_string(ctx, p_str);
    offset = strlen(p_str)+1;
    p_str += offset;

    // value3
    duk_push_string(ctx, p_str);

    free(data);

    return 4;
}
void mqtt_data_event_handler (char* data) {
    cJSON *obj = cJSON_Parse(data);
    const char* event = cJSON_GetStringValue(cJSON_GetObjectItem(obj, "event"));
    const char* value1 = cJSON_GetStringValue(cJSON_GetObjectItem(obj, "value1"));
    const char* value2 = cJSON_GetStringValue(cJSON_GetObjectItem(obj, "value2"));
    const char* value3 = cJSON_GetStringValue(cJSON_GetObjectItem(obj, "value3"));

    ESP_LOGI(LOG_TAG, "Receive MQTT event=%s with value1=%s value2=%s value3=%s", event, value1, value2, value3);

    // prepare parameters
    void* params = (void*)malloc(strlen(event)+1 + strlen(value1)+1 + strlen(value2)+1 + strlen(value3)+1);
    char* p_str = (char*)params;

    strcpy(p_str, event);
    p_str += strlen(event)+1;
    strcpy(p_str, value1);
    p_str += strlen(value1)+1;
    strcpy(p_str, value2);
    p_str += strlen(value2)+1;
    strcpy(p_str, value3);

    // call callback
    event_newCallbackRequestedEvent(
        ESP32_DUKTAPE_CALLBACK_STATIC_TYPE_FUNCTION,
        mqtt_callback,
        mqtt_callback_push_values,
        params
    );
}

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event) {
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(LOG_TAG, "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_subscribe(client, mqtt_key, 0);
            ESP_LOGI(LOG_TAG, "sent subscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(LOG_TAG, "MQTT_EVENT_DISCONNECTED");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(LOG_TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(LOG_TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(LOG_TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(LOG_TAG, "MQTT_EVENT_DATA");
            ESP_LOGI(LOG_TAG, "TOPIC=%.*s\r\n", event->topic_len, event->topic);
            ESP_LOGI(LOG_TAG, "DATA=%.*s\r\n", event->data_len, event->data);
            mqtt_data_event_handler(event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(LOG_TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(LOG_TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}

// function startWaitingMQTTEvent(remoteAddress: string, remotePort: number)
static duk_ret_t startWaitingMQTTEvent(duk_context* ctx) {
    if (mqtt_client) return 0;

    // get parameters
    int id = -2;
    const char* remoteAddress;
    remoteAddress = duk_get_string(ctx, id);
    id++;
    const uint32_t remotePort = duk_get_int(ctx, id);
    id++;

    // broker config
    esp_mqtt_client_config_t mqtt_cfg = {};
    mqtt_cfg.event_handle = mqtt_event_handler;
    mqtt_cfg.host = remoteAddress;
    mqtt_cfg.port = remotePort;
    // mqtt_cfg.keepalive = 10 * 60;    // 10 min, 2 min default
    mqtt_cfg.disable_auto_reconnect = false;
    mqtt_cfg.task_prio = tskIDLE_PRIORITY;

    // start
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    if (!mqtt_client) {
        ESP_LOGE(LOG_TAG, "Init mqtt client failed");
        return 0;
    }
    esp_err_t err = esp_mqtt_client_start(mqtt_client);
    if (err != ESP_OK) {
        ESP_LOGE(LOG_TAG, "Start mqtt client failed");
        return 0;
    }

    return 0;
}

static duk_ret_t stopWaitingMQTTEvent(duk_context* ctx) {
    if (!mqtt_client) return 0;

    esp_err_t err = esp_mqtt_client_stop(mqtt_client);
    if (err != ESP_OK) {
        ESP_LOGE(LOG_TAG, "Stop mqtt client failed");
        return 0;
    }
    esp_mqtt_client_destroy(mqtt_client);
    mqtt_client = NULL;

    return 0;
}

// register events that would be called from remote
// function registerMQTTCallback(cb: (event: string, value1: string, value2: string, value3: string) => void): void
static duk_ret_t registerMQTTCallback(duk_context* ctx) {
    mqtt_callback = esp32_duktape_stash_array(ctx, 1);

    ESP_LOGI(LOG_TAG, "stashed MQTT callback with key: %i", mqtt_callback);

    return 0;
}

/////////////////////////////////////////
////////// Else /////////////////////////
/////////////////////////////////////////
extern "C" void iotBeforeStopJSTask() {
    stopWaitingMQTTEvent(NULL);
}

extern "C" duk_ret_t ModuleIoT(duk_context *ctx) {
    // set key of the hardware with macaddress (for mqtt)
    uint8_t macaddress[6];
    esp_read_mac(macaddress, ESP_MAC_WIFI_STA);
    for (int i=3; i<6; i++) {
        sprintf(mqtt_key+strlen(mqtt_key), "%02X", macaddress[i]);
    }
    mqtt_key[7] = '\0';

    ADD_FUNCTION("triggerIFTTTEvent", triggerIFTTTEvent, 5);
    ADD_FUNCTION("registerMQTTCallback", registerMQTTCallback, 1);
    ADD_FUNCTION("startWaitingMQTTEvent", startWaitingMQTTEvent, 2);
    ADD_FUNCTION("stopWaitingMQTTEvent", stopWaitingMQTTEvent, 0);

    return 0;
}