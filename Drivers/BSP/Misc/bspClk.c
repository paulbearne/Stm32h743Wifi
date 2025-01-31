/**
******************************************************************************
* @file    bspClk.c
* @author  Aaron Escoboza, Github account: https://github.com/aaron-ev
* @brief   source file to implement functions related to the clock tree.
******************************************************************************
*/

#include "bspClk.h"

/**
* @brief Gets system clock, PCLKx and CLK dividers.
* @param *pcWriteBuffer pointer to buffer where clock information
          will be stored.
* @param xWriteBufferLen buffer length.
* @retval void
*/
void bspGetClockIinfo(char *pcWriteBuffer, size_t xWriteBufferLen)
{
    uint32_t uPCLK1;
    uint32_t uPCLK2;
    uint32_t uSysClock;
    uint32_t FLatency;
    RCC_ClkInitTypeDef  RCC_ClkInitStruct;

    /* Update clock system according to register values */
    SystemCoreClockUpdate();
    HAL_RCC_GetClockConfig(&RCC_ClkInitStruct,&FLatency);
    /* Read SysClock, PCLK1 and PCLK2 */
    uSysClock = HAL_RCC_GetHCLKFreq();
    uPCLK1 = HAL_RCC_GetPCLK1Freq();
    uPCLK2 = HAL_RCC_GetPCLK2Freq();
    /* Calculate APB1 and APB2*/


    snprintf(pcWriteBuffer, xWriteBufferLen,
                "Clock name           Hz       kHz       MHz\n"\
                "===========       ========  ========  ========\n"\
                "System clock      %lu     %lu        %lu\n"\
                "APB1 peripheral   %lu     %lu        %lu\n"\
                "APB2 peripheral   %lu     %lu        %lu\n",
                uSysClock, uSysClock / 1000, uSysClock / 1000000,
                uPCLK1, uPCLK1 / 1000, uPCLK1 / 1000000,
                uPCLK2, uPCLK2 / 1000, uPCLK2 / 1000000);
}
