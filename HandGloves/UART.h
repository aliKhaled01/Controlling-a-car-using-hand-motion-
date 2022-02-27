/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v02
*Brief: UART peripheral
*******************************************************/
#ifndef UART__H_
#define UART__H_
#include "MCAL_REGISTERS/Mem_Map32.h"
#include "STD_TYPES.h"
#include "utiles.h"
#include "UART_Lcfg.h"

void UART_Init(void);
void UART_SendByte(uint8 data);
uint8 UART_ReceiveByte(void);

uint8 UART_Receive_NoBlock(uint8*pdata);

void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));

void UART_SendByteNoBlock(uint8 data);
uint8 UART_ReceiveByteNoBlock(void);
#endif /* UART_H_ */
