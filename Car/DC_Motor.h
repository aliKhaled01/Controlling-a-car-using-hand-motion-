/*
 * DC_Motor.h
 *
 * Created: 10/15/2021 1:30:05 AM
 *  Author: Abdelaziz Moustafa
 */


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "Dio.h"
#include "ATmega32_Cfg.h"
#include "LCD.h"


#define DC_MOTOR_R_DIR_REG        (PORTC_DIR_REG)
#define DC_MOTOR_R_OUT_REG        (PORTC_OUT_REG)
#define DC_MOTOR_R_IN1_PIN        (DIO_PIN5)
#define DC_MOTOR_R_IN2_PIN        (DIO_PIN6)

#define DC_MOTOR_R_EN_DIR_REG     (PORTD_DIR_REG)
#define DC_MOTOR_R_EN_PIN         (DIO_PIN5)

#define DC_MOTOR_L_DIR_REG        (PORTC_DIR_REG)
#define DC_MOTOR_L_OUT_REG        (PORTC_OUT_REG)
#define DC_MOTOR_L_IN1_PIN        (DIO_PIN3)
#define DC_MOTOR_L_IN2_PIN        (DIO_PIN4)

#define DC_MOTOR_L_EN_DIR_REG     (PORTD_DIR_REG)
#define DC_MOTOR_L_EN_PIN         (DIO_PIN4)
typedef enum
{
	DC_MOTOR_TURN_CW,
	DC_MOTOR_TURN_CCW
}DcMotor_RotationDirType;

typedef enum
{
	DC_MOTOR_SPEED_LOW,
	DC_MOTOR_SPEED_MID,
	DC_MOTOR_SPEED_HIGH
}DcMotor_SpeedType;

void DcMotorR_Init(void);
void DcMotorR_Control(DcMotor_RotationDirType Dir, DcMotor_SpeedType Speed);

void DcMotorL_Init(void);
void DcMotorL_Control(DcMotor_RotationDirType Dir, DcMotor_SpeedType Speed);

void Forward(void);
void Backward(void);
void Left(void);
void Right(void);

#endif /* DC_MOTOR_H_ */
