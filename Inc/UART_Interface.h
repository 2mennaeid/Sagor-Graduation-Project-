/*
 * UART_Interface.h
 *
 *  Created on: Jan 25, 2024
 *      Author: Menna Eid
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/********************************** Interfacing macros ************************/

typedef enum
{
	TC_INTERRUPT_ENABLE=0x40,
	RXNE_INTERRUPT_ENABLE=0x20,
	TC_RXNE_INTERRUPT_ENABLE=0x60,
	DISABLE_INTERRUPTS = 0x00
}UART_Interrupt_Status_t;

typedef enum
{
	Baudrate_2400=0xD05,
	Baudrate_4800=0x683,
	Baudrate_9600=0x341,
	Baudrate_115200=0x45
}UART_BaudRate_t;

/****************************** Prototypes **********************************/



void UART_vInit(UART_BaudRate_t Copy_enuBaudRate,UART_Interrupt_Status_t Copy_enuINT_status);

void UART_vSendByte(u8_t Copy_u8data);

void UART_vReceiveByte(u8_t*Copy_u8data);

void UART_vSendStream(u8_t*Copy_u8data,u16_t Copy_u16Length);

void UART_vReceiveStream(u8_t*Copy_u8data,u16_t Copy_u16Length);

/*void UART_vAsych_SendByte(u8_t Copy_u8data);

void UART_vAsych_ReceiveByte(u8_t*Copy_u8data);

void UART_vAsych_SendStream(u8_t*Copy_u8data);

void UART_vAsych_ReceiveStream(u8_t*Copy_u8data);*/





#endif /* UART_INTERFACE_H_ */
