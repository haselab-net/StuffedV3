#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_adc_cal.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "soc/syscon_struct.h"
#include "soc/syscon_reg.h"
#include "soc/mcpwm_struct.h"
#include "soc/mcpwm_reg.h"
#include "driver/mcpwm.h"
#include "driver/i2s.h"
#include "driver/adc.h"
#include "MotorDriver.h"
extern "C" {
#include "../../PIC/control.h"
}

MotorDriver motorDriver;



void MotorDriver::AdcReadTaskStatic(void* arg){
    MotorDriver* md = (MotorDriver*)arg;
    md->AdcReadTask();
}
void MotorDriver::AdcReadTask(){
    size_t bufLen = ADC_DMA_LEN * 2;
    uint16_t buf[ADC_DMA_LEN];
    while(1) {
        system_event_t evt;
        if (xQueueReceive(queue, &evt, portMAX_DELAY) == pdPASS) {
            if (evt.event_id==2) {
                size_t readBytes;
                i2s_read(I2S_NUM_0, buf, bufLen, &readBytes, portMAX_DELAY);
                for (int i=0; i<readBytes/2; ++i){
                    int ch = buf[i] >> 11;                    
                    int value = buf[i] &0x7FF;
                    int pos = adcChsRev[ch];
                    adcRaws[pos] = adcRaws[pos]*15/16 + value; 
                }
                onControlTimer();
            }
        }
    }
}

void MotorDriver::Init(){
    for(int i=0; i < sizeof(adcChsRev) / sizeof(adcChsRev[0]);++i){
        adcChsRev[adcChs[i]] = i;
    }

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
    Pwm(0, 0.0f);
    Pwm(1, 0.0f);
    Pwm(2, 0.0f);

//#if 1   //  ADC & DMA & I2S
    i2s_config_t i2s_config = {
        mode : (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
        sample_rate : 8000,
        bits_per_sample : i2s_bits_per_sample_t(16),
        channel_format : I2S_CHANNEL_FMT_ONLY_LEFT,
        communication_format : I2S_COMM_FORMAT_I2S_LSB,
        intr_alloc_flags : ESP_INTR_FLAG_LEVEL1,
        dma_buf_count : 2,
        dma_buf_len : ADC_DMA_LEN,
        use_apll : false,
        fixed_mclk : 0,
    };
    vTaskDelay(10);    //  Wait for wake up of ADC.
    adc_set_i2s_data_source(ADC_I2S_DATA_SRC_ADC);
    adc_i2s_mode_init(ADC_UNIT_1, ADC_CHANNEL_0);
    //  Install and start I2S driver
    i2s_driver_install(I2S_NUM_0, &i2s_config, 1, &queue);
    i2s_set_adc_mode(ADC_UNIT_1, ADC1_CHANNEL_0);
    i2s_adc_enable(I2S_NUM_0);

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
    printf("%08x ", patTab.tab[0]);
    printf("%08x ", patTab.tab[1]);
    SYSCON.saradc_sar1_patt_tab[0] = patTab.tab[0];
    SYSCON.saradc_sar1_patt_tab[1] = patTab.tab[1];
    SYSCON.saradc_ctrl2.sar1_inv = 1;
    xTaskCreate(AdcReadTaskStatic, "ADC", 1024*10, this, configMAX_PRIORITIES-1, &task);
#if 0
    while(1){
        for(int ch=0; ch<6; ++ch){
            printf("%3d ", adcRaws[ch]);
        }
        printf("\r\n");
        vTaskDelay(50);
    }
#endif
}

void MotorDriver::Pwm(int ch, float duty){
    if (duty > 0){
        mcpwm_set_signal_low(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_B);
        mcpwm_set_duty(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_A, duty * 100);
        mcpwm_set_duty_type(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
    }else{
        duty *= -1;
        mcpwm_set_signal_low(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_A);
        mcpwm_set_duty(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_B, duty * 100);
        mcpwm_set_duty_type(MCPWM_UNIT_0, (mcpwm_timer_t)ch, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
    }
}
int MotorDriver::GetAdcRaw(int ch){
    return adcRaws[ch];
}
uint32_t MotorDriver::GetAdcVoltage(int ch){
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adcRaws[ch], &adc_chars);
    return voltage;
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
            mcos[i] = motorDriver.adcRaws[i*2] - mcosOffset[i];
            msin[i] = motorDriver.adcRaws[i*2 + 1] - msinOffset[i];
        }
    }
    void setPwm(int ch, SDEC ratio){
        motorDriver.Pwm(ch, (float)ratio / SDEC_ONE);
    }	
}
