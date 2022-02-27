
#ifndef UART_LCFG_H_
#define UART_LCFG_H_

/******************* UART configuration *********************************/
#define  SPEED_MODE         NORMAL_SPEED
#define  CPU_F               _16_MHZ
#define  BUAD_RATE          BAUD_9600
#define  SYNCH_MODE         ASYNCH
#define  PARITY_MODE        NO_PARITY
#define  N_DATA_BITS        _8_DATA_BITS
#define  N_STOP_BITS        ONE_STOP_BIT


/******************** speed mode *************************/
#define NORMAL_SPEED      0
#define DOUBLE_SPEED      1
#define TOTAL_SPEED_MODE  2 //unused
/******************** cpu freqs ***************************/
#define   _4_MHZ         0
#define   _8_MHZ         1
#define  _16_MHZ         2
#define  TOTAL_CPU_F     3
/*******************baud rate *****************************/
#define  BAUD_2400       0
#define  BAUD_4800       1
#define  BAUD_9600       2
#define  BAUD_14400      3
#define  BAUD_19200      4
#define  BAUD_28800      5
#define  BAUD_115200     6
#define  TOTAL_BAUD_RATE 7
/*******************parity mode*************************/
#define NO_PARITY    0
#define EVEN_PARITY  1
#define ODD_PARITY   2

/*************** number of data bits********************/

#define  _5_DATA_BITS    5
#define  _6_DATA_BITS    6
#define  _7_DATA_BITS    7
#define  _8_DATA_BITS    8
#define  _9_DATA_BITS    9

/***************      sync mode*************************/

#define  SYNCH  0
#define  ASYNCH 1

/************    number of stop bits*****************/

#define  ONE_STOP_BIT   1
#define  TWO_STOP_BIT   2

#endif /* UART_LCFG_H_ */
