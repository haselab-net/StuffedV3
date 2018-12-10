#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <stdio.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "../../PIC/boardType.h"
extern "C" {
    #include "../../PIC/control.h"
}

class MotorDriver{
    esp_adc_cal_characteristics_t adc_chars;
    TaskHandle_t task;
    QueueHandle_t queue;
    static void AdcReadTaskStatic(void*);
    void AdcReadTask();
    const int DEFAULT_VREF = 1100;        //Use adc2_vref_to_gpio() to obtain a better estimate
    enum {ADC_DMA_LEN = 8};
#ifdef BOARD3_SEPARATE
    public:
    enum {
        NTARGET_DIRECT = 12,
        NMOTOR_DIRECT = BoardInfo::NMOTOR,
        NFORCE_DIRECT = 0,
    };
    private:
    const int pwmPins[NMOTOR_DIRECT*2] = {4, 19, 26, 27, 21, 22};    //M2, M3, M0, M1, M4, M5
    const int adcChs[ADC_DMA_LEN] = {0, 3, 5, 4, 6, 7, 1, 2};
    int adcChsRev[8];   //  must be larger than ch numbers
#endif


public:
    int adcRaws[NMOTOR_DIRECT*2];
    void Init();
    void Pwm(int ch, float duty);
    uint32_t GetAdcVoltage(int ch);
    int GetAdcRaw(int ch);
};
extern MotorDriver motorDriver;
