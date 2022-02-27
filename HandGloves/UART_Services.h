#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_



#include "UART.h"

#include "Std_Types.h"
void UART_SendString( uint8 *Str);
void UART_SendString_Asynch(uint8 *Str);
void UART_SendString_Asynch_NocodeInInt(uint8 *Str);

void UART_ReceiveString(uint8 *Str); // Receive until #
void UART_ReceiveString_NoBlock(uint8 *Str);   // Receive until #
void UART_ReceiveString_Asynch(sint8 *Str);

void UART_ResetCounterRecieveing();

#endif /* UART_SERVICES_H_ */
