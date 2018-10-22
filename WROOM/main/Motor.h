#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <stdio.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "../../PIC/boardType.h"

#ifdef BOARD3_SEPARATE
#define NMOTOR_DIRECT	3
extern int pwmPins[NMOTOR_DIRECT*2];
extern int adcChs[NMOTOR_DIRECT*2];
#endif

class MotorDriver{
    esp_adc_cal_characteristics_t adc_chars;
    int adcRaws[NMOTOR_DIRECT*2];
public:
    void Init();
    void Pwm(int ch, float duty);
    void AdcRead();
    uint32_t GetAdcVoltage(int ch);
    int GetAdcRaw(int ch);
};
