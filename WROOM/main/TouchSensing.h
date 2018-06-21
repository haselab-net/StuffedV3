#include "driver/touch_pad.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef enum : uint16_t
{
    TOUCH_PAD_FLAG_NONE = 0x0000,
    TOUCH_PAD_FLAG0 = 1 << 0,
    TOUCH_PAD_FLAG1 = 1 << 1,
    TOUCH_PAD_FLAG2 = 1 << 2,
    TOUCH_PAD_FLAG3 = 1 << 3,
    TOUCH_PAD_FLAG4 = 1 << 4,
    TOUCH_PAD_FLAG5 = 1 << 5,
    TOUCH_PAD_FLAG6 = 1 << 6,
    TOUCH_PAD_FLAG7 = 1 << 7,
    TOUCH_PAD_FLAG8 = 1 << 8,
    TOUCH_PAD_FLAG9 = 1 << 9,
    TOUCH_PAD_FLAG_ALL = 0x03FF,
} touch_pad_flag_t;

class TouchPad
{
  private:
    touch_pad_t num_touch_pad_;
    uint16_t raw_value_;
    uint32_t current_status_;

  public:
    TouchPad();
    TouchPad(touch_pad_t touch_pad) : num_touch_pad_(touch_pad){};

    void init();
    touch_pad_t num_touch_pad() { return num_touch_pad_; };
    void set_num_touch_pad(touch_pad_t num) { num_touch_pad_ = num; };
    uint16_t raw_value();
    uint32_t current_status();
};

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