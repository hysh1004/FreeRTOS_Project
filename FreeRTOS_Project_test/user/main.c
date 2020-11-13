#include "main.h"
#include "stm32f4xx_gpio.h"
#include "Nokia_lcd.h"
#include "delay.h" 
#include "led.h"
#include "time3.h"
#include "adc1.h"
#include "usart.h"
#include "FreeRTOS.h"					//FreeRTOS使用		  
#include "task.h"

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

#define LED0_TASK_PRIO		3
#define LED0_STK_SIZE 		120  
TaskHandle_t LED0Task_Handler;
void led0_task(void);

#define LED1_TASK_PRIO		2
#define LED1_STK_SIZE 		120  
TaskHandle_t LED1Task_Handler;
void led1_task(void);
#define DATESIZE 50
char date_buff[DATESIZE] ={0};
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	delay_Init(168);
	Led_config();
	My_USART1_Init(19200);
	//创建开始任务
	xTaskCreate((TaskFunction_t )start_task,            //任务函数
							(const char*    )"start_task",          //任务名称
							(uint16_t       )START_STK_SIZE,        //任务堆栈大小
							(void*          )NULL,                  //传递给任务函数的参数
							(UBaseType_t    )START_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
	vTaskStartScheduler();          //开启任务调度
}
//开始任务任务函数
void start_task(void *pvParameters)
{
		xTaskCreate((TaskFunction_t )led0_task,            //任务函数
							(const char*    )"led0_task",          //任务名称
							(uint16_t       )LED0_STK_SIZE,        //任务堆栈大小
							(void*          )NULL,                  //传递给任务函数的参数
							(UBaseType_t    )LED0_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  )&LED0Task_Handler);   //任务句柄  
		xTaskCreate((TaskFunction_t )led1_task,            //任务函数
							(const char*    )"led1_task",          //任务名称
							(uint16_t       )LED1_STK_SIZE,        //任务堆栈大小
							(void*          )NULL,                  //传递给任务函数的参数
							(UBaseType_t    )LED1_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  )&LED1Task_Handler);   //任务句柄
		vTaskDelete(StartTask_Handler);
}
void led0_task()
{
		uint8_t temp = 0,runnum = 0,taskrun_flag = 0;
		while(1)
		{
				temp = !temp;
				LED0(temp);
				runnum++;
				sprintf(date_buff, "task1 is:%d\r\n",runnum);
				usart_send(date_buff);
				if(runnum>5 && taskrun_flag==0)
				{
						taskrun_flag = 1;
						sprintf(date_buff, "task2 is deleted!!!\r\n");
						usart_send(date_buff);
						vTaskDelete(LED0Task_Handler);
				}
				vTaskDelay(500);
		}
}
void led1_task()
{
		uint8_t temp = 0,runnum = 0;
		while(1)
		{
				temp = !temp;
				LED1(temp);
				runnum++;
				sprintf(date_buff, "task2 is:%d\r\n",runnum);
				usart_send(date_buff);
				vTaskDelay(500);
		}
}
