/*
 * Pwm.c
 *
 * Created: 10/14/2021 11:26:28 PM
 *  Author: Abdelaziz Moustafa
 */

#include "Pwm.h"
#include "ATmega32_Cfg.h"
#include "Macros.h"

uint16 gu16TimerTopValue = 0U;

void Pwm_Init(const Pwm_ConfigType *ConfigPtr)
{
	switch(ConfigPtr->PwmCh)
	{
		case PWM_CHANNEL_0:
		/* !Comment: Clear Registers before applying configuration */
		*TIMER0_CTRL_REG = 0x00U;
		*TIMER0_COUNTER_REG = 0x00U;
		/* !Comment: Apply configuration */
		*TIMER0_CTRL_REG |= ConfigPtr->PwmClkDiv | ConfigPtr->PwmMode | ConfigPtr->PwmPolarity;
		switch(ConfigPtr->PwmPolarity)
		{
			case PWM_HIGH:
			*TIMER0_CMP_REG = (uint8) (((100U - ConfigPtr->PwmDuty) / 100U) * PWM0_RESOLUTION);
			break;
			case PWM_LOW:
			*TIMER0_CMP_REG = (uint8) ((ConfigPtr->PwmDuty / 100U) * PWM0_RESOLUTION);
			break;
			default:
			break;
		}
		break;
		case PWM_CHANNEL_1:
		/* !Comment: Clear Registers before applying configuration */
		*TIMER1_CTRL_A_REG = 0x00U;
		*TIMER1_CTRL_B_REG = 0x00U;
		*(uint16 *)TIMER1_COUNTER_LOW_REG = 0x00U;
		/* !Comment: Apply configuration */
		switch(ConfigPtr->PwmMode)
		{
			case PWM_MODE_FAST:
			CLEAR_BIT(*TIMER1_CTRL_A_REG, 0U);
			SET_BIT(*TIMER1_CTRL_A_REG, 1U);
			SET_BIT(*TIMER1_CTRL_B_REG, 3U);
			SET_BIT(*TIMER1_CTRL_B_REG, 4U);
			break;
			case PWM_MODE_PHASE_CORRECT:
			SET_BIT(*TIMER1_CTRL_A_REG, 0U);
			SET_BIT(*TIMER1_CTRL_A_REG, 1U);
			CLEAR_BIT(*TIMER1_CTRL_B_REG, 3U);
			SET_BIT(*TIMER1_CTRL_B_REG, 4U);
			break;
			default:
			break;
		}
		/* !Comment: Set TOP ticks in ICR1 Register */
		gu16TimerTopValue = (uint16)(F_CPU / (ConfigPtr->PrescaleValue * (1000.0 / ConfigPtr->PwmPeriod))) - 1U;
		*(uint16*)TIMER1_INP_CAP_LOW_REG = (uint16)gu16TimerTopValue;

		switch(ConfigPtr->PwmPolarity)
		{
			case PWM_HIGH:
			SET_BIT(*TIMER1_CTRL_A_REG, 6U);
			SET_BIT(*TIMER1_CTRL_A_REG, 7U);
			*(uint16 *)TIMER1_CMP_A_LOW_REG = (uint16) (((100U - ConfigPtr->PwmDuty) / 100.0) * gu16TimerTopValue);
			break;
			case PWM_LOW:
			CLEAR_BIT(*TIMER1_CTRL_A_REG, 6U);
			SET_BIT(*TIMER1_CTRL_A_REG, 7U);
			*(uint16 *)TIMER1_CMP_A_LOW_REG = (uint16) ((ConfigPtr->PwmDuty / 100.0) * gu16TimerTopValue);
			break;
			default:
			break;
		}
		*TIMER1_CTRL_B_REG |= ConfigPtr->PwmClkDiv;
		break;
		case PWM_CHANNEL_2:
		break;
		default:
		break;
	}
}
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
	switch(ChannelNumber)
	{
		case PWM_CHANNEL_0:
		switch(gStrPwm_Configuration->PwmPolarity)
		{
			case PWM_HIGH:
			*TIMER0_CMP_REG = (uint8) (((100U - DutyCycle) / 100U) * PWM0_RESOLUTION);
			break;
			case PWM_LOW:
			*TIMER0_CMP_REG = (uint8) ((DutyCycle / 100U) * PWM0_RESOLUTION);
			break;
			default:
			break;
		}
		break;
		case PWM_CHANNEL_1:
		switch(gStrPwm_Configuration->PwmPolarity)
		{
			case PWM_HIGH:
			*(uint16 *)TIMER1_CMP_A_LOW_REG = (uint16) (((100U - DutyCycle) / 100.0) * gu16TimerTopValue);
			break;
			case PWM_LOW:
			*(uint16 *)TIMER1_CMP_A_LOW_REG = (uint16) ((DutyCycle / 100.0) * gu16TimerTopValue);
			break;
			default:
			break;
		}
		break;
		case PWM_CHANNEL_2:
		break;
		default:
		break;
	}
}
