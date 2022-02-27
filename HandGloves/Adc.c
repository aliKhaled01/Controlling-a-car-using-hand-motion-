/*****************************************************
 *Author :Moatasem
 *Date:   12/10/2018
 *Version: v02
 *Brief: GPIO peripheral
 *******************************************************/
#include "Adc.h"
#if ADC_UC==1
#include <stddef.h>
#include "utiles.h"

static void(*adcInterrupt)(void);

void ADC_init(ADC_Config_t *obj){

	WRITE_BIT(ADCSRA ,ADEN ,HIGH);//enable adc module
	/* select reference voltage */
	if (obj->select_reference_voltage ==VrefAt_AREF_Pin)
	{
		WRITE_BIT(ADMUX,REFS0 , LOW);
		WRITE_BIT(ADMUX,REFS1, LOW);
	}
	else if (obj->select_reference_voltage ==VrefAt_AVCC_pin_AREF_pin)
	{
		WRITE_BIT(ADMUX,REFS0 , HIGH);
		WRITE_BIT(ADMUX,REFS1, LOW);
	}
	else
	{
		WRITE_BIT(ADMUX,REFS0 , HIGH);
		WRITE_BIT(ADMUX,REFS1, HIGH);
	}

	/*select ADC channel */
	if (obj->select_ADC_channel == Single_Ended_Input_On_Channel_0_ADC0)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (obj->select_ADC_channel == Single_Ended_Input_On_Channel_1_ADC1)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (obj->select_ADC_channel == Single_Ended_Input_On_Channel_2_ADC2)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (obj->select_ADC_channel == Single_Ended_Input_On_Channel_3_ADC3)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (obj->select_ADC_channel == Single_Ended_Input_On_Channel_4_ADC4)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (obj->select_ADC_channel == Single_Ended_Input_On_Channel_5_ADC5)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (obj->select_ADC_channel == Single_Ended_Input_On_Channel_6_ADC6)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (obj->select_ADC_channel == Single_Ended_Input_On_Channel_7_ADC7)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
#ifdef ENABLE_ADC_DIFFERENTIAL_INPUT

	else if (obj->select_ADC_channel == DifferentialWithGain_10x_PositiveInputOn_ADC1_NegativeInputOn_ADC0)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , LOW);
	}

	else if (obj->select_ADC_channel == DifferentialWithGain_200x_PositiveInputOn_ADC1_NegativeInputOn_ADC0)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , LOW);
	}

	else if (obj->select_ADC_channel == DifferentialWithGain_10x_PositiveInputOn_ADC3_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , LOW);
	}

	else if (obj->select_ADC_channel == DifferentialWithGain_200x_PositiveInputOn_ADC3_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}

	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC2_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (obj->select_ADC_channel == DifferentialWithGain_200x_PositiveInputOn_ADC3_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC6_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC7_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC1_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}

	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC3_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (obj->select_ADC_channel == DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
#endif

	// select prescaler
	//	if (obj->select_ADC_prescaler == DivisionBy_2)
	//	{
	//		WRITE_BIT(ADCSRA , 0, HIGH);
	//		WRITE_BIT(ADCSRA , 1, LOW);
	//		WRITE_BIT(ADCSRA , 2, LOW);
	//	}
	//	else if (obj->select_ADC_prescaler == DivisionBy_4)
	//	{
	//		WRITE_BIT(ADCSRA , 0, LOW);
	//		WRITE_BIT(ADCSRA , 1, HIGH);
	//		WRITE_BIT(ADCSRA , 2, LOW);
	//	}
	//	else if (obj->select_ADC_prescaler == DivisionBy_8)
	//	{
	//		WRITE_BIT(ADCSRA , 0, HIGH);
	//		WRITE_BIT(ADCSRA , 1, HIGH);
	//		WRITE_BIT(ADCSRA , 2, LOW);
	//	}
	//	else if (obj->select_ADC_prescaler == DivisionBy_16)
	//	{
	//		WRITE_BIT(ADCSRA , 0, LOW);
	//		WRITE_BIT(ADCSRA , 1, LOW);
	//		WRITE_BIT(ADCSRA , 2, HIGH);
	//	}
	//
	//	else if (obj->select_ADC_prescaler == DivisionBy_64)
	//	{
	//		WRITE_BIT(ADCSRA , 0, LOW);
	//		WRITE_BIT(ADCSRA , 1, HIGH);
	//		WRITE_BIT(ADCSRA , 2, HIGH);
	//	}
	//	else if (obj->select_ADC_prescaler == DivisionBy_128)
	//	{
	//		WRITE_BIT(ADCSRA , 0, HIGH);
	//		WRITE_BIT(ADCSRA , 1, HIGH);
	//		WRITE_BIT(ADCSRA , 2, HIGH);
	//	}
	//	else
	//	{
	//		WRITE_BIT(ADCSRA , 0, LOW);
	//		WRITE_BIT(ADCSRA , 1, LOW);
	//		WRITE_BIT(ADCSRA , 2, LOW);
	//	}

	ADCSRA&=~(7);//clear 3 bits
	ADCSRA|=obj->select_ADC_prescaler;

	if (obj->select_AutoTrigger_source == AutoTriggerIS_Disabled)
	{
		WRITE_BIT(ADCSRA , 5 , LOW);  // disable auto trigger
	}
	// Auto Trigger select
#ifdef ENABLE_AUTO_TRIGGER_SOURCE
	else if (obj->select_AutoTrigger_source == Free_Running_Mode)
	{

		WRITE_BIT(SFIOR , 5 , LOW);
		WRITE_BIT(SFIOR , 6 , LOW);
		WRITE_BIT(SFIOR , 7, LOW);
	}

	else{


		if (obj->select_AutoTrigger_source == Analog_Comparator)
		{
			WRITE_BIT(SFIOR , 5 , HIGH);
			WRITE_BIT(SFIOR , 6 , LOW);
			WRITE_BIT(SFIOR , 7, LOW);
		}
		else if (obj->select_AutoTrigger_source == External_Interrupt_Request_0)
		{
			WRITE_BIT(SFIOR , 5 , LOW);
			WRITE_BIT(SFIOR , 6 , HIGH);
			WRITE_BIT(SFIOR , 7, LOW);
		}
		else if (obj->select_AutoTrigger_source == Timer_Counter0_Compare_Match)
		{
			WRITE_BIT(SFIOR , 5 , HIGH);
			WRITE_BIT(SFIOR , 6 , HIGH);
			WRITE_BIT(SFIOR , 7, LOW);
		}
		else if (obj->select_AutoTrigger_source == Timer_Counter0_Overflow)
		{
			WRITE_BIT(SFIOR , 5 , LOW);
			WRITE_BIT(SFIOR , 6 , LOW);
			WRITE_BIT(SFIOR , 7, HIGH);
		}
		else if (obj->select_AutoTrigger_source == Timer_Counter_Compare_Match_B)
		{
			WRITE_BIT(SFIOR , 5 , HIGH);
			WRITE_BIT(SFIOR , 6 , LOW);
			WRITE_BIT(SFIOR , 7, HIGH);
		}
		else if (obj->select_AutoTrigger_source == Timer_Counter1_Overflow)
		{
			WRITE_BIT(SFIOR , 5 , LOW);
			WRITE_BIT(SFIOR , 6 , HIGH);
			WRITE_BIT(SFIOR , 7, HIGH);
		}
		else if (obj->select_AutoTrigger_source == Timer_Counter1_Capture_Event)
		{
			WRITE_BIT(SFIOR , 5 , HIGH);
			WRITE_BIT(SFIOR , 6 , HIGH);
			WRITE_BIT(SFIOR , 7, HIGH);
		}
	}
	WRITE_BIT(ADCSRA , 5 , HIGH); // enable autotrigger

#endif

}
//------------------------------------------------
uint16 ADC_read(){
	uint16 data=0;
	ADC_start_conversion(); // start conversion//fclk fclk/128 adc< cpu
	while(GET_BIT(ADCSRA ,ADIF) == 0);  // wait until conversion completes , flag = 1when conversion completes
	data=((uint8)ADCL)|(ADCH<<8);
	return data;
}

