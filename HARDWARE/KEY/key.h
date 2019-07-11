#ifndef _KEY_H_
#define _KEY_H_
#include "myconfig.h"


#define KEY0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)		//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)	//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)	//读取按键2 
#define KEY3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)	//读取按键3
#define KEY4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)	//读取按键4

#define KEY0_UP			1			//加 
#define KEY1_DOWN		2		  //减 
#define KEY2_ENTER	3		  //确认  
#define KEY3_MENU		4		  //菜单  
#define KEY4_ESC		5		  //返回 

#define Collision   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)

void keyInit(void); 
u8 keyScan(u8 mode);

#endif



