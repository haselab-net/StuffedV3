#pragma once
#include <vector>
#include "../../../PIC/env.h"
#include "driver/touch_pad.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class TouchPads
{
  private:
    std::vector<touch_pad_t> pads;
    int Add(touch_pad_t pad);
  public:
    void Init();
    int NPad(){return (int)pads.size();}
    uint16_t Filtered(int i);
    uint32_t Status();
};
extern TouchPads touchPads;
/*
class TouchSensing
{
  private:
    uint16_t enable_mask_;
  public:
    static const int COUNT_TOUCH_PAD = 9;
    TouchPad* touch_pads[COUNT_TOUCH_PAD];
    // uint16_t raw_values[COUNT_TOUCH_PAD];
    TaskHandle_t handle_read_task;

    TouchSensing();
    ~TouchSensing();
    TouchSensing(uint16_t mask) : enable_mask_(mask){};

    void init();
    void set_enable_mask(uint16_t mask) { enable_mask_ = mask; };
    uint16_t enable_mask() { return enable_mask_; };
    void read_task();
    void create_task();
};

extern TouchSensing touch_sensing;
*/