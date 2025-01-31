#include "lcd.h"
#include "font.h"
#include "spi.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"

//LCD_RST
#define LCD_RST_SET     
#define LCD_RST_RESET  
//LCD_RS//dc  
#define LCD_RS_SET      HAL_GPIO_WritePin(LCD_WR_RS_GPIO_Port,LCD_WR_RS_Pin,GPIO_PIN_SET)//PC4 
#define LCD_RS_RESET    HAL_GPIO_WritePin(LCD_WR_RS_GPIO_Port,LCD_WR_RS_Pin,GPIO_PIN_RESET)
//LCD_CS  
#define LCD_CS_SET      HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_SET)
#define LCD_CS_RESET    HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_RESET)
//SPI Driver
#define SPI spi4
#define SPI_Drv (&hspi4)
#define delay_ms osDelay
#define get_tick xTaskGetTickCount
//LCD_Brightness timer
#define LCD_Brightness_timer &htim1
#define LCD_Brightness_channel TIM_CHANNEL_2

static int32_t lcd_init(void);
static int32_t lcd_gettick(void);
static int32_t lcd_writereg(uint8_t reg, uint8_t *pdata, uint32_t length);
static int32_t lcd_readreg(uint8_t reg, uint8_t *pdata);
static int32_t lcd_senddata(uint8_t *pdata, uint32_t length);
static int32_t lcd_recvdata(uint8_t *pdata, uint32_t length);

uint16_t POINT_COLOR = 0xFFFF;
uint16_t BACK_COLOR = BLACK;

ST7735_IO_t st7735_pIO = { lcd_init,
NULL, 0, lcd_writereg, lcd_readreg, lcd_senddata, lcd_recvdata, lcd_gettick };

ST7735_Object_t st7735_pObj;
uint32_t st7735_id;

void startLcd(void) {

#ifdef TFT96
	ST7735Ctx.Orientation = ST7735_ORIENTATION_LANDSCAPE_ROT180;
	ST7735Ctx.Panel = HannStar_Panel;
	ST7735Ctx.Type = ST7735_0_9_inch_screen;
#elif TFT18
	ST7735Ctx.Orientation = ST7735_ORIENTATION_PORTRAIT;
	ST7735Ctx.Panel = BOE_Panel;
	ST7735Ctx.Type = ST7735_1_8a_inch_screen;
	#else
	error "Unknown Screen"
	
	#endif

	ST7735_RegisterBusIO(&st7735_pObj, &st7735_pIO);
	ST7735_LCD_Driver.Init(&st7735_pObj, ST7735_FORMAT_RBG565, &ST7735Ctx);
	ST7735_LCD_Driver.ReadID(&st7735_pObj, &st7735_id);

	lcdSetBrightness(0);

	//ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, ST7735Ctx.Width,ST7735Ctx.Height, BLACK);

	delay_ms(100);

}

void lcdClearScr(void) {
	ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, 0, ST7735Ctx.Width,
			ST7735Ctx.Height, BACK_COLOR);
}

void lcdSetBrightness(uint32_t Brightness) {
	__HAL_TIM_SetCompare(LCD_Brightness_timer, LCD_Brightness_channel, Brightness);
}

void lcdSetTextColor(uint32_t color) {
	POINT_COLOR = color;
}

void lcdSetBackColor(uint32_t color) {
	BACK_COLOR = color;
}

void lcdShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size,
		uint8_t mode) {
	uint8_t temp, t1, t;
	uint16_t y0 = y;
	uint16_t x0 = x;
	uint16_t colortemp = POINT_COLOR;
	uint32_t h, w;

	uint16_t write[size][size == 12 ? 6 : 8];
	uint16_t count;

	ST7735_GetXSize(&st7735_pObj, &w);
	ST7735_GetYSize(&st7735_pObj, &h);

	num = num - ' ';
	count = 0;

	if (!mode) {
		for (t = 0; t < size; t++) {
			if (size == 12)
				temp = asc2_1206[num][t];
			else
				temp = asc2_1608[num][t];

			for (t1 = 0; t1 < 8; t1++) {
				if (temp & 0x80)
					POINT_COLOR = (colortemp & 0xFF) << 8 | colortemp >> 8;
				else
					POINT_COLOR = (BACK_COLOR & 0xFF) << 8 | BACK_COLOR >> 8;

				write[count][t / 2] = POINT_COLOR;
				count++;
				if (count >= size)
					count = 0;

				temp <<= 1;
				y++;
				if (y >= h) {
					POINT_COLOR = colortemp;
					return;
				}
				if ((y - y0) == size) {
					y = y0;
					x++;
					if (x >= w) {
						POINT_COLOR = colortemp;
						return;
					}
					break;
				}
			}
		}
	} else {
		for (t = 0; t < size; t++) {
			if (size == 12)
				temp = asc2_1206[num][t];
			else
				temp = asc2_1608[num][t];
			for (t1 = 0; t1 < 8; t1++) {
				if (temp & 0x80)
					write[count][t / 2] = (POINT_COLOR & 0xFF) << 8
							| POINT_COLOR >> 8;
				count++;
				if (count >= size)
					count = 0;

				temp <<= 1;
				y++;
				if (y >= h) {
					POINT_COLOR = colortemp;
					return;
				}
				if ((y - y0) == size) {
					y = y0;
					x++;
					if (x >= w) {
						POINT_COLOR = colortemp;
						return;
					}
					break;
				}
			}
		}
	}
	ST7735_FillRGBRect(&st7735_pObj, x0, y0, (uint8_t*) &write,
			size == 12 ? 6 : 8, size);
	POINT_COLOR = colortemp;
}

void lcdShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
		uint8_t size, uint8_t *p) {
	uint8_t x0 = x;
	width += x;
	height += y;
	while ((*p <= '~') && (*p >= ' ')) {
		if (x >= width) {
			x = x0;
			y += size;
		}
		if (y >= height)
			break; //�˳�
		lcdShowChar(x, y, *p, size, 0);
		x += size / 2;
		p++;
	}
}

static int32_t lcd_init(void) {
	int32_t result = ST7735_OK;
	HAL_TIMEx_PWMN_Start(LCD_Brightness_timer, LCD_Brightness_channel);
	return result;
}

static int32_t lcd_gettick(void) {
	uint32_t tickval = get_tick;
	return tickval;
}

static int32_t lcd_writereg(uint8_t reg, uint8_t *pdata, uint32_t length) {
	int32_t result;
	LCD_CS_RESET;
	LCD_RS_RESET;
	result = HAL_SPI_Transmit(SPI_Drv, &reg, 1, 100);
	LCD_RS_SET;
	if (length > 0)
		result += HAL_SPI_Transmit(SPI_Drv, pdata, length, 500);
	LCD_CS_SET;
	if (result > 0) {
		result = -1;
	} else {
		result = 0;
	}
	return result;
}

static int32_t lcd_readreg(uint8_t reg, uint8_t *pdata) {
	int32_t result;
	LCD_CS_RESET;
	LCD_RS_RESET;

	result = HAL_SPI_Transmit(SPI_Drv, &reg, 1, 100);
	LCD_RS_SET;
	result += HAL_SPI_Receive(SPI_Drv, pdata, 1, 500);
	LCD_CS_SET;
	if (result > 0) {
		result = -1;
	} else {
		result = 0;
	}
	return result;
}

static int32_t lcd_senddata(uint8_t *pdata, uint32_t length) {
	int32_t result;
	LCD_CS_RESET;
	//LCD_RS_SET;
	result = HAL_SPI_Transmit(SPI_Drv, pdata, length, 100);
	LCD_CS_SET;
	if (result > 0) {
		result = -1;
	} else {
		result = 0;
	}
	return result;
}

static int32_t lcd_recvdata(uint8_t *pdata, uint32_t length) {
	int32_t result;
	LCD_CS_RESET;
	//LCD_RS_SET;
	result = HAL_SPI_Receive(SPI_Drv, pdata, length, 500);
	LCD_CS_SET;
	if (result > 0) {
		result = -1;
	} else {
		result = 0;
	}
	return result;
}

