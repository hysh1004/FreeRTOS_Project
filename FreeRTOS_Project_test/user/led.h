#ifndef _LED_H_
#define _LED_H_
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
void Led_config(void);
void relaycontrol(void);
#define LED0(x) GPIO_WriteBit(GPIOF,GPIO_Pin_9,x)
#define LED1(x) GPIO_WriteBit(GPIOF,GPIO_Pin_10,x)
#define LED0_ON GPIO_WriteBit(GPIOF,GPIO_Pin_9,Bit_RESET)
#define LED0_OFF GPIO_WriteBit(GPIOF,GPIO_Pin_9,Bit_SET)
#define LED1_ON GPIO_WriteBit(GPIOF,GPIO_Pin_10,Bit_RESET)
#define LED1_OFF GPIO_WriteBit(GPIOF,GPIO_Pin_10,Bit_SET)
#endif
