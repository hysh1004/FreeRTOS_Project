#include "adc1.h"
#include "delay.h"
#define DateNum 11
void Adc_config(void)
{
		GPIO_InitTypeDef GPIO_STU;
		ADC_CommonInitTypeDef ADC_COM_STU;
		ADC_InitTypeDef ADC_STU;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		GPIO_STU.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
		GPIO_STU.GPIO_Mode = GPIO_Mode_AN;
		GPIO_STU.GPIO_OType = GPIO_OType_PP;
		GPIO_STU.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_STU.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOC,&GPIO_STU);
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);		//ADC¸´Î»
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);		//¸´Î»½áÊø
		
		ADC_COM_STU.ADC_Mode = ADC_Mode_Independent;
		ADC_COM_STU.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
		ADC_COM_STU.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
		ADC_COM_STU.ADC_Prescaler = ADC_Prescaler_Div4;
		ADC_CommonInit(&ADC_COM_STU);
		
		ADC_STU.ADC_Resolution = ADC_Resolution_12b;
		ADC_STU.ADC_ScanConvMode = DISABLE;
		ADC_STU.ADC_ContinuousConvMode = DISABLE;
		ADC_STU.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		ADC_STU.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_STU.ADC_NbrOfConversion = 1;
		ADC_Init(ADC1,&ADC_STU);
		ADC_Cmd(ADC1,ENABLE);
}
uint16_t get_Adc(uint8_t ch)
{
		ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_3Cycles);
		ADC_SoftwareStartConv(ADC1);
		while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
		return ADC_GetConversionValue(ADC1);
}
uint16_t Get_Average(uint8_t ch)
{
		uint32_t temp = 0;
		int i = 0;
		for(i=0;i<DateNum;i++)
		{
				temp += get_Adc(ch);
		}
		return temp/DateNum;                                                                                              
}
