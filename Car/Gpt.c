/*
 * Gpt.c
 *
 * Created: 10/9/2021 10:26:51 PM
 *  Author: Abdelaziz Moustafa
 */

#include "Gpt.h"
#include "ATmega32_Cfg.h"
#include "Macros.h"

void Gpt_Init(const Gpt_ConfigType *ConfigPtr)
{

	switch(ConfigPtr->GptNo)
	{
		case GPT_TIMER0:
		/* !Comment: Clear Registers before applying configuration */
		*TIMER0_CTRL_REG = 0x00U;
		/* !Comment: Apply configuration */
		switch(ConfigPtr->GptMode)
		{
			case GPT_NORMAL_MODE:
			*TIMER0_CTRL_REG |= GPT_NORMAL_MODE;
			*TIMER_INT_MASK_REG |= ConfigPtr->GptIntState;
			break;
			case GPT_CTC_MODE:
			*TIMER0_CTRL_REG |= GPT_CTC_MODE;
			*TIMER_INT_MASK_REG |= (ConfigPtr->GptIntState << TIMER0_CMP_MATCH_INT_ENABLE_BIT);
			*TIMER0_CMP_REG = (ConfigPtr->GptCmpValue - 1U);
			break;
			default:
			break;
		}
		*TIMER0_CTRL_REG |= ConfigPtr->GptClkDivision;
		*TIMER0_COUNTER_REG = 0x00U;
		break;
		case GPT_TIMER1:
		/* !Comment: Clear Registers before applying configuration */
		*TIMER1_CTRL_B_REG = 0x00U;
		*(uint16 *)TIMER1_COUNTER_LOW_REG = 0x00U;
		/* !Comment: Apply configuration */
		switch(ConfigPtr->GptMode)
		{
			case GPT_NORMAL_MODE:
			*TIMER1_CTRL_B_REG |= GPT_NORMAL_MODE;
			*TIMER_INT_MASK_REG |= (ConfigPtr->GptIntState << TIMER1_OVF_INT_ENABLE_BIT);
			break;
			case GPT_CTC_MODE:
			*TIMER1_CTRL_B_REG |= GPT_CTC_MODE;
			*TIMER_INT_MASK_REG |= (ConfigPtr->GptIntState << TIMER1_CMP_MATCH_A_INT_ENABLE_BIT);
			*(uint16 *)TIMER1_CMP_A_LOW_REG = (ConfigPtr->GptCmpValue -1U);
			break;
			default:
			break;
		}
		*TIMER1_CTRL_B_REG |= ConfigPtr->GptClkDivision;
		break;
		case GPT_TIMER2:
		break;
		default:
		break;
	}
}

Gpt_StatusType Gpt_StatusGet(Gpt_ChannelType Channel)
{
	Gpt_StatusType enuLocalGptStatus = GPT_STATUS_RUNNING;
	switch(Channel)
	{
		case GPT_TIMER0:
		switch(gaStrGpt_Configuration[GPT_TIMER0].GptMode)
		{
			case GPT_NORMAL_MODE:
			if (READ_BIT(*TIMER_INT_FLAG_REG, TIMER0_OVF_BIT))
			{
				enuLocalGptStatus = GPT_STATUS_OV_CMP;
				/* !Comment: Clear The TOV bit */
				SET_BIT(*TIMER_INT_FLAG_REG, TIMER0_OVF_BIT);
			}
			else
			{
				/* Do Nothing */
			}
			break;
			case GPT_CTC_MODE:
			if (READ_BIT(*TIMER_INT_FLAG_REG, TIMER0_CMP_MATCH_BIT))
			{
				enuLocalGptStatus = GPT_STATUS_OV_CMP;
				/* !Comment: Clear The OCF bit */
				SET_BIT(*TIMER_INT_FLAG_REG, TIMER0_CMP_MATCH_BIT);
			}
			else
			{
				/* Do Nothing */
			}
			break;
			default:
			break;
		}
		break;
		case GPT_TIMER1:
		switch(gaStrGpt_Configuration[GPT_TIMER1].GptMode)
		{
			case GPT_NORMAL_MODE:
			if (READ_BIT(*TIMER_INT_FLAG_REG, TIMER1_OVF_BIT))
			{
				enuLocalGptStatus = GPT_STATUS_OV_CMP;
				/* !Comment: Clear The TOV bit */
				SET_BIT(*TIMER_INT_FLAG_REG, TIMER1_OVF_BIT);
			}
			else
			{
				/* Do Nothing */
			}
			break;
			case GPT_CTC_MODE:
			if (READ_BIT(*TIMER_INT_FLAG_REG, TIMER1_CMP_MATCH_A_BIT))
			{
				enuLocalGptStatus = GPT_STATUS_OV_CMP;
				/* !Comment: Clear The TOV bit */
				SET_BIT(*TIMER_INT_FLAG_REG, TIMER1_CMP_MATCH_A_BIT);
			}
			else
			{
				/* Do Nothing */
			}
			break;
			default:
			break;
		}
		break;
		case GPT_TIMER2:
		break;
		default:
		break;
	}
	return (enuLocalGptStatus);
}
