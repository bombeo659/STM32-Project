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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t segNumber[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};

void display7SEG(int num){
	uint8_t val = segNumber[num];
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, ((val>>0)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, ((val>>1)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, ((val>>2)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, ((val>>3)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, ((val>>4)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, ((val>>5)&0x01));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, ((val>>6)&0x01));
}

int led_buffer [4] = {1 , 2 , 3 , 4};
void update7SEG(int index){
	switch(index){
		case 0:
			// Display the first 7 SEG with led_buffer [0]
			display7SEG(led_buffer[index]);
			break ;
		case 1:
			// Display the second 7 SEG with led_buffer [1]
			display7SEG(led_buffer[index]);
			break ;
		case 2:
			// Display the third 7 SEG with led_buffer [2]
			display7SEG(led_buffer[index]);
			break ;
		case 3:
			// Display the fourth 7 SEG with led_buffer [3]
			display7SEG(led_buffer[index]);
			break ;
		default:
			break ;
	}
}

void updateClockBuffer(int hour, int minute){
	if(hour > 9){
		led_buffer[1] = hour%10;
		led_buffer[0] = hour/10;
	}
	else{
		led_buffer[1] = hour;
		led_buffer[0] = 0;
	}
	if(minute > 9){
		led_buffer[3] = minute%10;
		led_buffer[2] = minute/10;
	}
	else{
		led_buffer[3] = minute;
		led_buffer[2] = 0;
	}
}

int TIMER_CYCLE = 10;

int timer0_counter0 = 0;
int timer0_flag0 = 0;

int timer0_counter1 = 0;
int timer0_flag1 = 0;

int timer0_counter2 = 0;
int timer0_flag2 = 0;

void setTimer0 (int duration){
	timer0_counter0 = duration/TIMER_CYCLE;
	timer0_flag0 = 0;
}
void setTimer1 (int duration){
	timer0_counter1 = duration/TIMER_CYCLE;
	timer0_flag1 = 0;
}

void setTimer2 (int duration){
	timer0_counter2 = duration/TIMER_CYCLE;
	timer0_flag2 = 0;
}

void timer_run0(){
	if(timer0_counter0 > 0){
		timer0_counter0 --;
		if( timer0_counter0 == 0)
			timer0_flag0 = 1;
	}

	if(timer0_counter1 > 0){
		timer0_counter1 --;
		if( timer0_counter1 == 0)
			timer0_flag1 = 1;
	}

	if(timer0_counter2 > 0){
		timer0_counter2 --;
		if( timer0_counter2 == 0)
			timer0_flag2 = 1;
	}
}


void displayRow(uint8_t number){
	HAL_GPIO_WritePin(GPIOB, ROW0_Pin, ((number>>0)&0x01));
	HAL_GPIO_WritePin(GPIOB, ROW1_Pin, ((number>>1)&0x01));
	HAL_GPIO_WritePin(GPIOB, ROW2_Pin, ((number>>2)&0x01));
	HAL_GPIO_WritePin(GPIOB, ROW3_Pin, ((number>>3)&0x01));
	HAL_GPIO_WritePin(GPIOB, ROW4_Pin, ((number>>4)&0x01));
	HAL_GPIO_WritePin(GPIOB, ROW5_Pin, ((number>>5)&0x01));
	HAL_GPIO_WritePin(GPIOB, ROW6_Pin, ((number>>6)&0x01));
	HAL_GPIO_WritePin(GPIOB, ROW7_Pin, ((number>>7)&0x01));
}

void displayCol(uint8_t number){
	HAL_GPIO_WritePin(GPIOA, ENM0_Pin, ((number>>0)&0x01));
	HAL_GPIO_WritePin(GPIOA, ENM1_Pin, ((number>>1)&0x01));
	HAL_GPIO_WritePin(GPIOA, ENM2_Pin, ((number>>2)&0x01));
	HAL_GPIO_WritePin(GPIOA, ENM3_Pin, ((number>>3)&0x01));
	HAL_GPIO_WritePin(GPIOA, ENM4_Pin, ((number>>4)&0x01));
	HAL_GPIO_WritePin(GPIOA, ENM5_Pin, ((number>>5)&0x01));
	HAL_GPIO_WritePin(GPIOA, ENM6_Pin, ((number>>6)&0x01));
	HAL_GPIO_WritePin(GPIOA, ENM7_Pin, ((number>>7)&0x01));
}
void displayMatrix(uint8_t row, uint8_t col){
	displayRow(row);
	displayCol(col);
}
uint8_t matrix_row[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uint8_t matrix_col[8] = {0xc3,0x81,0x99,0x99,0x81,0x81,0x99,0x99}; //A
uint8_t matrix [8][8] = {{0xc3,0x81,0x99,0x99,0x81,0x81,0x99,0x99},
						{0xe1,0xc0,0xcc,0xcc,0xc0,0xc0,0xcc,0xcc},
						{0xf0,0x60,0x66,0x66,0x60,0x60,0x66,0x66},
						{0x78,0x30,0x33,0x33,0x30,0x30,0x33,0x33},
						{0x3c,0x18,0x99,0x99,0x18,0x18,0x99,0x99},
						{0x1e,0x0c,0xcc,0xcc,0x0c,0x0c,0xcc,0xcc},
						{0x0f,0x06,0x66,0x66,0x06,0x06,0x66,0x66},
						{0x87,0x03,0x33,0x33,0x03,0x03,0x33,0x33}};

uint8_t row = 0xff;
uint8_t col = 0x00;
void updateLEDMatrix (int index, uint8_t col_val[]){
	switch(index){
	case 0:
		row = matrix_row[index];
		col = col_val[index];
		break;
	case 1:
		row = matrix_row[index];
		col = col_val[index];
		break;
	case 2:
		row = matrix_row[index];
		col = col_val[index];
		break;
	case 3:
		row = matrix_row[index];
		col = col_val[index];
		break;
	case 4:
		row = matrix_row[index];
		col = col_val[index];
		break;
	case 5:
		row = matrix_row[index];
		col = col_val[index];
		break;
	case 6:
		row = matrix_row[index];
		col = col_val[index];
		break;
	case 7:
		row = matrix_row[index];
		col = col_val[index];
		break;
	case 8:
		row = 0xff;
		col = 0x00;
		break;
	default :
		break ;
	}
}
uint8_t shiftData(uint8_t data, int shiftBit){
	uint8_t result = data;
	for(int i = 1; i <= shiftBit; i+=1){
		result = result<<1;
		uint8_t temp = (data>>(8-i))&0x01;
		result += temp;
	}
	return result;
}
uint8_t *updateStatus(int status, uint8_t col[])
{
  static uint8_t result[8];
  if(status == 0) return col;
  else{
    for(int i = 0; i < 8; i++){
      result[i] = shiftData(col[i], status);
    }
    return result;
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);

  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                            |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                            |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                            |ENM6_Pin|ENM7_Pin, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int hour = 15 , minute = 8 , second = 50;
  setTimer0(1000);
  setTimer1(250);
  setTimer2(10);
  int select7SEG = 0;
  int selectMatrixRow = 0;
  int selectMatrixStatus = 0;
  int count = 0;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(timer0_flag0 == 1){
		  setTimer0(1000);

		  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		  HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);

		  if(second >= 60){
			  second = 0;
			  minute ++;
		  }
		  if(minute >= 60){
			  minute = 0;
			  hour ++;
		  }
		  if(hour >= 24){
			  hour = 0;
		  }
		  updateClockBuffer(hour, minute);
		  second ++;


	  }
	  if(timer0_flag1 == 1){
		  setTimer1(250);
		  switch (select7SEG){
			  case 0:
					HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
					update7SEG(select7SEG);
					select7SEG = 1;
					break;
			  case 1:
					HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
					update7SEG(select7SEG);
					select7SEG = 2;
					break;
			  case 2:
					HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
					update7SEG(select7SEG);
					select7SEG = 3;
					break;
			  case 3:
					HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
					update7SEG(select7SEG);
					select7SEG = 0;
					break;
		  }
	  }

//	  if(timer0_flag2 == 1){
//		  setTimer2(100);
//		  if(selectMatrixRow >= 9) selectMatrixRow = 0;
//
//		  updateLEDMatrix(selectMatrixRow, matrix_col);
//
//		  displayMatrix(row, col);
//
//		  selectMatrixRow ++;
//	  }

	  if(timer0_flag2 == 1){
		  setTimer2(10);
		  if(selectMatrixRow >= 9){
			  selectMatrixRow = 0;
			  count ++;
			  if(count == 5){
				  selectMatrixStatus ++;
				  count = 0;
			  }
			  if(selectMatrixStatus >= 8) selectMatrixStatus = 0;
		  }
		  updateLEDMatrix(selectMatrixRow, updateStatus(selectMatrixStatus, matrix_col));
		  displayMatrix(row, col);
		  selectMatrixRow ++;
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8000-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin PB3 PB4 PB5
                           PB6 ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/*int counter = 200;
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim){
	counter --;
	if(counter == 150){
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
		update7SEG(0);
	}
	if(counter == 100){
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
		update7SEG(1);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
	}
	if(counter == 50){
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
		update7SEG(2);
	}
	if(counter <= 0){
		counter = 200;
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
		update7SEG(3);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
	}
}*/
/*int counter = 100;
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim){
	timer_run0();
	counter --;
	if(counter == 75){
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
		update7SEG(0);
	}
	if(counter == 50){
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
		update7SEG(1);
	}
	if(counter == 25){
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
		update7SEG(2);
	}
	if(counter <= 0){
		counter = 100;
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
		update7SEG(3);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
	}
}*/
//--------------//
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim){
	timer_run0();
}
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
