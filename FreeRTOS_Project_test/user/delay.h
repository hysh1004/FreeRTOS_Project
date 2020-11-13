#ifndef _DELAY_H
#define _DELAY_H
#include <stdint.h>
#include "misc.h"
void delay_Init(unsigned char SYSCLK);
void delay_us(uint32_t nus);
void delay_xms(uint32_t nms);
void delay_ms(uint32_t nms);
#endif
