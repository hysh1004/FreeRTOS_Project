#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "usart.h"
#include "delay.h"
uint8_t USART_BUFF[DATA_NUM] = {0};
unsigned int DATA_STATUS_FLAG = 0;
unsigned int ReceiveDataNum = 0;
uint8_t res = 0;
extern float float_num;
void My_USART1_Init(int BaudRate)
{
	
	GPIO_InitTypeDef GPIO_STR;
	USART_InitTypeDef USART_STR;
	NVIC_InitTypeDef NVIC_STR;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	//使能串口1时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	//是能GPIOA时钟
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);		//PA9引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);	//PA10引脚复用映射
	
	GPIO_STR.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_STR.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_STR.GPIO_OType = GPIO_OType_PP;
	GPIO_STR.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_STR.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_STR);
	
	USART_STR.USART_BaudRate = BaudRate;
	USART_STR.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_STR.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_STR.USART_Parity = USART_Parity_No;
	USART_STR.USART_StopBits = USART_StopBits_1;
	USART_STR.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_STR);
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_STR.NVIC_IRQChannel = USART1_IRQn;
	NVIC_STR.NVIC_IRQChannelCmd = ENABLE;
	NVIC_STR.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_STR.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_STR);
}

void USART1_IRQHandler(void)
{
	int i;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		res = USART_ReceiveData(USART1);
		
		if((DATA_STATUS_FLAG&0x8000)==0)
		{
			if(DATA_STATUS_FLAG&0x4000)			//接收到结束符
			{
				if(res==0x0a)
				{
					DATA_STATUS_FLAG |= 0x8000;
					if((DATA_STATUS_FLAG&0x3FFF)>=DATA_NUM)
						DATA_STATUS_FLAG = 0;
					USART_BUFF[DATA_STATUS_FLAG&0x3FFF] = res;
					DATA_STATUS_FLAG++;
					ReceiveDataNum = DATA_STATUS_FLAG&0x3fff;
				}
				else
					DATA_STATUS_FLAG = 0;
			}
			else if((DATA_STATUS_FLAG&0x4000)==0)		//未收到结束符
			{
				if(res==0x0d)
				{
					DATA_STATUS_FLAG |= 0x4000;
					if((DATA_STATUS_FLAG&0x3FFF)>=DATA_NUM)
						DATA_STATUS_FLAG = 0;
					USART_BUFF[DATA_STATUS_FLAG&0x3FFF] = res;
					DATA_STATUS_FLAG++;
				}
				else
				{
					if((DATA_STATUS_FLAG&0x3FFF)>=DATA_NUM)
						DATA_STATUS_FLAG = 0;
					USART_BUFF[DATA_STATUS_FLAG&0x3FFF] = res;
					DATA_STATUS_FLAG++;
				}
			}
		}
		if(DATA_STATUS_FLAG&0x8000)
		{
			for(i=0;i<ReceiveDataNum;i++)
			{
				USART_SendData(USART1,USART_BUFF[i]);
				USART_BUFF[i] = 0;
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//??????
			}
			DATA_STATUS_FLAG = 0;
			ReceiveDataNum = 0;
		}
	}
}
void usart_send(char *date_buff){
		int j;
		static uint8_t firstdate_flag = 0;
		for( j= 0; j < strlen(date_buff); j++) {
				USART_SendData(USART1, date_buff[j]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
				if(firstdate_flag==0)
				{
						firstdate_flag = 1;
						delay_us(500);
				}
		}
		
}
