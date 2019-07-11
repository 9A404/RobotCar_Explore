#include "key.h"
#include "myconfig.h"


/*

* 函数介绍：按键GPIO配置
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void keyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);
	/*配置GPIOC*/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	/*配置GPIOD*/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);		
}

/*

* 函数介绍：按键扫描
* 输入参数：mode:0,不支持连续按;1,支持连续按;
* 输出参数：无
* 返回值  ：KEY
* 作者    ：@断忆

*/
u8 keyScan(u8 mode)
{
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)			return KEY0_UP;
		else if(KEY1==0)return KEY1_DOWN;
		else if(KEY2==0)return KEY2_ENTER; 
		else if(KEY3==0)return KEY3_MENU;
		else if(KEY4==0)return KEY4_ESC;
	}
	else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1; 	     
	return 0;
}















/************************************按键中断初始化程序*****************************************/
///*

//* 函数介绍：按键GPIO配置
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：无
//* 作者    ：@断忆

//*/
//static void GPIOConfig(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
//	/*配置GPIOC*/
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);	
//	/*配置GPIOD*/
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOD, &GPIO_InitStructure);				
//}

///*

//* 函数介绍：按键外部中断配置
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：无
//* 作者    ：@断忆

//*/
//void keyInit(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;	
//	
//	GPIOConfig();

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
//	/*PC10*/
//	EXTI_ClearITPendingBit(EXTI_Line10);  
//  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource10);//PC10  为GPIOC的PIN10 
//  EXTI_InitStructure.EXTI_Line= EXTI_Line10; //PC10，为：EXTI_Line10  
//  EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;   
//  EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;   //中断方式为下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;  
//  EXTI_Init(&EXTI_InitStructure);
//	/*PC11*/
//	EXTI_ClearITPendingBit(EXTI_Line11);  
//  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource11);//PC11  为GPIOC的PIN10 
//  EXTI_InitStructure.EXTI_Line= EXTI_Line11; //PC11，为：EXTI_Line11  
//  EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;   
//  EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;   //中断方式为下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;  
//  EXTI_Init(&EXTI_InitStructure);
//	/*PC12*/
//	EXTI_ClearITPendingBit(EXTI_Line12);  
//  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource12);//PC12  为GPIOC的PIN12
//  EXTI_InitStructure.EXTI_Line= EXTI_Line12; //PC12，为：EXTI_Line12 
//  EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;   
//  EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;   //中断方式为下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;  
//  EXTI_Init(&EXTI_InitStructure);
//	/*PC13*/
//	EXTI_ClearITPendingBit(EXTI_Line13);  
//  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);//PC13  为GPIOC的PIN13
//  EXTI_InitStructure.EXTI_Line= EXTI_Line13; //PC13，为：EXTI_Line13  
//  EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;   
//  EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;   //中断方式为下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;  
//  EXTI_Init(&EXTI_InitStructure);
//	/*PD0*/
//	EXTI_ClearITPendingBit(EXTI_Line0);  
//  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0);//PD0  为GPIOD的PIN0
//  EXTI_InitStructure.EXTI_Line= EXTI_Line0; //PD0，为：EXTI_Line0 
//  EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;   
//  EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;   //中断方式为下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;  
//  EXTI_Init(&EXTI_InitStructure);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;  
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 3;  //抢断优先级
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 3;         //响应优先级
//  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;     
//  NVIC_Init(&NVIC_InitStructure); 
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;  
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 3;  
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 2;          
//  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;     
//  NVIC_Init(&NVIC_InitStructure); 
//	
//}

//void EXTI15_10_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line10) != RESET)         //这里为判断相应的中断号是否进入中断，用于多个中断
//	{
//		
//		
//		EXTI_ClearITPendingBit(EXTI_Line10);       			//清中断  
//	}
//	
//	if(EXTI_GetITStatus(EXTI_Line11) != RESET)         //这里为判断相应的中断号是否进入中断，用于多个中断
//	{
//		
//		
//		EXTI_ClearITPendingBit(EXTI_Line11);      			 //清中断  
//	}
//	
//	
//	if(EXTI_GetITStatus(EXTI_Line12) != RESET)         //这里为判断相应的中断号是否进入中断，用于多个中断
//	{
//		
//		
//		EXTI_ClearITPendingBit(EXTI_Line12);      			 //清中断  
//	}
//	
//	
//	if(EXTI_GetITStatus(EXTI_Line13) != RESET)         //这里为判断相应的中断号是否进入中断，用于多个中断
//	{
//		
//		
//		EXTI_ClearITPendingBit(EXTI_Line13);      			 //清中断  
//	}

//}

///*PD0 触发外部中断*/
//void EXTI0_IRQHandler(void)
//{
//		if(EXTI_GetITStatus(EXTI_Line0) != RESET)         //这里为判断相应的中断号是否进入中断
//	{
//		delay_ms(10);
//		key0_Flag++;
//		if(3 == key0_Flag)key0_Flag = 0;
//		
//		EXTI_ClearITPendingBit(EXTI_Line0);       			//清中断  
//	}
//	
//}






