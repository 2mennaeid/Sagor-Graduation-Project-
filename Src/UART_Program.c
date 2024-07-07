/*
 * UART_Program.c
 *
 *  Created on: Jan 26, 2024
 *      Author: Menna Eid
 */


#include "STDTYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"
#include "errorstate.h"
#include "RCC_Priv.h"
#include "RCC_Interface.h"
#include "UART_Interface.h"


void UART_vInit(UART_BaudRate_t Copy_enuBaudRate,UART_Interrupt_Status_t Copy_enuINT_status)
{
	/*Enable RCC for UART2*/
	RCC_voidEnablePeriphralCLK(RCC_u8_APB1_BUS,17);
    /*Reset CR1 register*/
	UART->CR1 =0;
	/*enable uart*/
	SET_BIT(UART->CR1,13);
	/*set baudrate*/
	UART->BRR =Copy_enuBaudRate;
	/*set interrupt status*/
	UART->CR1 |= Copy_enuINT_status;
	/*Enable Transmitter and Receiver*/
	SET_BIT(UART->CR1,2);
	SET_BIT(UART->CR1,3);

}

void UART_vSendByte(u8_t Copy_u8data)
{

	UART->DR = Copy_u8data;
	while(READ_BIT(UART->SR,6)==0);
	CLEAR_BIT(UART->SR,6);

}

void UART_vReceiveByte(u8_t*Copy_u8data)
{
	     while(READ_BIT(UART->SR,5)==0);
		 *Copy_u8data = UART->DR;
		 CLEAR_BIT(UART->SR,5);
}

void UART_vSendStream(u8_t*Copy_u8data,u16_t Copy_u16Length)
{
	while(Copy_u16Length>0)
	{
		   if(READ_BIT(UART->SR,7))
		   {
			   UART->DR = *Copy_u8data;
			   while(READ_BIT(UART->SR,6)==0);
			   CLEAR_BIT(UART->SR,6);
			   Copy_u8data++;
			   Copy_u16Length--;
		   }
		   else
		   {
			   while(READ_BIT(UART->SR,7)==0);
		   }

			/*waiting for Transmission complete*/

	}
}

void UART_vReceiveStream(u8_t*Copy_u8data,u16_t Copy_u16Length)
{
	while(Copy_u16Length-->0)
	{
		while(READ_BIT(UART->SR,5)==0);
		*Copy_u8data = UART->DR;
		CLEAR_BIT(UART->SR,5);
		Copy_u8data++;
	}
}

/*void UART_vAsych_SendByte(u8_t Copy_u8data)
{

}

void UART_vAsych_ReceiveByte(u8_t*Copy_u8data)
{

}

void UART_vAsych_SendStream(u8_t*Copy_u8data)
{

}

void UART_vAsych_ReceiveStream(u8_t*Copy_u8data)
{

}
void USART1_IRQHandler()
{

}*/
