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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void cau1 (){
	// LED RED IS ON
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	  HAL_Delay(200);

	  // LED GREEN IS ON
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	  HAL_Delay(200);
}
//////////////////////////////////////////////
/////////////////////////////////////////////
void cau2(){
	// LED RED IS ON
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_Delay(500);

	// LED YELLOW IS ON
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_Delay(200);

	// LED GREEN IS ON
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_Delay(300);
}
//////////////////////////////////////////////
/////////////////////////////////////////////
void cau3(int status){
	switch (status) {
		case 0: // RED - GREEN - col
			HAL_GPIO_WritePin(GPIOA, out_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_5_Pin, GPIO_PIN_SET);

			HAL_GPIO_WritePin(GPIOA, out_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, out_6_Pin, GPIO_PIN_RESET);
			break;
		case 1: // RED - YELLOW - row
			HAL_GPIO_WritePin(GPIOA, out_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_6_Pin, GPIO_PIN_SET);

			HAL_GPIO_WritePin(GPIOA, out_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, out_5_Pin, GPIO_PIN_RESET);
			break;
		case 2: // RED - GREEN - row
			HAL_GPIO_WritePin(GPIOA, out_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_6_Pin, GPIO_PIN_SET);

			HAL_GPIO_WritePin(GPIOA, out_4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, out_3_Pin, GPIO_PIN_RESET);
			break;
		case 3: // RED - YELLOW - col
			HAL_GPIO_WritePin(GPIOA, out_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_5_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, out_6_Pin, GPIO_PIN_SET);

			HAL_GPIO_WritePin(GPIOA, out_4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, out_2_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}
}
//////////////////////////////////////////////
/////////////////////////////////////////////
uint8_t segNumber[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};

void display7SEG_1(uint8_t val){
	HAL_GPIO_WritePin(GPIOB, seg_0_Pin, ((val>>0)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_1_Pin, ((val>>1)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_2_Pin, ((val>>2)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_3_Pin, ((val>>3)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_4_Pin, ((val>>4)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_5_Pin, ((val>>5)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_6_Pin, ((val>>6)&0x01));
}

void cau4(int count){
	display7SEG_1(segNumber[count]);
	HAL_Delay(200);
}

void display7SEG_2(uint8_t number){
	HAL_GPIO_WritePin(GPIOB, seg_7_Pin, ((number>>0)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_8_Pin, ((number>>1)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_9_Pin, ((number>>2)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_10_Pin, ((number>>3)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_11_Pin, ((number>>4)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_12_Pin, ((number>>5)&0x01));
	HAL_GPIO_WritePin(GPIOB, seg_13_Pin, ((number>>6)&0x01));
}

void cau5(int count){
	switch (count) {
		case 0:
			count = 1;
			display7SEG_2(segNumber[5]);
			display7SEG_1(segNumber[3]);
			cau3(0);
			HAL_Delay(200);

			display7SEG_2(segNumber[4]);
			display7SEG_1(segNumber[2]);
			HAL_Delay(200);

			display7SEG_2(segNumber[3]);
			display7SEG_1(segNumber[1]);
			HAL_Delay(200);

			display7SEG_2(segNumber[2]);
			display7SEG_1(segNumber[0]);
			HAL_Delay(200);

			display7SEG_2(segNumber[1]);
			display7SEG_1(segNumber[1]);
			cau3(1);
			HAL_Delay(200);

			display7SEG_2(segNumber[0]);
			display7SEG_1(segNumber[0]);
			HAL_Delay(200);

			break;
		case 1:
			count = 0;
			display7SEG_1(segNumber[5]);
			display7SEG_2(segNumber[3]);
			cau3(2);
			HAL_Delay(200);

			display7SEG_1(segNumber[4]);
			display7SEG_2(segNumber[2]);
			HAL_Delay(200);

			display7SEG_1(segNumber[3]);
			display7SEG_2(segNumber[1]);
			HAL_Delay(200);

			display7SEG_1(segNumber[2]);
			display7SEG_2(segNumber[0]);
			HAL_Delay(200);

			display7SEG_1(segNumber[1]);
			display7SEG_2(segNumber[1]);
			cau3(3);
			HAL_Delay(200);

			display7SEG_1(segNumber[0]);
			display7SEG_2(segNumber[0]);
			HAL_Delay(200);

			break;
		default :
			break;
	}
}

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  int count = 0;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  cau1();

//	  cau2();

//	  if(count == 4) count = 0;
//	  cau3();
//	  count ++;

//	  if(count == 10) count = 0;
//	  cau4(count);
//	  count ++;

//	  if(count == 2) count = 0;
//	  cau5(count);
//	  count ++;

	  for(int i = 9; i >= 0; i--){
		  display7SEG_2(segNumber[i]);
		  if (i-6 >= 0)
			  display7SEG_1(segNumber[i-6]);
		  else
			  display7SEG_1(segNumber[i]);
		  HAL_Delay(1000);
	  }

	  for(int i = 9; i >= 0; i--){
		  display7SEG_1(segNumber[i]);
		  if (i-6 >= 0)
			  display7SEG_2(segNumber[i-6]);
		  else
			  display7SEG_2(segNumber[i]);
		  HAL_Delay(1000);
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|out_1_Pin
                          |out_2_Pin|out_3_Pin|out_4_Pin|out_5_Pin
                          |out_6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, seg_0_Pin|seg_1_Pin|seg_2_Pin|seg_10_Pin
                          |seg_11_Pin|seg_12_Pin|seg_13_Pin|seg_3_Pin
                          |seg_4_Pin|seg_5_Pin|seg_6_Pin|seg_7_Pin
                          |seg_8_Pin|seg_9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA5 PA6 PA7 out_1_Pin
                           out_2_Pin out_3_Pin out_4_Pin out_5_Pin
                           out_6_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|out_1_Pin
                          |out_2_Pin|out_3_Pin|out_4_Pin|out_5_Pin
                          |out_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : seg_0_Pin seg_1_Pin seg_2_Pin seg_10_Pin
                           seg_11_Pin seg_12_Pin seg_13_Pin seg_3_Pin
                           seg_4_Pin seg_5_Pin seg_6_Pin seg_7_Pin
                           seg_8_Pin seg_9_Pin */
  GPIO_InitStruct.Pin = seg_0_Pin|seg_1_Pin|seg_2_Pin|seg_10_Pin
                          |seg_11_Pin|seg_12_Pin|seg_13_Pin|seg_3_Pin
                          |seg_4_Pin|seg_5_Pin|seg_6_Pin|seg_7_Pin
                          |seg_8_Pin|seg_9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