/************************************************************************/
/*                 ADC interrupt                                        */
/************************************************************************/
void ADC_init_interrupt(void(*adcInterruptFunctionPtr)(void)){
	WRITE_BIT(ADCSRA , 3 , HIGH);//enable interrupt
	adcInterrupt = adcInterruptFunctionPtr ;
}
//------------------------------------------------------------------------
void ADC_change_prescalar(ADC_Prescaler_t ADC_prescaler)
{
	if (ADC_prescaler == DivisionBy_2)
	{
		WRITE_BIT(ADCSRA , 0, HIGH);
		WRITE_BIT(ADCSRA , 1, LOW);
		WRITE_BIT(ADCSRA , 2, LOW);
	}
	else if (ADC_prescaler == DivisionBy_4)
	{
		WRITE_BIT(ADCSRA , 0, LOW);
		WRITE_BIT(ADCSRA , 1, HIGH);
		WRITE_BIT(ADCSRA , 2, LOW);
	}
	else if (ADC_prescaler == DivisionBy_8)
	{
		WRITE_BIT(ADCSRA , 0, HIGH);
		WRITE_BIT(ADCSRA , 1, HIGH);
		WRITE_BIT(ADCSRA , 2, LOW);
	}
	else if (ADC_prescaler == DivisionBy_16)
	{
		WRITE_BIT(ADCSRA , 0, LOW);
		WRITE_BIT(ADCSRA , 1, LOW);
		WRITE_BIT(ADCSRA , 2, HIGH);
	}
	else if (ADC_prescaler == DivisionBy_2)
	{
		WRITE_BIT(ADCSRA , 0, HIGH);
		WRITE_BIT(ADCSRA , 1, LOW);
		WRITE_BIT(ADCSRA , 2, HIGH);
	}
	else if (ADC_prescaler == DivisionBy_64)
	{
		WRITE_BIT(ADCSRA , 0, LOW);
		WRITE_BIT(ADCSRA , 1, HIGH);
		WRITE_BIT(ADCSRA , 2, HIGH);
	}
	else if (ADC_prescaler == DivisionBy_128)
	{
		WRITE_BIT(ADCSRA , 0, HIGH);
		WRITE_BIT(ADCSRA , 1, HIGH);
		WRITE_BIT(ADCSRA , 2, HIGH);
	}
	else
	{
		WRITE_BIT(ADCSRA , 0, LOW);
		WRITE_BIT(ADCSRA , 1, LOW);
		WRITE_BIT(ADCSRA , 2, LOW);
	}

}
void ADC_change_channel(ADC_channelSelect_t ADC_channelSelect)
{
	if (ADC_channelSelect == Single_Ended_Input_On_Channel_0_ADC0)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (ADC_channelSelect == Single_Ended_Input_On_Channel_1_ADC1)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (ADC_channelSelect == Single_Ended_Input_On_Channel_2_ADC2)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (ADC_channelSelect == Single_Ended_Input_On_Channel_3_ADC3)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (ADC_channelSelect == Single_Ended_Input_On_Channel_4_ADC4)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (ADC_channelSelect == Single_Ended_Input_On_Channel_5_ADC5)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (ADC_channelSelect == Single_Ended_Input_On_Channel_6_ADC6)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (ADC_channelSelect == Single_Ended_Input_On_Channel_7_ADC7)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
#ifdef ENABLE_ADC_DIFFERENTIAL_INPUT
	else if (ADC_channelSelect == DifferentialWithGain_10x_PositiveInputOn_ADC1_NegativeInputOn_ADC0)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , LOW);
	}

	else if (ADC_channelSelect == DifferentialWithGain_200x_PositiveInputOn_ADC1_NegativeInputOn_ADC0)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , LOW);
	}

	else if (ADC_channelSelect == DifferentialWithGain_10x_PositiveInputOn_ADC3_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , LOW);
	}

	else if (ADC_channelSelect == DifferentialWithGain_200x_PositiveInputOn_ADC3_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , LOW);
	}
	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}

	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC2_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (ADC_channelSelect == DifferentialWithGain_200x_PositiveInputOn_ADC3_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC6_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC7_NegativeInputOn_ADC1)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , LOW);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC1_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}

	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC3_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, HIGH);
		WRITE_BIT(ADMUX , 2, LOW);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, LOW);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
	else if (ADC_channelSelect == DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC2)
	{
		WRITE_BIT(ADMUX , 0, HIGH);
		WRITE_BIT(ADMUX , 1, LOW);
		WRITE_BIT(ADMUX , 2, HIGH);
		WRITE_BIT(ADMUX , 3 , HIGH);
		WRITE_BIT(ADMUX , 4 , HIGH);
	}
