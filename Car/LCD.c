/*
 * LCD.c
 *
 * Created: 9/23/2021 11:30:25 PM
 *  Author: Abdelaziz Moustafa
 */

#include "LCD.h"
#include "Dio.h"
#include <stdlib.h>
#include <util/delay.h>


void LCD_Init(void)
{
	/* !Comment: Wait for more than 15 ms after VCC rises to 4.5V   */
	_delay_ms(20U);
	/* !Comment: Set The Control Pins Direction to OUTPUT   */
	Dio_ChannelDirectionSet(LCD_CTRL_DIR_REG, LCD_RS, DIO_OUTPUT);
	Dio_ChannelDirectionSet(LCD_CTRL_DIR_REG, LCD_RW, DIO_OUTPUT);
	Dio_ChannelDirectionSet(LCD_CTRL_DIR_REG, LCD_EN, DIO_OUTPUT);
#if LCD_EIGHTBIT_DATA
	/* !Comment: Set the Direction of the 8 Data pins to OUTPUT   */
	*LCD_DATA_DIR_REG = 0xFFU;
#else
	/* !Comment: Set the Direction of the Upper 4 Data pins to OUTPUT   */
	*LCD_DATA_DIR_REG |= (0xF0U);
	LCD_Send_Instruction(LCD_RETURN_HOME);
#endif
	/* !Comment: Set the initial configurations you made in the config file  */
	LCD_Send_Instruction(LCD_FUNCTION_SET);
	LCD_Send_Instruction(LCD_DISPLAY_ON);
	LCD_Send_Instruction(LCD_CLEAR_DISPLAY);
}

void LCD_Send_Instruction(uint8 Instruction)
{
	/* !Comment: RW, RS Should be 0 when Writing instructions to LCD  */
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_RS, DIO_LOW);
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_RW, DIO_LOW);
	/* !Comment: Delay of Address Set 60ns minimum */
	_delay_ms(1);
	/* !Comment: Enable LCD E=1 */
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_EN, DIO_HIGH);
	/* !Comment: Delay for processing PW min 450ns */
	_delay_ms(1);
#if LCD_EIGHTBIT_DATA
	Dio_PortWrite(LCD_DATA_OUT_REG, Instruction);
	/* !Comment: Data set-up time delay  Tdsw = 195 ns */
	_delay_ms(1);
	/* !Comment: Disable LCD E=0 */
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_EN, DIO_LOW);
	/* !Comment: Data Hold delay Th = 10ns */
	_delay_ms(1);
#else
	/* !Comment: Clear the Previous Data */
	*LCD_DATA_OUT_REG &= 0x0FU;
	*LCD_DATA_OUT_REG |= (Instruction & 0xF0U);
	/* !Comment: Data set-up time delay  Tdsw = 195 ns */
	_delay_ms(1);
	/* !Comment: Disable LCD E=0 */
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_EN, DIO_LOW);
	/* !Comment: Data Hold delay Th = 10ns */
	_delay_ms(1);

	/* !Comment: Enable LCD E=1  (To write the other 4-bit of the instruction)*/
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_EN, DIO_HIGH);
	/* !Comment: Delay for processing PW min 450ns */
	_delay_ms(1);
	/* !Comment: Clear the Previous Data */
	*LCD_DATA_OUT_REG &= 0x0FU;
	*LCD_DATA_OUT_REG |= ((Instruction<<4) & 0xF0U);
	/* !Comment: Data set-up time delay  Tdsw = 195 ns */
	_delay_ms(1);
	/* !Comment: Disable LCD E=0 */
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_EN, DIO_LOW);
	/* !Comment: Data Hold delay Th = 10ns */
	_delay_ms(1);
#endif
}

void LCD_Clear(void)
{
	LCD_Send_Instruction(LCD_CLEAR_DISPLAY);
}

void LCD_RowCol_Select(uint8 Row, uint8 Col)
{
	uint8 u8LocalLineAddress = 0U;

	switch(Row)
	{
		case 0:
			/* !Comment: When Writing To LCD 1st Col The Base Address is 0x00 */
			u8LocalLineAddress = Col | LCD_1ST_LINE_BASE;
			break;
		case 1:
			/* !Comment: When Writing To LCD 2nd Col The Base Address is 0x40 */
			u8LocalLineAddress = Col | LCD_2ND_LINE_BASE;
			break;
		case 2:
			/* !Comment: When Writing To LCD 1st Col The Base Address is 0x10 */
			u8LocalLineAddress = Col | LCD_3RD_LINE_BASE;
			break;
		case 3:
			/* !Comment: When Writing To LCD 1st Col The Base Address is 0x50 */
			u8LocalLineAddress = Col | LCD_4TH_LINE_BASE;
			break;
		default:
			break;
	}
	LCD_Send_Instruction(LCD_DDRAM_CONST | u8LocalLineAddress);
}
void LCD_CharDisplay(uint8 Data)
{
	/* !Comment: RW  Should be 0  and RS should be 1 when Writing Data to LCD */
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_RS, DIO_HIGH);
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_RW, DIO_LOW);
	/* !Comment: Delay of Address Set 60ns minimum */
	_delay_ms(1);
	/* !Comment: Enable LCD E=1 */
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_EN, DIO_HIGH);
	/* !Comment: Delay for processing PW min 450ns */
	_delay_ms(1);
#if LCD_EIGHTBIT_DATA
	Dio_PortWrite(LCD_DATA_OUT_REG, Data);
#else
	/* !Comment: Clear the Previous Data */
	*LCD_DATA_OUT_REG &= 0x0FU;
	*LCD_DATA_OUT_REG |= (Data & 0xF0U);
	/* !Comment: Data set-up time delay  Tdsw = 195 ns */
	_delay_ms(1);
	/* !Comment: Disable LCD E=0 */
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_EN, DIO_LOW);
	/* !Comment: Data Hold delay Th = 10ns */
	_delay_ms(1);

	/* !Comment: Enable LCD E=1  (To write the other 4-bit of the instruction)*/
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_EN, DIO_HIGH);
	/* !Comment: Delay for processing PW min 450ns */
	_delay_ms(1);
	/* !Comment: Clear the Previous Data */
	*LCD_DATA_OUT_REG &= 0x0FU;
	*LCD_DATA_OUT_REG |= ((Data << 4U) & 0xF0U);
	/* !Comment: Data set-up time delay  Tdsw = 195 ns */
	_delay_ms(1);
	/* !Comment: Disable LCD E=0 */
	Dio_ChannelWrite(LCD_CTRL_OUT_REG, LCD_EN, DIO_LOW);
	/* !Comment: Data Hold delay Th = 10ns */
	_delay_ms(1);
#endif
}

void LCD_StringDisplay(char *Str)
{
	while(*Str != '\0')
	{
		LCD_CharDisplay(*Str);
		Str++;
	}
}

void LCD_IntegerDisplay(sint32 Data)
{
	/* !Comment: String to hold the ascii result */
	char au8LocalResult[17];
	/* !Comment: 10 for decimal */
	itoa(Data, au8LocalResult, 10);
	/* !Comment: Display The Result */
	LCD_StringDisplay(au8LocalResult);
}
