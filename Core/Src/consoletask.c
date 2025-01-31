/**
 ******************************************************************************
 * @file         console.c
 * @author       Aaron Escoboza, Github account: https://github.com/aaron-ev
 * @brief        Command Line Interpreter based on FreeRTOS and STM32 HAL layer
 ******************************************************************************
 */

#include <consoletask.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS_CLI.h"
#include "queue.h"
#include "stm32h7xx_hal.h"
#include "bspRtc.h"
#include "bspGpio.h"
#include "bspPwm.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "cmsis_os.h"
#include "tusb.h"
#include "tusb_config.h"
#include "bspClk.h"
#include "adc.h"
#include "event_groups.h"
#include "fatfs.h"
#include "ff.h"
#include "main.h"

#define CONSOLE_VERSION_MAJOR                   1
#define CONSOLE_VERSION_MINOR                   0

#define MAX_IN_STR_LEN                          300
#define MAX_OUT_STR_LEN                         600
#define MAX_RX_QUEUE_LEN                        300

/* ASCII code definition */
#define ASCII_TAB                               '\t'  /* Tabulate              */
#define ASCII_CR                                '\r'  /* Carriage return       */
#define ASCII_LF                                '\n'  /* Line feed             */
#define ASCII_BACKSPACE                         '\b'  /* Back space            */
#define ASCII_FORM_FEED                         '\f'  /* Form feed             */
#define ASCII_DEL                               127   /* Delete                */
#define ASCII_CTRL_PLUS_C                         3   /* CTRL + C              */
#define ASCII_NACK                               21   /* Negative acknowledge  */

#define CHUNK_SIZE 64

adc_data_t adcData;
camera_t cameraData;
char cRxData;
typedef enum {
	CDCWAITCONNECT, CDCWAITCHAR, CDCFIRSTCONNECT, CDCDISCONNECT, CDCPROCESSCHAR
} connect_state_t;

EventGroupHandle_t Send_Complete_Handle;
extern osMessageQId adcQueueHandle;

const int SEND_COMPLETE_BIT = 0x000000001;
static char *pcWelcomeMsg =
		"Welcome to the console. Enter 'help' to view a list of available commands.\n";

static const char *prvpcTaskListHeader =
		"Task states: Bl = Blocked, Re = Ready, Ru = Running, De = Deleted,  Su = Suspended\n\n"
				"Task name         State  Priority  Stack remaining  CPU usage  Runtime(us)\n"
				"================= =====  ========  ===============  =========  ===========\n";
static char *prvpcPrompt = "#cmd: ";

