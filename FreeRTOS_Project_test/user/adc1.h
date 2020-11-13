#ifndef _ADC_H_
#define _ADC_H_
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
void Adc_config(void);
uint16_t get_Adc(uint8_t ch);
uint16_t Get_Average(uint8_t ch);
#endif
