#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#ifndef _WIN32
#include "esp_adc_cal.h"
extern "C"{
#include "soc/syscon_struct.h"
}
#include "soc/syscon_reg.h"
#include <soc/mcpwm_struct.h>
#include <soc/mcpwm_reg.h>
#include <driver/mcpwm.h>
#include "driver/i2s.h"
#include "driver/adc.h"
#endif 

#include <string.h>
#include "MotorDriver.h"
extern "C" {
#include "../../../PIC/control.h"
}

#ifdef _WIN32
#include <math.h>
float pwm[NMOTOR];
float theta[NMOTOR];
#endif

MotorDriver motorDriver;


void MotorDriver::AdcReadTaskStatic(void* arg){
    MotorDriver* md = (MotorDriver*)arg;
    md->AdcReadTask();
}

#define ADCI2SNUM   I2S_NUM_0
void MotorDriver::AdcReadTask(){
    const gpio_num_t GPIO_LED = GPIO_NUM_26;
    const size_t bufLen = ADC_DMA_LEN * 2;
#ifndef _WIN32
    gpio_reset_pin(GPIO_LED);
    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);
    int count=0;
	while(1) {
        static uint16_t buf[ADC_DMA_LEN];
        static system_event_t evt;
        count ++;
        if (xQueueReceive(queue, &evt, portMAX_DELAY) == pdPASS) {
            if (evt.event_id==2) {
                //  read ADC
                static size_t readBytes;
                i2s_read(ADCI2SNUM, buf, bufLen, &readBytes, portMAX_DELAY);
                for (int i=0; i<readBytes/2; ++i){
                    int ch = buf[i] >> 11;                    
                    int value = buf[i] &0x7FF;
                    int pos = adcChsRev[ch];
#define FILTER_TIME 16
                    adcRaws[pos] = adcRaws[pos]*(FILTER_TIME-1)/FILTER_TIME + value; 
                }
                //  update target state for targetsAddOrUpdated()
                if (!bForTargetsAddUpdated){
                    readForTargetsAdd = targets.read;
                    availForTargetsAdd = targetsReadAvail();
                    tcrForTargetsAdd = targets.targetCountRead;
                    bForTargetsAddUpdated = true;
                }
                if (bControl && count % 4 == 0){
                    gpio_set_level(GPIO_LED, 1);
                    controlLoop();
                    gpio_set_level(GPIO_LED, 0);
                }
            }
        }
    }
#elif defined _WIN32
	while(1) {
		if (bControl) controlLoop();
		vTaskDelay(1);
    }
#else
#error
#endif
}

void MotorDriver::Init(){
    bControl = true;
#ifndef _WIN32
	//  PWM Init
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, pwmPins[0]);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, pwmPins[1]);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, pwmPins[2]);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, pwmPins[3]);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM2A, pwmPins[4]);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM2B, pwmPins[5]);

    mcpwm_config_t pwm_config;
    pwm_config.frequency = 20000;       //frequency in Hz,
    pwm_config.cmpr_a = 0;              //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;              //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A & PWM0B with above settings
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);    //Configure PWM0A & PWM0B with above settings
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);    //Configure PWM0A & PWM0B with above settings
#endif

    //  Init control/command and set initial values to motors. 
    controlInit();
    commandInit();

    //  ADC with DMA and I2S mode init. This also start periodic interrupt for control.
    //  i2s settings
    for(int i=0; i < sizeof(adcChsRev) / sizeof(adcChsRev[0]);++i){
        adcChsRev[adcChs[i]] = i;
    }
#ifndef _WIN32
	i2s_config_t i2s_config;
    memset(&i2s_config, 0, sizeof(i2s_config));
    i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN);
    i2s_config.sample_rate = ADC_DMA_LEN * 3000 * 4;   //  3kHz * 4
    i2s_config.bits_per_sample = i2s_bits_per_sample_t(16);
    i2s_config.channel_format = I2S_CHANNEL_FMT_ONLY_LEFT;
    i2s_config.communication_format = I2S_COMM_FORMAT_I2S_LSB;
    i2s_config.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;
    i2s_config.dma_buf_count = 2;
    i2s_config.dma_buf_len = ADC_DMA_LEN;
    vTaskDelay(50);    //  Wait for wake up of ADC.
    adc_set_i2s_data_source(ADC_I2S_DATA_SRC_ADC);
    adc_i2s_mode_init(ADC_UNIT_1, ADC_CHANNEL_0);
    //  Install and start I2S driver
    i2s_driver_install(ADCI2SNUM, &i2s_config, 1, &queue);
    i2s_set_adc_mode(ADC_UNIT_1, ADC1_CHANNEL_0);
    i2s_adc_enable(ADCI2SNUM);

