#ifndef _LED_H_
#define _LED_H_

#include "myconfig.h"

#define LED0 PEout(2)		// PE2
#define LED1 PEout(4)		// PE3	
#define LED2 PEout(3)		// PE4
#define BEEP PEout(14)	// PE14


void ledInit(void);     //led初始化
void led_light(u8 n);   //点亮led
void buzzerInit(void);  //蜂鸣器初始化
void buzzer_beep(void); //蜂鸣器响起
void led0_flash(void);      //led0闪烁
void led1_flash(void);			//led1闪烁

#endif



