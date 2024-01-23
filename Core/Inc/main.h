/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32l4xx_hal.h"

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
void cppMain(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCDD6_Pin GPIO_PIN_13
#define LCDD6_GPIO_Port GPIOC
#define LCDD5_Pin GPIO_PIN_14
#define LCDD5_GPIO_Port GPIOC
#define LCDD4_Pin GPIO_PIN_15
#define LCDD4_GPIO_Port GPIOC
#define LCDD3_Pin GPIO_PIN_0
#define LCDD3_GPIO_Port GPIOC
#define LCDD2_Pin GPIO_PIN_1
#define LCDD2_GPIO_Port GPIOC
#define LCDD1_Pin GPIO_PIN_2
#define LCDD1_GPIO_Port GPIOC
#define LCDD0_Pin GPIO_PIN_3
#define LCDD0_GPIO_Port GPIOC
#define RELAY2_Pin GPIO_PIN_1
#define RELAY2_GPIO_Port GPIOA
#define LCDRS_Pin GPIO_PIN_4
#define LCDRS_GPIO_Port GPIOA
#define RELAY3_Pin GPIO_PIN_4
#define RELAY3_GPIO_Port GPIOC
#define RELAY4_Pin GPIO_PIN_5
#define RELAY4_GPIO_Port GPIOC
#define _W25QXX_CS_PIN_Pin GPIO_PIN_0
#define _W25QXX_CS_PIN_GPIO_Port GPIOB
#define WIFIRST_Pin GPIO_PIN_2
#define WIFIRST_GPIO_Port GPIOB
#define W5500_CS_Pin GPIO_PIN_12
#define W5500_CS_GPIO_Port GPIOB
#define W5500_INT_Pin GPIO_PIN_6
#define W5500_INT_GPIO_Port GPIOC
#define W5500RST_Pin GPIO_PIN_7
#define W5500RST_GPIO_Port GPIOC
#define InputMachine1_Pin GPIO_PIN_8
#define InputMachine1_GPIO_Port GPIOC
#define InputMachine2_Pin GPIO_PIN_9
#define InputMachine2_GPIO_Port GPIOC
#define InputMachine3_Pin GPIO_PIN_8
#define InputMachine3_GPIO_Port GPIOA
#define InputMachine4_Pin GPIO_PIN_9
#define InputMachine4_GPIO_Port GPIOA
#define InputMachine5_Pin GPIO_PIN_10
#define InputMachine5_GPIO_Port GPIOA
#define InputMachine6_Pin GPIO_PIN_11
#define InputMachine6_GPIO_Port GPIOA
#define InputMachine_Pin GPIO_PIN_12
#define InputMachine_GPIO_Port GPIOA
#define GLCDEN_Pin GPIO_PIN_10
#define GLCDEN_GPIO_Port GPIOC
#define GLCDCS2_Pin GPIO_PIN_11
#define GLCDCS2_GPIO_Port GPIOC
#define GLCDRW_Pin GPIO_PIN_12
#define GLCDRW_GPIO_Port GPIOC
#define GLCDCS1_Pin GPIO_PIN_2
#define GLCDCS1_GPIO_Port GPIOD
#define LCDD7_Pin GPIO_PIN_5
#define LCDD7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
