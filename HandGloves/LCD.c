/*
 * LCD.c
 *
 *  Created on: Oct 3, 2021
 *      Author: lenovo
 */
#include "LCD.h"
#include <util/delay.h>
#include "GPIO.h"
#include "utiles.h"
#include "STD_TYPES.h"

static void LCD_WriteCommnd(uint8 value)
{
	GPIO_WritePin(RS_PORT,RS_PIN,GPIO_LOW);
	GPIO_WritePin(D4_PORT,D4_PIN,GET_BIT(value,4));
	GPIO_WritePin(D5_PORT,D5_PIN,GET_BIT(value,5));
	GPIO_WritePin(D6_PORT,D6_PIN,GET_BIT(value,6));
	GPIO_WritePin(D7_PORT,D7_PIN,GET_BIT(value,7));
	GPIO_WritePin(EN_PORT,EN_PIN,GPIO_HIGH);
	_delay_ms(2);
	GPIO_WritePin(EN_PORT,EN_PIN,GPIO_LOW);
	_delay_ms(2);
	GPIO_WritePin(D4_PORT,D4_PIN,GET_BIT(value,0));
	GPIO_WritePin(D5_PORT,D5_PIN,GET_BIT(value,1));
	GPIO_WritePin(D6_PORT,D6_PIN,GET_BIT(value,2));
	GPIO_WritePin(D7_PORT,D7_PIN,GET_BIT(value,3));
	GPIO_WritePin(EN_PORT,EN_PIN,GPIO_HIGH);
	_delay_ms(2);
	GPIO_WritePin(EN_PORT,EN_PIN,GPIO_LOW);
	_delay_ms(2);

	_delay_ms(10);

}

void LCD_Init()
{
	GPIO_InitPin(RS_PORT,RS_PIN,GPIO_OUTPUT);
	GPIO_InitPin(EN_PORT,EN_PIN,GPIO_OUTPUT);
	GPIO_InitPin(D4_PORT,D4_PIN,GPIO_OUTPUT);
	GPIO_InitPin(D5_PORT,D5_PIN,GPIO_OUTPUT);
	GPIO_InitPin(D6_PORT,D6_PIN,GPIO_OUTPUT);
	GPIO_InitPin(D7_PORT,D7_PIN,GPIO_OUTPUT);
	_delay_ms(50);
	LCD_WriteCommnd(0x02);//4 bit mode only
	_delay_ms(1);
	LCD_WriteCommnd(0x28); //N=1 , F=0
	_delay_ms(1);           //delay 1ms a must delay as said in Data sheet
	LCD_WriteCommnd(0x0c); //D=1(LCD itself on or off) C=0, B=0
	_delay_ms(1);    //delay 1ms
	LCD_WriteCommnd(0x01); //clear LCD
	_delay_ms(20);
	LCD_WriteCommnd(0x06);
	LCD_WriteCommnd(0x80);
}


void LCD_WriteData(uint8 value)
{
	GPIO_WritePin(RS_PORT,RS_PIN,GPIO_HIGH);
	GPIO_WritePin(D4_PORT,D4_PIN,GET_BIT(value,4));
	GPIO_WritePin(D5_PORT,D5_PIN,GET_BIT(value,5));
	GPIO_WritePin(D6_PORT,D6_PIN,GET_BIT(value,6));
	GPIO_WritePin(D7_PORT,D7_PIN,GET_BIT(value,7));
	GPIO_WritePin(EN_PORT,EN_PIN,GPIO_HIGH);
	_delay_ms(2);
	GPIO_WritePin(EN_PORT,EN_PIN,GPIO_LOW);
	_delay_ms(2);
	GPIO_WritePin(D4_PORT,D4_PIN,GET_BIT(value,0));
	GPIO_WritePin(D5_PORT,D5_PIN,GET_BIT(value,1));
	GPIO_WritePin(D6_PORT,D6_PIN,GET_BIT(value,2));
	GPIO_WritePin(D7_PORT,D7_PIN,GET_BIT(value,3));
	GPIO_WritePin(EN_PORT,EN_PIN,GPIO_HIGH);
	_delay_ms(2);
	GPIO_WritePin(EN_PORT,EN_PIN,GPIO_LOW);
	_delay_ms(2);



}


void LCD_Clear()
{
	LCD_WriteCommnd(LCD_CLEAR_COMMND);

}
void LCD_WriteString(sint8* string)
{
	uint8 i=0;
	while(string[i]!='\0')
	{
		LCD_WriteData(string[i]);
		i++;
	}

}
void LCD_WriteNumber(uint32 value)  //123....> "123" then write in the screen
{
	if(value==0)
	{
		LCD_WriteData((uint8)48);
	}
	else
	{
		uint32 value2 = value;
		uint32  rev_no=0;
		while(value!=0)
		{
			rev_no=rev_no*10+value%10;
			value/=10;
		}
		while(rev_no!=0)
		{

			LCD_WriteData((uint8)((rev_no%10)+48));
			rev_no/=10;
		}
		while((value2)%10==0)
		{
			LCD_WriteData((uint8)48);
			(value2)/=10;
		}
	}
}
//static  void String_To_Number(sint8* string)  // "123" ...> 123


