/*
 * GPIO.c
 *
 *  Created on: Sep 25, 2021
 *      Author: lenovo
 */


#include "GPIO.h"
uint8 GPIO_InitPin(uint8 port,uint8 pin,uint8 direction)
{
	uint8 ret;
	switch(port)
	{
	if(port>GPIO_D||pin>GPIO_PIN7||direction>GPIO_OUTPUT)
	{
		ret = ERORR_FAIL;
	}
	else
	{
		ret = ERORR_SUCCESS;
	case  GPIO_A:
		if(direction==GPIO_OUTPUT)
		{
			SET_BIT(DDRA,pin);
		}

		else
		{
			CLEAR_BIT(DDRA,pin);
		}
		break;

	case GPIO_B:
		if(direction==GPIO_OUTPUT)
		{
			SET_BIT(DDRB,pin);
		}
		else
		{

			CLEAR_BIT(DDRB,pin);
		}
		break;

	case GPIO_C :
		if(direction==GPIO_OUTPUT)
		{
			SET_BIT(DDRC,pin);
		}
		else
		{
			CLEAR_BIT(DDRC,pin);
		}
		break;

	case GPIO_D:
		if(direction==GPIO_OUTPUT)
		{
			SET_BIT(DDRD,pin);
		}
		else
		{
			CLEAR_BIT(DDRD,pin);
		}
		break;

	}

	}
	return ret ;
}




uint8 GPIO_WritePin(uint8 port,uint8 pin,uint8 value) // @suppress("No return")
{
	uint8 ret;
	switch(port)
	{

	if(port>3||pin>7||value>1)
	{
		ret= ERORR_FAIL;
	}
	else
	{
		ret = ERORR_SUCCESS;
	case GPIO_A :
		if(value==GPIO_HIGH)
		{
			SET_BIT(PORTA,pin);
		}
		else
		{
			CLEAR_BIT(PORTA,pin);
		}
		break;

	case GPIO_B :
		if(value==GPIO_HIGH)
		{
			SET_BIT(PORTB,pin);
		}
		else
		{
			CLEAR_BIT(PORTB,pin);
		}
		break;
	case GPIO_C:
		if(value==GPIO_HIGH)
		{
			SET_BIT(PORTC,pin);
		}
		else
		{
			CLEAR_BIT(PORTC,pin);
		}
		break;
	case GPIO_D:
		if(value==GPIO_HIGH)
		{
			SET_BIT(PORTD,pin);
		}
		else
		{
			CLEAR_BIT(PORTD,pin);
		}
		break;
	}
	}
	return ret;
}



uint8 GPIO_GetPin(uint8 port,uint8 pin,uint8 *val)
{
	uint8 ret;
	if(port>3||pin>7)
	{
		ret = ERORR_FAIL;
	}
	else
	{
		ret = ERORR_SUCCESS;
		switch(port)
		{

		case GPIO_A:
			*val = GET_BIT(PINA,pin);
			break;

		case GPIO_B:
			*val = GET_BIT(PINB,pin);
			break;

		case GPIO_C:
			*val = GET_BIT(PINC,pin);
			break;

		case GPIO_D:
			*val = GET_BIT(PIND,pin);
			break;
		}
	}

	return ret;

}
void GPIO_TogglePin(uint8 port,uint8 pin)
{
	switch(port)
	{

	case GPIO_A:
		TOGGLE_BIT(PORTA,pin);
		break;

	case GPIO_B:
		TOGGLE_BIT(PORTB,pin);
		break;

	case GPIO_C:
		TOGGLE_BIT(PORTC,pin);
		break;

	case GPIO_D:
		TOGGLE_BIT(PORTD,pin);
		break;
	}
}


