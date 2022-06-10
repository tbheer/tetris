//#include "stm32f4xx_hal.h"
#include "stm32h7xx_hal.h"
#include "st7735.h"
//#include "cpp_main.h"
//#include "main.h"

#define DELAY 0x80
int32_t Ymax,Ymin,X;        // X goes from 0 to 127
int32_t Yrange; //YrangeDiv2;
int TimeIndex;
uint16_t PlotBGColor;
 
static void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	uint8_t buffer[4], error=0;

    	lcd7735_sendCmd(ST7735_CASET); // Column addr set

/*		lcd7735_sendData(0x00);            // XS15 ~ XS8
		lcd7735_sendData(x0+ST7735_XSTART);     // XSTART       XS7 ~ XS0
		lcd7735_sendData(0x00);            // XE15 ~ XE8
		lcd7735_sendData(x1+ST7735_XSTART);     // XEND         XE7 ~ XE0
 */

    	buffer[0] = 0x00;
    	buffer[1]= (x0+ST7735_XSTART);
    	buffer[2] = 0x00;
    	buffer[3] = (x1+ST7735_XSTART);
    	LCD_DC1;
    	HAL_SPI_Transmit(&hspi5, buffer,sizeof(buffer),HAL_MAX_DELAY);
        if(error == HAL_ERROR || error == HAL_TIMEOUT || error == HAL_BUSY)
        {
        	error = 0;
        }
        LCD_CS1;
        LCD_CS0;
		lcd7735_sendCmd(ST7735_RASET); // Row addr set
/*		lcd7735_sendData(0x00);
		lcd7735_sendData(y0+ST7735_YSTART);     // YSTART
		lcd7735_sendData(0x00);
		lcd7735_sendData(y1+ST7735_YSTART);     // YEND
	*/
    	buffer[0] = 0x00;
    	buffer[1]= (y0+ST7735_YSTART);
    	buffer[2] = 0x00;
    	buffer[3] = (y1+ST7735_YSTART);
    	LCD_DC1;
    	HAL_SPI_Transmit(&hspi5, buffer,sizeof(buffer),HAL_MAX_DELAY);
        if(error == HAL_ERROR || error == HAL_TIMEOUT || error == HAL_BUSY)
        {
        	error = 0;
        }
        LCD_CS1;
        LCD_CS0;
		lcd7735_sendCmd(ST7735_RAMWR); 
}
void ST7735_Init() {		// Vor ausführen idealerweise Reset mit Seesaw ausführen
    //ST7735_Select();
	LCD_CS0;
    //ST7735_Reset();
//	LCD_RST0;		Müsste mit Seesaw Umgesetzt werden
//	HAL_Delay(7);
//	LCD_RST1;
	
    //ST7735_ExecuteCommandList(init_cmds1);
		ST7735_Init_Command1();
    //ST7735_ExecuteCommandList(init_cmds2);
		ST7735_Init_Command2();
    //ST7735_ExecuteCommandList(init_cmds3);
		ST7735_Init_Command3();
	
    //ST7735_Unselect();
		LCD_CS1;		
}
 
