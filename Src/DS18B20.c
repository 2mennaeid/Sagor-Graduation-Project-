/*
 * DS18B20.c
 *
 *  Created on: Jun 21, 2024
 *      Author: Menna Eid
 */


#include "DS18B20.h"

GPIO_PinConfig_t ds18b20;

void DS18B20_set_pin_output()
{
    ds18b20.PortId = PORTA;
    ds18b20.PinId  = PIN0;
    ds18b20.PinMode = OUTPUT_PUSHPULL_2MHZ;
    GPIO_enuSetPinMode(&ds18b20);
}

void DS18B20_set_pin_input()
{
    ds18b20.PortId = PORTA;
    ds18b20.PinId  = PIN0;
    ds18b20.PinMode = INPUT_PULLUP;
    GPIO_enuSetPinMode(&ds18b20);
}

void DS18B20_start_sensor(u8_t* response)
{
    *response = 0;
    u8_t pinvalue = 0;
    DS18B20_set_pin_output();
    GPIO_enuSetPinValue(&ds18b20, LOW);
    SYSTICK_enuDelay_us(1000);
    DS18B20_set_pin_input();
    SYSTICK_enuDelay_us(350);
    GPIO_enuGetPinValue(&ds18b20, &pinvalue);
    SYSTICK_enuDelay_us(450);
    GPIO_enuGetPinValue(&ds18b20, &pinvalue);
    if (pinvalue == 0)
    {
        *response = 1;
    }
    SYSTICK_enuDelay_us(400);  // Adjust this timing
}

void DS18B20_writeData(u8_t data)
{
    for (int i = 0; i < 8; i++)
    {
        DS18B20_set_pin_output();
        if ((data & (1 << i)) != 0)  // if the bit is high
        {
            GPIO_enuSetPinValue(&ds18b20, LOW);
            SYSTICK_enuDelay_us(1);
            GPIO_enuSetPinValue(&ds18b20, HIGH);
            SYSTICK_enuDelay_us(60);
        }
        else
        {
            GPIO_enuSetPinValue(&ds18b20, LOW);
            SYSTICK_enuDelay_us(60);
            GPIO_enuSetPinValue(&ds18b20, HIGH);
        }
    }
}

void DS18B20_read_data(u8_t* data)
{
    u8_t pinvalue;
    *data = 0;
    for (int i = 0; i < 8; i++)
    {
        DS18B20_set_pin_output();
        GPIO_enuSetPinValue(&ds18b20, LOW);
        SYSTICK_enuDelay_us(1);
        DS18B20_set_pin_input();
        SYSTICK_enuDelay_us(14);
        GPIO_enuGetPinValue(&ds18b20, &pinvalue);
        if (pinvalue)
        {
            *data |= 1 << i;
        }
        SYSTICK_enuDelay_us(45);
    }
}


/* Function to read temperature in Celsius */
f32 DS18B20_read_temp_celsius()
{
    u8_t temp_lsb, temp_msb;
    u8_t response;

    DS18B20_start_sensor(&response);
    DS18B20_writeData(0xCC); // Skip ROM
    DS18B20_writeData(0x44); // Convert T command

    SYSTICK_enuDelay_us(800000); // Wait for conversion to complete (750ms for 12-bit resolution)

    DS18B20_start_sensor(&response);
    DS18B20_writeData(0xCC); // Skip ROM
    DS18B20_writeData(0xBE); // Read scratchpad

    DS18B20_read_data(&temp_lsb);
    DS18B20_read_data(&temp_msb);

    u16_t temp = (temp_msb << 8) | temp_lsb;
    return (f32)temp / 16.0; // 12-bit resolution
}