void LCD_Goto_xy(uint8 line,uint8 y)
{
	if(0==line&&y<20)
	{
		LCD_WriteCommnd(0x80+y);

	}
	else if(1==line&&y<20)
	{
		LCD_WriteCommnd(0xC0+y);
	}

	else if(2==line&&y<20)
	{
		LCD_WriteCommnd(0x94+y);
	}
	else if(3==line&&y<20)
	{
		LCD_WriteCommnd(0xD4+y);
	}


}
void LCD_move_left_right_string(sint8* string,enLine starting_line)

{
	uint8 string_length = strlen(string);
	for(uint8 first_char_position =0; first_char_position<=(20-string_length); first_char_position++ )
	{
		LCD_Goto_xy(starting_line,first_char_position);
		LCD_WriteString(string);
		_delay_ms(500);
		if(first_char_position <(20-string_length))
		{
			LCD_Goto_xy(starting_line,first_char_position);
			LCD_WriteString(" ");
		}
		else if(first_char_position==(20-string_length))
		{

			for(uint8 i=(20-string_length);i<20;i++)
			{
				LCD_Goto_xy(starting_line,i);
				LCD_WriteString(" ");

			}
		}

	}
	for(uint8 first_char_position =(20-string_length)-1;first_char_position>0;first_char_position--)
	{
		LCD_Goto_xy(starting_line,first_char_position);
		LCD_WriteString(string);
		_delay_ms(500);

		if(first_char_position >0)
		{
			LCD_Goto_xy(starting_line,first_char_position+(strlen(string)-1));

			LCD_WriteString(" ");
		}
		else if(first_char_position==1)
		{


			for(uint8 delete_string_after_reaching_to_last_col=1; delete_string_after_reaching_to_last_col<string_length;delete_string_after_reaching_to_last_col++)
			{
				LCD_Goto_xy(starting_line, delete_string_after_reaching_to_last_col);
				LCD_WriteString(" ");
			}
		}
	}

}
void LCD_StringRotate(sint8 * string)
{
	uint8 string_length = strlen(string);
	for(uint8 first_char_position =0; first_char_position<=(20-string_length); first_char_position++ )
	{
		LCD_Goto_xy(LINE1,first_char_position);
		LCD_WriteString(string);
		_delay_ms(500);
		if(first_char_position <(20-string_length))
		{
			LCD_Goto_xy(LINE1,first_char_position);
			LCD_WriteString(" ");
		}
		else if(first_char_position==(20-string_length))
		{

			for(uint8 i=(20-string_length);i<20;i++)
			{
				LCD_Goto_xy(LINE1,i);
				LCD_WriteString(" ");

			}

		}

	}
	for(uint8 line=LINE2;line<=LINE4;line++)
	{
		LCD_Goto_xy(line,20-string_length);
		LCD_WriteString(string);
		_delay_ms(500);
		for(uint8 col=20-string_length;col<20;col++)
		{
			LCD_Goto_xy(line,col);
			LCD_WriteString(" ");
		}

	}

	for(sint8 col=(20-string_length)-1; col>=0; col--)
	{
		LCD_Goto_xy(LINE4,col);
		LCD_WriteString(string);
		_delay_ms(500);
		if(col>0)
		{
			LCD_Goto_xy(LINE4,col+string_length-1);
			LCD_WriteString(" ");
		}
		else if(col==0)
		{

			for(uint8 line4_col=0;line4_col<string_length;line4_col++)
			{
				LCD_Goto_xy(LINE4,line4_col);
				LCD_WriteString(" ");
			}

		}
	}
	for(sint8 line=LINE3;line>LINE1;line--)
	{
		LCD_Goto_xy(line,0);
		LCD_WriteString(string);
		_delay_ms(500);
		for(uint8 col=0;col<string_length;col++)
		{
			LCD_Goto_xy(line,col);
			LCD_WriteString(" ");
		}

	}

}
void LCD_storeCustomCharAtCgRam(uint8* pattern ,uint8 CGRAM_LOCATION)	//YOU HAVE 8 LOCATIONS TO WRITE IN
{
	uint8 address;
	uint8 index;
	if( CGRAM_LOCATION<8)
	{
		address = CGRAM_LOCATION*8;
		address =SET_BIT(address,6);
		LCD_WriteCommnd(address);
		for(index =0 ;index<8;index++)
		{
			LCD_WriteData(pattern[index]);
		}
	}
	LCD_WriteCommnd(RETURN_HOME_COMMND);
}
void LCD_DisplayCustomChar(uint8  CGRAM_LOCATION ,uint8 row, uint8 col)

{
	LCD_Goto_xy(row,col);
	LCD_WriteData(CGRAM_LOCATION);
}

