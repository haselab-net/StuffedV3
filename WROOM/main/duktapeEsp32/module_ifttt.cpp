#include "module_ifttt.h"

#include <string>
#include <unordered_map>

extern "C" {
    #include <esp_http_client.h>
    #include <esp_log.h>
    #include <cJSON.h>

    #include <freertos/task.h>

    #include "duktape_event.h"
}

#include "WebSocket.h"
#include "Task.h"
#include "FreeRTOS.h"
#include "Socket.h"

static char LOG_TAG[] = "module_ifttt";

static TaskHandle_t ifttt_ws_event_task_handle = NULL;

static std::unordered_map<std::string, uint32_t> event_stash_keys;

bool isTCPWaiting = false;

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
static duk_ret_t triggerEvent(duk_context* ctx) {
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

enum DataType {
    DT_NONE = 0,
    DT_ID = 1
};

class IFTTTEventListener {
    public:
    void start(std::string serverAddress, uint16_t serverPort, std::string key);
    void stop();

    const uint16_t RECONNECT_INTERVAL = 5000;
    const uint16_t LISTEN_INTERVAL = 2000; 

    void addEventHandler(void (*IFTTTEventHandler)(std::string event, std::string value1, std::string value2, std::string value3));
    
    private:
    friend class IFTTTEventListenerTask;

    std::string m_serverAddress;
    uint16_t m_serverPort;
    std::string m_key;
    Socket m_socket;
    void (*m_iftttEventHandler)(std::string event, std::string value1, std::string value2, std::string value3);
    FreeRTOS::Semaphore m_semaphoreTCPConStarted = FreeRTOS::Semaphore("TCPConStarted");
};

class IFTTTEventListenerTask : public Task {
    public:
    IFTTTEventListenerTask(std::string name): Task(name, 4 * 1024, tskIDLE_PRIORITY) {
        m_iftttEventListener = nullptr;
    }

    void run(void* data) {
        m_iftttEventListener = (IFTTTEventListener*) data;

        // connect to server
        if (!tryConnect()) {
            m_iftttEventListener->m_semaphoreTCPConStarted.give();
            return;
        }

        void* tcp_data = (void*)malloc(512);
        // listen loop
        while (1) {
            // try to reconnect if go offline
            if (!m_iftttEventListener->m_socket.isValid()) {
                if (!tryConnect()) {
                    m_iftttEventListener->m_semaphoreTCPConStarted.give();
                    return;
                }
            }

            // stop waiting
            if (!isTCPWaiting) {
                m_iftttEventListener->m_semaphoreTCPConStarted.give();
                return;
            }

            // receive data
            size_t size = m_iftttEventListener->m_socket.receive((uint8_t*)tcp_data, 512, false);
            if (size > 0) {
                ESP_LOGI(LOG_TAG, "message received");
                processEvent(tcp_data, size);
            }

            // interval
            vTaskDelay(pdMS_TO_TICKS(m_iftttEventListener->LISTEN_INTERVAL));
        }
    }

    private:
    IFTTTEventListener* m_iftttEventListener;
    void processEvent(void* data, size_t size) {
        cJSON *obj = cJSON_Parse((char*) data);
        const char* event = cJSON_GetStringValue(cJSON_GetObjectItem(obj, "event"));
        const char* value1 = cJSON_GetStringValue(cJSON_GetObjectItem(obj, "value1"));
        const char* value2 = cJSON_GetStringValue(cJSON_GetObjectItem(obj, "value2"));
        const char* value3 = cJSON_GetStringValue(cJSON_GetObjectItem(obj, "value3"));

        ESP_LOGI(LOG_TAG, "Receive event=%s with value1=%s value2=%s value3=%s", event, value1, value2, value3);

        m_iftttEventListener->m_iftttEventHandler(event, value1, value2, value3);
    }

    bool connect() {
        m_iftttEventListener->m_socket = Socket();
        ESP_LOGI(LOG_TAG, "try connect to: %s : %i ...", m_iftttEventListener->m_serverAddress.c_str(), m_iftttEventListener->m_serverPort);
        int connected = m_iftttEventListener->m_socket.connect(m_iftttEventListener->m_serverAddress.c_str(), m_iftttEventListener->m_serverPort);
        if (connected == -1) return false;
        else return true;
    }

    bool tryConnect() {
        bool flag = connect();
        while (!flag) {
            ESP_LOGI(LOG_TAG, "Connect to tcp server failed");
            if (!isTCPWaiting) {
                return false;
            }
            vTaskDelay(pdMS_TO_TICKS(m_iftttEventListener->RECONNECT_INTERVAL));
            if (!isTCPWaiting) {
                return false;
            }
            ESP_LOGI(LOG_TAG, "try to reconnect");
            flag = connect();
        }

        // send id
        cJSON* obj = cJSON_CreateObject();
        cJSON_AddNumberToObject(obj, "type", DataType::DT_ID);
        cJSON_AddStringToObject(obj, "key", m_iftttEventListener->m_key.c_str());
        const char* obj_str = cJSON_Print(obj);
        m_iftttEventListener->m_socket.send(obj_str);

        return true;
    }
};

void IFTTTEventListener::start(std::string serverAddress, uint16_t serverPort, std::string key) {
    isTCPWaiting = true;

    this->m_serverAddress = serverAddress;
    this->m_serverPort = serverPort;
    this->m_key = key;

    if (!m_semaphoreTCPConStarted.take(100, "start")) {
        ESP_LOGD(LOG_TAG, "<< start: Already running");
        return;
    }

    // start task
    IFTTTEventListenerTask* task = new IFTTTEventListenerTask("ifttt_task");
    task->start(this);

    ESP_LOGD(LOG_TAG, "<< start");
}
void IFTTTEventListener::stop() {
    isTCPWaiting = false;

    m_socket.close();
    m_semaphoreTCPConStarted.wait("stop");

    ESP_LOGD(LOG_TAG, "<< stop");
}

void IFTTTEventListener::addEventHandler(void (*IFTTTEventHandler)(std::string event, std::string value1, std::string value2, std::string value3)) {
    m_iftttEventHandler = IFTTTEventHandler;
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
void eventHandler(std::string event, std::string value1, std::string value2, std::string value3) {
    // find function
    std::unordered_map<std::string, uint32_t>::iterator func = event_stash_keys.find(event);
    if (func == event_stash_keys.end()) {
        ESP_LOGI(LOG_TAG, "No registered event with name: %s", event.c_str());
        return;
    }

    uint32_t func_key = func->second;

    // prepare parameters
    void* params = (void*)malloc(sizeof(value1.c_str()) + sizeof(value2.c_str()) + sizeof(value3.c_str()));
    char* p_str = (char*)params;
    strcpy(p_str, value1.c_str());
    p_str += sizeof(value1.c_str());
    strcpy(p_str, value2.c_str());
    p_str += sizeof(value2.c_str());
    strcpy(p_str, value3.c_str());

    // call callback
    event_newCallbackRequestedEvent(
        ESP32_DUKTAPE_CALLBACK_STATIC_TYPE_FUNCTION,
        func_key,
        pushValues,
        params
    );
}

IFTTTEventListener iftttEventListener = IFTTTEventListener();

// function startWaitingEvent(remoteAddress: string, remotePort: number)
static duk_ret_t startWaitingEvent(duk_context* ctx) {
    int id = -2;

    const char* remoteAddress;
    remoteAddress = duk_get_string(ctx, id);
    id++;

    const uint16_t remotePort = duk_get_int(ctx, id);
    id++;

    iftttEventListener.addEventHandler(eventHandler);
    iftttEventListener.start(remoteAddress, remotePort, "macaddress");

    return 0;
}

static duk_ret_t stopWaitingEvent(duk_context* ctx) {
    iftttEventListener.stop();

    return 0;
}

// register events that would be called from remote
// function registerEvent(event: string, cb: (value1: string, value2: string, value3: string) => void): void
static duk_ret_t registerEvent(duk_context* ctx) {
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
    iftttEventListener.stop();
}

extern "C" duk_ret_t ModuleIFTTT(duk_context *ctx) {
    ADD_FUNCTION("triggerEvent", triggerEvent, 5);
    ADD_FUNCTION("registerEvent", registerEvent, 2);
    ADD_FUNCTION("startWaitingEvent", startWaitingEvent, 2);
    ADD_FUNCTION("stopWaitingEvent", stopWaitingEvent, 0);

    return 0;
}