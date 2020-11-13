#ifndef _NOKIA_LCD_H_
#define __NOKIA_LCD_H_
#include "stdint.h"
#include "stm32f4xx_gpio.h"
#define Reset_Flag(x) (GPIO_WriteBit(GPIOA,GPIO_Pin_0,x))
#define CE_Flag(x) (GPIO_WriteBit(GPIOA,GPIO_Pin_1,x))
#define DC_Flag(x) (GPIO_WriteBit(GPIOA,GPIO_Pin_2,x))
#define DIN_Flag(x) (GPIO_WriteBit(GPIOA,GPIO_Pin_3,x))
#define CLK_Flag(x) (GPIO_WriteBit(GPIOA,GPIO_Pin_4,x))
#define BL_Flag(x) (GPIO_WriteBit(GPIOA,GPIO_Pin_5,x))

void Nokia_lcd_config(void);
void Nokia_Init(void);
void Nokia_send_byte(uint8_t date,BitAction command);
void Nokia_clear(void);
void Nokia_set_XY(uint8_t X,uint8_t Y);
void Nokia_Date(uint8_t X,uint8_t Y,char *s);
void Date_Send(uint8_t X,uint8_t Y,uint16_t date);
#define DateSize 10
#endif
