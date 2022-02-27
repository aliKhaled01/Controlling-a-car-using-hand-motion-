/*
 * LCD.h
 *
 * Created: 9/23/2021 10:29:33 PM
 *  Author: Abdelaziz Moustafa
 */


#ifndef LCD_H_
#define LCD_H_

#include "LCD_Cfg.h"

/* List of command codes  */
#define LCD_CLEAR_DISPLAY			(0x01U)
#define LCD_RETURN_HOME				(0x02U)
#define LCD_DISPLAY_OFF				(0x08U)
#define LCD_DISPLAY_ON              (0x0CU |(LCD_CURSOR << 1u) | (LCD_BLINK))
#define LCD_CURSOR_SHIFT_RIGHT      (0x14U)
#define LCD_CURSOR_SHIFT_LEFT       (0x10U)
#define LCD_DISPLAY_SHIFT_RIGHT     (0x1CU)
#define LCD_DISPLAY_SHIFT_LEFT      (0x18U)
#define LCD_FUNCTION_SET			(0x20U |(LCD_5X10_DOT << 2) | (LCD_TWO_FOUR_LINES << 3U) | (LCD_EIGHTBIT_DATA << 4U))
#define LCD_DDRAM_CONST             (0x80U)

#define LCD_1ST_LINE_BASE           (0x00U)
#define LCD_2ND_LINE_BASE           (0x40U)
#define LCD_3RD_LINE_BASE           (0x10U)
#define LCD_4TH_LINE_BASE           (0x50U)

#define LCD_SHIFT(DIR)	       ((DIR == LCD_SHIFT_LEFT)? LCD_Send_Instruction(LCD_DISPLAY_SHIFT_LEFT) : LCD_Send_Instruction(LCD_DISPLAY_SHIFT_RIGHT))
#define LCD_CURSOR_SHIFT(DIR)  ((DIR == LCD_SHIFT_LEFT)? LCD_Send_Instruction(LCD_CURSOR_SHIFT_LEFT)  : LCD_Send_Instruction(LCD_CURSOR_SHIFT_RIGHT))

/* List of LCD APIs */
void LCD_Init(void);
void LCD_Send_Instruction(uint8 Instruction);
void LCD_Clear(void);
void LCD_RowCol_Select(uint8 Row, uint8 Col);
void LCD_CharDisplay(uint8 Data);
void LCD_StringDisplay(char *Str);
void LCD_IntegerDisplay(sint32 Data);

#endif /* LCD_H_ */
