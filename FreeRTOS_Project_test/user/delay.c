#include "stm32f4xx_gpio.h"
#include "delay.h"
#include "FreeRTOS.h"					//FreeRTOSʹ��		  
#include "task.h"
static  uint8_t fac_us = 0;
static  uint16_t fac_ms = 0;

extern void xPortSysTickHandler(void);
//systick�жϷ�����,ʹ��OSʱ�õ�
void SysTick_Handler(void)
{	
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
    {
        xPortSysTickHandler();	
    }
}
void delay_Init(unsigned char SYSCLK)
{
		uint32_t reload;
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); 
		fac_us=SYSCLK;							//�����Ƿ�ʹ��OS,fac_us����Ҫʹ��
		reload=SYSCLK;							//ÿ���ӵļ������� ��λΪM	   
		reload*=1000000/configTICK_RATE_HZ;		//����configTICK_RATE_HZ�趨���ʱ��
												//reloadΪ24λ�Ĵ���,���ֵ:16777216,��168M��,Լ��0.0998s����	
		fac_ms=1000/configTICK_RATE_HZ;			//����OS������ʱ�����ٵ�λ	   
		SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//����SYSTICK�ж�
		SysTick->LOAD=reload; 					//ÿ1/configTICK_RATE_HZ��һ��	
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; //����SYSTICK
}

void delay_us(uint32_t nus)
{
		uint32_t ticks;
		uint32_t told,tnow,tcnt=0;
		uint32_t reload=SysTick->LOAD;				//LOAD��ֵ	    	 
		ticks=nus*fac_us; 						//��Ҫ�Ľ����� 
		told=SysTick->VAL;        				//�ս���ʱ�ļ�����ֵ
		while(1)
		{
			tnow=SysTick->VAL;	
			if(tnow!=told)
			{	    
				if(tnow<told)tcnt+=told-tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
				else tcnt+=reload-tnow+told;	    
				told=tnow;
				if(tcnt>=ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
			}  
		}
}

void delay_ms(uint32_t nms)
{
		if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
		{		
			if(nms>=fac_ms)						//��ʱ��ʱ�����OS������ʱ������ 
			{ 
					vTaskDelay(nms/fac_ms);	 		//FreeRTOS��ʱ
			}
			nms%=fac_ms;						//OS�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
		}
		delay_us((u32)(nms*1000));				//��ͨ��ʽ��ʱ
}


void delay_xms(uint32_t nms)
{
		uint32_t i;
		for(i=0;i<nms;i++) delay_us(1000);
}
