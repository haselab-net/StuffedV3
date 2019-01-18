#pragma once

typedef enum {
    TOUCH_PAD_NUM0 = 0, /*!< Touch pad channel 0 is GPIO4 */
    TOUCH_PAD_NUM1,     /*!< Touch pad channel 1 is GPIO0 */
    TOUCH_PAD_NUM2,     /*!< Touch pad channel 2 is GPIO2 */
    TOUCH_PAD_NUM3,     /*!< Touch pad channel 3 is GPIO15*/
    TOUCH_PAD_NUM4,     /*!< Touch pad channel 4 is GPIO13*/
    TOUCH_PAD_NUM5,     /*!< Touch pad channel 5 is GPIO12*/
    TOUCH_PAD_NUM6,     /*!< Touch pad channel 6 is GPIO14*/
    TOUCH_PAD_NUM7,     /*!< Touch pad channel 7 is GPIO27*/
    TOUCH_PAD_NUM8,     /*!< Touch pad channel 8 is GPIO33*/
    TOUCH_PAD_NUM9,     /*!< Touch pad channel 9 is GPIO32*/
    TOUCH_PAD_MAX,
} touch_pad_t;

typedef enum {
    TOUCH_HVOLT_KEEP = -1, /*!<Touch sensor high reference voltage, no change  */
    TOUCH_HVOLT_2V4 = 0,   /*!<Touch sensor high reference voltage, 2.4V  */
    TOUCH_HVOLT_2V5,       /*!<Touch sensor high reference voltage, 2.5V  */
    TOUCH_HVOLT_2V6,       /*!<Touch sensor high reference voltage, 2.6V  */
    TOUCH_HVOLT_2V7,       /*!<Touch sensor high reference voltage, 2.7V  */
    TOUCH_HVOLT_MAX,
} touch_high_volt_t;

typedef enum {
    TOUCH_LVOLT_KEEP = -1, /*!<Touch sensor low reference voltage, no change  */
    TOUCH_LVOLT_0V5 = 0,   /*!<Touch sensor low reference voltage, 0.5V  */
    TOUCH_LVOLT_0V6,       /*!<Touch sensor low reference voltage, 0.6V  */
    TOUCH_LVOLT_0V7,       /*!<Touch sensor low reference voltage, 0.7V  */
    TOUCH_LVOLT_0V8,       /*!<Touch sensor low reference voltage, 0.8V  */
    TOUCH_LVOLT_MAX,
} touch_low_volt_t;

typedef enum {
    TOUCH_HVOLT_ATTEN_KEEP = -1,  /*!<Touch sensor high reference voltage attenuation, no change  */
    TOUCH_HVOLT_ATTEN_1V5 = 0,    /*!<Touch sensor high reference voltage attenuation, 1.5V attenuation  */
    TOUCH_HVOLT_ATTEN_1V,         /*!<Touch sensor high reference voltage attenuation, 1.0V attenuation  */
    TOUCH_HVOLT_ATTEN_0V5,        /*!<Touch sensor high reference voltage attenuation, 0.5V attenuation  */
    TOUCH_HVOLT_ATTEN_0V,         /*!<Touch sensor high reference voltage attenuation,   0V attenuation  */
    TOUCH_HVOLT_ATTEN_MAX,
} touch_volt_atten_t;

typedef enum {
    TOUCH_PAD_SLOPE_0 = 0,       /*!<Touch sensor charge / discharge speed, always zero  */
    TOUCH_PAD_SLOPE_1 = 1,       /*!<Touch sensor charge / discharge speed, slowest  */
    TOUCH_PAD_SLOPE_2 = 2,       /*!<Touch sensor charge / discharge speed */
    TOUCH_PAD_SLOPE_3 = 3,       /*!<Touch sensor charge / discharge speed  */
    TOUCH_PAD_SLOPE_4 = 4,       /*!<Touch sensor charge / discharge speed  */
    TOUCH_PAD_SLOPE_5 = 5,       /*!<Touch sensor charge / discharge speed  */
    TOUCH_PAD_SLOPE_6 = 6,       /*!<Touch sensor charge / discharge speed  */
    TOUCH_PAD_SLOPE_7 = 7,       /*!<Touch sensor charge / discharge speed, fast  */
    TOUCH_PAD_SLOPE_MAX,
} touch_cnt_slope_t;

typedef enum {
    TOUCH_TRIGGER_BELOW = 0,   /*!<Touch interrupt will happen if counter value is less than threshold.*/
    TOUCH_TRIGGER_ABOVE = 1,   /*!<Touch interrupt will happen if counter value is larger than threshold.*/
    TOUCH_TRIGGER_MAX,
} touch_trigger_mode_t;

typedef enum {
    TOUCH_TRIGGER_SOURCE_BOTH = 0,  /*!< wakeup interrupt is generated if both SET1 and SET2 are "touched"*/
    TOUCH_TRIGGER_SOURCE_SET1 = 1,  /*!< wakeup interrupt is generated if SET1 is "touched"*/
    TOUCH_TRIGGER_SOURCE_MAX,
} touch_trigger_src_t;

typedef enum {
    TOUCH_PAD_TIE_OPT_LOW = 0,    /*!<Initial level of charging voltage, low level */
    TOUCH_PAD_TIE_OPT_HIGH = 1,   /*!<Initial level of charging voltage, high level */
    TOUCH_PAD_TIE_OPT_MAX,
} touch_tie_opt_t;

typedef enum {
    TOUCH_FSM_MODE_TIMER = 0,   /*!<To start touch FSM by timer */
    TOUCH_FSM_MODE_SW,          /*!<To start touch FSM by software trigger */
    TOUCH_FSM_MODE_MAX,
} touch_fsm_mode_t;


typedef uint32_t TickType_t;
typedef int esp_err_t;
inline esp_err_t touch_pad_read(touch_pad_t touch_num, uint16_t *touch_value){
	return 0;
}
inline int touch_pad_get_status(){ return 0; }