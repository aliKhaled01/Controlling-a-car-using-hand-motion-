
#include "UART.h"
#include "UART_Lcfg.h"

/****************************Pointer to functions to be assigned to ISR*********************************/
#if UART
static void (*UART_RX_Fptr) (void);
static void (*UART_TX_Fptr) (void);


/********************************************initialization **********************************************/

/************************* Array of  UBRR values ***************************/
const uint16 BaudRateArray[TOTAL_SPEED_MODE][TOTAL_CPU_F][TOTAL_BAUD_RATE]=
{{{103, 51, 25, 16, 12,  8,0},{207,103, 51, 34, 25, 16,3},{416,207,103, 68 ,51, 34,8}},
		{{207,103, 51, 34, 25, 16,0},{416,207,103, 68 ,51, 34,8},{832,416,207,138,103, 68,16}}};

void UART_Init(void)
{
	volatile uint8  UCSRC_var=0;
	uint16 UBRR_var=0;
	/***************************** transmission speed***************************/
#if (SPEED_MODE==NORMAL_SPEED)
	CLEAR_BIT(UCSRA,U2X);
#elif (SPEED_MODE==DOUBLE_SPEED)
	SET_BIT(UCSRA,U2X);
#endif

	//******************set URSEL to write data to UCSRC register***************/
	SET_BIT(UCSRC_var,7);

	//********************************synch***********************************/
#if (SYNCH_MODE==SYNCH)
	SET_BIT(UCSRC_var,UMSEL)
#elif (SYNCH_MODE==ASYNCH)
	CLEAR_BIT(UCSRC_var,UMSEL);
#endif
	//*****************************parity mode*******************************/

#if (PARITY_MODE==NO_PARITY)
	CLEAR_BIT(UCSRC_var,UPM0);
	CLEAR_BIT(UCSRC_var,UPM1);
#elif (PARITY_MODE==EVEN_PARITY)
	CLEAR_BIT(UCSRC_var,UPM0);
	SET_BIT(UCSRC_var,UPM1);
#elif (PARITY_MODE==ODD_PARITY)
	SET_BIT(UCSRC_var,UPM0);
	SET_BIT(UCSRC_var,UPM1);
#endif
	//************************Data bits*******************************/
#if (N_DATA_BITS==_5_DATA_BITS)
	CLEAR_BIT(UCSRC_var,UCSZ0);
	CLEAR_BIT(UCSRC_var,UCSZ1);
	CLEAR_BIT(UCSRC_var,UCSZ2);
#elif (N_DATA_BITS==_6_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	CLEAR_BIT(UCSRC_var,UCSZ1);
	CLEAR_BIT(UCSRC_var,UCSZ2);
#elif (N_DATA_BITS==_7_DATA_BITS)
	CLEAR_BIT(UCSRC_var,UCSZ0);
	SET_BIT(UCSRC_var,UCSZ1);
	CLEAR_BIT(UCSRB,UCSZ2);
#elif (N_DATA_BITS==_8_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	SET_BIT(UCSRC_var,UCSZ1);
	CLEAR_BIT(UCSRB,UCSZ2);
#elif (N_DATA_BITS==_9_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	SET_BIT(UCSRC_var,UCSZ1);
	SET_BIT(UCSRB,UCSZ2);
#endif
	//************************Stop bits*******************************/
#if (N_STOP_BITS==ONE_STOP_BIT)
	CLEAR_BIT(UCSRC_var,USBS);
#elif (N_STOP_BITS==TWO_STOP_BIT)
	SET_BIT(UCSRC_var,USBS);
#endif
	//*****************set UCSRC value   *******************************/
	UCSRC=UCSRC_var;

	//************************Baud rate *******************************/

	UBRR_var=BaudRateArray[SPEED_MODE][CPU_F][BUAD_RATE];
	UBRRH = (uint8)(UBRR_var>>8);
	UBRRL = (uint8)UBRR_var;

	//************************Enable*******************************/
	//enable UART  receiver.
	SET_BIT(UCSRB,RXEN);
	//enable UART  transmitter .
	SET_BIT(UCSRB,TXEN);
}


/*****************************************Interrupt functions*********************************************/


void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,TXCIE);
}
/*****************************************Set Call Back Functions*********************************************/
void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}
/***********************************************ISR ************************************************************/
ISR(USART_RXC_vect)
{
	if (UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}

ISR(USART_TXC_vect)
{
	if (UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}


/****************************************Send and receive functions with no ckecking********************************/

void UART_SendByteNoBlock(uint8 data)
{
	UDR = data;
}

uint8 UART_ReceiveByteNoBlock(void)
{
	return UDR;
}
/****************************************Send and receive functions with polling     ********************************/
void UART_SendByte(uint8 data)
{
	/*UDRE flag is set when the buffer is empty and ready
	for transmitting a new byte so wait until this flag is set to one
	and it will cleared by hardware when u write  new data to puffer.*/
	while(!(GET_BIT(UCSRA,UDRE)));
	UDR = data;
}

uint8 UART_ReceiveByte(void)
{
	/*RXC flag is set when the UART receive data so  wait until this flag is set to one
	and it will cleared by hardware when u read the data*/
	while(!(GET_BIT(UCSRA,RXC)));
	return UDR;
}


uint8 UART_Receive_NoBlock(uint8*pdata)
{
	uint8 status=0;
	if(GET_BIT(UCSRA,RXC))
	{
		*pdata=UDR;
		status=1;
	}
	else
	{
	status=0;
	}
	return status;
}
#endif








