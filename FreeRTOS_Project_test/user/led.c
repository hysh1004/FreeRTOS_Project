#include "led.h"
void Led_config(void)
{
		GPIO_InitTypeDef GPIO_STU;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
		GPIO_STU.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_STU.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_STU.GPIO_OType = GPIO_OType_PP;
		GPIO_STU.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_STU.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF,&GPIO_STU);
}
