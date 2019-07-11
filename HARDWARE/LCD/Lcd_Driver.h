/******************************************************************************
//本程序适用与STM32F103RB
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PB13（SCL）
//              SDA   接PB15（SDA）
//              RES   接PD15
//              DC    接PD14
//              CS    接PD13 
//							BL		接(暂时接vcc)
*******************************************************************************/

#ifndef _LCD_H_
#define _LCD_H_

#include "myconfig.h"

/*屏幕分辨率*/
#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160

/*屏幕颜色*/
#define RED  		0x001f
#define GREEN		0x07e0
#define BLUE 		0xf800
#define WHITE		0xffff
#define BLACK		0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   			//灰色0 31650 011000 1011 00101
#define GRAY1   0x8410      	//灰色1 00000 000000 00000
#define GRAY2   0x4208      	//灰色2 11111 111110 11111

/*io口*/
#define LCD_SCL        	GPIO_Pin_13	 
#define LCD_SDA        	GPIO_Pin_15	
#define LCD_CS        	GPIO_Pin_13  
#define LCD_LED        	GPIO_Pin_10  
#define LCD_RS         	GPIO_Pin_14	  //DC
#define LCD_RST     		GPIO_Pin_15	

//#define LCD_CS_SET(x) LCD_CTRL->ODR=(LCD_CTRL->ODR&~LCD_CS)|(x ? LCD_CS:0)

/*液晶控制口置1操作语句宏定义*/
#define	LCD_SCL_SET  	GPIOB->BSRR=LCD_SCL    
#define	LCD_SDA_SET  	GPIOB->BSRR=LCD_SDA   
#define	LCD_CS_SET  	GPIOD->BSRR=LCD_CS   
#define	LCD_LED_SET  	GPIOD->BSRR=LCD_LED   
#define	LCD_RS_SET  	GPIOD->BSRR=LCD_RS 
#define	LCD_RST_SET  	GPIOD->BSRR=LCD_RST 

/*液晶控制口置0操作语句宏定义*/
#define	LCD_SCL_CLR  	GPIOB->BRR=LCD_SCL  
#define	LCD_SDA_CLR  	GPIOB->BRR=LCD_SDA 
#define	LCD_CS_CLR  	GPIOD->BRR=LCD_CS     
#define	LCD_LED_CLR  	GPIOD->BRR=LCD_LED 
#define	LCD_RST_CLR  	GPIOD->BRR=LCD_RST
#define	LCD_RS_CLR  	GPIOD->BRR=LCD_RS 


#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //数据输出
#define LCD_DATAIN     LCD_DATA->IDR;   //数据输入

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 



void LCD_GPIO_Init(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index,u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int Lcd_ReadPoint(u16 x,u16 y);
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);
void Lcd_Clear_partial(u8 x1,u8 y1,u8 x2,u8 y2,u16 Color);
void lcd_LEDControl(u8 sw);

#endif
