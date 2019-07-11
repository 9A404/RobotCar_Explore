#include "timer.h"
#include "adc.h"
#include "mpu6050.h"
#include "myconfig.h"

/*

* 函数介绍：配置TIM2
* 输入参数：arr(自动重载值),psc(预分频系数)
* 输出参数：无
* 返回值  ：无

*/
static void TIM2_Config(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 					NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 							//时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; 												//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 											//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 									//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 						//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2 , TIM_IT_Update , ENABLE);							//使能TIM2的更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  							//TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	 //抢占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  				//响应优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//IRQ通道被使能
	
	NVIC_Init(&NVIC_InitStructure);  												//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	
							 
}

/*

* 函数介绍：采样时间初始化，默认频率为10k
* 输入参数：采样周期time/10毫秒
* 输出参数：无
* 返回值  ：无

*/
void sampingTime_Init(u16 time)
{
	TIM2_Config(time-1,7200-1);
	sampingStart(START);

}

/*

* 函数介绍：采样启动/停止控制
* 输入参数：开始：newState==START，停止：newState==STOP
* 输出参数：无
* 返回值  ：无

*/
void sampingStart(SWITCHState newState)
{
	if(newState == START)
			TIM_Cmd(TIM2, ENABLE);  	//使能TIMx外设
	else if(newState == STOP)
			TIM_Cmd(TIM2, DISABLE);  //不使能TIMx外设
}

/*

* 函数介绍：TIM2中断处理函数
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 其他：中断一次就更新一次glsensor_ad_value[NUM_OF_SENSOR]
*/
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
    {
			ADC_ConvertOnce();	
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx更新中断标志 
    }
}



/*

* 函数介绍：配置TIM5
* 输入参数：arr(自动重载值),psc(预分频系数)
* 输出参数：无
* 返回值  ：无

*/
static void TIM5_Config(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 					NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 							//时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; 												//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 											//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 									//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 						//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM5 , TIM_IT_Update , ENABLE);							//使能TIM5的更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  							//TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	 //抢占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  				//响应优先级1级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//IRQ通道被使能
	
	NVIC_Init(&NVIC_InitStructure);  												//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
						 
}

/*

* 函数介绍：TIM中断处理函数
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 其他：		中断一次就更新一次欧拉角
*/
void TIM5_IRQHandler(void)
{
	static u8 times;
	u8 i;
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  //检查TIM5更新中断发生与否
    {
		  #ifdef _NEW_MPU6050_
		   MPU6050_Pose_usart();
		  #else 
			for(i=0;i<30;i++)
				MPU6050_Pose();
          #endif		
//		  glPitchbuff[0] = glPitchbuff[1] ;
//			glPitchbuff[1] = glPitch;
//			gldif_Pitch = glPitchbuff[1]-glPitchbuff[0];
			/*上台检测*/
			if(U_Dswitch == 1)
			{
				if((mpu6050_flag == 0) && glPitch < -13)
				{
					times++;
					if(times > 0)
					{
						mpu6050_flag = 1;
						times=0;
					}
				
				}
				else if((mpu6050_flag == 1)&&(glPitch>-10))
				{
					times++;
					if(times>2)
					{
						mpu6050_flag = 2;
						times = 0;
					}
				}
//				if((mpu6050_flag == 0)&&(gldif_Pitch < -5.0))
//					mpu6050_flag = 1;
//				else if((mpu6050_flag == 1)&&(gldif_Pitch > 4))
//					mpu6050_flag = 2;
			}
			
			/*下台检测*/
			else if(U_Dswitch == 2)
			{
				if(mpu6050_flag==0 && glPitch>10)
					mpu6050_flag = 1;
				else if(mpu6050_flag==1 && glPitch <8)
					mpu6050_flag = 2;
			}
//			
			
      TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //清除TIMx更新中断标志 
    }
}

/*

* 函数介绍：采样启动/停止控制
* 输入参数：开始：newState==START，停止：newState==STOP
* 输出参数：无
* 返回值  ：无

*/
void mpu6050_samping(SWITCHState newState)
{
	if(newState == START)
			TIM_Cmd(TIM5, ENABLE);  	//使能TIMx外设
	else if(newState == STOP)
			TIM_Cmd(TIM5, DISABLE);  //不使能TIMx外设
}


/*

* 函数介绍：采样时间初始化，默认频率为10k
* 输入参数：采样周期time/10毫秒
* 输出参数：无
* 返回值  ：无

*/
void mpu6050_sampingTime_Init(u16 time)
{
	TIM5_Config(time-1,7200-1);
	mpu6050_samping(STOP);

}


/*

* 函数介绍：配置TIM3
* 输入参数：arr(自动重载值),psc(预分频系数)
* 输出参数：无
* 返回值  ：无

*/
void TIM3_Config(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 					NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 							//时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; 												//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 											//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 									//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 						//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3 , TIM_IT_Update , ENABLE);							//使能TIM2的更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  							//TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	 //抢占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  				//响应优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//IRQ通道被使能
	
	NVIC_Init(&NVIC_InitStructure);  												//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
						 
}

/*

* 函数介绍：TIM3中断处理函数
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 其他：中断一次就更新一次glsensor_ad_value[NUM_OF_SENSOR]
*/
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
    {
			gl_time++;
      TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志 
    }
}


/*

* 函数介绍：定时器3开关
* 输入参数：开始：newState==START，停止：newState==STOP
* 输出参数：无
* 返回值  ：无

*/
void Time3(SWITCHState newState)
{
	if(newState == START)
			TIM_Cmd(TIM3, ENABLE);  	//使能TIMx外设
	else if(newState == STOP)
			TIM_Cmd(TIM3, DISABLE);  //不使能TIMx外设
}


























