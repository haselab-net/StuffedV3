#include "TouchSensing.h"
#include "esp_log.h"
#include "../../../PIC/boardType.h"

#define TOUCHPAD_FILTER_TOUCH_PERIOD (10)
#define TOUCH_THRESH_NO_USE   (0)

TouchPads touchPads;

void TouchPads::Init()
{
#ifndef _WIN32
	touch_pad_init();
    touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
#ifdef BOARD3_SEPARATE 
    Add(TOUCH_PAD_NUM2);
    Add(TOUCH_PAD_NUM3);
    Add(TOUCH_PAD_NUM4);
    Add(TOUCH_PAD_NUM5);
    Add(TOUCH_PAD_NUM6);
    Add(TOUCH_PAD_NUM7);
#endif
    for(int i=0; i<pads.size(); ++i){
        touch_pad_config(pads[i], TOUCH_THRESH_NO_USE);
    }
    touch_pad_filter_start(TOUCHPAD_FILTER_TOUCH_PERIOD);
#endif
};
int TouchPads::Add(touch_pad_t pad){
    for(int i=0; i<(int)pads.size(); ++i){
        if (pad == pads[i]) return -1;
    }
    pads.push_back(pad);
    return pads.size()-1;
}

uint16_t TouchPads::Raw(int i)
{
    uint16_t raw=0;
	ESP_ERROR_CHECK(touch_pad_read(pads[i], &raw));
	return raw;
};
uint32_t TouchPads::Status() {
    return touch_pad_get_status();
}

/*
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
        6,
        &handle_read_task);
};

TouchSensing touch_sensing;
*/