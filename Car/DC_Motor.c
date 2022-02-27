/*
 * DC_Motor.c
 *
 * Created: 10/15/2021 1:30:21 AM
 *  Author: Abdelaziz Moustafa
 */

#include "DC_Motor.h"

#include <util/delay.h>

#include "Pwm.h"

void DcMotorR_Init(void)
{
	/* !Comment: Initialize the DC Motor direction selection Pins */
	Dio_ChannelDirectionSet(DC_MOTOR_R_DIR_REG, DC_MOTOR_R_IN1_PIN, DIO_OUTPUT);
	Dio_ChannelDirectionSet(DC_MOTOR_R_DIR_REG, DC_MOTOR_R_IN2_PIN, DIO_OUTPUT);
	Dio_ChannelDirectionSet(DC_MOTOR_R_EN_DIR_REG, DC_MOTOR_R_EN_PIN, DIO_OUTPUT);
	/* !Comment: Initialize PWM module */
	Pwm_Init(&gStrPwm_Configuration[PWM_CHANNEL_1]);
}
void DcMotorR_Control(DcMotor_RotationDirType Dir, DcMotor_SpeedType Speed)
{
	switch(Dir)
	{
	case DC_MOTOR_TURN_CW:
		Dio_ChannelWrite(DC_MOTOR_R_OUT_REG, DC_MOTOR_R_IN1_PIN, DIO_HIGH);
		Dio_ChannelWrite(DC_MOTOR_R_OUT_REG, DC_MOTOR_R_IN2_PIN, DIO_LOW);
		break;
	case DC_MOTOR_TURN_CCW:
		Dio_ChannelWrite(DC_MOTOR_R_OUT_REG, DC_MOTOR_R_IN1_PIN, DIO_LOW);
		Dio_ChannelWrite(DC_MOTOR_R_OUT_REG, DC_MOTOR_R_IN2_PIN, DIO_HIGH);
		break;
	default:
		break;
	}
	switch(Speed)
	{
	case DC_MOTOR_SPEED_LOW:
		Pwm_SetDutyCycle(PWM_CHANNEL_1, 20U);
		break;
	case DC_MOTOR_SPEED_MID:
		Pwm_SetDutyCycle(PWM_CHANNEL_1, 50U);
		break;
	case DC_MOTOR_SPEED_HIGH:
		Pwm_SetDutyCycle(PWM_CHANNEL_1, 90U);
		break;
	default:
		break;
	}
}

void DcMotorL_Init(void)
{
	/* !Comment: Initialize the DC Motor direction selection Pins */
	Dio_ChannelDirectionSet(DC_MOTOR_L_DIR_REG, DC_MOTOR_L_IN1_PIN, DIO_OUTPUT);
	Dio_ChannelDirectionSet(DC_MOTOR_L_DIR_REG, DC_MOTOR_L_IN2_PIN, DIO_OUTPUT);
	Dio_ChannelDirectionSet(DC_MOTOR_L_EN_DIR_REG, DC_MOTOR_L_EN_PIN, DIO_OUTPUT);
	/* !Comment: Initialize PWM module */
	Pwm_Init(&gStrPwm_Configuration[PWM_CHANNEL_1]);
}
void DcMotorL_Control(DcMotor_RotationDirType Dir, DcMotor_SpeedType Speed)
{
	switch(Dir)
	{
	case DC_MOTOR_TURN_CW:
		Dio_ChannelWrite(DC_MOTOR_L_OUT_REG, DC_MOTOR_L_IN1_PIN, DIO_HIGH);
		Dio_ChannelWrite(DC_MOTOR_L_OUT_REG, DC_MOTOR_L_IN2_PIN, DIO_LOW);
		break;
	case DC_MOTOR_TURN_CCW:
		Dio_ChannelWrite(DC_MOTOR_L_OUT_REG, DC_MOTOR_L_IN1_PIN, DIO_LOW);
		Dio_ChannelWrite(DC_MOTOR_L_OUT_REG, DC_MOTOR_L_IN2_PIN, DIO_HIGH);
		break;
	default:
		break;
	}
	switch(Speed)
	{
	case DC_MOTOR_SPEED_LOW:
		Pwm_SetDutyCycle(PWM_CHANNEL_1, 20U);
		break;
	case DC_MOTOR_SPEED_MID:
		Pwm_SetDutyCycle(PWM_CHANNEL_1, 50U);
		break;
	case DC_MOTOR_SPEED_HIGH:
		Pwm_SetDutyCycle(PWM_CHANNEL_1, 90U);
		break;
	default:
		break;
	}
}

void Forward(void)
{
	DcMotorR_Control(DC_MOTOR_TURN_CW, DC_MOTOR_SPEED_MID);
	DcMotorL_Control(DC_MOTOR_TURN_CW, DC_MOTOR_SPEED_MID);
	LCD_Clear();
	LCD_RowCol_Select(0,0);
	LCD_StringDisplay("Moving Forward");


}
void Backward(void)
{
	DcMotorR_Control(DC_MOTOR_TURN_CCW, DC_MOTOR_SPEED_MID);
	DcMotorL_Control(DC_MOTOR_TURN_CCW, DC_MOTOR_SPEED_MID);
	LCD_Clear();
	LCD_RowCol_Select(0,0);
	LCD_StringDisplay("Moving Backward");

}
void Left(void)
{
	DcMotorR_Control(DC_MOTOR_TURN_CW, DC_MOTOR_SPEED_MID);
	DcMotorL_Control(DC_MOTOR_TURN_CCW, DC_MOTOR_SPEED_MID);


}
void Right(void)
{
	DcMotorR_Control(DC_MOTOR_TURN_CCW, DC_MOTOR_SPEED_MID);
	DcMotorL_Control(DC_MOTOR_TURN_CW, DC_MOTOR_SPEED_MID);


}


