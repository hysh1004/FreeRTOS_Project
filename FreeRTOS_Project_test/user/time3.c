#include "time3.h"
#include "usart.h"
time mytime;
time_date mytime_date;
uint8_t LcdShow_Flag = 0;
uint8_t UsartSend_Flag = 0;

un_SysFlag System_time;
unsigned long ul_100usCnt = 0;
uint16_t usUARTCounter = 0;
uint16_t m_i16_NumFor10ms = 0;
uint16_t m_i16_NumFor20ms = 0;
uint16_t m_i16_NumFor40ms = 0;
uint16_t m_i16_NumFor100ms = 0;
uint16_t m_i16_NumFor200ms = 0;
uint16_t m_i16_NumFor250ms = 0;
uint16_t m_i16_NumFor300ms = 0;
uint16_t m_i16_NumFor500ms = 0;
uint16_t m_i16_NumFor1s = 0;
uint16_t m_i16_NumFor5s = 0;
uint16_t m_i16_NumFor10s = 0;


void time3_config(int arr,int psc)
{
		TIM_TimeBaseInitTypeDef TIME3_STU;
		NVIC_InitTypeDef NVIC_STU;
		NVIC_STU.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_STU.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_STU.NVIC_IRQChannelSubPriority = 1;
		NVIC_STU.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_STU);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		TIME3_STU.TIM_ClockDivision = TIM_CKD_DIV1;
		TIME3_STU.TIM_CounterMode = TIM_CounterMode_Up;
		TIME3_STU.TIM_Period = arr;
		TIME3_STU.TIM_Prescaler = psc;
		TIM_TimeBaseInit(TIM3,&TIME3_STU);
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
		TIM_Cmd(TIM3,ENABLE);
}

void TIM3_IRQHandler(void)
{
		if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
		{
				LcdShow_Flag = 1;
				UsartSend_Flag = 1;
				
				if (++ul_100usCnt >= 60000)   // 6s��ʱ��
					ul_100usCnt = 0;
		}
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

void SysTimerMaintain(void)
{
    uint16_t m_i16_temp;


    System_time.bTimer10ms = 0;										//��40ms��ʱ��־
    m_i16_temp= ul_100usCnt/100;
    if (m_i16_temp!=m_i16_NumFor10ms )									//40ms��
    {

        m_i16_NumFor10ms = m_i16_temp;
        System_time.bTimer10ms = 1;								//��10ms��ʱ��־

    }

    System_time.bTimer20ms = 0;										//��20ms��ʱ��־
    m_i16_temp= ul_100usCnt/200;
    if ( m_i16_temp!=m_i16_NumFor20ms )									//20ms��
    {

        m_i16_NumFor20ms = m_i16_temp;
        System_time.bTimer20ms = 1;								//��20ms��ʱ��־
    }

    System_time.bTimer40ms = 0;										//��40ms��ʱ��־
    m_i16_temp= ul_100usCnt/400;
    if ( m_i16_temp!=m_i16_NumFor40ms )									//40ms��
    {
        m_i16_NumFor40ms = m_i16_temp;
        System_time.bTimer40ms = 1;									//��40ms��ʱ��־
    }

    System_time.bTimer100ms = 0;										//��100ms��ʱ��־
    m_i16_temp= ul_100usCnt/1000;
    if ( m_i16_temp!=m_i16_NumFor100ms )								//100ms��
    {
        m_i16_NumFor100ms = m_i16_temp;
        System_time.bTimer100ms = 1;									//��100ms��ʱ��־

    }

    System_time.bTimer200ms = 0;										//��200ms��ʱ��־
    m_i16_temp= ul_100usCnt/2000;
    if ( m_i16_temp!=m_i16_NumFor200ms )								//200ms��
    {
        m_i16_NumFor200ms = m_i16_temp;
        System_time.bTimer200ms = 1;									//��200ms��ʱ��־
    }


    System_time.bTimer250ms = 0;										//��250ms��ʱ��־
    m_i16_temp= ul_100usCnt/2500;
    if ( m_i16_temp!=m_i16_NumFor250ms )								//250ms��
    {
        m_i16_NumFor250ms = m_i16_temp;
        System_time.bTimer250ms = 1;									//��250ms��ʱ��־
    }

    System_time.bTimer300ms = 0;										//��300ms��ʱ��־
    m_i16_temp= ul_100usCnt/3000;
    if ( m_i16_temp!=m_i16_NumFor300ms )								//300ms��
    {
        m_i16_NumFor300ms = m_i16_temp;
        System_time.bTimer300ms = 1;									//��300ms��ʱ��־
    }

    System_time.bTimer500ms = 0;										//��500ms��ʱ��־
    m_i16_temp= ul_100usCnt/5000;
    if ( m_i16_temp!=m_i16_NumFor500ms )								//300ms��
    {
        m_i16_NumFor500ms = m_i16_temp;
        System_time.bTimer500ms = 1;									//��500ms��ʱ��־
    }

    System_time.bTimer1s = 0;										//��1s��ʱ��־
    m_i16_temp= ul_100usCnt/10000;
    if ( m_i16_temp!=m_i16_NumFor1s )									//1s��
    {
        m_i16_NumFor1s = m_i16_temp;
        System_time.bTimer1s = 1;									//��1s��ʱ��־
				mytime.sec++;
    }
    System_time.bTimer5s = 0;										//��5s��ʱ��־
    m_i16_temp= ul_100usCnt/50000;
    if ( m_i16_temp!=m_i16_NumFor5s )									//5s��
    {
        m_i16_NumFor5s = m_i16_temp;
        System_time.bTimer5s = 1;								  	//��5s��ʱ��־
    }

    return;
}

void my_time(void)
{
		if(mytime.sec>=60)
		{
				mytime.sec = 0;
				mytime.min++;
		}
		if(mytime.min>=60)
		{
				mytime.min = 0;
				mytime.hour++;
		}
		if(mytime.hour>=24)
		{
				mytime.hour = 0;
		}
		mytime_date.hour_h = mytime.hour/10+48;
		mytime_date.hour_l = mytime.hour%10+48;
		mytime_date.c1 = '-';
		mytime_date.min_h  = mytime.min/10+48;
		mytime_date.min_l  = mytime.min%10+48;
		mytime_date.c2 = '-';
		mytime_date.sec_h  = mytime.sec/10+48;
		mytime_date.sec_l  = mytime.sec%10+48;
}
