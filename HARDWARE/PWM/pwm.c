#include "pwm.h"
#include "myconfig.h"

/*

* 函数介绍：电机两路PWM初始化
* 输入参数：arr（自动重装值），psc（时钟预分频数）
* 输出参数：无
* 返回值  ：无

*/
static void TIM4_PWM_Init(u16 arr,u16 psc)       
{    
	GPIO_InitTypeDef 				 GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			 TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);     //使能TIM4外设时钟使能
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  // 使能GPIO外设时钟使能
	                                                                     	
	//配置（PB6,PB7,PB8,PB9）为复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;      
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; 												//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 											//设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 									//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 						//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 								//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 		//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; 																//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 				//输出极性:TIM输出比较极性高
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  												//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  												//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  												//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  												//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  	 
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM4, ENABLE);  
                            
}     

/*

* 函数介绍：舵机PWM初始化
* 输入参数：arr（自动重装值），psc（时钟预分频数）
* 输出参数：无
* 返回值  ：无

*/
static void TIM8_PWM_Init(u16 arr,u16 psc)       
{    
	GPIO_InitTypeDef 				 GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			 TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);     //使能TIM8外设时钟使能
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  // 使能GPIO外设时钟使能
	                                                                     	
	//配置（PC6,PC7,PC8,PC9）为复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;      
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; 												//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 											//设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 									//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 						//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 								//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 		//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; 																//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 				//输出极性:TIM输出比较极性高
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  												//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  												//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  												//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  												//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC2PreloadConfig(TIM8,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  	 
	TIM_OC4PreloadConfig(TIM8,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM8, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM8, ENABLE);  
                            
}     


/*

* 函数介绍：对任意舵机进行任意角度控制
* 输入参数：num(想控制的舵机)(参数：HEAD、L_ARM、R_ARM)，angle（想转过的角度）(参数：L_90，L_45，MID ，R_45，R_90 )
* 输出参数：无
* 返回值  ：无

*/
void sgAngleControl(SgNumber num,RotationAngle angle)
{
	switch(num)
	{
		case HEAD	:	TIM8->CCR3 = angle;break;
		case L_ARM: TIM8->CCR1 = angle;break;
		case R_ARM:	TIM8->CCR2 = angle;break;
		default 	: break;
	}
}

/*

* 函数介绍：舵机PWM频率初始化成50赫兹
* 输入参数：无
* 输出参数：无
* 返回值  ：无

*/
void sg_PWM_Init(void)
{
	TIM8_PWM_Init(7200-1,200-1); //初始化PWM频率为50hz
	sgAngleControl(HEAD,H_MID);
	sgAngleControl(L_ARM,L_DOWN);
	sgAngleControl(R_ARM,R_DOWN);
}




/*

* 函数介绍：电机PWM频率初始化成10k
* 输入参数：无
* 输出参数：无
* 返回值  ：无

*/
void motor_PWM_Init(void)
{
	TIM4_PWM_Init(7200-1,0); //初始化PWM频率为10k
	speedAdjustment(0,0);
}

/*

* 函数介绍：左右轮子速度的调节
* 输入参数：lspeed（左轮的占空比）rspeed（右轮的占空比）
* 输出参数：无
* 返回值  ：无

*/
void speedAdjustment(int lspeed,int rspeed)
{
	  if(rspeed>0)   
	{
		TIM4->CCR4 = 0;         // PB9
		TIM4->CCR3 = rspeed;	  // PB8          

	}
	else
	{ 
	  TIM4->CCR3 = 0;
		TIM4->CCR4 = -rspeed;              
	}
	
	if(lspeed>0)
 	{		
		TIM4->CCR2 = lspeed;	   			//PB7
		TIM4->CCR1 = 0;	  //PB6     
	}
		else
		{
	  TIM4->CCR1 = -lspeed;
		TIM4->CCR2 = 0;	         
		}
	
}

/*

* 函数介绍：(增量式)最终对电机PWM的输出
* 输入参数：motorSpeedTypeDef(保存最新的速度参数)，dSpeed（偏差速度）
* 输出参数：无
* 返回值  ：无
* 其他    ：实现让小车能够在设定的速度下稳定跑直线
*/
void incrementalSpeedOut(motorSpeedTypeDef *p,int dSpeed)
{
	dSpeed=dSpeed/2;
	p->leftSpeed  -= dSpeed;
	p->rightSpeed += dSpeed;
  
	speedAdjustment(p->leftSpeed,p->rightSpeed);

}

/*

* 函数介绍：(增量式)最终对电机PWM的输出
* 输入参数：leftSpeed(初始左轮速度)，rightSpeed（初速右轮速度），dSpeed（偏差速度）
* 输出参数：无
* 返回值  ：无
* 其他    ：实现让小车能够在设定的速度下稳定跑直线
*/
void positionSpeedOut(int leftSpeed,int rightSpeed,int dSpeed)
{
	dSpeed=dSpeed/2;
	leftSpeed  -= dSpeed;
	rightSpeed += dSpeed;

	speedAdjustment(leftSpeed,rightSpeed);

}

/*

* 函数介绍：设定速度记录器（结构体motorSpeedTypeDef）初始化进行设置
* 输入参数：speedRegulator（速度记录器），leftSpeed（左轮初始值）rightSpeed（右轮初始值）
* 输出参数：无
* 返回值  ：无
* 其他		：无
*/
void speedRec_Init(motorSpeedTypeDef *speedRegulator,int leftSpeed,int rightSpeed)
{
	speedRegulator->leftSpeed = leftSpeed;
	speedRegulator->rightSpeed = rightSpeed;
}




