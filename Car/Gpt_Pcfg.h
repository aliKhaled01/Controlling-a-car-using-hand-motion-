/*
 * Gpt_Pcfg.h
 *
 * Created: 10/11/2021 8:44:02 PM
 *  Author: Abdelaziz Moustafa
 */


#ifndef GPT_PCFG_H_
#define GPT_PCFG_H_

#define GPT_CHANNELS_NUM                    (3U)

#define TIMER0_OVF_BIT						(0U)
#define TIMER0_CMP_MATCH_BIT				(1U)

#define TIMER0_OVF_INT_ENABLE_BIT			(0U)
#define TIMER0_CMP_MATCH_INT_ENABLE_BIT		(1U)

#define TIMER1_OVF_BIT						(2U)
#define TIMER1_CMP_MATCH_A_BIT				(4U)
#define TIMER1_CMP_MATCH_B_BIT				(3U)

#define TIMER1_OVF_INT_ENABLE_BIT			(2U)
#define TIMER1_CMP_MATCH_A_INT_ENABLE_BIT	(4U)
#define TIMER1_CMP_MATCH_B_INT_ENABLE_BIT	(3U)

#endif /* GPT_PCFG_H_ */
