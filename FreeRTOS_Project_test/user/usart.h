#ifndef __USART_H
#define __USART_H
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "misc.h"
void My_USART1_Init(int BaudRate);
void usart_send(char *date_buff);
#define DATA_NUM  100
extern uint8_t USART_BUFF[DATA_NUM];
extern unsigned int DATA_STATUS_FLAG;
extern unsigned int ReceiveDataNum;
#endif
