/*
 * pH.c
 *
 *  Created on: Apr 27, 2024
 *      Author: Menna Eid
 */


#include "pH_Interface.h"

extern ADC_HandleTypeDef hadc1;

void pH_vReadValue(uint16_t buff[] ,float*Copy_f32pHValue)
{
	  uint16_t temp =0;
	  uint16_t average;
	  uint8_t i;
	  uint8_t  j;
	  float ph_value = 0;
	  for(i=0;i<10;i++)
	  {
	     HAL_ADC_Start(&hadc1);
	     HAL_ADC_PollForConversion(&hadc1,2000);
	     buff[i] = HAL_ADC_GetValue(&hadc1);
	     HAL_ADC_Stop(&hadc1);
	     HAL_Delay(100);
	  }
	  for(i=0;i<9;i++)
	  {
	  	 for(j=i+1;j<10;j++)
	  	 {
	  	 	if(buff[i]>buff[j])
	  	 	{
	  	 		temp = buff[i];
	  	 		buff[i] = buff[j];
	  	 		buff[j] = temp;
	  	 	}
	  	 }
	  }
	   average =0;
	   for(i =2;i<8;i++)
	   {
	    	average += buff[i];
	   }
	   ph_value = (float)average*3.3/4096/6;
	   *Copy_f32pHValue = (-5.70*ph_value) + Calibration;
}
void ConvertToString(float Copy_fnum,char*PtrArray)
{
    uint16_t Local_s16iter;
    uint16_t Local_u8num;
    Local_u8num = Copy_fnum;
    if(Local_u8num<10)
    {
        PtrArray[0] = Local_u8num + '0';
        PtrArray[1] = '.';
    }
    else if(Local_u8num<100)
    {
        Local_s16iter=1;
        PtrArray[2] = '.';
        while(Local_s16iter>=0)
        {
           PtrArray[Local_s16iter] = (Local_u8num%10)+ '0';
           Local_u8num = Local_u8num /10;
            Local_s16iter--;
        }
    }

    else if(Local_u8num>99)
    {
        Local_s16iter=2;
        PtrArray[3] = '.';
        while(Local_s16iter>=0)
        {
          PtrArray[Local_s16iter] = (Local_u8num%10)+ '0';
          Local_u8num = Local_u8num /10;
          Local_s16iter--;
        }
    }
}
void ConverFracToString(float x,char*PtrArray,char*index)
{
   uint8_t temp1;
   uint8_t temp2;
   uint8_t num;
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
