#include "MCAL_REGISTERS/Mem_Map32.h"
#include "LCD.h"
#include "UART.h"
#include "Adc.h"

int main()
{
	UART_Init();
    LCD_Init();
	uint16 Thump_Value1_unbent=0 ,Thump_Value2_unbent=256;
	uint16 Thump_Value1_bent=257,Thump_Value2_bent=1023;

	uint16 Finger2_Value1_unbent=0 ,Finger2_Value2_unbent=256;
	uint16 Finger2_Value1_bent=257 ,Finger2_Value2_bent=1023;

	uint16 Finger3_Value1_unbent=0 ,Finger3_Value2_unbent=256;
	uint16 Finger3_Value1_bent=257 ,Finger3_Value2_bent=1023;

	uint16 Finger4_Value1_unbent=0 ,Finger4_Value2_unbent=256;
	uint16 Finger4_Value1_bent=257 ,Finger4_Value2_bent=1023;

	uint16 Finger5_Value1_unbent=0 ,Finger5_Value2_unbent=256;
	uint16 Finger5_Value1_bent=257,Finger5_Value2_bent=1023;
	uint8 moved_forward=0,moved_backward=0,moved_high=0,moved_low=0,forward_backward_direction_controlled=0,moved_right=0,moved_left=0,car_stoped=0;

	while(1)
	{

		if((Thump_Value1_unbent<=ADC0_Read()&&ADC0_Read()<=Thump_Value2_unbent)&&(Finger3_Value1_unbent<=ADC3_Read()&&ADC3_Read()<=Finger3_Value2_unbent)&&(Finger4_Value1_unbent<=ADC4_Read()&&ADC4_Read()<=Finger4_Value2_unbent)&&(Finger5_Value1_unbent<=ADC5_Read()&&ADC5_Read()<=Finger5_Value2_unbent))
		{
			if((Finger2_Value1_unbent<=ADC1_Read()&&ADC1_Read()<=Finger2_Value2_unbent)&&moved_forward==0)
			{
				UART_SendByte('f'); //move forward
				moved_forward=1;
				moved_backward=0;

			}
			if((Finger2_Value1_bent<=ADC1_Read()&& ADC1_Read()<=Finger2_Value2_bent)&&moved_backward==0)
			{
				UART_SendByte('b'); //move backward
				moved_forward=0;
				moved_backward=1;
			}
			forward_backward_direction_controlled=1;
		}
		if(forward_backward_direction_controlled==1)
		{
			if((Thump_Value1_bent<=ADC0_Read()&&ADC0_Read()<=Thump_Value2_bent)&&moved_high==0)
			{
				UART_SendByte('H');  //high speed
				moved_high=1;
				moved_low=0;
			}
			if((Thump_Value1_unbent<=ADC0_Read()&&ADC0_Read()<=Thump_Value2_unbent)&&moved_low==0)
			{
				UART_SendByte('D');  //low speed
				moved_high=0;
				moved_low=1;
			}
			if((Finger4_Value1_bent<=ADC4_Read()&&ADC4_Read()<=Finger4_Value2_bent)&&moved_right==0)
			{
				UART_SendByte('r');  //turn right
				moved_right=1;
				moved_left=0;

			}
			if((Finger5_Value1_bent<=ADC5_Read()&&ADC5_Read()<=Finger5_Value2_bent)&&moved_left==0)
			{
				UART_SendByte('l');  //turn left
				moved_right=0;
				moved_left=1;
			}

		}
		if(car_stoped==0&&(Finger5_Value1_bent<=ADC5_Read()&&ADC5_Read()<=Finger5_Value2_bent)&&(Finger4_Value1_bent<=ADC4_Read()&&ADC4_Read()<=Finger4_Value2_bent)&&(Finger2_Value1_bent<=ADC1_Read()&& ADC1_Read()<=Finger2_Value2_bent))
		{
			UART_SendByte('s');     //stop the car
			car_stoped=1;
			forward_backward_direction_controlled=0;

		}

	}

}







