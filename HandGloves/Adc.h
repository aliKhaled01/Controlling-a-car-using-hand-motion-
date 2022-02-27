/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v02
*Brief: ADC peripheral
*******************************************************/

#ifndef ADC_H_
#define ADC_H_
#include "STD_TYPES.h"
#include "MCAL_REGISTERS/Mem_Map32.h"


/*uncomment the next line to enable differential GPIO_INPUT*/
//#define ENABLE_ADC_DIFFERENTIAL_INPUT

/*Uncomment the next line to Enable Auto trigger sources*/
#define ENABLE_AUTO_TRIGGER_SOURCE
/************************* configuration parameters *********************************************/
typedef enum voltageReference{
	VrefAt_AREF_Pin = 0 ,
	VrefAt_AVCC_pin_AREF_pin,
	VrefAt_Internal_2560mV
}ADC_referenceVoltageSelect_t;

typedef enum channel{
	Single_Ended_Input_On_Channel_0_ADC0 = 0 ,
	Single_Ended_Input_On_Channel_1_ADC1 ,
	Single_Ended_Input_On_Channel_2_ADC2 ,
	Single_Ended_Input_On_Channel_3_ADC3 ,
	Single_Ended_Input_On_Channel_4_ADC4 ,
	Single_Ended_Input_On_Channel_5_ADC5 ,
	Single_Ended_Input_On_Channel_6_ADC6 ,
	Single_Ended_Input_On_Channel_7_ADC7 ,


	DifferentialWithGain_10x_PositiveInputOn_ADC1_NegativeInputOn_ADC0  ,
	DifferentialWithGain_200x_PositiveInputOn_ADC1_NegativeInputOn_ADC0 ,
	DifferentialWithGain_10x_PositiveInputOn_ADC3_NegativeInputOn_ADC2  ,
	DifferentialWithGain_200x_PositiveInputOn_ADC3_NegativeInputOn_ADC2 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC2_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC3_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC6_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC7_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC2 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC1_NegativeInputOn_ADC2 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC3_NegativeInputOn_ADC2 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC2 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC2

}ADC_channelSelect_t;

typedef enum prescaler{
	DivisionBy_2 = 0 ,
	DivisionBy_2_ = 1 ,
	DivisionBy_4 ,
	DivisionBy_8 ,
	DivisionBy_16 ,
	DivisionBy_32 ,
	DivisionBy_64 ,
	DivisionBy_128,
}ADC_Prescaler_t;

typedef enum autotrigger{
	AutoTriggerIS_Disabled = 0    ,
	Free_Running_Mode             ,
	Analog_Comparator             ,
	External_Interrupt_Request_0  ,
	Timer_Counter0_Compare_Match  ,
	Timer_Counter0_Overflow       ,
	Timer_Counter_Compare_Match_B ,
	Timer_Counter1_Overflow       ,
	Timer_Counter1_Capture_Event
}ADC_autoTriggerSource_t;
/************************* configuration struct *********************************************/
typedef struct adcConfig{
	ADC_referenceVoltageSelect_t select_reference_voltage ;
	ADC_channelSelect_t select_ADC_channel ;
	ADC_Prescaler_t select_ADC_prescaler ;
	ADC_autoTriggerSource_t select_AutoTrigger_source ;

}ADC_Config_t;

/************************* prototypes *********************************************/
void ADC_init(ADC_Config_t *obj);
uint16 ADC_read( );

void ADC_change_prescalar(ADC_Prescaler_t ADC_prescaler);
void ADC_change_channel(ADC_channelSelect_t ADC_channelSelect);
void ADC_change_triggersource(ADC_autoTriggerSource_t ADC_autoTriggerSource);
void ADC_change_vref(ADC_referenceVoltageSelect_t ADC_referenceVoltageSelect);

void ADC_enable();
void ADC_disable();
void ADC_start_conversion();

uint16 ADC_get_adcregister();
uint8 ADC_get_interrupt_flag();
void ADC_init_interrupt( void(*adcInterruptFunctionPtr)(void) );


#endif /* ADC_H_ */
