/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define seg_0_Pin GPIO_PIN_0
#define seg_0_GPIO_Port GPIOB
#define seg_1_Pin GPIO_PIN_1
#define seg_1_GPIO_Port GPIOB
#define seg_2_Pin GPIO_PIN_2
#define seg_2_GPIO_Port GPIOB
#define seg_10_Pin GPIO_PIN_10
#define seg_10_GPIO_Port GPIOB
#define seg_11_Pin GPIO_PIN_11
#define seg_11_GPIO_Port GPIOB
#define seg_12_Pin GPIO_PIN_12
#define seg_12_GPIO_Port GPIOB
#define seg_13_Pin GPIO_PIN_13
#define seg_13_GPIO_Port GPIOB
#define out_1_Pin GPIO_PIN_10
#define out_1_GPIO_Port GPIOA
#define out_2_Pin GPIO_PIN_11
#define out_2_GPIO_Port GPIOA
#define out_3_Pin GPIO_PIN_12
#define out_3_GPIO_Port GPIOA
#define out_4_Pin GPIO_PIN_13
#define out_4_GPIO_Port GPIOA
#define out_5_Pin GPIO_PIN_14
#define out_5_GPIO_Port GPIOA
#define out_6_Pin GPIO_PIN_15
#define out_6_GPIO_Port GPIOA
#define seg_3_Pin GPIO_PIN_3
#define seg_3_GPIO_Port GPIOB
#define seg_4_Pin GPIO_PIN_4
#define seg_4_GPIO_Port GPIOB
#define seg_5_Pin GPIO_PIN_5
#define seg_5_GPIO_Port GPIOB
#define seg_6_Pin GPIO_PIN_6
#define seg_6_GPIO_Port GPIOB
#define seg_7_Pin GPIO_PIN_7
#define seg_7_GPIO_Port GPIOB
#define seg_8_Pin GPIO_PIN_8
#define seg_8_GPIO_Port GPIOB
#define seg_9_Pin GPIO_PIN_9
#define seg_9_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
