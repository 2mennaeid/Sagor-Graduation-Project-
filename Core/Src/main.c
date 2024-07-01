/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "MCAL_Init.h"
#include "pH_Interface.h"

uint16_t App_ph_samples[10];
unsigned char App_index;
char App_temp_str[7];
float App_temp;

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();

  while (1)
  {
	  pH_vReadValue(App_ph_samples,&App_temp);
	  ConvertToString(App_temp,&App_temp_str);
	  ConverFracToString(App_temp,&App_temp_str,&App_index);
	  UART_vTransimt(&App_temp_str,App_index);
	  HAL_Delay(7000);
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
