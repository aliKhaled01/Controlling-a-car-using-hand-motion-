/*
 * Gpt_Lcfg.c
 *
 * Created: 10/9/2021 11:00:19 PM
 *  Author: Abdelaziz Moustafa
 */

#include "Gpt.h"

const Gpt_ConfigType gaStrGpt_Configuration[GPT_CHANNELS_NUM] =
{
	{
		GPT_TIMER0,
	    GPT_NORMAL_MODE,
		GPT_PRESCALE_256,
		GPT_INTERRUPT_ENABLE,
		0U  /* Not in CTC Mode */
	},
	{
		GPT_TIMER1,
		GPT_CTC_MODE,
		GPT_PRESCALE_1024,
		GPT_INTERRUPT_ENABLE,
		15625U  /* Not in CTC Mode */
	},
	{
		GPT_TIMER2,
		GPT_NORMAL_MODE,
		GPT_PRESCALE_256,
		GPT_INTERRUPT_ENABLE,
		0U  /* Not in CTC Mode */
	}
};
