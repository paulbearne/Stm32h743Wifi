/**
  ******************************************************************************
  * @file    bspPwm.h
  * @author  Aaron Escoboza, Github account: https://github.com/aaron-ev
  * @brief   Header file that exposes PWM data types and PWM APIs
  ******************************************************************************
*/

#ifndef __BSP_PWM_H
#define __BSP_PWM_H

#include "stdint.h"
#include "stm32h7xx_hal.h"
//#include "bspTypeDef.h"

#define PWM_GPIO_INSTANCE                   GPIOC
#define PWM_GPIO_PINX                       GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
#define PWM_GPIO_ALTERNATE                  GPIO_AF1_TIM2
#define PWM_TIM_INSTANCE                    TIM2

typedef enum
{
    PWM_CH_1,
    PWM_CH_2,
    PWM_CH_3,
    PWM_CH_4,
    MAX_PWM_CH,
} pwmChannels_e;

typedef enum {
	PwmChannelError,
	PwmFrequencyError,
	PwmHalError,
	PwmOK
} pwmerror_t;

pwmerror_t bspPwmInit(void);
TIM_HandleTypeDef* bspPwmGetHandler(void);
pwmerror_t bspPwmSetFreq(uint32_t uNewFreq);
void bspPwmStart(pwmChannels_e eChannelIndex);
pwmerror_t bspPwmSetDuty(uint8_t uNewDuty, pwmChannels_e xChannel);

#endif