void ST7735_Init_Command1(void)
{
	uint8_t buffer[10];
	lcd7735_sendCmd(ST7735_SWRESET);		//  1: Software reset
	HAL_Delay(150);
	lcd7735_sendCmd(ST7735_SLPOUT);			//  2: Out of sleep mode
	HAL_Delay(500);
	lcd7735_sendCmd(ST7735_FRMCTR1);		//  3: Frame rate ctrl - normal mode
/*	lcd7735_sendData(0x01);							//     Rate = fosc/(1x2+40) * (LINE+2C+2D)
	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x2D);*/
	buffer[0]=0x01;
	buffer[1]=0x2C;
	buffer[2]=0x2D;
	HAL_SPI_Transmit(&hspi5, buffer, 3,HAL_MAX_DELAY);

	lcd7735_sendCmd(ST7735_FRMCTR2);		//  4: Frame rate control - idle mode
/*	lcd7735_sendData(0x01);							//  Rate = fosc/(1x2+40) * (LINE+2C+2D)
	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x2D);*/
	buffer[0]=0x01;
	buffer[1]=0x2C;
	buffer[2]=0x2D;
	HAL_SPI_Transmit(&hspi5, buffer, 3,HAL_MAX_DELAY);

	lcd7735_sendCmd(ST7735_FRMCTR3);		//  5: Frame rate ctrl - partial mode
/*	lcd7735_sendData(0x01);							//     Dot inversion mode
	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x2D);
	lcd7735_sendData(0x01);							//     Line inversion mode
	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x2D);*/
	buffer[0]=0x01;
	buffer[1]=0x2C;
	buffer[2]=0x2D;
	buffer[3]=0x01;
	buffer[4]=0x2C;
	buffer[5]=0x2D;
	HAL_SPI_Transmit(&hspi5, buffer, 6,HAL_MAX_DELAY);

	lcd7735_sendCmd(ST7735_INVCTR);			//  6: Display inversion ctrl
//	lcd7735_sendData(0x07);
	buffer[0]=0x07;
	HAL_SPI_Transmit(&hspi5, buffer, 1,HAL_MAX_DELAY);

	//     No inversion
	lcd7735_sendCmd(ST7735_PWCTR1);			//  7: Power control
/*	lcd7735_sendData(0xA2);
	lcd7735_sendData(0x02);							//     -4.6V
	lcd7735_sendData(0x84);	*/
	buffer[0]=0xA2;
	buffer[1]=0x02;
	buffer[2]=0x84;
	HAL_SPI_Transmit(&hspi5, buffer, 3,HAL_MAX_DELAY);

	//     AUTO mode
	lcd7735_sendCmd(ST7735_PWCTR2);			//  8: Power control
//	lcd7735_sendData(0xC5);
	buffer[0]=0xC5;
	HAL_SPI_Transmit(&hspi5, buffer, 1,HAL_MAX_DELAY);

	//     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
	lcd7735_sendCmd(ST7735_PWCTR3);			//  9: Power control
//	lcd7735_sendData(0x0A);							//     Opamp current small
//	lcd7735_sendData(0x00);
	buffer[0]=0x0A;
	buffer[1]=0x00;
	HAL_SPI_Transmit(&hspi5, buffer, 2,HAL_MAX_DELAY);

	//     Boost frequency
	lcd7735_sendCmd(ST7735_PWCTR4);			// 10: Power control
//	lcd7735_sendData(0x8A);							//     BCLK/2, Opamp current small & Medium low
//	lcd7735_sendData(0x2A);
	buffer[0]=0x8A;
	buffer[1]=0x2A;
	HAL_SPI_Transmit(&hspi5, buffer, 2,HAL_MAX_DELAY);

	lcd7735_sendCmd(ST7735_PWCTR5);			// 11: Power control
//	lcd7735_sendData(0x8A);
//	lcd7735_sendData(0xEE);
	buffer[0]=0x8A;
	buffer[1]=0xEE;
	HAL_SPI_Transmit(&hspi5, buffer, 2,HAL_MAX_DELAY);

	lcd7735_sendCmd(ST7735_VMCTR1);			// 12: Power control
//	lcd7735_sendData(0x0E);
	buffer[0]=0x0E;
	HAL_SPI_Transmit(&hspi5, buffer, 1,HAL_MAX_DELAY);

	lcd7735_sendCmd(ST7735_INVOFF);			// 13: Don't invert display
	lcd7735_sendCmd(ST7735_MADCTL);			// 14: Memory access control (directions)
//	lcd7735_sendData(ST7735_ROTATION);	//     row addr/col addr, bottom to top refresh
	buffer[0]=ST7735_ROTATION;
	HAL_SPI_Transmit(&hspi5, buffer, 1,HAL_MAX_DELAY);
	lcd7735_sendCmd(ST7735_COLMOD);			// 15: set color mode
//	lcd7735_sendData(0x05);							//     16-bit color
	buffer[0]=0x05;
	HAL_SPI_Transmit(&hspi5, buffer, 1,HAL_MAX_DELAY);
}
 
void ST7735_Init_Command2(void)
{
	uint8_t buffer[4];
	lcd7735_sendCmd(ST7735_CASET);			//  1: Column addr set
/*	lcd7735_sendData(0x00);							//     XSTART = 0
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);							//     XEND = 127
	lcd7735_sendData(0x7F);*/

	buffer[0]=0x00;
	buffer[1]=0x00;
	buffer[2]=0x00;
	buffer[3]=0x7F;
	HAL_SPI_Transmit(&hspi5, buffer, 4,HAL_MAX_DELAY);

	lcd7735_sendCmd(ST7735_RASET);			//  2: Row addr set
/*	lcd7735_sendData(0x00);							//     YSTART = 0
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);							//     YEND = 127
	lcd7735_sendData(0x7F);*/

	buffer[0]=0x00;
	buffer[1]=0x00;
	buffer[2]=0x00;
	buffer[3]=0x9F;									// YEND = 159
	HAL_SPI_Transmit(&hspi5, buffer, 4,HAL_MAX_DELAY);
}
 
