/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    gpio.c
 * @brief   This file provides code for the configuration
 *          of all used GPIO pins.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "stdbool.h"
#include "spi_drv.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
bool wifdataready = false;
bool wifihandshake = false;
/* USER CODE END 1 */

/** Configure pins
 PC14-OSC32_IN (OSC32_IN)   ------> RCC_OSC32_IN
 PC15-OSC32_OUT (OSC32_OUT)   ------> RCC_OSC32_OUT
 PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
 PH1-OSC_OUT (PH1)   ------> RCC_OSC_OUT
 PA13 (JTMS/SWDIO)   ------> DEBUG_JTMS-SWDIO
 PA14 (JTCK/SWCLK)   ------> DEBUG_JTCK-SWCLK
 */
void MX_GPIO_Init(void) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, LCD_CS_Pin | LCD_WR_RS_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(WIFI_RESET_GPIO_Port, WIFI_RESET_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(FSPI_CS_GPIO_Port, FSPI_CS_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : LED1_Pin */
	GPIO_InitStruct.Pin = LED1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : KEY_Pin */
	GPIO_InitStruct.Pin = KEY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LCD_CS_Pin LCD_WR_RS_Pin */
	GPIO_InitStruct.Pin = LCD_CS_Pin | LCD_WR_RS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pin : WIFI_RESET_Pin */
	GPIO_InitStruct.Pin = WIFI_RESET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(WIFI_RESET_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = WIFI_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(WIFI_CS_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : WIFI_HANDSHAKE_Pin WIFI_DATA_READY_Pin */
	GPIO_InitStruct.Pin = WIFI_HANDSHAKE_Pin | WIFI_DATA_READY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = SDMMC_DETECT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(SDMMC_DETECT_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = CAMERA_XCLK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
	HAL_GPIO_Init(CAMERA_XCLK_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : FSPI_CS_Pin */
	GPIO_InitStruct.Pin = FSPI_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(FSPI_CS_GPIO_Port, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	sdpresent = (HAL_GPIO_ReadPin(SDMMC_DETECT_GPIO_Port, SDMMC_DETECT_Pin)
			== GPIO_PIN_SET);
}

/* USER CODE BEGIN 2 */
void SDMMC_Detect_Callback(uint16_t GPIO_Pin) {

	sdpresent = (HAL_GPIO_ReadPin(SDMMC_DETECT_GPIO_Port, SDMMC_DETECT_Pin)
			== GPIO_PIN_SET);
	// if we have an msc callback call it

}

void WIFI_Data_Ready_Callback(uint16_t GPIO_Pin) {

	wifdataready = (HAL_GPIO_ReadPin(WIFI_DATA_READY_GPIO_Port,
			WIFI_DATA_READY_Pin) == GPIO_PIN_RESET);
	wifi_gpio_extint_callback(GPIO_Pin);
	// if we have an msc callback call it

}

void WIFI_Handshake_Callback(uint16_t GPIO_Pin) {

	wifihandshake = (HAL_GPIO_ReadPin(WIFI_HANDSHAKE_GPIO_Port,
			WIFI_HANDSHAKE_Pin) == GPIO_PIN_RESET);
	wifi_gpio_extint_callback(GPIO_Pin);
	// if we have an msc callback call it

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == SDMMC_DETECT_Pin) {
		SDMMC_Detect_Callback(GPIO_Pin);
	}

	if (GPIO_Pin == WIFI_DATA_READY_Pin) {
		WIFI_Data_Ready_Callback(GPIO_Pin);
	}

	if (GPIO_Pin == WIFI_HANDSHAKE_Pin) {
		WIFI_Handshake_Callback(GPIO_Pin);
	}
}
/* USER CODE END 2 */
