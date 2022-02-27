/*
 * Pwm.c
 *
 * Created: 10/14/2021 11:20:54 PM
 * Author : Abdelaziz Moustafa
 */


#include "DC_Motor.h"
#include "Pwm.h"
#include <util/delay.h>

#include <avr/io.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)


void USART_init(void){
	UBRRH = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRRL = (uint8_t)(BAUD_PRESCALLER);
	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
}

/* Function to receive byte/char */
unsigned char USART_receive(void){
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}
/* Function to send byte/char */
void USART_send( unsigned char data){
	while(!(UCSRA & (1<<UDRE)));
	UDR = data;
}
/* Send string */
void USART_putstring(char* StringPtr){
	while(*StringPtr != 0x00){
		USART_send(*StringPtr);
		StringPtr++;}

}



int main(void)
{
	uint8 ReceivedData;

	DcMotorR_Init();
	DcMotorL_Init();
	LCD_Init();
	USART_init();


	while (1)
	{
		ReceivedData = USART_receive();
		if(ReceivedData == 'l')
		{

			LCD_Clear();
			LCD_RowCol_Select(0,0);
			LCD_StringDisplay("Turning Left");
			Left();


		}
		if (ReceivedData == 'r')
		{
			LCD_Clear();
			LCD_RowCol_Select(0,0);
			LCD_StringDisplay("Turning Right");
			Right();
		}
		if (ReceivedData == 'f')
		{
			Forward();

		}
		if (ReceivedData == 'b')
		{
			Backward();
		}
		if (ReceivedData =='D')
		{
			LCD_Clear();
			LCD_RowCol_Select(0,0);
			LCD_StringDisplay("Moving Low");
			Pwm_SetDutyCycle(PWM_CHANNEL_1,20U);
		}
		if(ReceivedData =='H')
		{
			LCD_Clear();
			LCD_RowCol_Select(0,0);
			LCD_StringDisplay("Moving High");
			Pwm_SetDutyCycle(PWM_CHANNEL_1,90U);
		}
		if(ReceivedData=='s')
		{
			LCD_Clear();
			LCD_RowCol_Select(0,0);
			LCD_StringDisplay("Car Stopped");
			Pwm_SetDutyCycle(PWM_CHANNEL_1,0U);
			//function to stop the car
			Dio_ChannelWrite(DC_MOTOR_R_OUT_REG, DC_MOTOR_R_IN1_PIN, DIO_HIGH);
			Dio_ChannelWrite(DC_MOTOR_R_OUT_REG, DC_MOTOR_R_IN2_PIN, DIO_LOW);
		}


	}
}

