#include "bell.h"
#include "myconfig.h"

void Bell_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);	//使能PORTC时钟
	/*PE14*/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				//设置成推挽输出
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
	 GPIO_SetBits(GPIOE,GPIO_Pin_14);						 //PE.14 输出高
}




