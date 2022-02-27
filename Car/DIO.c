/*
 * Dio.c
 *
 * Created: 9/12/2021 7:09:28 PM
 *  Author: Abdelaziz Moustafa
 */

#include "Dio.h"
#include "Macros.h"
#include "Std_Types.h"
#include "ATmega32_Cfg.h"

void Dio_ChannelDirectionSet(volatile uint8 * Port_reg, DioPinEnum_t Channel, DioPinDirectionEnum_t Direction)
{

	switch(Direction)
	{
		case DIO_INPUT:
		CLEAR_BIT(*Port_reg,Channel);
		break;
		case DIO_OUTPUT:
		SET_BIT(*Port_reg,Channel);
		break;
		default:
		break;
	}
}

DioPinStateEnum_t Dio_ChannelRead(volatile uint8 * Port_reg, DioPinEnum_t Channel)
{
	DioPinStateEnum_t u8LocalPinValue = READ_BIT(*Port_reg,Channel);
	return (u8LocalPinValue);
}

void Dio_ChannelWrite(volatile uint8 * Port_reg, DioPinEnum_t Channel, DioPinStateEnum_t State)
{
	switch(State)
	{
		case DIO_LOW:
		CLEAR_BIT(*Port_reg,Channel);
		break;
		case DIO_HIGH:
		SET_BIT(*Port_reg,Channel);
		break;
		default:
		break;
	}
}
void Dio_ChannelToggle(volatile uint8 * Port_reg, DioPinEnum_t Channel)
{
	TOGGLE_BIT(*Port_reg,Channel);
}

void Dio_PortWrite(volatile uint8 * Port_reg, uint8 Value)
{
	*Port_reg = Value;
}

uint8 Dio_PortRead(volatile uint8 * Port_reg)
{
	uint8 u8LocalPortValue = *Port_reg;
	return u8LocalPortValue;
}
