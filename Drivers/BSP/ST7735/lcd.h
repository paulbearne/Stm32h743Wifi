#ifndef __LCD_H
#define __LCD_H		

#include "main.h"
#include "st7735.h"
#include <stdio.h>

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40
#define BRRED 			 0XFC07
#define GRAY  			 0X8430
#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458

void startLcd(void);
void lcdSetBrightness(uint32_t Brightness);
void lcdShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode);
void lcdShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p);
void lcdClearScr();
void lcdSetTextColor(uint32_t color);
void lcdSetBackColor(uint32_t color);
extern ST7735_Ctx_t ST7735Ctx;

#endif  
