/*
 * displaytask.c
 *
 *  Created on: Jan 30, 2025
 *      Author: paul
 */
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bspRtc.h"
#include "string.h"
#include "rtc.h"
#include "lcd.h"

disp_data_t msglist[3];


static void RTC_CalendarShow(RTC_DateTypeDef *sdatestructureget,
		bsp_rtc_datetime_t *stimestructureget) {

	/* Both time and date must be obtained or RTC cannot be read next time */
	/* Get the RTC current Time */
	//HAL_RTC_GetTime(&hrtc, stimestructureget, RTC_FORMAT_BIN);
	bspRtcGetTime(stimestructureget);

	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, sdatestructureget, RTC_FORMAT_BIN);
}

void updateScreen(void) {
	//lcdClearScr();
	lcdShowString(msglist[0].x, msglist[0].y, ST7735Ctx.Width, 16, 16,
			(uint8_t*) msglist[0].str);
	lcdShowString(msglist[1].x, msglist[1].y, ST7735Ctx.Width, 16, 16,
			(uint8_t*) msglist[1].str);
	//sprintf((char*) &text, "LCD ID:0x%X", (unsigned int) st7735_id);
	lcdShowString(msglist[2].x, msglist[2].y, ST7735Ctx.Width, 16, 16,
			(uint8_t*) msglist[2].str);
}

/**
 * @brief Function implementing the DISPLAYTASK thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_startDisplayTask */
void startDisplayTask(void const *argument) {
	/* USER CODE BEGIN startDisplayTask */
	disp_data_t queuemsg;
	uint8_t text[50];

	bool lcdStarted = false;
	RTC_DateTypeDef sdatestructureget;
	bsp_rtc_datetime_t dateTime;

	bspRtcInit();
	sprintf((char*) &msglist[0].str, "ESP32 Wifi App");
	msglist[0].x = 4;
	msglist[0].y = 4;
	sprintf((char*) &msglist[1].str, "STM32H7xx 0x%X",
			(unsigned int) HAL_GetDEVID());
	msglist[1].x = 4;
	msglist[1].y = 22;
	startLcd();
	sprintf((char*) &msglist[2].str, "LCD ID: 0x%X", (unsigned int) st7735_id);
	msglist[2].x = 4;
	msglist[2].y = 40;
	lcdSetBrightness(10);
	lcdSetBackColor(BLUE);
	lcdClearScr();
	for (;;) {

		osDelay(100);
		if (lcdStarted == false) {
			updateScreen();
			lcdStarted = true;
		} else {
			if (uxQueueMessagesWaiting(displayQueueHandle) > 0) {
				if (xQueueReceive(displayQueueHandle, &queuemsg,
						(TickType_t) 10) == pdPASS) {
					strcpy(msglist[0].str, msglist[1].str);
					strcpy(msglist[1].str, msglist[2].str);
					sprintf(msglist[2].str,"%-20s",queuemsg.str);
					updateScreen();
				}
			}
			RTC_CalendarShow(&sdatestructureget, &dateTime);

			//if (stimestructureget.uSeconds % 2 == 1)
			sprintf((char*) &text, "Time: %02d:%02d:%02d", dateTime.uHours,
					dateTime.uMinutes, dateTime.uSeconds);
			//else
			//	sprintf((char*) &text, "Time: %02d %02d",
			//		stimestructureget.uHours, stimestructureget.Minutes);
			lcdShowString(4, 58, 160, 16, 16, text);

			//	sprintf((char*) &text, "Tick: %u ms", (unsigned int) HAL_GetTick());
			//	lcdShowString(4, 74, 160, 16, 16, text);
		}
	}
	/* USER CODE END startDisplayTask */
}
