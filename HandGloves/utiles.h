/*
 * utiles.h
 *
 *  Created on: Sep 25, 2021
 *      Author: le		novo
 */

//macros
#ifndef UTILES_H_
#define UTILES_H_
#define SET_BIT(REG,INDEX)	 (REG|=(1<<(INDEX)))
#define CLEAR_BIT(REG,INDEX) (REG&=~(1<<(INDEX)))
#define GET_BIT(REG,INDEX)	  ((REG>>INDEX)&0x01)
#define LED_PORT 				 PORTC
#define LED_DIR			   		DDRC
#define LED_PIN					6
#define NULLPTR 				((void*)0)
#define PIN_HIGH 1
#define PIN_LOW  0
#define TOGGLE_BIT(REG,INDEX) (REG ^= (1<<INDEX))
#define WRITE_BIT(REG,PIN,DATA)			(REG)=(REG&(~(1<<PIN)))|(DATA<<PIN)

#endif /* UTILES_H_ */
