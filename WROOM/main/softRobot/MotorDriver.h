#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <stdio.h>
#ifndef _WIN32
#include "driver/adc.h"
#include "esp_adc_cal.h"
#endif
#include "../../../PIC/boardType.h"
#include "commandWROOM.h"
extern "C"{
#include "../../../PIC/control.h"
}

class MotorDriver{
#ifndef _WIN32
	esp_adc_cal_characteristics_t adc_chars;
#endif
	xTaskHandle task;
    xQueueHandle queue;
    static void AdcReadTaskStatic(void*);
    void AdcReadTask();
    const int DEFAULT_VREF = 1100;        //Use adc2_vref_to_gpio() to obtain a better estimate
    enum {ADC_DMA_LEN = 8};
    public:
    bool bControl;
#ifdef BOARD3_SEPARATE
    enum {
        NTARGET_DIRECT = 12,
        NMOTOR_DIRECT = BoardInfo::NMOTOR,
        NFORCE_DIRECT = 0,
    };
#else
    enum {
        NTARGET_DIRECT = 0xFF,
        NMOTOR_DIRECT = 0,
        NFORCE_DIRECT = 0,
    };
#endif
    private:
#ifdef BOARD3_SEPARATE
    const int pwmPins[NMOTOR_DIRECT*2] = {4, 27, 21, 22, 0, 19};    //M0, M1, M2
#else
    const int pwmPins[0] = {};
#endif
    const int adcChs[ADC_DMA_LEN] = {0, 3, 5, 4, 6, 7, 1, 2};   //M0, M1, M2, dummy
    int adcChsRev[8];   //  must be larger than ch numbers


public:
    int adcRaws[NMOTOR_DIRECT*2];
    void Init();
    void Pwm(int ch, float duty);
    uint32_t GetAdcVoltage(int ch);
    int GetAdcRaw(int ch);
};
extern MotorDriver motorDriver;
