/*
 * LCD.h
 *
 *  Created on: Oct 3, 2021
 *      Author: lenovo
 */#ifndef LCD_H_
#define LCD_H_
#include "STD_TYPES.h"
#define RS_PORT GPIO_A
#define RS_PIN GPIO_PIN3
#define EN_PORT GPIO_A
#define EN_PIN GPIO_PIN2
#define D4_PORT GPIO_B
#define D4_PIN GPIO_PIN0
#define D5_PORT GPIO_B
#define D5_PIN GPIO_PIN1
#define D6_PORT GPIO_B
#define D6_PIN GPIO_PIN2
#define D7_PORT GPIO_B
#define D7_PIN GPIO_PIN4
#define LCD_CLEAR_COMMND 0x01
#define SET_4BIT_MODE_COMMND 0x28
#define DISPLAY_ON_CURSOR_OFF_COMMND 0x0C
#define SET_CURSOR_TO_FROW_FCOL_COMMND 0X80
#define RETURN_HOME_COMMND 0X02
 typedef enum
 {
	 LINE1,LINE2,LINE3,LINE4
 }enLine;
 void LCD_Init();
 /*
  * Description: Set Rs as output
 	 	 	 	Set Enaable as output
 	 	 	 	Set datapins as outputs
 	 	 	 	Set cursor to (0,0)
 	 	 	 	Set the 4 bit mode
 	 	 	 	Display on cursor off
 	 	 	 	LCD clear

  *
  */

 //static void LCD_WriteCommnd(uint8 value);
 /*
  * Description : clear RS
 	 	 	 	 send the upper 4bit to {D4,D5,D6,D7}
 	 	 	 	 enable pulse
 	 	 	 	 then send the loweer 4bit to {D4,D5,D6,D7}
			     enable pulse


  */

 void LCD_Goto_xy(uint8 line,uint8 y);
 void LCD_WriteNumber(uint32 value);
 void LCD_WriteString(sint8* string);
 void LCD_Clear();
 void LCD_move_left_right_string(sint8* string,enLine starting_line);
 void LCD_StringRotate(sint8 * string);
 void LCD_DisplayCustomChar(uint8  CGRAM_LOCATION ,uint8 row, uint8 col);
 void LCD_storeCustomCharAtCgRam(uint8* pattern ,uint8 CGRAM_LOCATION);	//YOU HAVE 8 LOCATIONS TO WRITE IN
 void LCD_WriteData(uint8 value);



#endif

