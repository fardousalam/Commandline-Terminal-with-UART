/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include<string.h>
#define TRUE 1
#define FALSE 0

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart2;
char *user_data = "The program is running\r\n";
uint8_t recvd_data;
uint8_t data_buffer[10];

uint32_t count=0;
int ON_Counter=0;
int OFF_Counter=0;
volatile uint8_t reception_complete = FALSE;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  //uint16_t len_of_data = strlen(user_data);
  HAL_UART_Transmit(&huart2,(uint8_t*)user_data,strlen(user_data),HAL_MAX_DELAY);

  while(reception_complete != TRUE)
        	 	          	        {


	                                    	HAL_UART_Receive_IT(&huart2,&recvd_data,1);


        	 	          	        }




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
        while (1)
        {




        }

  /* USER CODE END 3 */
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(&huart2,&recvd_data,1);
	if(recvd_data == '\r')
		 {
			 reception_complete = TRUE;
			 char *overload_buffer = "Buffer is full!\r\n";

			 //int result1,result2;
			 if(count>=10)
					 {
						 HAL_UART_Transmit(huart,(uint8_t*)overload_buffer,strlen(overload_buffer),HAL_MAX_DELAY); // "Buffer is full"

						 while (count>0)
						 {                                       //buffer wieder leer machen
							 data_buffer[count]=0;
							 count--;
						   }
					 }
					 else
					 {
						                     char str1[]="LED ON";  //Befehl f??r LED an
						 					 char str2[]="LED OFF";  //Befehl f??r LED aus
						 					 char str3[]="COUNTER ON"; //Befehl f??r Zaeler an
						 					 char str4[]="COUNTER OFF";// Befehl f??r Zaeler aus
						 					 char str5[]="COUNTER"; //Befehl f??r Zaeler
						 					 char *error_buffer = "Command is Invalid\r\n"; // ung??ltig Befehl
						 					// char *ON_buffer = "LED is ON\r\n";
						 					// char *OFF_buffer = " LED is OFF\r\n";

						 					 char LED_OFF_buffer[10];
						 					 char LED_ON_buffer[10];


						 					 if(strcmp(str1,(char*)data_buffer)==0)               //Befehl vergleichen
						 					 	{
						 					 		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET); // LED an
						 					 		ON_Counter++;
						 					 	}
						 					 else if(strcmp(str2,(char*)data_buffer)==0)   //Befehl vergleichen
						 					 	{
						 					 		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);  //LED aus
						 					 		OFF_Counter++;

						 					 	}
						 					 else if(strcmp(str3,(char*)data_buffer)==0)   //Befehl vergleichen
						 					 {

						 						 //HAL_UART_Transmit(huart,(uint8_t*)ON_buffer,strlen(error_buffer),HAL_MAX_DELAY);
						 						// HAL_UART_Transmit(huart,(uint8_t*) ON_Counter,strlen(error_buffer),HAL_MAX_DELAY);
						 						 //HAL_UART_Transmit(huart,(uint8_t*)OFF_buffer,strlen(error_buffer),HAL_MAX_DELAY);
						 						 //HAL_UART_Transmit(huart, (uint8_t*)OFF_Counter,strlen(error_buffer),HAL_MAX_DELAY);

						 						 sprintf(LED_ON_buffer,"LED is ON %d times\r\n",ON_Counter);
						 						 HAL_UART_Transmit(huart, (uint8_t*)LED_ON_buffer,strlen(LED_ON_buffer) ,HAL_MAX_DELAY);


						 					 }
						 					 else if(strcmp(str4,(char*)data_buffer)==0)   //Befehl vergleichen
						 					 {
						 						sprintf(LED_OFF_buffer,"LED is OFF %d times\r\n",OFF_Counter);
						 						HAL_UART_Transmit(huart, (uint8_t*)LED_OFF_buffer,strlen(LED_OFF_buffer),HAL_MAX_DELAY);
						 					 }

						 					 else if(strcmp(str5,(char*)data_buffer)==0)  //Befehl vergleichen
						 					 {
						 						 sprintf(LED_ON_buffer,"LED is ON %d times\r\n",ON_Counter);
						 						 HAL_UART_Transmit(huart, (uint8_t*)LED_ON_buffer,strlen(LED_ON_buffer) ,HAL_MAX_DELAY); // Zaeler daten senden
						 						 sprintf(LED_OFF_buffer,"LED is OFF %d times\r\n",OFF_Counter);
						 						 HAL_UART_Transmit(huart, (uint8_t*)LED_OFF_buffer,strlen(LED_OFF_buffer),HAL_MAX_DELAY); // Zaeler daten senden
						 					 }
						 					 else
						 					 	{
						 					 		 HAL_UART_Transmit(huart,(uint8_t*)error_buffer,strlen(error_buffer),HAL_MAX_DELAY);  //"ung??ltig Befehl" ??bertragen
						 					 	}

					 }


					 data_buffer[count++]='\r';

			 for(count=10; count>0; count--)                        //buffer leer machen


			       {

				 data_buffer[count]=0;
		           }
		     }
		 else
		 {
			 data_buffer[count++] = recvd_data;
		 }


}

int __io_putchar(int ch)
{
 uint8_t c[1];
 c[0] = ch & 0x00FF;
 HAL_UART_Transmit(&huart2, &*c, 1, 10);
 return ch;
}

int _write(int file,char *ptr, int len)
{
 int DataIdx;
 for(DataIdx= 0; DataIdx< len; DataIdx++)
 {
 __io_putchar(*ptr++);
 }
return len;
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
