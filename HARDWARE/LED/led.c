#include "led.h"
#include "myconfig.h"

/*

* 函数介绍：LED灯GPIO配置
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void ledInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	/*配置GPIOE*/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	/*默认不亮*/
	LED0=1;
	LED1=1;
	LED2=1;
}


/*

* 函数介绍：LED灯亮灭N次
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void led_light(u8 n)
{
	u8 i;
	for(i=0;i<n;i++)
	{
		LED0=0;
		LED1=0;
		LED2=0;
		delay_ms(500);
		LED0=1;
		LED1=1;
		LED2=1;
		delay_ms(500);	
	}
}

/*

* 函数介绍：LED0闪烁一次
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void led0_flash()
{
		LED0 = 0;
		delay_ms(50);
		LED0 = 1;
}

/*

* 函数介绍：LED1闪烁一次
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void led1_flash()
{
		LED1 = 0;
		delay_ms(50);
		LED1 = 1;
}




/*

* 函数介绍：蜂鸣器GPIO配置
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void buzzerInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	/*配置GPIOE*/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	/*默认不响*/
	BEEP=1;
}


/*

* 函数介绍：蜂鸣器响起1次
* 输入参数：
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void buzzer_beep()
{
	BEEP = 0;
	delay_ms(20);
	BEEP = 1;
}

















