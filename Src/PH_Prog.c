/*
 * PH_Prog.c
 *
 *  Created on: Feb 11, 2024
 *      Author: Menna Eid
 */


#include "PH_Interface.h"

#define PH_u8_Calibartion        13.34

GPIO_PinConfig_t App_PORTA;

ES_t pH_enuInit(u8_t Copy_u8channelId)
{
	ES_t LocalErrorState = ES_OK;
	if(Copy_u8channelId>17)
	{
		LocalErrorState = ES_NOK;
	}
	else
	{
		ADC_enuInit(Single);
		ADC_SelectChannel(Copy_u8channelId,SQR2,1);
		ADC_vSetSampleTime(Copy_u8channelId,Cycle_7);
		App_PORTA.PortId = PORTA;
		App_PORTA.PinId = Copy_u8channelId;
		App_PORTA.PinMode = INPUT_ANALOG;
		GPIO_enuSetPinMode(&App_PORTA);

	}

	return LocalErrorState;
}

ES_t pH_enuReadValue(u16_t buff[] ,f32*Copy_f32pHValue)
{
	ES_t LocalErrorState = ES_OK;
	u32_t average =0;
	f32 ph_value;
	u32_t temp;
	if(Copy_f32pHValue!=NULLPTR)
	{
	  //Get 10 sample value from the sensor for smooth the value
		for(u8_t i=0;i<10;i++)
		{
			ADC_vStartConversion();
			ADC_vPollingSystem();
			buff[i] = ADC_enuRead();
            SYSTICK_enuDelay_us(2000);
            ADC_vStopConversion();
		}
		// sort analog values
		for(u8_t i=0;i<9;i++)
		{
			for(u8_t j=i+1;j<10;j++)
			{
				if(buff[i]>buff[j])
				{
					temp = buff[i];
					buff[i] = buff[j];
					buff[j] = temp;
				}
			}
		}
		 //take the average value of 6 center sample
		for(u8_t i =2;i<8;i++)
		{
			average += buff[i];
		}
		ph_value = (f32)average*3.3/ADC_RES/6;
		*Copy_f32pHValue = (-5.70*ph_value) + PH_u8_Calibartion;

	}
	else
    {
		LocalErrorState = ES_NOK;
    }
	return LocalErrorState;
}

void ConvertFloatToString(f32 Copy_fnum,u8_t*PtrArray)
{
    u16_t Local_u16iter;
    u16_t Local_u16num;
    Local_u16num = Copy_fnum;
    if(Local_u16num<10)
    {
        PtrArray[0] = Local_u16num + '0';
        PtrArray[1] = '.';
    }
    else if(Local_u16num<100)
    {
        Local_u16iter=1;
        PtrArray[2] = '.';
        while(Local_u16iter>=0)
        {
           PtrArray[Local_u16iter] = (Local_u16num%10)+ '0';
           Local_u16num = Local_u16num /10;
            Local_u16iter--;
        }
    }

    else if(Local_u16num>99)
    {
        Local_u16iter=2;
        PtrArray[3] = '.';
        while(Local_u16iter>=0)
        {
          PtrArray[Local_u16iter] = (Local_u16num%10)+ '0';
          Local_u16num = Local_u16num /10;
          Local_u16iter--;
        }
    }
}
void ConverFracToString(f32 x,u8_t*PtrArray,u8_t*index)
{
   u8_t temp1;
   u8_t temp2;
   u8_t num;
    temp1 = x ;
    x = x - temp1;
    num  = x*100;
    temp2 = num%10;
    num = num /10;
    if(temp1<10)
    {
        PtrArray[2] = num  + '0';
        PtrArray[3] = temp2 + '0';
        PtrArray[4] = '\0';
        *index = 3;
    }
    else if(temp1<100)
     {
        PtrArray[3] = num  + '0';
        PtrArray[4] = temp2 + '0';
        PtrArray[5] = '\0';
        *index = 4;
     }
    else if(temp1>99)
    {
        PtrArray[4] = num  + '0';
        PtrArray[5] = temp2 + '0';
        PtrArray[6] = '\0';
        *index = 5;
     }
}
