#include "pes.h"
#include "myconfig.h"

/*

* 函数介绍：光电传感器初始化
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/

void pesInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	//使能PORTC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能PORTA时钟
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//使能PORTB时钟
	/*PC2、PC3*/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 				//设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/*PA15*/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 				//设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
}



///*

//* 函数介绍：光电传感器IO口配置
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：无
//* 作者    ：@断忆

//*/

//static void GPIOConfig(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	//使能PORTC时钟
//	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能PORTA时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);	//使能PORTE时钟
//	/*PC2、PC3、PC4*/
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 				//设置成上拉输入
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	/*PE7、PE8*/
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7|GPIO_Pin_8;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 				//设置成上拉输入
// 	GPIO_Init(GPIOE, &GPIO_InitStructure);
//	
//}

///*

//* 函数介绍：左右光电外部中断配置
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：无
//* 作者    ：@断忆

//*/
//void pesInit(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;
//	
//	GPIOConfig();
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
//	
//	/*PC2*/
//	EXTI_ClearITPendingBit(EXTI_Line2);  
//  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);//PC8
//  EXTI_InitStructure.EXTI_Line= EXTI_Line2; //PC2，为：EXTI_Line2 
//  EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;   
//  EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;   //中断方式为下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;  
//  EXTI_Init(&EXTI_InitStructure);
//	
//	/*PC3*/
//	EXTI_ClearITPendingBit(EXTI_Line3);  
//  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);//PC3
//  EXTI_InitStructure.EXTI_Line= EXTI_Line3; //PC3，为：EXTI_Line3 
//  EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;   
//  EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;   //中断方式为下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;  
//  EXTI_Init(&EXTI_InitStructure);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;  
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 1;  //抢断优先级
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1;         //响应优先级
//  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;     
//  NVIC_Init(&NVIC_InitStructure);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;  
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 1;  //抢断优先级
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1;         //响应优先级
//  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;     
//  NVIC_Init(&NVIC_InitStructure);	
//}

///*PC3 触发外部中断*/
//void EXTI3_IRQHandler(void)
//{
//		if(EXTI_GetITStatus(EXTI_Line3) != RESET)         //这里为判断相应的中断号是否进入中断
//	{
//		pes_R = 1;
//		
//		EXTI_ClearITPendingBit(EXTI_Line3);       			//清中断  
//	}
//	
//}


///*PC2 触发外部中断*/
//void EXTI2_IRQHandler(void)
//{
//		if(EXTI_GetITStatus(EXTI_Line2) != RESET)         //这里为判断相应的中断号是否进入中断
//	{
//		pes_L = 1;
//		
//		EXTI_ClearITPendingBit(EXTI_Line2);       			//清中断  
//	}
//	
//}



///*

//* 函数介绍：左光电外部中断开关(PC2)
//* 输入参数：开始：newState==START，停止：newState==STOP
//* 输出参数：无
//* 返回值  ：无
//* 作者    ：@断忆

//*/
//void pesLSwitch(SWITCHState newState)
//{
//	if(newState == START)
//	{
//		EXTI->IMR |=  0x04;
//		EXTI->PR=0;
//	}
//	else if(newState == STOP)
//			EXTI->IMR &= (~0x04);
//}

///*

//* 函数介绍：右光电外部中断开关(PC3)
//* 输入参数：开始：newState==START，停止：newState==STOP
//* 输出参数：无
//* 返回值  ：无
//* 作者    ：@断忆

//*/
//void pesRSwitch(SWITCHState newState)
//{
//	if(newState == START)
//	{
//		EXTI->IMR |=  0x08;
//		EXTI->PR=0;
//	}
//	else if(newState == STOP)
//			EXTI->IMR &= (~0x08);
//}