void ST7735_Init_Command3(void)
{
	uint8_t buffer[16];
	lcd7735_sendCmd(ST7735_GMCTRP1);  //  1: Magical unicorn dust

/*	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x02);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x1C);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x07);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x12);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x37);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x32);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x29);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x2D);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x29);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x25);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x2B);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x39);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x00);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x01);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x03);
	lcd7735_sendData(0x12);					//	lcd7735_sendData(0x10);
	*/
	buffer[0] = 0x02;
	buffer[1] = 0x1C;
	buffer[2] = 0x07;
	buffer[3] = 0x12;
	buffer[4] = 0x37;
	buffer[5] = 0x32;
	buffer[6] = 0x29;
	buffer[7] = 0x2D;
	buffer[8] = 0x29;
	buffer[9] = 0x25;
	buffer[10] = 0x2B;
	buffer[11] = 0x39;
	buffer[12] = 0x00;
	buffer[13] = 0x01;
	buffer[14] = 0x03;
	buffer[15] = 0x10;
	HAL_SPI_Transmit(&hspi5, buffer, 16,HAL_MAX_DELAY);

	lcd7735_sendCmd(ST7735_GMCTRN1);  //  2: Sparkles and rainbows
/*	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x03);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x1D);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x07);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x06);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x2E);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x29);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x2D);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x2E);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x2E);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x37);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x3F);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x00);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x00);
	lcd7735_sendData(0x10);					//	lcd7735_sendData(0x02);
	lcd7735_sendData(0x10);	*/				//	lcd7735_sendData(0x10);

	buffer[0] = 0x03;
	buffer[1] = 0x1D;
	buffer[2] = 0x07;
	buffer[3] = 0x06;
	buffer[4] = 0x2E;
	buffer[5] = 0x2C;
	buffer[6] = 0x29;
	buffer[7] = 0x2D;
	buffer[8] = 0x2E;
	buffer[9] = 0x2E;
	buffer[10] = 0x37;
	buffer[11] = 0x3F;
	buffer[12] = 0x00;
	buffer[13] = 0x00;
	buffer[14] = 0x02;
	buffer[15] = 0x10;
	HAL_SPI_Transmit(&hspi5, buffer, 16,HAL_MAX_DELAY);


	lcd7735_sendCmd(ST7735_NORON);
	HAL_Delay(10);
	lcd7735_sendCmd(ST7735_DISPON);
	HAL_Delay(100);
}


void ST7735_PlotPoint(int32_t data1, uint16_t color1){
  data1 = ((data1 - Ymin)*100)/Yrange;
  if(data1 > 98){
    data1 = 98;
    color1 = ST7735_RED;
  }
  if(data1 < 0){
    data1 = 0;
    color1 = ST7735_RED;
  }
  ST7735_DrawPixel(TimeIndex + 11, 116 - data1, color1);
  ST7735_DrawPixel(TimeIndex + 11, 115 - data1, color1);
}

void ST7735_PlotIncrement(void){
  TimeIndex = TimeIndex + 1;
  if(TimeIndex > 99){
    TimeIndex = 0;
  }
  ST7735_DrawFastVLine(TimeIndex + 11, 17, 100, PlotBGColor);
}

void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
        return;
 
    LCD_CS0;
 
    ST7735_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[2];
		data[0] = color >> 8;
		data[1] = color & 0xFF;
		LCD_DC1;
		HAL_SPI_Transmit(&hspi5, data,sizeof(data),HAL_MAX_DELAY);
		//lcd7735_sendData(data[0]);
		//lcd7735_sendData(data[1]);
 
		LCD_CS1;  //unselect
}
uint32_t ST7735_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor){
  uint32_t count = 0;
  if(y>15) return 0;
  while(*pt){
    ST7735_DrawCharS(x*6, y*10, *pt, textColor, ST7735_BLACK, 1);
    pt++;
    x = x+1;
    if(x>20) return count;  // number of characters printed
    count++;
  }
  return count;  // number of characters printed
}

uint32_t ST7735_DrawString_wS(uint16_t x, uint16_t y, char *pt, int16_t textColor, uint8_t size){
  uint32_t count = 0;
//  if(y>15) return 0;
  while(*pt){
    ST7735_DrawCharS(x, y, *pt, textColor, ST7735_BLACK, size);
    pt++;
    x = x+(6*size);
    if(x>128) return count;  // number of characters printed
    count++;
  }
  return count;  // number of characters printed
}



