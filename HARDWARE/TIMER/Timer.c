#include "timer.h"
#include "adc.h"
#include "mpu6050.h"
#include "myconfig.h"

/*

* �������ܣ�����TIM2
* ���������arr(�Զ�����ֵ),psc(Ԥ��Ƶϵ��)
* �����������
* ����ֵ  ����

*/
static void TIM2_Config(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 					NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 							//ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; 												//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 											//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 									//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 						//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2 , TIM_IT_Update , ENABLE);							//ʹ��TIM2�ĸ����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  							//TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	 //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  				//��Ӧ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//IRQͨ����ʹ��
	
	NVIC_Init(&NVIC_InitStructure);  												//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	
							 
}

/*

* �������ܣ�����ʱ���ʼ����Ĭ��Ƶ��Ϊ10k
* �����������������time/10����
* �����������
* ����ֵ  ����

*/
void sampingTime_Init(u16 time)
{
	TIM2_Config(time-1,7200-1);
	sampingStart(START);

}

/*

* �������ܣ���������/ֹͣ����
* �����������ʼ��newState==START��ֹͣ��newState==STOP
* �����������
* ����ֵ  ����

*/
void sampingStart(SWITCHState newState)
{
	if(newState == START)
			TIM_Cmd(TIM2, ENABLE);  	//ʹ��TIMx����
	else if(newState == STOP)
			TIM_Cmd(TIM2, DISABLE);  //��ʹ��TIMx����
}

/*

* �������ܣ�TIM2�жϴ�������
* �����������
* �����������
* ����ֵ  ����
* �������ж�һ�ξ͸���һ��glsensor_ad_value[NUM_OF_SENSOR]
*/
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
    {
			ADC_ConvertOnce();	
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx�����жϱ�־ 
    }
}



/*

* �������ܣ�����TIM5
* ���������arr(�Զ�����ֵ),psc(Ԥ��Ƶϵ��)
* �����������
* ����ֵ  ����

*/
static void TIM5_Config(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 					NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 							//ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; 												//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 											//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 									//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 						//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM5 , TIM_IT_Update , ENABLE);							//ʹ��TIM5�ĸ����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  							//TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	 //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  				//��Ӧ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//IRQͨ����ʹ��
	
	NVIC_Init(&NVIC_InitStructure);  												//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
						 
}

/*

* �������ܣ�TIM�жϴ�������
* �����������
* �����������
* ����ֵ  ����
* ������		�ж�һ�ξ͸���һ��ŷ����
*/
void TIM5_IRQHandler(void)
{
	static u8 times;
	u8 i;
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  //���TIM5�����жϷ������
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
			/*��̨���*/
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
			
			/*��̨���*/
			else if(U_Dswitch == 2)
			{
				if(mpu6050_flag==0 && glPitch>10)
					mpu6050_flag = 1;
				else if(mpu6050_flag==1 && glPitch <8)
					mpu6050_flag = 2;
			}
//			
			
      TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIMx�����жϱ�־ 
    }
}

/*

* �������ܣ���������/ֹͣ����
* �����������ʼ��newState==START��ֹͣ��newState==STOP
* �����������
* ����ֵ  ����

*/
void mpu6050_samping(SWITCHState newState)
{
	if(newState == START)
			TIM_Cmd(TIM5, ENABLE);  	//ʹ��TIMx����
	else if(newState == STOP)
			TIM_Cmd(TIM5, DISABLE);  //��ʹ��TIMx����
}


/*

* �������ܣ�����ʱ���ʼ����Ĭ��Ƶ��Ϊ10k
* �����������������time/10����
* �����������
* ����ֵ  ����

*/
void mpu6050_sampingTime_Init(u16 time)
{
	TIM5_Config(time-1,7200-1);
	mpu6050_samping(STOP);

}


/*

* �������ܣ�����TIM3
* ���������arr(�Զ�����ֵ),psc(Ԥ��Ƶϵ��)
* �����������
* ����ֵ  ����

*/
void TIM3_Config(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 					NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 							//ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; 												//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 											//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 									//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 						//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3 , TIM_IT_Update , ENABLE);							//ʹ��TIM2�ĸ����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  							//TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	 //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  				//��Ӧ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//IRQͨ����ʹ��
	
	NVIC_Init(&NVIC_InitStructure);  												//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
						 
}

/*

* �������ܣ�TIM3�жϴ�������
* �����������
* �����������
* ����ֵ  ����
* �������ж�һ�ξ͸���һ��glsensor_ad_value[NUM_OF_SENSOR]
*/
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
    {
			gl_time++;
      TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
    }
}


/*

* �������ܣ���ʱ��3����
* �����������ʼ��newState==START��ֹͣ��newState==STOP
* �����������
* ����ֵ  ����

*/
void Time3(SWITCHState newState)
{
	if(newState == START)
			TIM_Cmd(TIM3, ENABLE);  	//ʹ��TIMx����
	else if(newState == STOP)
			TIM_Cmd(TIM3, DISABLE);  //��ʹ��TIMx����
}

























