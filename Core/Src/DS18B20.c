/*
 * DS18B20.C
 *
 *  Created on: Apr 27, 2024
 *      Author: Menna Eid
 */


/*#include "DS18B20_Interface.h"

extern TIM_HandleTypeDef htim2;

void delay_us(uint32_t us)
{
    uint32_t start = __HAL_TIM_GET_COUNTER(&htim2);
    while ((__HAL_TIM_GET_COUNTER(&htim2) - start) < us);
}



void ONEWIRE_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = ONEWIRE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ONEWIRE_PORT, &GPIO_InitStruct);

    HAL_GPIO_WritePin(ONEWIRE_PORT, ONEWIRE_PIN, GPIO_PIN_SET);
}

void ONEWIRE_WriteBit(uint8_t bit)
{
    HAL_GPIO_WritePin(ONEWIRE_PORT, ONEWIRE_PIN, GPIO_PIN_RESET);
    delay_us(bit ? 1 : 60);
    HAL_GPIO_WritePin(ONEWIRE_PORT, ONEWIRE_PIN, GPIO_PIN_SET);
    delay_us(bit ? 60 : 1);
}

uint8_t ONEWIRE_ReadBit(void)
{
    uint8_t bit = 0;

    HAL_GPIO_WritePin(ONEWIRE_PORT, ONEWIRE_PIN, GPIO_PIN_RESET);
    delay_us(2);
    HAL_GPIO_WritePin(ONEWIRE_PORT, ONEWIRE_PIN, GPIO_PIN_SET);
    delay_us(15);
    bit = HAL_GPIO_ReadPin(ONEWIRE_PORT, ONEWIRE_PIN);
    delay_us(45);

    return bit;
}

void ONEWIRE_WriteByte(uint8_t byte)
{
    for (int i = 0; i < 8; i++)
    {
        ONEWIRE_WriteBit(byte & 0x01);
        byte >>= 1;
    }
}

uint8_t ONEWIRE_ReadByte(void)
{
    uint8_t byte = 0;

    for (int i = 0; i < 8; i++)
    {
        byte >>= 1;
        if (ONEWIRE_ReadBit()) {
            byte |= 0x80;
        }
    }

    return byte;
}

uint8_t ONEWIRE_Reset(void)
{
    uint8_t presence = 0;

    HAL_GPIO_WritePin(ONEWIRE_PORT, ONEWIRE_PIN, GPIO_PIN_RESET);
    delay_us(480);
    HAL_GPIO_WritePin(ONEWIRE_PORT, ONEWIRE_PIN, GPIO_PIN_SET);
    delay_us(80);
    presence = HAL_GPIO_ReadPin(ONEWIRE_PORT, ONEWIRE_PIN);
    delay_us(410);

    return presence;
}



void DS18B20_Init(DS18B20_InitTypeDef *ds18b20)
{
    ONEWIRE_Init();
}

void DS18B20_StartConversion(DS18B20_InitTypeDef *ds18b20)
{
    ONEWIRE_Reset();
    ONEWIRE_WriteByte(DS18B20_CMD_SKIPROM);
    ONEWIRE_WriteByte(DS18B20_CMD_CONVERTTEMP);
}

uint8_t DS18B20_ReadTemperature(DS18B20_InitTypeDef *ds18b20, float *temperature)
{
    uint8_t temp_lsb, temp_msb;
    int16_t temp;
    uint8_t presence;

    presence = ONEWIRE_Reset();
    if (presence) {
        return 1;  // Error: No presence detected
    }

    ONEWIRE_WriteByte(DS18B20_CMD_SKIPROM);
    ONEWIRE_WriteByte(DS18B20_CMD_RSCRATCHPAD);

    temp_lsb = ONEWIRE_ReadByte();
    temp_msb = ONEWIRE_ReadByte();
    temp = (temp_msb << 8) | temp_lsb;

    *temperature = (float)temp * 0.0625;

    return 0;  // Success
}*/


