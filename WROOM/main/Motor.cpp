#include "Motor.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#ifdef BOARD3_SEPARATE
#define NMOTOR_DIRECT	3
int pwmPins[NMOTOR_DIRECT*2] = {4, 19, 26, 27, 21, 22};    //M2, M3, M0, M1, M4, M5
int adcChs[NMOTOR_DIRECT*2] = {3, 0, 6, 7, 4, 5};
#endif

#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate


void MotorDriver::Init(){
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

    //  ADC Init
    adc1_config_width(ADC_WIDTH_12Bit);
    for(int i=0; i<NMOTOR_DIRECT*2; ++i){
        adc1_config_channel_atten((adc1_channel_t)adcChs[i], ADC_ATTEN_DB_11);
        adc_gpio_init(ADC_UNIT_1, (adc_channel_t)adcChs[i]);
    }
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_11db, ADC_WIDTH_BIT_12, DEFAULT_VREF, &adc_chars);
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
void MotorDriver::AdcRead(){
    for(int ch=0; ch < NMOTOR_DIRECT*2; ++ch){
        adcRaws[ch] = 0;// adcRaws[ch] * 15 / 16;
        adcRaws[ch] += adc1_get_raw((adc1_channel_t)adcChs[ch]);
    }
}
int MotorDriver::GetAdcRaw(int ch){
    return adcRaws[ch];
}
uint32_t MotorDriver::GetAdcVoltage(int ch){
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adcRaws[ch], &adc_chars);
    return voltage;
}