#endif
}
//
//void ADC_change_triggersource(ADC_autoTriggerSource_t ADC_autoTriggerSource)
//{
//
//	#ifdef ENABLE_AUTO_TRIGGER_SOURCE
//	 if (ADC_autoTriggerSource == Free_Running_Mode)
//	{
//
//		WRITE_BIT(SFIOR , 5 , LOW);
//		WRITE_BIT(SFIOR , 6 , LOW);
//		WRITE_BIT(SFIOR , 7, LOW);
//	}
//
//	else{
//
//
//		if (ADC_autoTriggerSource == Analog_Comparator)
//		{
//			WRITE_BIT(SFIOR , 5 , HIGH);
//			WRITE_BIT(SFIOR , 6 , LOW);
//			WRITE_BIT(SFIOR , 7, LOW);
//		}
//		else if (ADC_autoTriggerSource == External_Interrupt_Request_0)
//		{
//			WRITE_BIT(SFIOR , 5 , LOW);
//			WRITE_BIT(SFIOR , 6 , HIGH);
//			WRITE_BIT(SFIOR , 7, LOW);
//		}
//		else if (ADC_autoTriggerSource == Timer_Counter0_Compare_Match)
//		{
//			WRITE_BIT(SFIOR , 5 , HIGH);
//			WRITE_BIT(SFIOR , 6 , HIGH);
//			WRITE_BIT(SFIOR , 7, LOW);
//		}
//		else if (ADC_autoTriggerSource == Timer_Counter0_Overflow)
//		{
//			WRITE_BIT(SFIOR , 5 , LOW);
//			WRITE_BIT(SFIOR , 6 , LOW);
//			WRITE_BIT(SFIOR , 7, HIGH);
//		}
//		else if (ADC_autoTriggerSource == Timer_Counter_Compare_Match_B)
//		{
//			WRITE_BIT(SFIOR , 5 , HIGH);
//			WRITE_BIT(SFIOR , 6 , LOW);
//			WRITE_BIT(SFIOR , 7, HIGH);
//		}
//		else if (ADC_autoTriggerSource == Timer_Counter1_Overflow)
//		{
//			WRITE_BIT(SFIOR , 5 , LOW);
//			WRITE_BIT(SFIOR , 6 , HIGH);
//			WRITE_BIT(SFIOR , 7, HIGH);
//		}
//		else if (ADC_autoTriggerSource == Timer_Counter1_Capture_Event)
//		{
//			WRITE_BIT(SFIOR , 5 , HIGH);
//			WRITE_BIT(SFIOR , 6 , HIGH);
//			WRITE_BIT(SFIOR , 7, HIGH);
//		}
//	}
//	WRITE_BIT(ADCSRA , 5 , HIGH); // enable autotrigger
//
//	#endif
//
//}
//void ADC_change_vref(ADC_referenceVoltageSelect_t ADC_referenceVoltageSelect){
//
//	/* select reference voltage */
//	if (ADC_referenceVoltageSelect ==VrefAt_AREF_Pin)
//	{
//		WRITE_BIT(ADMUX,REFS0 , LOW);
//		WRITE_BIT(ADMUX,REFS1, LOW);
//	}
//	else if (ADC_referenceVoltageSelect ==VrefAt_AVCC_pin_AREF_pin)
//	{
//		WRITE_BIT(ADMUX,REFS0 , HIGH);
//		WRITE_BIT(ADMUX,REFS1, LOW);
//	}
//	else
//	{
//		WRITE_BIT(ADMUX,REFS0 , HIGH);
//		WRITE_BIT(ADMUX,REFS1, HIGH);
//	}
//}
//void ADC_enable(){
//	WRITE_BIT(ADCSRA , 7,HIGH);//enable adc module
//}
//void ADC_disable(){
//	WRITE_BIT(ADCSRA , 7,LOW);//enable adc module
//}


