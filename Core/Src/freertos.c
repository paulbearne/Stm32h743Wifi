/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include <consoletask.h>
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tusb.h"
#include "tusb_config.h"
#include "adc.h"
#include "ff.h"
#include "fatfs.h"
#include "wifi.h"
#include "cameratask.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
enum {
	BLINK_NOT_MOUNTED = 250, BLINK_MOUNTED = 1000, BLINK_SUSPENDED = 2500,
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define Avg_Slope (2) // mV/¡ãC

#define USBD_STACK_SIZE   16384 // (3*configMINIMAL_STACK_SIZE/2) * (CFG_TUSB_DEBUG ? 2 : 1)
#define CDC_STACK_SIZE      8192
#define BLINKY_STACK_SIZE   configMINIMAL_STACK_SIZE
#define DISPLAY_STACK_SIZE 8192
#define DEFAULT_STACK_SIZE 1024
#define ADC_STACK_SIZE 1024
#define CAMERA_STACK_SIZE 4096
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId DEFAULTTASKHandle;
osThreadId USBTASKHandle;
osThreadId LEDTASKHandle;
osThreadId ADCTASKHandle;
osThreadId DISPLAYTASKHandle;
osThreadId CDCTASKHandle;
osThreadId CAMERATASKHandle;
osMessageQId displayQueueHandle;
osMessageQId ledQueueHandle;
osMessageQId usbQueueHandle;
osMessageQId adcQueueHandle;
osMessageQId cameraQueueHandle = NULL;
osMessageQId SDQueueID = NULL;
osMutexId SDMutexHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void startDefaultTask(void const *argument);
void startUsbTask(void const *argument);
void startLedTask(void const *argument);
void startAdcTask(void const *argument);
void startDisplayTask(void const *argument);
void startCdcTask(void const *argument);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	/* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */
	/* Create the mutex(es) */
	/* definition and creation of SDMutex */
	osMutexDef(SDMutex);
	SDMutexHandle = osMutexCreate(osMutex(SDMutex));

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* Create the queue(s) */
	/* definition and creation of displayQueue */
	osMessageQDef(displayQueue, 10, disp_data_t);
	displayQueueHandle = osMessageCreate(osMessageQ(displayQueue), NULL);

	/* definition and creation of ledQueue */
	osMessageQDef(ledQueue, 6, uint16_t);
	ledQueueHandle = osMessageCreate(osMessageQ(ledQueue), NULL);

	/* definition and creation of usbQueue */
	osMessageQDef(usbQueue, 16, uint16_t);
	usbQueueHandle = osMessageCreate(osMessageQ(usbQueue), NULL);

	/* definition and creation of adcQueue */
	osMessageQDef(adcQueue, 10, adc_data_t);
	adcQueueHandle = osMessageCreate(osMessageQ(adcQueue), NULL);

	osMessageQDef(cameraQueue, 10, camera_t);
	cameraQueueHandle = osMessageCreate(osMessageQ(cameraQueue), NULL);

	/* USER CODE BEGIN RTOS_QUEUES */
	osMessageQDef(SD_Queue, QUEUE_SIZE, uint16_t);
	SDQueueID = osMessageCreate(osMessageQ(SD_Queue), NULL);
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of DEFAULTTASK */
	osThreadDef(DEFAULTTASK, startDefaultTask, osPriorityNormal, 0, DEFAULT_STACK_SIZE);
	DEFAULTTASKHandle = osThreadCreate(osThread(DEFAULTTASK), NULL);

	/* definition and creation of USBTASK */
	osThreadDef(USBTASK, startUsbTask, osPriorityNormal, 0, USBD_STACK_SIZE);
	USBTASKHandle = osThreadCreate(osThread(USBTASK), NULL);

	/* definition and creation of LEDTASK */
	osThreadDef(LEDTASK, startLedTask, osPriorityLow, 0, BLINKY_STACK_SIZE);
	LEDTASKHandle = osThreadCreate(osThread(LEDTASK), NULL);

