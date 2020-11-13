#include "stm32f4xx_gpio.h"
#include "delay.h"
#include "FreeRTOS.h"					//FreeRTOS使用		  
#include "task.h"
static  uint8_t fac_us = 0;
static  uint16_t fac_ms = 0;

extern void xPortSysTickHandler(void);
//systick中断服务函数,使用OS时用到
void SysTick_Handler(void)
{	
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//系统已经运行
    {
        xPortSysTickHandler();	
    }
}
void delay_Init(unsigned char SYSCLK)
{
		uint32_t reload;
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); 
		fac_us=SYSCLK;							//不论是否使用OS,fac_us都需要使用
		reload=SYSCLK;							//每秒钟的计数次数 单位为M	   
		reload*=1000000/configTICK_RATE_HZ;		//根据configTICK_RATE_HZ设定溢出时间
												//reload为24位寄存器,最大值:16777216,在168M下,约合0.0998s左右	
		fac_ms=1000/configTICK_RATE_HZ;			//代表OS可以延时的最少单位	   
		SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//开启SYSTICK中断
		SysTick->LOAD=reload; 					//每1/configTICK_RATE_HZ断一次	
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; //开启SYSTICK
}

void delay_us(uint32_t nus)
{
		uint32_t ticks;
		uint32_t told,tnow,tcnt=0;
		uint32_t reload=SysTick->LOAD;				//LOAD的值	    	 
		ticks=nus*fac_us; 						//需要的节拍数 
		told=SysTick->VAL;        				//刚进入时的计数器值
		while(1)
		{
			tnow=SysTick->VAL;	
			if(tnow!=told)
			{	    
				if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
				else tcnt+=reload-tnow+told;	    
				told=tnow;
				if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
			}  
		}
}

void delay_ms(uint32_t nms)
{
		if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//系统已经运行
		{		
			if(nms>=fac_ms)						//延时的时间大于OS的最少时间周期 
			{ 
					vTaskDelay(nms/fac_ms);	 		//FreeRTOS延时
			}
			nms%=fac_ms;						//OS已经无法提供这么小的延时了,采用普通方式延时    
		}
		delay_us((u32)(nms*1000));				//普通方式延时
}


void delay_xms(uint32_t nms)
{
		uint32_t i;
		for(i=0;i<nms;i++) delay_us(1000);
}