void ADC_start_conversion()
{
	WRITE_BIT(ADCSRA , ADSC , HIGH); // start conversion
}
uint16 ADC_get_adcregister(){
	//ADC//10 8bit ADCL 2 bit ADCH
	return ( ( (uint8)ADCL) | (ADCH<<8) );
}
uint8 ADC_get_interrupt_flag()
{
	return GET_BIT(ADCSRA ,4);
}
uint16 ADC0_Read()
{
	ADC_Config_t LM35_object;
	LM35_object.select_ADC_channel  =   Single_Ended_Input_On_Channel_0_ADC0;
	LM35_object.select_ADC_prescaler=DivisionBy_8;
	LM35_object.select_AutoTrigger_source=Free_Running_Mode;
	LM35_object.select_reference_voltage=VrefAt_AVCC_pin_AREF_pin;
	ADC_init(&LM35_object);
	return ADC_read();
}
uint16  ADC1_Read()
{
	ADC_Config_t LM35_object;
	LM35_object.select_ADC_channel  =   Single_Ended_Input_On_Channel_1_ADC1;
	LM35_object.select_ADC_prescaler=DivisionBy_8;
	LM35_object.select_AutoTrigger_source=Free_Running_Mode;
	LM35_object.select_reference_voltage=VrefAt_AVCC_pin_AREF_pin;
	ADC_init(&LM35_object);
	return ADC_read();
}
uint16  ADC2_Read()
{
	ADC_Config_t LM35_object;
	LM35_object.select_ADC_channel  =   Single_Ended_Input_On_Channel_2_ADC2;
	LM35_object.select_ADC_prescaler=DivisionBy_8;
	LM35_object.select_AutoTrigger_source=Free_Running_Mode;
	LM35_object.select_reference_voltage=VrefAt_AVCC_pin_AREF_pin;
	ADC_init(&LM35_object);
	return ADC_read();

}
uint16  ADC3_Read()
{
	ADC_Config_t LM35_object;
	LM35_object.select_ADC_channel  =   Single_Ended_Input_On_Channel_3_ADC3;
	LM35_object.select_ADC_prescaler=DivisionBy_8;
	LM35_object.select_AutoTrigger_source=Free_Running_Mode;
	LM35_object.select_reference_voltage=VrefAt_AVCC_pin_AREF_pin;
	ADC_init(&LM35_object);
	return ADC_read();
}
uint16  ADC4_Read()
{
	ADC_Config_t LM35_object;
	LM35_object.select_ADC_channel  =   Single_Ended_Input_On_Channel_4_ADC4;
	LM35_object.select_ADC_prescaler=DivisionBy_8;
	LM35_object.select_AutoTrigger_source=Free_Running_Mode;
	LM35_object.select_reference_voltage=VrefAt_AVCC_pin_AREF_pin;
	ADC_init(&LM35_object);
	return ADC_read();
}
uint16  ADC5_Read()
{	ADC_Config_t LM35_object;
LM35_object.select_ADC_channel  =   Single_Ended_Input_On_Channel_5_ADC5;
LM35_object.select_ADC_prescaler=DivisionBy_8;
LM35_object.select_AutoTrigger_source=Free_Running_Mode;
LM35_object.select_reference_voltage=VrefAt_AVCC_pin_AREF_pin;
ADC_init(&LM35_object);
return ADC_read();
}

ISR(ADC_vect)
{
	if(*adcInterrupt!=NULL)
	adcInterrupt();
}
#endif
