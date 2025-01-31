/**
  ******************************************************************************
  * @file    bspRtc.h
  * @author  Aaron Escoboza, Github account: https://github.com/aaron-ev
  * @brief   Header file that exposes RTC APIs
  ******************************************************************************
*/

#ifndef __BSP_RTC_H
#define __BSP_RTC_H

#include "stdint.h"
#include "stm32h7xx_hal.h"
//#include "bspTypeDef.h"

typedef struct
{
    uint8_t uHours;
    uint8_t uMinutes;
    uint8_t uSeconds;
}bsp_rtc_datetime_t;

typedef enum {
	RtcOK = 0,
	SetTimeError,
	GetTimeError,
	SetDateError,
	GetDateError,
	RtcInitError,
	RtcError
}bsp_rtc_error_t;

bsp_rtc_error_t bspRtcInit(void);
bsp_rtc_error_t bspRtcGetTime(bsp_rtc_datetime_t* bspRtcDateTime);
bsp_rtc_error_t bspRtcSetTime(bsp_rtc_datetime_t* bspRtcDateTime);

#endif
