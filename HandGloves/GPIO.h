/*
 * GPIO.h
 *
 *  Created on: Sep 25, 2021
 *      Author: lenovo
 */

#ifndef GPIO_H_
#define GPIO_H_
#include "STD_TYPES.h"
#include "MCAL_REGISTERS/MEM_Map32.h"
#include "utiles.h"
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_PIN0   0
#define GPIO_PIN1   1
#define GPIO_PIN2   2
#define GPIO_PIN3   3
#define GPIO_PIN4   4
#define GPIO_PIN5   5
#define GPIO_PIN6   6
#define GPIO_PIN7   7
#define GPIO_INPUT  0
#define GPIO_OUTPUT 1
#define GPIO_LOW      0
#define GPIO_HIGH     1
#define ERORR_FAIL    0
#define ERORR_SUCCESS 1

uint8 GPIO_InitPin(uint8 port,uint8 pin,uint8 direction);
/*
 * Name : void GPIO_InistPin(port,pin,direction)
 * input:
 *     	port: GPIO_D,GPIO_C,GPIO_B,GPIO_A
 *     	pin : PIN{0..7}
 *     	direction:GPIO_OUTPUT, GPIO_INPUT
 *Output:ERORR_FAIL   0
 *Output:ERORR_SUCESS 1
 *Description:
 *            GPIO_InitPin OutputPin
 *            GPIO_InitPin InputPin
 * log : v1 Released
 * log : v2 Fixed Bug
 * log : v2 Released
 */
uint8 GPIO_WritePin(uint8 port,uint8 pin,uint8 value);
/*
 * Name : voidGPIO_WritePin(port,pin,value)
 * input:
 *     	port: GPIO_D,GPIO_C,GPIO_B,GPIO_A
 *     	pin : PIN{0..7}
 *     	value:GPIO_HIGH, GPIO_LOW
 *Output:ERORR_FAIL   0
 *Output:ERORR_SUCESS 1
 *Description:
 *            GPIO_WritePin High
 *            GPIO_WritePin Low
 * log : v1 Released
 * log : v2 Fixed Bug
 * log : v2 Released
 */
uint8 GPIO_GetPin(uint8 port,uint8 pin,uint8 *val);
/*
 * Name : void GPIO_GetPin(port,pin,*val)
 * input:
 *     	port: GPIO_D,GPIO_C,GPIO_B,GPIO_A
 *     	pin : PIN{0..7}
 *     	*val:Address
 *     	            :StorePinValue
 *Output:ERORR_FAIL   0
 *Output:ERORR_SUCESS 1
 *Description:
 *            GPIO_GetPin High
 *            GPIO_GetPin Low
 * log : v1 Released
 * log : v2 Fixed Bug
 * log : v2 Released
 */

//val is return value
// function return return erorr state
//or put both in struct

void GPIO_TogglePin(uint8 port,uint8 pin);

#endif /* GPIO_H_ */
