/*
 * DS18B20.h
 *
 *  Created on: Jun 21, 2024
 *      Author: Menna Eid
 */

#ifndef DS18B20_H_
#define DS18B20_H_
#include "BIT_MATH.h"
#include "STDTYPES.h"
#include "stm32f103xx.h"
#include "errorstate.h"
#include "SYSTICK_Priv.h"
#include "SYSTICK_Interface.h"
#include "GPIO_Priv.h"
#include "GPIO_Interface.h"


void DS18B20_set_pin_output();
void DS18B20_set_pin_input();
void DS18B20_start_sensor(u8_t*response);
void DS18B20_writeData(u8_t Copy_u8data);
void DS18B20_read_data(u8_t*Copy_u8data);
void DS18B20_set_resolution(u8_t resolution);
f32 DS18B20_read_temp_celsius();

#endif /* DS18B20_H_ */
