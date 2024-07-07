/*
 * PH_Interface.h
 *
 *  Created on: Feb 11, 2024
 *      Author: Menna Eid
 */

#ifndef PH_INTERFACE_H_
#define PH_INTERFACE_H_

#include "STDTYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"
#include "errorstate.h"
#include "RCC_Priv.h"
#include "RCC_Interface.h"
#include "SYSTICK_Priv.h"
#include "SYSTICK_Interface.h"
#include "GPIO_Priv.h"
#include "GPIO_Interface.h"
#include "ADC_Interface.h"

ES_t pH_enuInit(u8_t Copy_u8channelId);

ES_t pH_enuReadValue(u16_t buff[] ,f32*Copy_f32pHValue);

void ConvertFloatToString(f32 Copy_fnum,u8_t*PtrArray);

void ConverFracToString(f32 x,u8_t*PtrArray,u8_t*index);

#endif /* PH_INTERFACE_H_ */
