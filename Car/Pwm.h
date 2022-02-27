/*
 * Pwm.h
 *
 * Created: 10/14/2021 11:25:30 PM
 *  Author: Abdelaziz Moustafa
 */


#ifndef PWM_H_
#define PWM_H_

#include "Std_Types.h"
#include "Pwm_Pcfg.h"

typedef uint16 Pwm_PeriodType;

typedef enum
{
	PWM_CHANNEL_0,
	PWM_CHANNEL_1,
	PWM_CHANNEL_2
}Pwm_ChannelType;

typedef enum
{
	PWM_MODE_FAST              = 0x48U,
	PWM_MODE_PHASE_CORRECT	   = 0x40U
}Pwm_ModeType;

typedef enum
{
	PWM_HIGH                  = 0x30,    /* Inverted PWM */
	PWM_LOW	                  = 0x20    /* Non-Inverted PWM */
}Pwm_OutputStateType;

typedef enum
{
	PWM_NO_CLK_SOURCE,
	PWM_NO_PRESCALE,
	PWM_PRESCALE_8,
	PWM_PRESCALE_64,
	PWM_PRESCALE_256,
	PWM_PRESCALE_1024,
	PWM_EXT_CLK_T0_FALLING,
	PWM_EXT_CLK_T0_RISING
}PWM_PrescaleType;

typedef struct
{
	Pwm_ChannelType PwmCh;
	Pwm_ModeType PwmMode;
	Pwm_OutputStateType PwmPolarity;
	PWM_PrescaleType PwmClkDiv;
	Pwm_PeriodType PwmPeriod;
	uint16 PrescaleValue;
	uint16 PwmDuty;
}Pwm_ConfigType;

void Pwm_Init(const Pwm_ConfigType *ConfiPWMr);
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
void Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle);

extern Pwm_ConfigType gStrPwm_Configuration[PWM_CHANNELS_NUM];

#endif /* PWM_H_ */
