

#include "bspRtc.h"
#include "stm32h7xx_hal.h"
#include "stdint.h"


static RTC_HandleTypeDef xRtcHandler;

/**
* @brief Get the current time stored in RTC registers
* @param bspRtcTime pointer to a RTC timer structure
* @retval BSP error
*/
bsp_rtc_error_t bspRtcGetTime(bsp_rtc_datetime_t* bspRtcDateTime)
{
    RTC_TimeTypeDef xTime;
    RTC_DateTypeDef sDate;
    HAL_RTC_GetTime(&xRtcHandler, &xTime, RTC_FORMAT_BIN);

    /* There is an issue with STM32, date should be
    *  read after time to make RTC work properly.
    *  Ref: https://community.st.com/t5/stm32-mcus-products/while-reading-the-rtc-not-providing-proper-date-after-the-rtc/td-p/138546
    */
    HAL_RTC_GetDate(&xRtcHandler, &sDate, RTC_FORMAT_BIN);

    bspRtcDateTime->uHours = xTime.Hours;
    bspRtcDateTime->uMinutes = xTime.Minutes;
    bspRtcDateTime->uSeconds = xTime.Seconds;
    return RtcOK;
}

/**
* @brief Set a new time to RTC registers
* @param bspRtcTime pointer to a RTC timer structure
* @retval BSP error
*/
bsp_rtc_error_t bspRtcSetTime(bsp_rtc_datetime_t* bspRtcDateTime)
{
    RTC_TimeTypeDef xTime = {0};
    HAL_StatusTypeDef halStatus;

    if (bspRtcDateTime->uHours < 0 || bspRtcDateTime->uHours > 24)
        return SetTimeError;
    if (bspRtcDateTime->uMinutes < 0 || bspRtcDateTime->uHours > 59)
        return SetTimeError;
    if (bspRtcDateTime->uSeconds < 0 || bspRtcDateTime->uSeconds > 59)
        return SetTimeError;

    xTime.Hours = bspRtcDateTime->uHours;
    xTime.Minutes = bspRtcDateTime->uMinutes;
    xTime.Seconds = bspRtcDateTime->uSeconds;
    halStatus = HAL_RTC_SetTime(&xRtcHandler, &xTime, RTC_FORMAT_BIN);
    if (halStatus != HAL_OK){
        return RtcError;
    }

    return RtcOK;
}

/**
* @brief Initialize RTC peripheral.
* @param void
* @retval BSP error
*/
bsp_rtc_error_t bspRtcInit(void)
 {
    RTC_TimeTypeDef timeDef;

    xRtcHandler.Instance = RTC;
    xRtcHandler.Init.HourFormat = RTC_HOURFORMAT_24;
    xRtcHandler.Init.AsynchPrediv = 127;
    xRtcHandler.Init.SynchPrediv = 255;
    xRtcHandler.Init.OutPut = RTC_OUTPUT_DISABLE;
    xRtcHandler.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_LOW;
    xRtcHandler.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    if (HAL_RTC_Init(&xRtcHandler) != HAL_OK)
        return RtcInitError;

    timeDef.Hours = 12;
    timeDef.Minutes = 0;
    if (HAL_RTC_SetTime(&xRtcHandler, &timeDef, RTC_FORMAT_BIN) != HAL_OK)
        return RtcInitError;

    return RtcOK;
 }
