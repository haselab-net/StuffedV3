#include "TouchPad.h"
#include "esp_log.h"


static const char* TAG = "TouchSensing";


void TouchPad::init()
{
    touch_pad_init();
    touch_pad_config(num_touch_pad_, 0);
};

uint16_t TouchPad::raw_value()
{
    ESP_ERROR_CHECK(touch_pad_read(num_touch_pad_, &raw_value_));
    return raw_value_;
};

uint32_t TouchPad::current_status() {
    current_status_ = touch_pad_get_status();
    return current_status_;
}

static void TouchSensingReadTask(void *arg) {
    ((TouchSensing*)arg)->read_task();
};

TouchSensing::TouchSensing() {
    for (int idx = 0; idx < COUNT_TOUCH_PAD; idx++)
        touch_pads[idx] = new TouchPad((touch_pad_t)idx);
    
    enable_mask_ = TOUCH_PAD_FLAG_ALL;
};

TouchSensing::~TouchSensing() {
    for (int idx = 0; idx < COUNT_TOUCH_PAD; idx++)
        delete touch_pads[idx];
}

void TouchSensing::init() {
    volatile uint16_t mask = enable_mask_;

    // esp_log_level_set(TAG, ESP_LOG_DEBUG);
    ESP_LOGI(TAG, "Touch Pad Mask is 0x%04X.", mask);

    for (int idx = 0; idx < COUNT_TOUCH_PAD; idx ++) {
        if (mask & (1 << idx))
            touch_pads[idx]->init();
    }

    create_task();
};

void TouchSensing::read_task() {
    while (1) {
        volatile uint16_t mask = enable_mask_;

        for (int idx = 0; idx < COUNT_TOUCH_PAD; idx ++) {
            if (mask & (1 << idx)) {
                volatile uint16_t raw_value = touch_pads[idx]->raw_value();
                ESP_LOGI(TAG, "Raw value of touch pad %d: 0x%04X", idx, raw_value);
            }
            else {
                ESP_LOGI(TAG, "Touch Pad %d is disabled.", idx);
            }
        }

        ESP_LOGI(TAG, "All values of touch pads have been read.");
        vTaskDelay(10000);
    }
}

void TouchSensing::create_task() {
    xTaskCreate(
        TouchSensingReadTask,
        "Touch Sensing Task",
        10 * 1024,
        this,
        8,
        &handle_read_task);
};

TouchSensing touch_sensing;