/* Command function prototypes */
void safe_cdc_write_const(char message[], uint32_t message_size);
static BaseType_t prvCommandWifiDataReadyState(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCommandWifiHandShakeState(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCommandPwmSetFreq(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCommandPwmSetDuty(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCommandGpioWrite(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCommandGpioRead(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCommandEcho(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandTaskStats(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCommandHeap(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandTicks(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandRtcGet(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandRtcSet(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandVersion(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandVref(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandBat(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandTemperature(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCommandAdc(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandMkdir(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandMount(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandFormat(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandDel(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandRename(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandDir(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandRmdir(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandPrune(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandCd(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandCwd(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCommandClearScreen(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t prvCommandCameraFps(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString);
/**
 *   @brief  This function is executed in case of error occurrence.
 *   @retval None
 */

static const char* prvpcMapTaskState(eTaskState eState) {
	switch (eState) {
	case eReady:
		return "Re";
	case eRunning:
		return "Ru";
	case eDeleted:
		return "De";
	case eBlocked:
		return "Bl";
	case eSuspended:
		return "S";
	default:
		return "??";
	}
}

static const CLI_Command_Definition_t xCommands[] =
		{
				{ "stats",
						"stats:\r\n \tDisplays a table with the state of each FreeRTOS task.",
						prvCommandTaskStats, 0 }, { "wifihsstate",
						"\r\nwifihsstate:\r\n \tRead wifi handshake pin state.",
						prvCommandWifiHandShakeState, 0 }, { "wifidrstate",
						"\r\nwifidrstate:\r\n \tRead wifi dataready pin state.",
						prvCommandWifiDataReadyState, 0 },
				{ "gpiowrite",
						"\r\ngpiowrite <gpio port> <pin number> <logical value>:\r\n \tWrite a digital value to GPIO pin.",
						prvCommandGpioWrite, 3 },
				{ "gpioread",
						"\r\ngpioread <gpio port> <pin number>:\r\n \tRead a GPIO pin.",
						prvCommandGpioRead, 2 }, { "echo",
						"\r\necho <string to echo>:\r\n \tdisplays a string.",
						prvCommandEcho, 1 },
				{ "pwmfreq",
						"\r\npwmfreq <Channel> <Frequency>:\r\n \tSet a new frequency. Valid Channels 0 to 3",
						prvCommandPwmSetFreq, 1 },
				{ "pwmduty",
						"\r\npwmduty <Channel> <Duty cycle> Channel>:\r\n \tSet a new PWM duty cycle of a giving channel.\r\n \tValid Channels 0 to 3",
						prvCommandPwmSetDuty, 2 }, { "heap",
						"\r\nheap:\r\n \tDisplay free heap memory.",
						prvCommandHeap, 0 },
				{ "ticks",
						"\r\nticks:\r\n \tDisplay OS tick count and run time in seconds.",
						prvCommandTicks, 0 }, { "vref",
						"\r\nvref:\r\n \tDisplay ADC Referance Voltage",
						prvCommandVref, 0 }, { "vbat",
						"\r\nvbat:\r\n \tDisplay ADC Battery Voltage",
						prvCommandBat, 0 }, { "temp",
						"\r\ntemp:\r\n \tDisplay ADC Cpu Temperature",
						prvCommandTemperature, 0 },
				{ "adc",
						"\r\nadc <Channel>:\r\n \tDisplay ADC Channel x Value channel 0 to 3",
						prvCommandAdc, 1 },
				{ "camera",
						"\r\ncamera <cameracommand>:\r\n \tGet Camera information\r\ncamera <cameracommand> <value>:\r\n \tSet camera parameter",
						prvCommandCameraFps, -1 }, { "gettime",
						"\r\ngettime:\r\n \tGet the current time",
						prvCommandRtcGet, 0 },
				{ "settime",
						"\r\nsettime <Hours> <Minutes> <Seconds>:\r\n \tSet a new time",
						prvCommandRtcSet, 3 }, { "mount",
						"\r\nmount:\r\n \tmount SD card", prvCommandMount, 0 },
				{ "format", "\r\nformat:\r\n \tFormat the SD card",
						prvCommandFormat, 0 },
				{ "cd",
						"\r\ncd <path>:\r\n \tchange the current directory on the SD card",
						prvCommandCd, 1 },
				{ "cwd",
						"\r\ncwd <path>:\r\n \tget the current directory on the SD card",
						prvCommandCwd, 0 },
				{ "mkdir",
						"\r\nmkdir <dirname>:\r\n \tCreate a new directory on SD card",
						prvCommandMkdir, 1 }, { "del",
						"\r\ndel <filename>:\r\n \tDelete file from SD card",
						prvCommandDel, 1 },
				{ "rmdir",
						"\r\nrmdir <path>:\r\n \tDelete empty directory from SD card",
						prvCommandRmdir, 1 },
				{ "prune",
						"\r\nprune <path>:\r\n \tDelete a non empty directory SD card",
						prvCommandPrune, 1 },
				{ "dir",
						"\r\ndir:\ndir <path>:\r\n \tDirectory listing of SD card",
						prvCommandDir, -1 },
				{ "ls",
						"\r\nls:\nls <path>:\r\n \tDirectory listing of SD card",
						prvCommandDir, -1 },
				{ "ren",
						"\r\nren <filename> <newfilename>:\r\n \tRename file on the SD card",
						prvCommandRename, 2 }, { "cls",
						"\r\ncls:\r\n \tClear the terminal window.",
						prvCommandClearScreen, 0 }, { "version",
						"\r\nversion:\r\n \tGet firmware version",
						prvCommandVersion, 0 }, { NULL, NULL, NULL, 0 } };

static const char* getSdStatusStr(FRESULT res) {
	const char *sdresultstr =
			"OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
					"INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
					"INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
					"LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0" "INVALID_PARAMETER\0";
	for (int i = 0; i != res && *sdresultstr; i++) {
		while (*sdresultstr++)
			;
	}
	return sdresultstr;
}

static BaseType_t prvCommandCameraFps(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString) {
	BaseType_t xParamLen;
	uint32_t paramcount = prvGetNumberOfParameters(pcCommandString);
	const char *cmd = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen);
	if (paramcount == 1) {
		// handle get command
		if (strcmp(cmd, "fps") == 0) {
			snprintf((char*) pcWriteBuffer, xWriteBufferLen, "%d FPS\n",
					(int) cameraData.fps);
			return pdFALSE;
		}
		if (strcmp(cmd, "id") == 0) {
			snprintf((char*) pcWriteBuffer, xWriteBufferLen, "Camera ID 0x%x\n",
					(int) cameraData.id);
			return pdFALSE;
		}
		if (strcmp(cmd, "type") == 0) {
			switch (cameraData.type) {
			case 0:
				strcpy(pcWriteBuffer, "Camera is unknown\n");
				break;
			case 1:
				strcpy(pcWriteBuffer, "Camera type is OV2640\n");
				break;
			case 2:
				strcpy(pcWriteBuffer, "Camera type is OV5640\n");
				break;
			case 3:
				strcpy(pcWriteBuffer, "Camera type is OV7670\n");
				break;
			case 4:
				strcpy(pcWriteBuffer, "Camera type is OV7725\n");
				break;
			default:
				strcpy(pcWriteBuffer, "Camera is unknown\n");
			}
			return pdFALSE;
		}
	} else if (paramcount == 2) {
		//set command
	} else {
		// wrong number of parameters
		strncpy(pcWriteBuffer,
				"Incorrect command parameter(s).  Enter \"camera help\" to view a list of available camera commands.\r\n\r\n",
				xWriteBufferLen);
		return pdFALSE;
	}
	strncpy((char*) pcWriteBuffer,
			"Camera command not found. \r\nEnter \"camera help\" to view a list of available camera commands.\r\n\r\n",
			xWriteBufferLen);
	return pdFALSE;
}

static BaseType_t prvCommandClearScreen(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString) {
	snprintf(pcWriteBuffer, xWriteBufferLen, "\x1b[2J\x1b[H");
	return pdFALSE;
}

static BaseType_t prvCommandWifiHandShakeState(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString) {
	BspPinNum_e bspPinNum = 8;
	BspGpioPinState_e xPinState;
	BspGpioInstance_e bspGpioInstance;
	bspGpioInstance = bspGpioMapInstance('d');  // port d 8
	xPinState = bspGpioRead(bspGpioInstance, bspPinNum);
	snprintf(pcWriteBuffer, xWriteBufferLen, "WIFI Handshake State: %d\n",
			xPinState);
	return pdFALSE;
}

static BaseType_t prvCommandWifiDataReadyState(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString) {
	BspPinNum_e bspPinNum = 9;
	BspGpioPinState_e xPinState;
	BspGpioInstance_e bspGpioInstance;
	bspGpioInstance = bspGpioMapInstance('d');  // port d 8
	xPinState = bspGpioRead(bspGpioInstance, bspPinNum);
	snprintf(pcWriteBuffer, xWriteBufferLen, "WIFI DataReady State: %d\n",
			xPinState);
	return pdFALSE;
}
/**
 * @brief Command that gets task statistics.
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandTaskStats(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString) {
	static uint32_t uTaskIndex = 0;
	static uint32_t uTotalOfTasks = 0;
	static uint32_t uTotalRunTime = 1;
	TaskStatus_t *pxTmpTaskStatus = NULL;
	static TaskStatus_t *pxTaskStatus = NULL;

	if (pxTaskStatus == NULL) {
		uTotalOfTasks = uxTaskGetNumberOfTasks();
		pxTaskStatus = pvPortMalloc(uTotalOfTasks * sizeof(TaskStatus_t));
		if (pxTaskStatus == NULL) {
			snprintf(pcWriteBuffer, xWriteBufferLen,
					"Error: Not enough memory 3 for task allocation");
			goto out_cmd_task_stats;
		}
		uTotalOfTasks = uxTaskGetSystemState(pxTaskStatus, uTotalOfTasks,
				&uTotalRunTime);
		uTaskIndex = 0;
		uTotalRunTime /= 100;
		snprintf(pcWriteBuffer, xWriteBufferLen, prvpcTaskListHeader);
	} else {
		memset(pcWriteBuffer, 0x00, MAX_OUT_STR_LEN);
		/* Prevent from zero division */
		if (!uTotalRunTime) {
			uTotalRunTime = 1;
		}

		pxTmpTaskStatus = &pxTaskStatus[uTaskIndex];
		if (pxTmpTaskStatus->ulRunTimeCounter / uTotalRunTime < 1) {
			snprintf(pcWriteBuffer, xWriteBufferLen,
					"%-16s  %5s  %8lu  %14dB       < 1%%  %11lu\n",
					pxTmpTaskStatus->pcTaskName,
					prvpcMapTaskState(pxTmpTaskStatus->eCurrentState),
					pxTmpTaskStatus->uxCurrentPriority,
					pxTmpTaskStatus->usStackHighWaterMark,
					pxTmpTaskStatus->ulRunTimeCounter);
		} else {
			snprintf(pcWriteBuffer, xWriteBufferLen,
					"%-16s  %5s  %8lu  %14dB  %8lu%%  %11lu\n",
					pxTmpTaskStatus->pcTaskName,
					prvpcMapTaskState(pxTmpTaskStatus->eCurrentState),
					pxTmpTaskStatus->uxCurrentPriority,
					pxTmpTaskStatus->usStackHighWaterMark,
					pxTmpTaskStatus->ulRunTimeCounter / uTotalRunTime,
					pxTmpTaskStatus->ulRunTimeCounter);
		}
		uTaskIndex++;
	}

	/* Check if there is more tasks to be process */
	if (uTaskIndex < uTotalOfTasks)
		return pdTRUE;
	else {
		out_cmd_task_stats: if (pxTaskStatus != NULL) {
			vPortFree(pxTaskStatus);
			pxTaskStatus = NULL;
		}
		return pdFALSE;
	}
}

/**
 * @brief Command that writes to a GPIOx pin.
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandGpioWrite(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString) {
	BaseType_t xParamLen;
	BspPinNum_e bspPinNum;
	const char *pcGpioPinNum;
	const char *pcGpioPinSate;
	const char *pcGpioInstance;
	BspGpioPinState_e bspPinState;
	BspGpioInstance_e bspGpioInstance;

	// Get GPIO instance and map it from data type char to BSP integer value
	pcGpioInstance = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen);
	bspGpioInstance = bspGpioMapInstance(*pcGpioInstance);
	if (bspGpioInstance >= BSP_MAX_GPIO_INSTANCE) {
		snprintf(pcWriteBuffer, xWriteBufferLen, "Error: invalid GPIO port\n");
		return pdFALSE;
	}
	// Get pin number
	pcGpioPinNum = FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParamLen);
	bspPinNum = atoi(pcGpioPinNum);
	if (bspPinNum < BSP_GPIO_PIN_0 || bspPinNum > BSP_GPIO_PIN_15) {
		snprintf(pcWriteBuffer, xWriteBufferLen, "Error: invalid pin number\n");
		return pdFALSE;
	}
	// Get new pin state
	pcGpioPinSate = FreeRTOS_CLIGetParameter(pcCommandString, 3, &xParamLen);
	bspPinState = atoi(pcGpioPinSate);
	if (bspPinState > BSP_GPIO_PIN_HIGH) {
		snprintf(pcWriteBuffer, xWriteBufferLen, "Error: invalid pin state\n");
		return pdFALSE;;
	}
	/* Write the new pin state to the GPIO pin and fill FreeRTOS write buffer */
	bspGpioWrite(bspGpioInstance, bspPinNum, bspPinState);
	snprintf(pcWriteBuffer, xWriteBufferLen, "GPIO: %c, Pin: %d set to %d\n",
			*pcGpioInstance, (int) bspPinNum, bspPinState);

	return pdFALSE;
}

/**
 * @brief Command that reads from GPIOx Pin
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandGpioRead(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString) {
	BaseType_t xParamLen;
	const char *pcGpioPinNum;
	const char *pcGpioInstance;
	BspPinNum_e bspPinNum;
	BspGpioPinState_e xPinState;
	BspGpioInstance_e bspGpioInstance;

	/* Get GPIO instance and map it from data type char to BSP integer value */
	pcGpioInstance = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen);
	bspGpioInstance = bspGpioMapInstance(*pcGpioInstance);
	if (bspGpioInstance >= BSP_MAX_GPIO_INSTANCE) {
		snprintf(pcWriteBuffer, xWriteBufferLen,
				"Error: invalid GPIO port should be a to \n");
		return pdFALSE;
	}
	/* Get pin number */
	pcGpioPinNum = FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParamLen);
	bspPinNum = atoi(pcGpioPinNum);
	if (bspPinNum < BSP_GPIO_PIN_0 || bspPinNum > BSP_GPIO_PIN_15) {
		snprintf(pcWriteBuffer, xWriteBufferLen,
				"Error: \r\ninvalid pin number value should be between 0 and 15\n");
		return pdFALSE;
	}
	/* Read pin state and fill FreeRTOS write buffer */
	xPinState = bspGpioRead(bspGpioInstance, bspPinNum);
	snprintf(pcWriteBuffer, xWriteBufferLen, "GPIO: %c Pin: %d state: %d\n",
			*pcGpioInstance, (int) bspPinNum, xPinState);

	return pdFALSE;
}

/**
 * @brief Echo command line in UNIX systems.
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandEcho(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	const char *pcStrToOutput;
	BaseType_t xParamLen;

	/* Get the user input and write it back the FreeRTOS write buffer */
	pcStrToOutput = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen);
	snprintf(pcWriteBuffer, xWriteBufferLen, "%s\n", pcStrToOutput);

	return pdFALSE;
}

/**
 * @brief Command that sets a new pwm frequency.
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandPwmSetFreq(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString) {
	const char *pcFreq;
	BaseType_t xParamLen;
	pwmerror_t bspStatus;

	pcFreq = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen);
	bspStatus = bspPwmSetFreq(atoi(pcFreq));
	if (bspStatus == PwmFrequencyError) {
		snprintf(pcWriteBuffer, xWriteBufferLen, "Error: Invalid parameter\n");
	} else if (bspStatus == PwmHalError) {
		snprintf(pcWriteBuffer, xWriteBufferLen, "Error: Hal Error\n");
	} else {
		snprintf(pcWriteBuffer, xWriteBufferLen, "Frequency set to %dHz\n",
				atoi(pcFreq));
	}
	return pdFALSE;
}

/**
 * @brief Command that sets a new pwm duty cycle.
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandPwmSetDuty(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString) {
	pwmerror_t bspStatus;
	BaseType_t xParamLen;
	const char *pcChannel;
	const char *pcDutyCycle;

	pcDutyCycle = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen);
	pcChannel = FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParamLen);

	/* Index starts at index 0, so 1 is subtracted from channel */
	bspStatus = bspPwmSetDuty(atoi(pcDutyCycle), atoi(pcChannel) - 1);
	if (bspStatus == PwmChannelError)
		snprintf(pcWriteBuffer, xWriteBufferLen, "Error: Invalid parameter\n");
	else
		snprintf(pcWriteBuffer, xWriteBufferLen,
				"Channel %d set to %d%% duty cycle \n", atoi(pcChannel),
				atoi(pcDutyCycle));
	//snprintf(pcWriteBuffer, xWriteBufferLen, "Error: Not Implemented yet\n");
	return pdFALSE;
}

/**
 * @brief Command that gets heap information
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandHeap(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {

	size_t xHeapFree;
	size_t xHeapMinMemExisted;

	xHeapFree = xPortGetFreeHeapSize();
	xHeapMinMemExisted = xPortGetMinimumEverFreeHeapSize();
	snprintf(pcWriteBuffer, xWriteBufferLen,
			"Heap size            : %3u bytes (%3d KiB)\nRemaining            : %3u bytes (%3d KiB)\nMinimum ever existed : %3u bytes (%3d KiB)\n",
			configTOTAL_HEAP_SIZE, configTOTAL_HEAP_SIZE / 1024, xHeapFree,
			xHeapFree / 1024, xHeapMinMemExisted, xHeapMinMemExisted / 1024);

	return pdFALSE;
}

/**
 * @brief Command that calculate OS ticks information.
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandTicks(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	uint32_t uMs;
	uint32_t uSec;
	TickType_t xTickCount = xTaskGetTickCount();

	uSec = xTickCount / configTICK_RATE_HZ;
	uMs = xTickCount % configTICK_RATE_HZ;
	snprintf(pcWriteBuffer, xWriteBufferLen,
			"Tick rate: %u Hz\nTicks: %lu\nRun time: %lu.%.3lu seconds\n",
			(unsigned) configTICK_RATE_HZ, xTickCount, uSec, uMs);

	return pdFALSE;
}

/**
 * @brief Get the current time stored in RTC registers
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandRtcGet(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	bsp_rtc_datetime_t bspRtcDateTime;
	bsp_rtc_error_t bspStatus;

	bspStatus = bspRtcGetTime(&bspRtcDateTime);
	if (bspStatus != RtcOK)
		snprintf(pcWriteBuffer, xWriteBufferLen,
				"Error: Could not get current time\n");

	snprintf(pcWriteBuffer, xWriteBufferLen,
			"Time (24hr format): %02u:%02u:%02u\n", bspRtcDateTime.uHours,
			bspRtcDateTime.uMinutes, bspRtcDateTime.uSeconds);

	return pdFALSE;
}

/**
 * @brief Set a new time in RCT registers
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandRtcSet(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	const char *cHours;
	const char *cMinutes;
	const char *cSeconds;
	BaseType_t xParamLen;
	bsp_rtc_error_t bspStatus;
	bsp_rtc_datetime_t bspRtcDateTime;

	cHours = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen);
	cMinutes = FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParamLen);
	cSeconds = FreeRTOS_CLIGetParameter(pcCommandString, 3, &xParamLen);

	bspRtcDateTime.uHours = atoi(cHours);
	bspRtcDateTime.uMinutes = atoi(cMinutes);
	bspRtcDateTime.uSeconds = atoi(cSeconds);

	bspStatus = bspRtcSetTime(&bspRtcDateTime);
	if (bspStatus == SetTimeError) {
		snprintf(pcWriteBuffer, xWriteBufferLen, "Error: Invalid parameters\n");
		return pdFALSE;
	} else if (bspStatus != RtcOK) {
		snprintf(pcWriteBuffer, xWriteBufferLen, "Error: I/O\n");
		return pdFALSE;
	} else {
		snprintf(pcWriteBuffer, xWriteBufferLen,
				"Time (24hr format) set to: %02u:%02u:%02u\n",
				bspRtcDateTime.uHours, bspRtcDateTime.uMinutes,
				bspRtcDateTime.uSeconds);
	}

	return pdFALSE;
}

/**
 * @brief Get current console version
 * @param *pcWriteBuffer FreeRTOS CLI write buffer.
 * @param xWriteBufferLen Length of write buffer.
 * @param *pcCommandString pointer to the command name.
 * @retval FreeRTOS status
 */
static BaseType_t prvCommandVersion(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	snprintf(pcWriteBuffer, xWriteBufferLen, "%d.%d\n",
			(uint8_t) (CONSOLE_VERSION_MAJOR),
			(uint8_t) (CONSOLE_VERSION_MINOR));
	return pdFALSE;
}

static BaseType_t prvCommandVref(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {

	snprintf((char*) pcWriteBuffer, xWriteBufferLen, " Vref: %4dmV\n",
			(int) adcData.vrefint);
	return pdFALSE;

}

static BaseType_t prvCommandBat(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	snprintf((char*) pcWriteBuffer, xWriteBufferLen, " vbat: %4dmV\n",
			(int) adcData.vbat);
	return pdFALSE;
}

static BaseType_t prvCommandTemperature(char *pcWriteBuffer,
		size_t xWriteBufferLen, const char *pcCommandString) {
	snprintf((char*) pcWriteBuffer, xWriteBufferLen, " temp: %3d 'C\n",
			(int) adcData.tempsensor);
	return pdFALSE;
}

static BaseType_t prvCommandAdc(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	BaseType_t xParamLen;
	const char *channel = FreeRTOS_CLIGetParameter(pcCommandString, 1,
			&xParamLen);
	int channelnumber = atoi(channel);
	char formatstr[30] = { 0 };
	uint32_t adcvalue = 0;
	if (channelnumber < 0 || channelnumber > 3) {
		snprintf(pcWriteBuffer, xWriteBufferLen, "Error: Invalid parameters\n");
		return pdFALSE;
	}
	switch (channelnumber) {
	case 0:
		adcvalue = adcData.adc3_inp0;
		strcpy(formatstr, " PC2: %4dmV\n");
		break;
	case 1:
		adcvalue = adcData.adc3_inp1;
		strcpy(formatstr, " PC3: %4dmV\n");
		break;
	case 2:
		adcvalue = adcData.adc3_inp2;
		strcpy(formatstr, " PC0: %4dmV\n");
		break;
	case 3:
		adcvalue = adcData.adc3_inp3;
		strcpy(formatstr, " PC1: %4dmV\n");
		break;
	}

	snprintf((char*) pcWriteBuffer, xWriteBufferLen, formatstr, (int) adcvalue);
	return pdFALSE;
}

static BaseType_t prvCommandFormat(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	FRESULT res;
	uint8_t buf[_MAX_SS];
	osMutexWait(SDMutexHandle, osWaitForever);
	res = f_mkfs("", FM_ANY, 0, buf, sizeof(buf));
	if (res != FR_OK) {
		osMutexRelease(SDMutexHandle);
		sprintf((char*) pcWriteBuffer, " Error: %s\n", getSdStatusStr(res));
		return pdFALSE;
	}
	// formatted ok so mount it
	res = f_mount(&SDFatFS, "", 0);
	if (res != FR_OK) {
		osMutexRelease(SDMutexHandle);
		sprintf((char*) pcWriteBuffer, " Error: %s\n", getSdStatusStr(res));
		return pdFALSE;
	}
	osMutexRelease(SDMutexHandle);
	sprintf((char*) pcWriteBuffer, "Sd Card Formatted and Mounted Ok\n");
	return pdFALSE;
}

static BaseType_t prvCommandMount(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	FRESULT res;
	osMutexWait(SDMutexHandle, osWaitForever);
	res = f_mount(&SDFatFS, "", 0);
	if (res != FR_OK) {
		osMutexRelease(SDMutexHandle);
		sprintf((char*) pcWriteBuffer, " Error: %s\n", getSdStatusStr(res));
		return pdFALSE;
	}
	osMutexRelease(SDMutexHandle);
	sprintf((char*) pcWriteBuffer, "Sd Card Mounted Ok\n");
	return pdFALSE;
}

static BaseType_t prvCommandCd(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	BaseType_t xParamLen;
	FRESULT res;
	const char *dirname = FreeRTOS_CLIGetParameter(pcCommandString, 1,
			&xParamLen);
	osMutexWait(SDMutexHandle, osWaitForever);
	res = f_chdir(dirname);
	if (res != FR_OK) {
		osMutexRelease(SDMutexHandle);
		sprintf((char*) pcWriteBuffer, " Error: %s\n", getSdStatusStr(res));
		return pdFALSE;
	}
	osMutexRelease(SDMutexHandle);
	sprintf((char*) pcWriteBuffer, " Ok\n");
	return pdFALSE;
}

static BaseType_t prvCommandCwd(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	FRESULT res;
	UINT sz = 0;
	char path[_MAX_LFN + 1] = { 0 };

	osMutexWait(SDMutexHandle, osWaitForever);
	sz = sizeof(path);
	res = f_getcwd(path, sz);
	if (res != FR_OK) {
		osMutexRelease(SDMutexHandle);
		sprintf((char*) pcWriteBuffer, "Disk Error: %s\n", getSdStatusStr(res));
		return pdFALSE;
	}
	osMutexRelease(SDMutexHandle);
	sprintf((char*) pcWriteBuffer, "Current path is %s\n", path);
	return pdFALSE;
}

static BaseType_t prvCommandMkdir(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	BaseType_t xParamLen;
	const char *dirname = FreeRTOS_CLIGetParameter(pcCommandString, 1,
			&xParamLen);
	osMutexWait(SDMutexHandle, osWaitForever);
	FRESULT res = f_mkdir(dirname);
	if (res != FR_OK) {
		osMutexRelease(SDMutexHandle);
		sprintf((char*) pcWriteBuffer, " Disk Error: %s\n",
				getSdStatusStr(res));
		return pdFALSE;
	}
	osMutexRelease(SDMutexHandle);
	sprintf((char*) pcWriteBuffer, "%s Directory Created\n", dirname);
	return pdFALSE;
}

static BaseType_t prvCommandDel(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	BaseType_t xParamLen;
	const char *filename = FreeRTOS_CLIGetParameter(pcCommandString, 1,
			&xParamLen);
	osMutexWait(SDMutexHandle, osWaitForever);
	FRESULT res = f_unlink(filename);
	if (res != FR_OK) {
		osMutexRelease(SDMutexHandle);
		sprintf((char*) pcWriteBuffer, " Disk Error: %s\n",
				getSdStatusStr(res));
		return pdFALSE;
	}
	osMutexRelease(SDMutexHandle);
	sprintf((char*) pcWriteBuffer, "%s Deleted\n", filename);
	return pdFALSE;
}

static BaseType_t prvCommandRmdir(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	BaseType_t xParamLen;
	FRESULT res;
	DIR dir;

	const char *path = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen);
	osMutexWait(SDMutexHandle, osWaitForever);

	res = f_opendir(&dir, path);
	if (res != FR_OK) {
		osMutexRelease(SDMutexHandle);
		sprintf((char*) pcWriteBuffer, " %s is not a directory\n", path);
		return pdFALSE;
	}

	res = f_unlink(path);
	if (res != FR_OK) {
		osMutexRelease(SDMutexHandle);
		sprintf((char*) pcWriteBuffer,
				" %s is not empty use prune to remove it and its contents\n",
				path);
		return pdFALSE;
	}
	osMutexRelease(SDMutexHandle);
	sprintf((char*) pcWriteBuffer, " %s Deleted\n", path);
	return pdFALSE;
}

FRESULT delete_node(TCHAR *path, /* Path name buffer with the sub-directory to delete */
UINT sz_buff, /* Size of path name buffer (items) */
FILINFO *fno /* Name read buffer */
) {
	UINT i, j;
	FRESULT res;
	DIR dir;

	res = f_opendir(&dir, path); /* Open the sub-directory to make it empty */
	if (res != FR_OK) {
		return res;
	}

	for (i = 0; path[i]; i++)
		; /* Get current path length */
	path[i++] = _T('/');

	for (;;) {
		res = f_readdir(&dir, fno); /* Get a directory item */
		if (res != FR_OK || !fno->fname[0]) {
			break; /* End of directory? */
		}
		j = 0;
		do { /* Make a path name */
			if (i + j >= sz_buff) { /* Buffer over flow? */
				res = 100;
				break; /* Fails with 100 when buffer overflow */
			}
			path[i + j] = fno->fname[j];
		} while (fno->fname[j++]);
		if (fno->fattrib & AM_DIR) { /* Item is a sub-directory */
			res = delete_node(path, sz_buff, fno);
		} else { /* Item is a file */
			res = f_unlink(path);
		}
		if (res != FR_OK) {
			break;
		}
	}

	path[--i] = 0; /* Restore the path name */
	f_closedir(&dir);

	if (res == FR_OK) {
		res = f_unlink(path); /* Delete the empty sub-directory */
	}
	return res;
}

static BaseType_t prvCommandPrune(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	BaseType_t xParamLen;
	FRESULT res;
	TCHAR buff[256];
	FILINFO Finfo;
	const char *path = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen);
	osMutexWait(SDMutexHandle, osWaitForever);
	strcpy(buff, path);

	// Delete the directory
	res = delete_node(buff, sizeof buff / sizeof buff[0], &Finfo);
	// Check the result
	if (res) {
		sprintf((char*) pcWriteBuffer, "Failed to delete the directory. (%u)\n",
				res);
	} else {
		sprintf((char*) pcWriteBuffer,
				" %s directory and the contents have successfully been deleted.\n",
				path);
	}
	osMutexRelease(SDMutexHandle);
	return pdFALSE;
}

static BaseType_t prvCommandRename(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	BaseType_t xParamLen;
	const char *filename = FreeRTOS_CLIGetParameter(pcCommandString, 1,
			&xParamLen);
	const char *newfilename = FreeRTOS_CLIGetParameter(pcCommandString, 2,
			&xParamLen);

	osMutexWait(SDMutexHandle, osWaitForever);
	FRESULT res = f_rename(filename, newfilename);
	if (res != FR_OK) {
		sprintf((char*) pcWriteBuffer, " Disk Error: %s\n",
				getSdStatusStr(res));
		return pdFALSE;
	}
	osMutexRelease(SDMutexHandle);
	sprintf((char*) pcWriteBuffer, "%s renamed to %s\n", filename, newfilename);
	return pdFALSE;
}

static BaseType_t prvCommandDir(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	BaseType_t xParamLen;
	const char *parampath;
	char path[_MAX_LFN + 1];
	DIR Dir;
	FATFS *fs;
	FRESULT res;
	FILINFO Finfo;
	DWORD dw;
	UINT sz = _MAX_LFN + 1;
	char fnamestr[_MAX_LFN + 1];
	uint32_t acc_size = 0;
	uint32_t acc_dirs = 0;
	uint32_t acc_files = 0;

	parampath = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen);
	osMutexWait(SDMutexHandle, osWaitForever); //( SDMutexHandle, portMAX_DELAY );
	if (parampath == NULL) {
		res = f_getcwd(path, sz);
		if (res != FR_OK) {
			osMutexRelease(SDMutexHandle);
			sprintf((char*) pcWriteBuffer, " Disk Error: %s\n",
					getSdStatusStr(res));
			return pdFALSE;
		}
		//strcpy(path, "/");
	} else {
		strcat(path, parampath);
	}

	res = f_opendir(&Dir, path);
	if (res != FR_OK) {
		osMutexRelease(SDMutexHandle);
		sprintf((char*) pcWriteBuffer, " Disk Error: %s\n",
				getSdStatusStr(res));
		return pdFALSE;
	}

	//acc_size = acc_dirs = acc_files = 0;
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
		strcpy(fnamestr, Finfo.fname);
		sprintf(pcWriteBuffer, "%c%c%c%c%c %u/%02u/%02u %02u:%02u %9lu  %s\n",
				(Finfo.fattrib & AM_DIR) ? 'D' : '-',
				(Finfo.fattrib & AM_RDO) ? 'R' : '-',
				(Finfo.fattrib & AM_HID) ? 'H' : '-',
				(Finfo.fattrib & AM_SYS) ? 'S' : '-',
				(Finfo.fattrib & AM_ARC) ? 'A' : '-', (Finfo.fdate >> 9) + 1980,
				(Finfo.fdate >> 5) & 15, Finfo.fdate & 31, (Finfo.ftime >> 11),
				(Finfo.ftime >> 5) & 63, (long unsigned int) Finfo.fsize,
				fnamestr);
		if ((Finfo.fattrib & AM_SYS) != AM_SYS) {
			safe_cdc_write_const(pcWriteBuffer, strlen(pcWriteBuffer));
		}
		memset(pcWriteBuffer, 0x00, MAX_OUT_STR_LEN);

	}

	sprintf((char*) pcWriteBuffer,
			"  %4u File(s)\t %u bytes total\n   %4u Dir(s)",
			(unsigned int) acc_files, (unsigned int) acc_size,
			(unsigned int) acc_dirs);
	safe_cdc_write_const(pcWriteBuffer, strlen(pcWriteBuffer));
	memset(pcWriteBuffer, 0x00, MAX_OUT_STR_LEN);
	res = f_getfree(path, (DWORD*) &dw, &fs);
	if (res == FR_OK) {
		char bytestr[10];
		char fmtstr[128];
		strcpy(fmtstr, " \t %.0f %s free\n");
		double sz = ((double) dw * (double) fs->csize) * 512.0;
		if (sz > (1 * 1024 * 1024 * 1024)) {
			sz = sz / 1024 / 1024 / 1024;
			strcpy(bytestr, "GB");
			strcpy(fmtstr, " \t %.1f  %s free\n");
		} else if (sz > (1 * 1024 * 1024)) {
			sz = sz / 1024 / 1024;
			strcpy(bytestr, "MB");
		} else {
			strcpy(bytestr, "bytes");
		}
		sprintf(pcWriteBuffer, fmtstr, sz, bytestr);
	} else {
		sprintf((char*) pcWriteBuffer, " Disk Error: %s\n",
				getSdStatusStr(res));
	}
	osMutexRelease(SDMutexHandle);
	return pdFALSE;
}

void safe_cdc_write_const(char message[], uint32_t message_size) {
	char *chunk = message;
	for (size_t i = 0; i + CHUNK_SIZE < message_size; i += CHUNK_SIZE)
	{
		xEventGroupClearBits(Send_Complete_Handle, SEND_COMPLETE_BIT);
		tud_cdc_write(chunk, CHUNK_SIZE);
		tud_cdc_write_flush();
		chunk += CHUNK_SIZE;
		xEventGroupWaitBits(Send_Complete_Handle, SEND_COMPLETE_BIT, false,
		true, portMAX_DELAY);
	}
	xEventGroupClearBits(Send_Complete_Handle, SEND_COMPLETE_BIT);
	tud_cdc_write(chunk, strlen(chunk));
	tud_cdc_write_flush();
	xEventGroupWaitBits(Send_Complete_Handle, SEND_COMPLETE_BIT, false, true,
	portMAX_DELAY);
}

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {
	(void) itf;
	(void) rts;

	// TODO set some indicator
	if (dtr) {
		// Terminal connected
	} else {
		// Terminal disconnected
	}
}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf) {
	(void) itf;
}

void tud_cdc_tx_complete_cb(uint8_t itf) {
	(void) itf;
	xEventGroupSetBits(Send_Complete_Handle, SEND_COMPLETE_BIT);
}

void tud_cdc_send_break_cb(uint8_t itf, uint16_t duration_ms) {

}

void tud_cdc_line_coding_cb(uint8_t itf, cdc_line_coding_t const *p_line_coding) {

}

void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char) {

}

/**
 * @brief Task to handle user commands via serial communication.
 * @param *pvParams Data passed at task creation.
 * @retval void
 */
void startCdcTask(void const *argument) {

	char cReadCh = '\0';
	connect_state_t cdcstate = CDCWAITCONNECT;
	//bool connected = false;
	//bool firstconnect = true;
	uint16_t uInputIndex = 0;
	BaseType_t xMoreDataToProcess;
	char pcInputString[MAX_IN_STR_LEN];
	char pcPrevInputString[MAX_IN_STR_LEN];
	char pcOutputString[MAX_OUT_STR_LEN];
	char asciiCmdStr[16];
	disp_data_t msg;
	memset(pcInputString, 0x00, MAX_IN_STR_LEN);
	memset(pcPrevInputString, 0x00, MAX_IN_STR_LEN);
	memset(pcOutputString, 0x00, MAX_OUT_STR_LEN);

	/* Create a queue to store characters from RX ISR */

	Send_Complete_Handle = xEventGroupCreate();

	xbspConsoleInit();

	while (1) {
		switch (cdcstate) {
		case CDCWAITCONNECT:
			if (tud_cdc_connected() == true) {
				cdcstate = CDCFIRSTCONNECT;
			}
			break;
		case CDCFIRSTCONNECT:
			//while (tud_cdc_connected() == false) {
			//		osDelay(100);
			strcpy(msg.str, "Cli Connected");
			xQueueSendToBack(displayQueueHandle, &msg, (TickType_t ) 10);
			cdcstate = CDCWAITCHAR;
			safe_cdc_write_const(pcWelcomeMsg, strlen(pcWelcomeMsg));
			safe_cdc_write_const(prvpcPrompt, strlen(prvpcPrompt));
			break;
		case CDCWAITCHAR:
			if (tud_cdc_available() == true) {
				cdcstate = CDCPROCESSCHAR;
			}
			//update the adc values while waiting
			if (uxQueueMessagesWaiting(adcQueueHandle)) {
				if (xQueueReceive(adcQueueHandle, &adcData,
						(TickType_t) 10) == pdPASS) {

				}
			}
			// update the camera fps
			if (uxQueueMessagesWaiting(cameraQueueHandle)) {
				if (xQueueReceive(cameraQueueHandle, &cameraData,
						(TickType_t) 10) == pdPASS) {

				}
			}
			// check if we have been disconnected
			if (tud_cdc_connected() == false) {
				cdcstate = CDCDISCONNECT;
			}
			break;

		case CDCPROCESSCHAR:
			tud_cdc_read(&cReadCh, sizeof(char));

			switch (cReadCh) {
			case ASCII_CR:
			case ASCII_LF:
				if (uInputIndex != 0) {
					strcpy(asciiCmdStr, "\n\n");
					safe_cdc_write_const(asciiCmdStr, strlen(asciiCmdStr));
					strncpy(pcPrevInputString, pcInputString, MAX_IN_STR_LEN);
					do {
						xMoreDataToProcess = FreeRTOS_CLIProcessCommand(
								pcInputString, /* Command string*/
								pcOutputString, /* Output buffer */
								MAX_OUT_STR_LEN /* Output buffer size */
								);
						safe_cdc_write_const(pcOutputString,
								strlen(pcOutputString));
					} while (xMoreDataToProcess != pdFALSE);
				}
				uInputIndex = 0;
				memset(pcInputString, 0x00, MAX_IN_STR_LEN);
				memset(pcOutputString, 0x00, MAX_OUT_STR_LEN);
				strcpy(asciiCmdStr, "\n");
				safe_cdc_write_const(asciiCmdStr, strlen(asciiCmdStr));
				safe_cdc_write_const(prvpcPrompt, strlen(prvpcPrompt));

				break;
			case ASCII_FORM_FEED:
				strcpy(asciiCmdStr, "\x1b[2J\x1b[0;0H\n");
				safe_cdc_write_const(asciiCmdStr, strlen(asciiCmdStr));
				safe_cdc_write_const(asciiCmdStr, strlen(prvpcPrompt));
				break;
			case ASCII_CTRL_PLUS_C:
				uInputIndex = 0;
				memset(pcInputString, 0x00, MAX_IN_STR_LEN);
				strcpy(asciiCmdStr, "\n");
				safe_cdc_write_const(asciiCmdStr, strlen(asciiCmdStr));
				safe_cdc_write_const(asciiCmdStr, strlen(prvpcPrompt));
				break;
			case ASCII_DEL:
			case ASCII_NACK:
			case ASCII_BACKSPACE:
				if (uInputIndex > 0) {
					uInputIndex--;
					pcInputString[uInputIndex] = '\0';
					strcpy(asciiCmdStr, "\b \b");
					safe_cdc_write_const(asciiCmdStr, strlen(asciiCmdStr));
				}
				break;
			case ASCII_TAB:
				while (uInputIndex) {
					uInputIndex--;
					strcpy(asciiCmdStr, "\b \b");
					safe_cdc_write_const(asciiCmdStr, strlen(asciiCmdStr));
				}
				strncpy(pcInputString, pcPrevInputString, MAX_IN_STR_LEN);
				uInputIndex = (unsigned char) strlen(pcInputString);
				safe_cdc_write_const(pcInputString, strlen(pcInputString));
				break;
			default:
				/* Check if read character is between [Space] and [~] in ASCII table */
				if (uInputIndex < (MAX_IN_STR_LEN - 1)
						&& (cReadCh >= 32 && cReadCh <= 126)) {
					pcInputString[uInputIndex] = cReadCh;
					safe_cdc_write_const((char*) &cReadCh, sizeof(char));
					uInputIndex++;
					//cReadCh = '\0';
				}
				break;
			}
			cdcstate = CDCWAITCHAR;
			break;
		case CDCDISCONNECT:
			strcpy(msg.str, "Cli Disconnected");
			xQueueSendToBack(displayQueueHandle, &msg, (TickType_t ) 10);
			cdcstate = CDCWAITCONNECT;
			break;
		}
		osDelay(10);
	}

}

/**
 * @brief Initialize the console by registering all commands and creating a task.
 * @param usStackSize Task console stack size
 * @param uxPriority Task console priority
 * @param *pxUartHandle Pointer for uart handle.
 * @retval FreeRTOS status
 */
void xbspConsoleInit(void) {
	const CLI_Command_Definition_t *pCommand;

	/* Register all commands that can be accessed by the user */
	for (pCommand = xCommands; pCommand->pcCommand != NULL; pCommand++) {
		FreeRTOS_CLIRegisterCommand(pCommand);
	}
}

/*void startCdcTask(void *argument) {

 xbspConsoleInit();
 //for (pCommand = xCommands; pCommand->pcCommand != NULL; pCommand++) {
 //		FreeRTOS_CLIRegisterCommand(pCommand);
 //}
 for (;;) {
 // There are data available
 //	while (tud_cdc_available()) {
 //		uint8_t buf[64];
 //		// read and echo back
 //		uint32_t count = tud_cdc_read(buf, sizeof(buf));
 //		(void) co  unt;
 //		tud_cdc_write(buf, count);
 //	}

 vTaskConsole();
 //tud_cdc_write_flush();
 osDelay(1);
 }

 }*/

/**
 * @brief Callback for UART RX, triggered any time there is a new character.
 * @param *huart Pointer to the uart handle.
 * @retval void
 */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
//	if (xQueueRxHandle != NULL) {
//		xQueueSendToBackFromISR(xQueueRxHandle, &cRxData,
//				&pxHigherPriorityTaskWoken);
//	}
//	vConsoleEnableRxInterrupt();
//}