	/* definition and creation of DISPLAYTASK */
	osThreadDef(DISPLAYTASK, startDisplayTask, osPriorityLow, 0, DISPLAY_STACK_SIZE);
	DISPLAYTASKHandle = osThreadCreate(osThread(DISPLAYTASK), NULL);

	/* definition and creation of CDCTASK */
	osThreadDef(CDCTASK, startCdcTask, osPriorityNormal, 0, CDC_STACK_SIZE);
	CDCTASKHandle = osThreadCreate(osThread(CDCTASK), NULL);

	osThreadDef(ADCTASK, startAdcTask, osPriorityNormal, 0, ADC_STACK_SIZE);
	ADCTASKHandle = osThreadCreate(osThread(ADCTASK), NULL);

	osThreadDef(CAMERATASK, startCameraTask, osPriorityNormal, 0, CAMERA_STACK_SIZE);
	CAMERATASKHandle = osThreadCreate(osThread(CAMERATASK), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	startWifi();
	/* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_startDefaultTask */
void testSD(void) {
	char pcWriteBuffer[600];
	DIR Dir;
	FATFS *fs;
	FILINFO Finfo;
	//FRESULT res;
	DWORD dw;
	QWORD acc_size, acc_dirs, acc_files;
	memset(pcWriteBuffer, 0x00, 600);
	FRESULT res = f_opendir(&Dir, "/");
	if (res != FR_OK) {
		//sprintf((char*) &pcWriteBuffer, " Disk Error: %s\n",
		//		getSdStatusStr(res));
		memset(pcWriteBuffer, 0x00, 600);
		return;
	}

	acc_size = acc_dirs = acc_files = 0;
	for (;;) {
		res = f_readdir(&Dir, &Finfo);
		if ((res != FR_OK) || !Finfo.fname[0]) {
			break; // finished so drop out of loop
		}
		if (Finfo.fattrib & AM_DIR) {
			acc_dirs++;
		} else {
			acc_files++;
			acc_size += Finfo.fsize;
		}
		sprintf(pcWriteBuffer, "%c%c%c%c%c %u/%02u/%02u %02u:%02u %9lu  %s\n",
				(Finfo.fattrib & AM_DIR) ? 'D' : '-',
				(Finfo.fattrib & AM_RDO) ? 'R' : '-',
				(Finfo.fattrib & AM_HID) ? 'H' : '-',
				(Finfo.fattrib & AM_SYS) ? 'S' : '-',
				(Finfo.fattrib & AM_ARC) ? 'A' : '-', (Finfo.fdate >> 9) + 1980,
				(Finfo.fdate >> 5) & 15, Finfo.fdate & 31, (Finfo.ftime >> 11),
				(Finfo.ftime >> 5) & 63, (unsigned long int)Finfo.fsize, Finfo.fname);
		//safe_cdc_write_const(pcWriteBuffer,strlen(pcWriteBuffer));
		memset(pcWriteBuffer, 0x00, 600);

	}
	sprintf(pcWriteBuffer, "%4u File(s),%10llu bytes total\n%4u Dir(s)",
			(unsigned int) acc_files, (long long int) acc_size,
			(unsigned int) acc_dirs);
	res = f_getfree("/", &dw, &fs);
	if (res == FR_OK) {
		sprintf(pcWriteBuffer, ", %10llu bytes free\n",
				(long long int) dw * fs->csize * 512);
	} else {
		//	sprintf(pcWriteBuffer, " Disk Error: %s\n",
		//		getSdStatusStr(res));
	}

}
/**
 * @brief  Function implementing the DEFAULTTASK thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_startDefaultTask */
void startDefaultTask(void const *argument) {
	/* USER CODE BEGIN startDefaultTask */
	/* Infinite loop */
	//FRESULT res = f_mount(&SDFatFS, "", 1);
	//if (res != FR_OK) {
	//}
	//testSD();
	for (;;) {
		osDelay(1);
	}
	/* USER CODE END startDefaultTask */
}

/* USER CODE BEGIN Header_startUsbTask */
/**
 * @brief Function implementing the USBTASK thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_startUsbTask */
void startUsbTask(void const *argument) {
	/* USER CODE BEGIN startUsbTask */
	tusb_rhport_init_t dev_init = { .role = TUSB_ROLE_DEVICE, .speed =
			TUSB_SPEED_AUTO };
	tusb_init(BOARD_TUD_RHPORT, &dev_init);

	/* Infinite loop */
	for (;;) {
		tud_task();
		// following code only run if tud_task() process at least 1 event
		tud_cdc_write_flush();
	}
	/* USER CODE END startUsbTask */
}

/* USER CODE BEGIN Header_startLedTask */
// Invoked when device is unmounted
void tud_umount_cb(void) {
	blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en) {
	(void) remote_wakeup_en;
	blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
	blink_interval_ms = tud_mounted() ? BLINK_MOUNTED : BLINK_NOT_MOUNTED;
}
/**
 * @brief Function implementing the LEDTASK thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_startLedTask */
void startLedTask(void const *argument) {
	/* USER CODE BEGIN startLedTask */
	static uint32_t start_ms = 0;
	static uint8_t ledstate = 0;
	/* Infinite loop */
	for (;;) {
		start_ms += blink_interval_ms;
		osDelay(blink_interval_ms);
		if (ledstate == 0) {
			ledstate = 1;
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		} else {
			ledstate = 0;
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		}
	}
	/* USER CODE END startLedTask */
}

/* USER CODE BEGIN Header_startDisplayTask */

/* USER CODE BEGIN Header_startCdcTask */

/**
 * @brief Function implementing the CDCTASK thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_startCdcTask */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void startAdcTask(void const *argument) {
	/* USER CODE BEGIN startDefaultTask */
	__IO uint16_t uhADCxConvertedValue[7];
	__IO uint32_t uhADCxInputVoltage[7];
	adc_data_t adcData;
	uint32_t adc3_inp0, adc3_inp1, adc3_inp2, adc3_inp3, vbat, tempsensor,
			vrefint;
	uint16_t V30 = 620;
	if (HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED)
			!= HAL_OK) {
		/* Calibration Error */
		Error_Handler();
	}
	for (;;) {
		for (uint32_t i = 0;
				i < (sizeof(uhADCxConvertedValue) / sizeof(uint16_t)); i++) {
			// Start the conversion process
			if (HAL_ADC_Start(&hadc3) != HAL_OK) {
				/* Start Conversation Error */
				Error_Handler();
			}
			//Wait for the end of conversion
			if (HAL_ADC_PollForConversion(&hadc3, 100) != HAL_OK) {
				// End Of Conversion flag not set on time
				Error_Handler();
			} else {
				// ADC conversion completed
				// Get the converted value of regular channel
				uhADCxConvertedValue[i] = HAL_ADC_GetValue(&hadc3);

				// Convert the result from 16 bit value to the voltage dimension (mV unit)
				// Vref = 3.3 V
				uhADCxInputVoltage[i] = ((uhADCxConvertedValue[i] * 3300)
						/ 0xFFFF);
			}
		}
		HAL_ADC_Stop(&hadc3);
		adc3_inp0 = uhADCxInputVoltage[0]; // mv
		adc3_inp1 = uhADCxInputVoltage[4]; // mv
		adc3_inp2 = uhADCxInputVoltage[5]; // mv
		adc3_inp3 = uhADCxInputVoltage[6]; // mv
		vrefint = uhADCxInputVoltage[1]; // type. 1200mV
		tempsensor = ((int32_t) uhADCxInputVoltage[2] - V30) / Avg_Slope + 30; // ¡ãC
		vbat = uhADCxInputVoltage[3] * 4;
		adcData.AvgSlope = Avg_Slope;
		adcData.V30 = V30;
		adcData.adc3_inp0 = adc3_inp0;
		adcData.adc3_inp1 = adc3_inp1;
		adcData.adc3_inp2 = adc3_inp2;
		adcData.adc3_inp3 = adc3_inp3;
		adcData.tempsensor = tempsensor;
		adcData.vbat = vbat;
		adcData.vrefint = vrefint;
		xQueueSendToBack(adcQueueHandle, &adcData, (TickType_t ) 0);
		osDelay(500);
	}
	/* USER CODE END startDefaultTask */
}

/* USER CODE END Application */
