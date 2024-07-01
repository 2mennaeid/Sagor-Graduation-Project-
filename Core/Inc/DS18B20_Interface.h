/*
 * DS18B20.h
 *
 *  Created on: Apr 27, 2024
 *      Author: Menna Eid
 */

/*#ifndef INC_DS18B20_INTERFACE_H_
#define INC_DS18B20_INTERFACE_H_*/


//#include "stdint.h"
/*#include "stm32f1xx_hal.h"

#define ONEWIRE_PORT    	   GPIOB
#define ONEWIRE_PIN     	   GPIO_PIN_0

#define DS18B20_CMD_CONVERTTEMP    0x44
#define DS18B20_CMD_RSCRATCHPAD    0xBE
#define DS18B20_CMD_WSCRATCHPAD    0x4E
#define DS18B20_CMD_CPYSCRATCHPAD  0x48
#define DS18B20_CMD_RECEEPROM      0xB8
#define DS18B20_CMD_RPWRSUPPLY     0xB4
#define DS18B20_CMD_SEARCHROM      0xF0
#define DS18B20_CMD_READROM        0x33
#define DS18B20_CMD_MATCHROM       0x55
#define DS18B20_CMD_SKIPROM        0xCC
#define DS18B20_CMD_ALARMSEARCH    0xEC

typedef struct {
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
} DS18B20_InitTypeDef;


void ONEWIRE_Init(void);
void ONEWIRE_WriteBit(uint8_t bit);
uint8_t ONEWIRE_ReadBit(void);
void ONEWIRE_WriteByte(uint8_t byte);
uint8_t ONEWIRE_ReadByte(void);
uint8_t ONEWIRE_Reset(void);

void DS18B20_Init(DS18B20_InitTypeDef *ds18b20);
void DS18B20_StartConversion(DS18B20_InitTypeDef *ds18b20);
uint8_t DS18B20_ReadTemperature(DS18B20_InitTypeDef *ds18b20, float *temperature);

#endif /* INC_DS18B20_INTERFACE_H_ */
