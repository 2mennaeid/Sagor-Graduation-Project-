/*
 * pH.h
 *
 *  Created on: Apr 27, 2024
 *      Author: Menna Eid
 */

#ifndef INC_PH_INTERFACE_H_
#define INC_PH_INTERFACE_H_

#include "stdint.h"
#include "stm32f1xx.h"

#define Calibration    14.34

void pH_vReadValue(uint16_t buff[] ,float*Copy_f32pHValue);

void ConvertToString(float Copy_fnum,char*PtrArray);

void ConverFracToString(float x,char*PtrArray,char*index);

#endif /* INC_PH_INTERFACE_H_ */
