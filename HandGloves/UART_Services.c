
#include "UART_Services.h"

static void Func_TX(void);
//static void Send_Int_Function2(void);
static void Receive_Int_Function(void);
/**********************************************variables*******************************************************/

//static volatile  uint8 flag=1;
static uint8  *Asynch_Send_Str;
static uint8  *Asynch_receive_str;

/*******************************************Send Functions*****************************************************/
static uint8 jcount=0;

void UART_SendString( uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_SendByte(Str[i]);
		i++;
	}
}
								////////////////////////////////////

void UART_SendString_Asynch(uint8 *Str)
{
	Asynch_Send_Str=Str;
	UART_SendByte(Str[0]);
	UART_TX_SetCallBack(Func_TX);
	UART_TX_InterruptEnable();

}

static void Func_TX(void)
{
static uint8 i=1;
	if(Asynch_Send_Str[i] !='\0')
	{
		UART_SendByteNoBlock(Asynch_Send_Str[i]);
		i++;
	}
	else
		{
		i=1;
		UART_TX_InterruptDisable();
		}
}
								////////////////////////////////////

//void UART_SendString_Asynch_NocodeInInt(uint8 *Str)
//{
//	UART_TX_SetCallBack(Send_Int_Function2);
//		UART_TX_InterruptEnable();
//	static	uint8 i=0;
//	if(flag)
//		{
//		if(Str[i])
//			{
//			UART_SendByteNoBlock(Str[i]);
//			i++;
//			flag=0;
//			}
//			else
//			i=0;
//
//		}
//
//}
//static void Send_Int_Function2(void)
//{
//	flag=1;
//}


/*****************************************Receive Functions*****************************************************/

void UART_ReceiveString(uint8 *Str)       //receive until 'enter'
{
	uint8 i = 0;
	Str[i] = UART_ReceiveByte();
	while(Str[i] != 0 )
	{
		i++;
		Str[i] = UART_ReceiveByte();
	}
	Str[i] = '\0';
	//UART_RecieveByte();
}


/*********************************** Receive Async ***************************************/

void UART_ReceiveString_Asynch(sint8 *Str)
{
	Asynch_receive_str=Str;
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(Receive_Int_Function);
	sei();
}

static void Receive_Int_Function(void)
{

	Asynch_receive_str[jcount]=UART_ReceiveByteNoBlock();
	jcount++;
}
void UART_ResetCounterRecieveing()
{
	jcount=0;
}


/************************************PROTOCOL ABOVE UART ***********************************/
