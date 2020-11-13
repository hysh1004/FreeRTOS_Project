#ifndef _TIME3_H_
#define _TIME3_H_
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
void time3_config(int arr,int psc);
void my_time(void);
typedef struct
{
		char hour;
		char min;
		char sec;
}time;
typedef struct
{
		char hour_h;
		char hour_l;
		char c1;
		char min_h;
		char min_l;
		char c2;
		char sec_h;
		char sec_l;
		char c3;
}time_date;
extern time mytime;
extern time_date mytime_date;

extern unsigned long ul_100usCnt;
extern uint16_t usUARTCounter;
extern uint16_t m_i16_NumFor10ms;
extern uint16_t m_i16_NumFor20ms;
extern uint16_t m_i16_NumFor40ms;
extern uint16_t m_i16_NumFor100ms;
extern uint16_t m_i16_NumFor200ms;
extern uint16_t m_i16_NumFor250ms;
extern uint16_t m_i16_NumFor300ms;
extern uint16_t m_i16_NumFor500ms;
extern uint16_t m_i16_NumFor1s;
extern uint16_t m_i16_NumFor5s;
extern uint16_t m_i16_NumFor10s;
typedef struct	SysStatesFlag
{
    uint16_t	bTimer100ms	:1;
    uint16_t	bTimer200ms	:1;
    uint16_t	bTimer250ms	:1;
    uint16_t	bTimer300ms	:1;
    uint16_t	bTimer500ms	:1;
    uint16_t	bTimer10ms		:1;
    uint16_t	bTimer20ms		:1;
    uint16_t 	bTimer40ms		:1;
    uint16_t	bTimer1s		:1;
    uint16_t	bTimer5s		:1;
    uint16_t	bTimer10s		:1;
    uint16_t 	bRsved		:2;
}un_SysFlag;
extern un_SysFlag System_time;
void SysTimerMaintain(void);
#endif