void ST7735_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size){
  uint8_t line; 
  int32_t i, j;
  if((x >= ST7735_WIDTH)            || 
     (y >= ST7735_HEIGHT)           || 
     ((x + 5 * size - 1) < 0) || 
     ((y + 8 * size - 1) < 0))   
    return;
 
  for (i=0; i<6; i++ ) {
    if (i == 5)
      line = 0x0;
    else
      line = Font[(c*5)+i];
    for (j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) 
          ST7735_DrawPixel(x+i, y+j, textColor);
        else {  
        	ST7735_FillRectangle_mod(x+(i*size), y+(j*size), size, size, textColor);
        }
      } else if (bgColor != textColor) {
        if (size == 1) // default size
          ST7735_DrawPixel(x+i, y+j, bgColor);
        else {  // big size
        	ST7735_FillRectangle_mod(x+i*size, y+j*size, size, size, bgColor);
        }
      }
      line >>= 1;
    }
  }
}

void ST7735_Drawaxes(uint16_t axisColor, uint16_t bgColor, char *xLabel,char *yLabel1, uint16_t label1Color, char *yLabel2, uint16_t label2Color,int32_t ymax, int32_t ymin)
	{
  int i;

  Ymax = ymax;
  Ymin = ymin;
  Yrange = Ymax - Ymin;
  TimeIndex = 0;
  PlotBGColor = bgColor;
	LCD_CS0;
  ST7735_FillRectangle(0, 0, 128, 160, bgColor);
  ST7735_DrawFastHLine(10, 140, 101, axisColor);
  ST7735_DrawFastVLine(10, 17, 124, axisColor);
  for(i=20; i<=110; i=i+10){
    ST7735_DrawPixel(i, 141, axisColor);
  }
  for(i=17; i<120; i=i+10){
    ST7735_DrawPixel(9, i, axisColor);
  }
  i = 50;
  while((*xLabel) && (i < 100)){
    ST7735_DrawCharS(i, 145, *xLabel, axisColor, bgColor, 1);
    i = i + 6;
    xLabel++;
  }
  if(*yLabel2){ // two labels
    i = 26;
    while((*yLabel2) && (i < 50)){
      ST7735_DrawCharS(0, i, *yLabel2, label2Color, bgColor, 1);
      i = i + 8;
      yLabel2++;
    }
    i = 82;
  }else{ // one label
    i = 42;
  }
  while((*yLabel1) && (i < 120)){
   ST7735_DrawCharS(0, i, *yLabel1, label1Color, bgColor, 1);
    i = i + 8;
    yLabel1++;
  }
	LCD_CS1;
}
	
void ST7735_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  uint8_t buffer[] = {(uint8_t)(color >> 8), (uint8_t)color};

  LCD_CS0;
  // Rudimentary clipping
  if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
  if((x+w-1) >= ST7735_WIDTH)  w = ST7735_WIDTH-x;
  ST7735_SetAddressWindow(x, y, x+w-1, y);
  LCD_DC1;//Set DC HIGH
  while (w--) {
	  HAL_SPI_Transmit(&hspi5, buffer, sizeof(buffer),HAL_MAX_DELAY);
  }
  LCD_CS1;

}

void ST7735_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	uint8_t buffer[] = {(uint8_t)(color >> 8), (uint8_t)color};
	LCD_CS0;

  // Rudimentary clipping
  if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
  if((y+h-1) >= ST7735_HEIGHT) h = ST7735_HEIGHT-y;
  ST7735_SetAddressWindow(x, y, x, y+h-1);
  LCD_DC1;//Set DC HIGH
  while (h--) {
	  HAL_SPI_Transmit(&hspi5, buffer, sizeof(buffer),HAL_MAX_DELAY);
  }
  LCD_CS1;
}
	
void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
	uint8_t buffer[] = {color >> 8, color & 0xFF };

    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) w = ST7735_WIDTH - x;
    if((y + h - 1) >= ST7735_HEIGHT) h = ST7735_HEIGHT - y;
 
    LCD_CS0;
    ST7735_SetAddressWindow(x, y, x+w-1, y+h-1);
    LCD_DC1;
    for(y = h; y > 0; y--) {
        for(x = w; x > 0; x--) {
        	HAL_SPI_Transmit(&hspi5, buffer, sizeof(buffer),HAL_MAX_DELAY);
//					lcd7735_sendData(color>>8);
//					lcd7735_sendData(color);
        }
    }
		
		LCD_CS1;  //Unselect
}

