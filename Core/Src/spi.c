/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    spi.c
 * @brief   This file provides code for the configuration
 *          of the SPI instances.
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
#include "spi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi4;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

/* SPI1 init function */
void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */
	// wifi spi
	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;  //30mhz clock
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 0x0;
	hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi1.Init.TxCRCInitializationPattern =
	SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi1.Init.RxCRCInitializationPattern =
	SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}
/* SPI2 init function */
void MX_SPI2_Init(void) {

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 0x0;
	hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	hspi2.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi2.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi2.Init.TxCRCInitializationPattern =
	SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi2.Init.RxCRCInitializationPattern =
	SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi2.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	hspi2.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	hspi2.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	hspi2.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi2.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	if (HAL_SPI_Init(&hspi2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI2_Init 2 */

	/* USER CODE END SPI2_Init 2 */

}
/* SPI4 init function */
void MX_SPI4_Init(void) {

	/* USER CODE BEGIN SPI4_Init 0 */

	/* USER CODE END SPI4_Init 0 */

	/* USER CODE BEGIN SPI4_Init 1 */

	/* USER CODE END SPI4_Init 1 */
	hspi4.Instance = SPI4;
	hspi4.Init.Mode = SPI_MODE_MASTER;
	hspi4.Init.Direction = SPI_DIRECTION_1LINE;
	hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi4.Init.NSS = SPI_NSS_SOFT;
	hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi4.Init.CRCPolynomial = 0x0;
	hspi4.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	hspi4.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi4.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi4.Init.TxCRCInitializationPattern =
	SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi4.Init.RxCRCInitializationPattern =
	SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi4.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	hspi4.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	hspi4.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	hspi4.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi4.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	if (HAL_SPI_Init(&hspi4) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI4_Init 2 */

	/* USER CODE END SPI4_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };
	if (spiHandle->Instance == SPI1) {
		/* USER CODE BEGIN SPI1_MspInit 0 */

		/* USER CODE END SPI1_MspInit 0 */

		/** Initializes the peripherals clock
		 */
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI1;
		PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
			Error_Handler();
		}

		/* SPI1 clock enable */
		__HAL_RCC_SPI1_CLK_ENABLE();

		__HAL_RCC_GPIOD_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**SPI1 GPIO Configuration
		 PD7     ------> SPI1_MOSI
		 PB3 (JTDO/TRACESWO)     ------> SPI1_SCK
		 PB4 (NJTRST)     ------> SPI1_MISO
		 */
		GPIO_InitStruct.Pin = FSPI_MOSI_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(FSPI_MOSI_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = FSPI_SCK_Pin | FSPI_MISO_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI1_MspInit 1 */
		hdma_spi1_rx.Instance = DMA1_Stream1;
		hdma_spi1_rx.Init.Request = DMA_REQUEST_SPI1_RX;
		hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_spi1_rx.Init.Mode = DMA_NORMAL;
		hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_spi1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK) {
			Error_Handler();
		}

		__HAL_LINKDMA(spiHandle, hdmarx, hdma_spi1_rx);

		/* SPI1_TX Init */
		hdma_spi1_tx.Instance = DMA1_Stream2;
		hdma_spi1_tx.Init.Request = DMA_REQUEST_SPI1_TX;
		hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_spi1_tx.Init.Mode = DMA_NORMAL;
		hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK) {
			Error_Handler();
		}

		__HAL_LINKDMA(spiHandle, hdmatx, hdma_spi1_tx);

		// spi1 interrupt
		HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(SPI1_IRQn);

		/* USER CODE END SPI1_MspInit 1 */
	} else if (spiHandle->Instance == SPI2) {
		/* USER CODE BEGIN SPI2_MspInit 0 */

		/* USER CODE END SPI2_MspInit 0 */

		/** Initializes the peripherals clock
		 */
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI2;
		PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
			Error_Handler();
		}

		/* SPI2 clock enable */
		__HAL_RCC_SPI2_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**SPI2 GPIO Configuration
		 PB13     ------> SPI2_SCK
		 PB14     ------> SPI2_MISO
		 PB15     ------> SPI2_MOSI
		 */
		GPIO_InitStruct.Pin = WIFI_CLK_Pin | WIFI_MISO_Pin | WIFI_MOSI_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI2_MspInit 1 */

		/* USER CODE END SPI2_MspInit 1 */
	} else if (spiHandle->Instance == SPI4) {
		/* USER CODE BEGIN SPI4_MspInit 0 */

		/* USER CODE END SPI4_MspInit 0 */

		/** Initializes the peripherals clock
		 */
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI4;
		PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
			Error_Handler();
		}

		/* SPI4 clock enable */
		__HAL_RCC_SPI4_CLK_ENABLE();

		__HAL_RCC_GPIOE_CLK_ENABLE();
		/**SPI4 GPIO Configuration
		 PE12     ------> SPI4_SCK
		 PE14     ------> SPI4_MOSI
		 */
		GPIO_InitStruct.Pin = LCD_SCK_Pin | LCD_MOSI_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI4_MspInit 1 */

		/* USER CODE END SPI4_MspInit 1 */
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spiHandle) {

	if (spiHandle->Instance == SPI1) {
		/* USER CODE BEGIN SPI1_MspDeInit 0 */

		/* USER CODE END SPI1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI1_CLK_DISABLE();

		/**SPI1 GPIO Configuration
		 PD7     ------> SPI1_MOSI
		 PB3 (JTDO/TRACESWO)     ------> SPI1_SCK
		 PB4 (NJTRST)     ------> SPI1_MISO
		 */
		HAL_GPIO_DeInit(FSPI_MOSI_GPIO_Port, FSPI_MOSI_Pin);

		HAL_GPIO_DeInit(GPIOB, FSPI_SCK_Pin | FSPI_MISO_Pin);

		/* USER CODE BEGIN SPI1_MspDeInit 1 */

		/* USER CODE END SPI1_MspDeInit 1 */
	} else if (spiHandle->Instance == SPI2) {
		/* USER CODE BEGIN SPI2_MspDeInit 0 */

		/* USER CODE END SPI2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI2_CLK_DISABLE();

		/**SPI2 GPIO Configuration
		 PB13     ------> SPI2_SCK
		 PB14     ------> SPI2_MISO
		 PB15     ------> SPI2_MOSI
		 */
		HAL_GPIO_DeInit(GPIOB, WIFI_CLK_Pin | WIFI_MISO_Pin | WIFI_MOSI_Pin);

		/* USER CODE BEGIN SPI2_MspDeInit 1 */

		/* USER CODE END SPI2_MspDeInit 1 */
	} else if (spiHandle->Instance == SPI4) {
		/* USER CODE BEGIN SPI4_MspDeInit 0 */

		/* USER CODE END SPI4_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI4_CLK_DISABLE();

		/**SPI4 GPIO Configuration
		 PE12     ------> SPI4_SCK
		 PE14     ------> SPI4_MOSI
		 */
		HAL_GPIO_DeInit(GPIOE, LCD_SCK_Pin | LCD_MOSI_Pin);

		/* USER CODE BEGIN SPI4_MspDeInit 1 */

		/* USER CODE END SPI4_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
