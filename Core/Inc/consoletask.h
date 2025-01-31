/**
 ******************************************************************************
 * @file    console.h
 * @author  Aaron Escoboza, Github account: https://github.com/aaron-ev
 * @brief   Console header file: APIs to handle the console.
 ******************************************************************************
 */

#ifndef __CONSOLE__H
#define __CONSOLE__H

#include "FreeRTOS.h"

typedef enum {
	ConsoleOK = 0,
	ConsoleReadError,
	ConsoleWriteError,
	ConsoleCommandError,
}bsp_console_error_t;

void xbspConsoleInit(void);
void startCdcTask(void const *argument);

#endif