void ST7735_FillRectangle_mod(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
	uint8_t buffer[40960], error=0;
	uint16_t i=0;
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) w = ST7735_WIDTH - x;
    if((y + h - 1) >= ST7735_HEIGHT) h = ST7735_HEIGHT - y;

    LCD_CS0;
    ST7735_SetAddressWindow(x, y, x+w-1, y+h-1);
    LCD_DC1;
    for(y = h; y > 0; y--) {
        for(x = w; x > 0; x--) {
        	buffer[i]=(uint8_t) (color>>8) ;
        	i++;
        	buffer[i]=(uint8_t) (color) ;
        	i++;
//					lcd7735_sendData(color>>8);
//					lcd7735_sendData(color);

        }
    }
    LCD_DC1;//Set DC HIGH
    error =  HAL_SPI_Transmit(&hspi5, buffer,i,HAL_MAX_DELAY);
    if(error == HAL_ERROR || error == HAL_TIMEOUT || error == HAL_BUSY)
    {
    	error = 0;
    }

	LCD_CS1;  //Unselect
}



void ST7735_FillScreen(uint16_t color) {
    ST7735_FillRectangle_mod(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}


void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data) {
int16_t skipC = 0;                      
  int16_t originalWidth = w;              
  int i = w*(h - 1);
 
  if((x >= ST7735_WIDTH) || ((y - h + 1) >= ST7735_HEIGHT) || ((x + w) <= 0) || (y < 0)){
    return;                             
  }
  if((w > ST7735_WIDTH) || (h > ST7735_HEIGHT)){    
   
    return;
  }
  if((x + w - 1) >= ST7735_WIDTH){            
    skipC = (x + w) - ST7735_WIDTH;           
    w = ST7735_WIDTH - x;
  }
  if((y - h + 1) < 0){                  
    i = i - (h - y - 1)*originalWidth;  
    h = y + 1;
  }
  if(x < 0){                            
    w = w + x;
    skipC = -1*x;                       
    i = i - x;                          
    x = 0;
  }
  if(y >= ST7735_HEIGHT){                     
    h = h - (y - ST7735_HEIGHT + 1);
    y = ST7735_HEIGHT - 1;
  }
	
	LCD_CS0;  //Select
 
  ST7735_SetAddressWindow(x, y-h+1, x+w-1, y);
 
  for(y=0; y<h; y=y+1){
    for(x=0; x<w; x=x+1){
                                        
      lcd7735_sendData((uint8_t)(data[i] >> 8));
                                        
      lcd7735_sendData((uint8_t)data[i]);
      i = i + 1;                       
    }
    i = i + skipC;
    i = i - 2*originalWidth;
  }
	LCD_CS1;  //Unselect
}
 
void ST7735_InvertColors(bool invert) {
  //ST7735_Select();
	LCD_CS0;
  //ST7735_WriteCommand(invert ? ST7735_INVON : ST7735_INVOFF);
	lcd7735_sendCmd(invert ? ST7735_INVON : ST7735_INVOFF);
  LCD_CS1;  //Unselect
}
 
void lcd7735_sendCmd(uint8_t cmd) {  //uint8_t       //unsigned char
	uint8_t error=0, i = 0;
	LCD_DC0; //Set DC low
	do
	{
		error =  HAL_SPI_Transmit(&hspi5, &cmd,sizeof(cmd),HAL_MAX_DELAY);
		i++;
		if(error == HAL_ERROR || error == HAL_TIMEOUT || error == HAL_BUSY)
		{
		   LCD_DC1; //Set DC low
		   LCD_CS1;
		   HAL_Delay(1);
		   LCD_CS0;
		   LCD_DC0; //Set DC low
		}
	}
	while(((error==HAL_ERROR)|| error==HAL_TIMEOUT|| error == HAL_BUSY) && (i<3));
	LCD_DC1;
   //lcd7735_senddata(cmd);
}
 
 
void lcd7735_sendData(uint8_t data) {  //uint8_t      //unsigned char
   LCD_DC1;//Set DC HIGH
   lcd7735_senddata(data);
}
 
void lcd7735_senddata(uint8_t data) {

	HAL_SPI_Transmit(&hspi5, &data,sizeof(data),HAL_MAX_DELAY);

}