#ifdef BOARD3_SEPARATE
    SYSCON.saradc_ctrl.sar1_patt_len = NMOTOR_DIRECT*2-1;   // table length - 1
#else
    SYSCON.saradc_ctrl.sar1_patt_len = 0;
#endif
    SYSCON.saradc_ctrl.data_sar_sel = true;
    //  Making ADC scanning table pattern (WIDTH=11, DB=11) = 7
    //  ADC_WIDTH_BIT_9 = 0, ADC_WIDTH_BIT_12 = 3;
    //  ADC_ATTEN_DB_0 = 0, ADC_ATTEN_DB_2_5=1, ADC_ATTEN_DB_6=2, ADC_ATTEN_DB_11=3
    uint32_t patterns[ADC_DMA_LEN];
    for(int i=0; i<ADC_DMA_LEN; ++i){
        patterns[i] = (adcChs[i]<<4) | 7;
    }
    union{
        uint32_t tab[2];
        unsigned char pat[ADC_DMA_LEN];
    } patTab;
    for(int i=0; i<8; ++i){
        patTab.pat[i] = patterns[(i-i%4) + (3-i%4)];
    }
    //logPrintf("%08x ", patTab.tab[0]);
    //logPrintf("%08x ", patTab.tab[1]);
    SYSCON.saradc_sar1_patt_tab[0] = patTab.tab[0];
    SYSCON.saradc_sar1_patt_tab[1] = patTab.tab[1];
    SYSCON.saradc_ctrl2.sar1_inv = 1;
#endif
	xTaskCreate(AdcReadTaskStatic, "ADC", 512, this, configMAX_PRIORITIES-1, &task);

    for(int ch=0; ch<NMOTOR_DIRECT; ++ch){
        torqueLimit.max[ch] = (SDEC)(1.0*SDEC_ONE);
        torqueLimit.min[ch] = (SDEC)(-1.0*SDEC_ONE);
        Pwm(ch, 0);
    }
}

void MotorDriver::Pwm(int ch, SDEC duty){  //   SDEC -1 to 1 (-1024 - 1024)
#ifndef _WIN32
    uint32_t set_duty = (MCPWM0.timer[(mcpwm_timer_t)ch].period.period) * duty / SDEC_ONE;
	if (duty > 0){
        mcpwm_set_signal_low(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_B);
        mcpwm_set_duty_in_us(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_A, set_duty);
        mcpwm_set_duty_type(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
    }else{
        duty *= -1;
        mcpwm_set_signal_low(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_A);
        mcpwm_set_duty_in_us(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_B, set_duty);
        mcpwm_set_duty_type(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
    }
#else
	pwm[ch] = duty;
	float dt = 0.1f;
	theta[ch] = theta[ch] + pwm[ch] * dt;
	motorDriver.adcRaws[ch * 2] = (int) ((1+sin(theta[ch])) * msinOffset[ch]);
	motorDriver.adcRaws[ch * 2 + 1] = (int) ((1 + cos(theta[ch])) * mcosOffset[ch]);
#endif
}
int MotorDriver::GetAdcRaw(int ch){
    return adcRaws[ch];
}

#define ADC_CENTER  ((0x700+0x35C0)/2)
const SDEC mcosOffset[NAXIS] ={
    ADC_CENTER, ADC_CENTER, ADC_CENTER
};
const SDEC msinOffset[NAXIS] ={
    ADC_CENTER, ADC_CENTER, ADC_CENTER
};

extern "C"{
    void readADC(){
        int i;
        for(i=0; i<MotorDriver::NMOTOR_DIRECT; ++i){
            msin[i] = motorDriver.adcRaws[i*2] - msinOffset[i];
            mcos[i] = motorDriver.adcRaws[i*2 + 1] - mcosOffset[i];
        }
    }
    void setPwm(int ch, SDEC ratio){
        motorDriver.Pwm(ch, ratio);
    }	
}
