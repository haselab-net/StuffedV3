#include "module_ifttt.h"

#include <string>
#include <unordered_map>

extern "C" {
    #include <esp_http_client.h>
    #include <esp_log.h>
    #include <cJSON.h>

    #include <freertos/task.h>

    #include "duktape_event.h"

    #include "mqtt/esp-mqtt/include/mqtt_client.h"
}

#include "WebSocket.h"
#include "Task.h"
#include "FreeRTOS.h"
#include "Socket.h"

static char LOG_TAG[] = "module_ifttt";

static TaskHandle_t ifttt_ws_event_task_handle = NULL;

static std::unordered_map<std::string, uint32_t> event_stash_keys;

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
static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event) {
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_publish(client, "/topic/qos1", "data_3", 0, 1, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
            ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}

int pushValues(duk_context* ctx, void* data) {
    size_t offset;
    char* p_str = (char*)data;
    
    duk_push_string(ctx, p_str);
    offset = sizeof(p_str);
    p_str += offset;

    duk_push_string(ctx, p_str);
    offset = sizeof(p_str);
    p_str += offset;

    duk_push_string(ctx, p_str);

    return 3;
}
void mqtt_data_event_handler (char* data) {
    // find function
    std::unordered_map<std::string, uint32_t>::iterator func = event_stash_keys.find(event);
    if (func == event_stash_keys.end()) {
        ESP_LOGI(LOG_TAG, "No registered event with name: %s", event.c_str());
        return;
    }

    uint32_t func_key = func->second;

    // call callback
    event_newCallbackRequestedEvent(
        ESP32_DUKTAPE_CALLBACK_STATIC_TYPE_FUNCTION,
        func_key,
        pushValues,
        (void*)data
    );
}

// function startWaitingMQTTEvent(remoteAddress: string, remotePort: number)
static duk_ret_t startWaitingMQTTEvent(duk_context* ctx) {
    if (esp_mqtt_client) return;

    // get parameters
    int id = -2;
    const char* remoteAddress;
    remoteAddress = duk_get_string(ctx, id);
    id++;
    const uint32_t remotePort = duk_get_int(ctx, id);
    id++;

    // broker config
    esp_mqtt_client_config_t mqtt_cfg = {};
    mqtt_cfg.host = remoteAddress;
    mqtt_cfg.port = remotePort;
    mqtt_cfg.event_handle = mqtt_event_handler;

    // start
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);

    return 0;
}

static duk_ret_t stopWaitingMQTTEvent(duk_context* ctx) {
    if (!esp_mqtt_client) return;

    esp_mqtt_client_stop(mqtt_client);
    mqtt_client = NULL;

    return 0;
}

// register events that would be called from remote
// function registerMQTTEvent(event: string, cb: (value1: string, value2: string, value3: string) => void): void
static duk_ret_t registerMQTTEvent(duk_context* ctx) {
    // ... event func 
    std::string event_name(duk_get_string(ctx, -2));
    event_stash_keys[event_name] = esp32_duktape_stash_array(ctx, 1);

    // ... event
    duk_pop(ctx);

    ESP_LOGI(LOG_TAG, "register event %s", event_name.c_str());

    return 0;
}

/////////////////////////////////////////
////////// other         ////////////////
/////////////////////////////////////////
void stopWaitingEventTask() {
    mqttEventListener.stop();
}

extern "C" duk_ret_t ModuleIoT(duk_context *ctx) {
    ADD_FUNCTION("triggerIFTTTEvent", triggerIFTTTEvent, 5);
    ADD_FUNCTION("registerMQTTEvent", registerMQTTEvent, 2);
    ADD_FUNCTION("startWaitingMQTTEvent", startWaitingMQTTEvent, 2);
    ADD_FUNCTION("stopWaitingMQTTEvent", stopWaitingMQTTEvent, 0);

    return 0;
}