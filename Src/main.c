/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define BLINK_GPIO_PORT              GPIOB
#define BLINK_GPIO_PINS              (GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15)
#define BLINK_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_GpioConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();

  /* Initialize GPIO */
  APP_GpioConfig();

  while (1)
  {
    /* Delay 500ms */
    HAL_Delay(500);

    /* Toggle PB11, PB12, PB13, PB14, PB15, PA8 */
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
  }
}

/**
  * @brief  GPIO configuration for PB11–PB15 and PA8 blink.
  * @param  None
  * @retval None
  */
static void APP_GpioConfig(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

  /* ---- GPIOB: PB11, PB12, PB13, PB14, PB15 ---- */
  BLINK_GPIO_CLK_ENABLE();                               /* Enable GPIOB clock */

  GPIO_InitStruct.Pin   = BLINK_GPIO_PINS;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;           /* Push-pull output */
  GPIO_InitStruct.Pull  = GPIO_NOPULL;                   /* No pull */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO speed */
  HAL_GPIO_Init(BLINK_GPIO_PORT, &GPIO_InitStruct);

  /* PB11-PB14 start HIGH (opposite phase), PB15 starts LOW */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 , GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15 | GPIO_PIN_14, GPIO_PIN_RESET);

  /* ---- GPIOA: PA8 ---- */
  __HAL_RCC_GPIOA_CLK_ENABLE();                         /* Enable GPIOA clock */

  GPIO_InitStruct.Pin   = GPIO_PIN_8;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;           /* Push-pull output */
  GPIO_InitStruct.Pull  = GPIO_NOPULL;                   /* No pull */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* GPIO speed */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}

/**
  * @brief  Error executing function.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  while (1)
  {
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
  /* Users can add their own printing information as needed,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
