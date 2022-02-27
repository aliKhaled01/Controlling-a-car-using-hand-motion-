/*
 * Dio.h
 *
 * Created: 9/12/2021 7:09:14 PM
 *  Author: Abdelaziz Moustafa
 */


#ifndef DIO_H_
#define DIO_H_

#include "Std_Types.h"

/**
 *  Defines an enumerated list of all the channels (pins) on the MCU device.
 */
typedef enum
{
    DIO_PIN0,
    DIO_PIN1,
    DIO_PIN2,
    DIO_PIN3,
    DIO_PIN4,
    DIO_PIN5,
    DIO_PIN6,
    DIO_PIN7
}DioPinEnum_t;

/**
 * Defines the possible states for a digital output pin.
 */
 typedef enum
 {
    DIO_LOW,             /** Defines digital state ground */
    DIO_HIGH             /** Defines digital state power */
 }DioPinStateEnum_t;

/**
 *  Defines the GPIO direction : Input or output
 */
typedef enum
{
    DIO_INPUT,
    DIO_OUTPUT
}DioPinDirectionEnum_t;

void Dio_ChannelDirectionSet(volatile uint8 * Port_reg, DioPinEnum_t Channel, DioPinDirectionEnum_t Direction);
DioPinStateEnum_t Dio_ChannelRead(volatile uint8 * Port_reg, DioPinEnum_t Channel);
void Dio_ChannelWrite(volatile uint8 * Port_reg, DioPinEnum_t Channel, DioPinStateEnum_t State);
void Dio_ChannelToggle(volatile uint8 * Port_reg, DioPinEnum_t Channel);
void Dio_PortWrite(volatile uint8 * Port_reg, uint8 Value);
uint8 Dio_PortRead(volatile uint8 * Port_reg);

#endif /* DIO_H_ */
