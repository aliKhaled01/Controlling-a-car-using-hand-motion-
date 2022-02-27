/*
 * LCD_Cfg.h
 *
 * Created: 9/23/2021 10:29:58 PM
 *  Author: Abdelaziz Moustafa
 */


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "ATmega32_Cfg.h"

/* Hardware Connections */
#define LCD_RS					(DIO_PIN1)
#define LCD_RW					(DIO_PIN2)
#define LCD_EN					(DIO_PIN3)

#define LCD_CTRL_DIR_REG        (PORTB_DIR_REG)
#define LCD_CTRL_OUT_REG        (PORTB_OUT_REG)

#define LCD_DATA_DIR_REG        (PORTA_DIR_REG)
#define LCD_DATA_OUT_REG        (PORTA_OUT_REG)

/* Initiation Settings */
#define LCD_CURSOR                  (0U)           /* 1 to Enable , 0 to Disable */
#define LCD_BLINK                   (0U)           /* 1 to Enable , 0 to Disable */
#define LCD_EIGHTBIT_DATA           (0U)           /* 1 to Enable , 0 for 4-bit  */
#define LCD_5X10_DOT                (0U)           /* 1 to Enable , 0 for 5 x 8 Dot */
#define LCD_TWO_FOUR_LINES          (1U)           /* 1 to Enable 2(in case of 16x2) or 4 lines(in case of 16x4)  , 0 for 1(in case of 16x2) or 2 Line(in case of 16x4) */

#define LCD_SHIFT_LEFT              (1U)
#define LCD_SHIFT_RIGHT             (0U)

/* Generating an error if the user selected to work with two/four line and 5x10 dot.*/
#if ( LCD_5X10_DOT && LCD_TWO_FOUR_LINES )
#pragma GCC error "You cannot Have Two/four Lines LCD with 5 * 10"
#endif

#endif /* LCD_CFG_H_ */
