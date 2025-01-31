/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stdbool.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct {
	uint32_t x;
	uint32_t y;
	uint8_t len;
	char str[50];
} disp_data_t;

typedef struct{
	uint16_t id;
	uint8_t type;
	uint16_t fps;
} camera_t;

/* USER CODE END ET */
#define QUEUE_SIZE         (uint32_t) 10
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
#define QSPI_IO2_Pin GPIO_PIN_2
#define QSPI_IO2_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_3
#define LED1_GPIO_Port GPIOE
#define KEY_Pin GPIO_PIN_13
#define KEY_GPIO_Port GPIOC
#define ADC3_CH10_Pin GPIO_PIN_0
#define ADC3_CH10_GPIO_Port GPIOC
#define ADC3_CH11_Pin GPIO_PIN_1
#define ADC3_CH11_GPIO_Port GPIOC
#define ADC3_CH0_Pin GPIO_PIN_2
#define ADC3_CH0_GPIO_Port GPIOC
#define ADC3_CH1_Pin GPIO_PIN_3
#define ADC3_CH1_GPIO_Port GPIOC
#define PWM_CH1_Pin GPIO_PIN_0
#define PWM_CH1_GPIO_Port GPIOA
#define PWM_CH2_Pin GPIO_PIN_1
#define PWM_CH2_GPIO_Port GPIOA
#define PWM_CH3_Pin GPIO_PIN_2
#define PWM_CH3_GPIO_Port GPIOA
#define PWM_CH4_Pin GPIO_PIN_3
#define PWM_CH4_GPIO_Port GPIOA
#define QSPI_CLK_Pin GPIO_PIN_2
#define QSPI_CLK_GPIO_Port GPIOB
#define LCD_BL_Pin GPIO_PIN_10
#define LCD_BL_GPIO_Port GPIOE
#define LCD_CS_Pin GPIO_PIN_11
#define LCD_CS_GPIO_Port GPIOE
#define LCD_SCK_Pin GPIO_PIN_12
#define LCD_SCK_GPIO_Port GPIOE
#define LCD_WR_RS_Pin GPIO_PIN_13
#define LCD_WR_RS_GPIO_Port GPIOE
#define LCD_MOSI_Pin GPIO_PIN_14
#define LCD_MOSI_GPIO_Port GPIOE
#define SDMMC_DETECT_Pin GPIO_PIN_4
#define SDMMC_DETECT_GPIO_Port GPIOD
#define WIFI_RESET_Pin GPIO_PIN_10
#define WIFI_RESET_GPIO_Port GPIOD
#define WIFI_CS_Pin GPIO_PIN_12
#define WIFI_CS_GPIO_Port GPIOB
#define WIFI_CLK_Pin GPIO_PIN_13
#define WIFI_CLK_GPIO_Port GPIOB
#define WIFI_MISO_Pin GPIO_PIN_14
#define WIFI_MISO_GPIO_Port GPIOB
#define WIFI_MOSI_Pin GPIO_PIN_15
#define WIFI_MOSI_GPIO_Port GPIOB
#define WIFI_HANDSHAKE_Pin GPIO_PIN_8
#define WIFI_HANDSHAKE_GPIO_Port GPIOD
#define WIFI_DATA_READY_Pin GPIO_PIN_9
#define WIFI_DATA_READY_GPIO_Port GPIOD
#define QSPI_IO0_Pin GPIO_PIN_11
#define QSPI_IO0_GPIO_Port GPIOD
#define QSPI_IO1_Pin GPIO_PIN_12
#define QSPI_IO1_GPIO_Port GPIOD
#define QSPI_IO3_Pin GPIO_PIN_13
#define QSPI_IO3_GPIO_Port GPIOD
#define FSPI_CS_Pin GPIO_PIN_6
#define FSPI_CS_GPIO_Port GPIOD
#define FSPI_MOSI_Pin GPIO_PIN_7
#define FSPI_MOSI_GPIO_Port GPIOD
#define FSPI_SCK_Pin GPIO_PIN_3
#define FSPI_SCK_GPIO_Port GPIOB
#define FSPI_MISO_Pin GPIO_PIN_4
#define FSPI_MISO_GPIO_Port GPIOB
#define QSPI_NCS_Pin GPIO_PIN_6
#define QSPI_NCS_GPIO_Port GPIOB
#define CAMERA_SCL_Pin GPIO_PIN_8
#define CAMERA_SCL_GPIO_Port GPIOB
#define CAMERA_SDA_Pin GPIO_PIN_9
#define CAMERA_SDA_GPIO_Port GPIOB
#define CAMERA_XCLK_Pin GPIO_PIN_8
#define CAMERA_XCLK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
extern uint32_t st7735_id;
extern osMutexId SDMutexHandle;
extern osMessageQId displayQueueHandle;
extern osMessageQId cameraQueueHandle;
extern bool sdpresent;
extern SPI_HandleTypeDef hspi2; //wifi spi
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
