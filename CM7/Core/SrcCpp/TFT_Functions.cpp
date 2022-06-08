#include "TFT_Functions.h"
#include "st7735.h"
#include "main.h"
#include <Adafruit_TFTShield18.h>


void setUpField()
{
	ST7735_DrawFastVLine(0x50, 0x00, 160, ST7735_WHITE);
	ST7735_DrawFastVLine(0x51, 0x00, 160, ST7735_WHITE);
	ST7735_DrawFastHLine(0x51, 0x30, 160, ST7735_WHITE);
	ST7735_DrawFastHLine(0x51, 0x31, 160, ST7735_WHITE);
	for(uint8_t i = 0; i<10; i++)
	{
		ST7735_FillRectangle((i*8), 0, 8, 8, ST7735_RED);
		i++;
		ST7735_FillRectangle((i*8), 0, 8, 8, ST7735_YELLOW);
	}

	for(uint8_t u = 1; u<20; u++)
	{
		ST7735_FillRectangle(0,(u*8), 8, 8, ST7735_YELLOW);
		u++;
		ST7735_FillRectangle(0, (u*8), 8, 8, ST7735_RED);
	}
	char text[] = "test" ;
	ST7735_DrawString_wS(0x0010, 0x0010, text, ST7735_BLUE, 3);
//	ST7735_DrawFastVLine(x, y, h, color)






}
