/*
 * MCAL_Init.h
 *
 *  Created on: Jun 26, 2024
 *      Author: Menna Eid
 */

#ifndef INC_MCAL_INIT_H_
#define INC_MCAL_INIT_H_

#include "stm32f1xx_hal.h"


void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void MX_ADC1_Init(void);
void UART_vTransimt(char*Copy_data,unsigned char length);


#endif /* INC_MCAL_INIT_H_ */
