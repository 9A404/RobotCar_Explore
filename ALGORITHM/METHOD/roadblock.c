#include "roadblock.h"
#include "myconfig.h"



/************************************************桥***********************************************************/
/*

* 函数介绍：识别是否为全0
* 输入参数：无
* 输出参数：无
* 返回值  ：1（到达路障）0（未到达路障）
* 其他		：传感器全为0的时候
* 作者    ：@断忆

*/
u8 identifyALL_Zero()
{
		glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold); 
	if( 0x000==glsensor_dig_value)
		return 1;
	else
		return 0;
}

/*

* 函数介绍：到桥头底部识别方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1（到达路障）0（未到达路障）
* 其他		：传感器全为0的时候
* 作者    ：@断忆

*/
u8 identifyComingBrige_Bottom()
{
	static u8 flag=0;
	if( 0==flag && 0==PES_Platform) flag=1;
	else if(1==flag&&1==PES_Platform)
	{
		flag=0;
		return 1;
	}	
	return 0;
}


/*

* 函数介绍：到桥头顶部识别方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1（到达路障）0（未到达路障）
* 其他		：传感器全为0的时候
* 作者    ：@断忆

*/
u8 identifyComingBrige_Top()
{
	static u8 flag=0;
//	if(1==identifyComingBrige_Bottom()) flag=1;
  if(0==flag && 0==PES_Platform)  flag=2;
	else if(2==flag && 1==PES_Platform) 
	{
		flag=0;
		return 1;
	}
		return 0;
}


/*

* 函数介绍：到桥尾顶部识别方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1（到达桥尾）0（未到达桥尾）
* 其他		：传感器全为1的时候
* 作者    ：@断忆

*/
u8 identifyCrossingBrige_Top()
{
	static u8 flag=0;
  if(0==flag && 0==PES_Platform)  flag=1;
	else if(1==flag && 1==PES_Platform) 
	{
		flag=0;
		return 1;
	}
		return 0;


}
/*

* 函数介绍：到桥尾底部部识别方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1（到达桥尾）0（未到达桥尾）
* 其他		：传感器全为1的时候
* 作者    ：@断忆

*/

u8 identifyCrossingBrige_Bottom()
{
	static u8 flag=0;
  if(0==flag && 0==PES_Platform)  flag=1;
	else if(1==flag && 1==PES_Platform) 
	{
		flag=0;
		return 1;
	}
		return 0;

}
/*

* 函数介绍：桥路障处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：将巡线方法切换成过桥的巡线
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Brige()
{
	static u8 flag=0;
	if(0==flag && 1==identifyComingBrige_Bottom())
	{
	//	save = glHello_control.linkInform.findLineWays;
		glHello_control.linkInform.findLineWays = FL_brigeup; 
		findLineFlag = 0;
		flag = 1;
	}
	if(1==flag && 1==identifyComingBrige_Top())
	{
		glHello_control.linkInform.findLineWays = FL_brige; 
		findLineFlag = 0;
		flag=2;
	}
	if(2==flag && 1==identifyCrossingBrige_Top())
	{
		glHello_control.linkInform.findLineWays = FL_brigedown
		;
	  findLineFlag = 0;
		flag=3;
	}
	if(3==flag && 1==identifyCrossingBrige_Bottom())
	{
		glHello_control.linkInform.findLineWays = FL_default;
	  findLineFlag = 0;
		flag=0;
		return 1;
	}
	
	return 0;
//static findLine save;
//	static u8 flag=0;
//     if(0 == flag)
//	 { 
//		 save = glHello_control.linkInform.findLineWays;
//		 Time3(START);
//		 gl_time = 0;
//      flag = 1;		 
//	 }
//	else if(1==flag && gl_time > 40)         //μ?′???í·μ×2?
//	{   
////		speedAdjustment(0,0);
////		while(1);
//	//	delay_ms(500);
//		glHello_control.linkInform.findLineWays = FL_angle; 
//		findLineFlag = 0;
//		angle_flag = 0;
//		flag = 2;
//	}
//	else if(2==flag && gl_time > 140 )          //?ú??í·??é?
//	{
//		
////	k 
//		glHello_control.linkInform.findLineWays = FL_brige; 
//		findLineFlag = 0;
//		flag=3;
//	}
//	else if(3==flag && gl_time > 255)          //?ú??í·?￥2?
//	{
////		speedAdjustment(0,0);
////     	while(1);
////		delay_ms(500);
//		flag=4;
//		Time3(STOP);
//	}
//	else if( 4 == flag )  
//	{
//     Time3(START);
//	 gl_time = 0;
//     glHello_control.linkInform.findLineWays = FL_angle;
//	 findLineFlag = 0; 
//     angle_flag = 0;
//	 flag = 5; 
//	}
//  	//?ú??é?
//	else if(5==flag && gl_time > 105)             //?ú???2?￥2?
//	{
////	    speedAdjustment(0,0);
////     	while(1);
//		glHello_control.linkInform.findLineWays = save;
//	    findLineFlag = 0;
//		flag=0;
//		return 1;
//		
//	}
////	if(6==flag && 0==PES_Platform)  flag=6;
////	if(6==flag && 1==PES_Platform)        //?ú???2μ×2?
////	{
////		glHello_control.linkInform.findLineWays = save;
////	  findLineFlag = 0;
////		flag=0;
////		return 1;
////	}
////	
//	return 0;
}
/************************************************桥***********************************************************/

/***************************************************门********************************************************/
/*

* 函数介绍：过门处理函数
* 输入参数：无
* 输出参数：无
* 返回值  ：1(门开或者更新了线路)0（门关且没有更新线路）
* 其他		：
* 作者    ：@陈

*/
u8 BlockHandleMethod_DOOR(void)
{
	static u8 flag=0;     //门开标志位  

	DoorFlag=1;
	if(0==flag)
	{
		Time3(START);
		gl_time=0;
		flag=1;
	}
	if(1==flag && 0 == PES_H)
	{
		rotAngle_Right(180);
		runMethodUpdate(runMethod,0,runMethodTableDoorAuto);   //39门关闭进行第一次更新路线
		DoorFlag_2=1;
		Control_Init(&glHello_control,runMethod);     //初始化控制台
		runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
		flag=0;
		return 1;
	}
	if(1==flag && gl_time>Door_Time)
	{
		Time3(STOP);
		gl_time = 0;
		led1_flash();
		glHello_control.linkInform.findLineWays = FL_default;  //切换到缺省巡线
		findLineFlag = 0;
		flag=0;
		return 1;
	}
	return 0;
}
/*

* 函数介绍：过门处理函数
* 输入参数：无
* 输出参数：无
* 返回值  ：1(门开或者更新了线路)0（门关且没有更新线路）
* 其他		：
* 作者    ：@陈

*/
u8 BlockHandleMethod_DOOR_2(void)
{
	static u8 flag1=0;     //门开标志位  

	if(0==flag1)
	{
		Time3(START);
		gl_time=0;
		flag1=1;
	}
	if(1==flag1 && 0 == PES_H)
	{
		rotAngle_Right(180);
		runMethodUpdate(runMethod,1,runMethodTableDoorAuto);  //40门关闭进行第二次更新路线
		DoorFlag_2=2;
		Control_Init(&glHello_control,runMethod);     //初始化控制台
		runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
		flag1=0;
		return 1;

	}
	if(1==flag1 && gl_time>Door_Time_2)
	{
		Time3(STOP);
		gl_time = 0;
		led1_flash();
		glHello_control.linkInform.findLineWays = FL_default;  //切换到缺省巡线
		findLineFlag = 0;
		flag1=0;
		return 1;
	}
	return 0;
}
/***************************************************门********************************************************/

/**************************************************平台********************************************************/
/*

* 函数介绍：处理7号平台
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_down_27_26()
{
	static findLine save;
	static u8 flag=0;
	
	if(flag == 0)
	{
		glHello_control.linkInform.findLineWays =NFL;
		flag = 1;
	}
	else if(1==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = FL_downPeak; 
		findLineFlag = 0;
		flag=2;
	}
	else if(2==flag && 0==PES_Platform) flag=3;
	else if(3==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = FL_default; 
		findLineFlag = 0;
		flag=4;
	}
	else if(4==flag && 0==PES_Platform) flag=5;
	else if(5==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = FL_slow; 
		findLineFlag = 0;
		Time3(START); //打开定时器
		gl_time=0;
		flag=6;
	}
	else if(6==flag && gl_time>200)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = save; 
		findLineFlag = 0;
		Time3(STOP); //打开定时器
		gl_time=0;
		flag=0;
		return 1;
	}
		return 0;

}
/*

* 函数介绍：检测是否通过斜坡（翻滚角）
* 输入参数：无
* 输出参数：无
* 返回值  ：翻滚角
* 其他		：
* 作者    ：@断忆

*/
float Monitor_ROLL()
{
	float temp;
	u8 i;
	#ifdef _NEW_MPU6050_
		MPU6050_Pose_usart();
		temp=glRoll;
	#else
		for(i=0;i<50;i++)
			MPU6050_Pose();				//更新欧拉角
		temp=glPitch;
	#endif
	return temp;
}
/*

* 函数介绍:路障读角度方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：将巡线方法切换成过桥的巡线
* 作者    ：你猜

*/
 u8 Angle_read()
{
  static u8 flag=0;
	if(flag == 0)
	{
	  Time3(START);
		gl_time = 0;
		flag = 1;
	}
	else if(flag == 1 && gl_time>80)
	{
		Time3(STOP);
//		speedAdjustment(0,0);
//		while(1);
		MPU6050_Pose_usart();
		angle_read = setYaw(glYaw,-81);	
		flag = 0;  
		return 1;
	}
	return 0;
}


/*

* 函数介绍：过跷跷板
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@林

*/
 u8 BlockHandleMethod_Seesaw()
{
//	static findLine save;
	static u8 flag=0,Turn_Flag=0;
	float temp;
	if(0==flag)                //在找点任务中将车摆正后延时直走
	{	
//		speedAdjustment(2450,2200);
		Time3(START);
		gl_time=0;
		glHello_control.linkInform.findLineWays = FL_angle;
    angle_flag = 0; 		
		findLineFlag = 0;
//		led0_flash();
		flag=1;
	}
	else if(1==flag&&gl_time>100)         
	{
//		temp = Monitor_ROLL();
//		if( temp > -10)               //如果车在跷跷板的另外一端则继续盲走后置flag=2
//		{
//			//flag++;
//			// ("glPitch%0.2f\r\n",temp);
//			speedAdjustment(2000,2000);

//			//glHello_control.linkInform.findLineWays = NFL; 
//			//led_flash();
//			flag=2;
//		}
//		else                         //如果车还没有到则继续盲走
//		{
//			speedAdjustment(2000,2120);
//		
//			delay_ms(1000);
//			delay_ms(200);
//			speedAdjustment(0,0);
//		
//			delay_ms(1000);

//			//u3_printf("glPitch%0.2f\r\n",glPitch);
//		}
		Time3(STOP);
		speedAdjustment(0,0);
		delay_ms(500);	
//		led0_flash();
//		while(1);
		temp = Monitor_ROLL();
		glHello_control.linkInform.findLineWays = FL_slow;
		findLineFlag = 0;
		if(temp>-10)
		{
			speedAdjustment(2000,2000);
			flag=2;
		}
			
		
	}
	else if(2 == flag)                //车子在跷跷板的另外一端则先检测传感器有没有在白线上
	{
		glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量	
		if(calculateNum(glsensor_dig_value)<=1 && Turn_Flag<3) 
		{
			rotAngle_Left(20);             //如果不在白线则左转20度，大多数情况下是车子偏右，故左转
			Turn_Flag++;
		}
		else                         //否则返回1完成障碍任务
		{
			flag=0;
			return 1;
		}
	}
		return 0;

}
/*

* 函数介绍：下平台处理方法（光电开关）
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：下完平台才巡线
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Platform ()
{
	static findLine save;
	static u8 flag=0;
	
	if(flag == 0)
	{
		save = glHello_control.linkInform.findLineWays;
		glHello_control.linkInform.findLineWays =NFL;
		flag = 1;
	}
	else if(1==flag&&1==PES_Platform)
	{
		glHello_control.linkInform.findLineWays = FL_DownPlatform; 
		findLineFlag = 0;
		flag=2;
	}
	else if(2==flag&&0==PES_Platform)  flag=3;
	else if(3==flag&&1==PES_Platform)  flag=4;
	else if(0==PES_Platform && 4==flag)
	{
		glHello_control.linkInform.findLineWays = save; 
		findLineFlag = 0;
		flag = 0;
		return 1;
	}
		return 0;

}


u8  BlockHandleMethod_Platform_37_15 ()
{
		static findLine save;
	static u8 flag=0;
	
	if(flag == 0)
	{
		save = glHello_control.linkInform.findLineWays;
		glHello_control.linkInform.findLineWays =NFL;
		flag = 1;
	}
	else if(1==flag&&1==PES_Platform)
	{
		glHello_control.linkInform.findLineWays = FL_DownPlatform; 
		findLineFlag = 0;
		flag=2;
	}
	else if(2==flag&&0==PES_Platform)  flag=3;
	else if(3==flag&&1==PES_Platform)  flag=4;
	else if(0==PES_Platform && 4==flag)
	{
		glHello_control.linkInform.findLineWays = save; 
		findLineFlag = 0;
		Time3(START);
		gl_time=0;
		flag=5;
	}
	else if(5 == flag && gl_time > 20)
	{
		flag = 6;
		gl_time=0;
		glHello_control.linkInform.findLineWays = FL_quickest;  //切换到超高速巡线
		findLineFlag = 0;
	}
	else if(6 == flag && gl_time > 70)
	{	
		speedAdjustment(0,0);
		delay_ms(500);
		Time3(STOP);
		flag = 0;
		gl_time = 0;
		glHello_control.linkInform.findLineWays = FL_default;  //切换到缺省巡线
		findLineFlag = 0;
		return 1;
	}	
		return 0;

}
/*

* 函数介绍：过山丘方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：无
* 作者    ：@林

*/
u8 BlockHandleMethod_Slope ()
{
	static u8 flag=0;
	static findLine save;
	if(flag == 0)
	{
		save=glHello_control.linkInform.findLineWays;
		flag=1;
	}
	else if(1 == flag&&1 == PES_Platform)          //前下光电开关不亮代表到达山丘底部
	{
			glHello_control.linkInform.findLineWays = FL_UpPlatform;   
			findLineFlag = 0;
			flag=2;	
	}
	else if(2==flag&&0==PES_Platform)         //前下光电开关亮代表到达山丘顶部
	{
		glHello_control.linkInform.findLineWays = FL_DownPlatform;   
		findLineFlag = 0;
		Time3(START); //打开定时器
		gl_time=0;
		flag=3;
	}
	else if(gl_time>260 && 3==flag)
	{
		Time3(STOP); //关闭定时器
		gl_time = 0;
//		speedAdjustment(0,0);
//		delay_ms(1000);
		glHello_control.linkInform.findLineWays = FL_default;   
		findLineFlag = 0;
		flag = 0;
		return 1;
	}
		return 0;

}
/***********************************************平台********************************************************/

/**********************************************起点挡板*****************************************************/
/*

* 函数介绍：挡板判断
* 输入参数：无
* 输出参数：无
* 返回值  ：1（到达路障）0（未到达路障）
* 其他		：前方光电没有检测到就出发
* 作者    ：@断忆

*/
static u8 BlockHandleMethod_Baffle()
{
	static u8 flag=0;
	if(flag == 0)
	{	
		speedAdjustment(0,0);	
				/*方便调试*/
		#ifdef _DJ_CONTROL_
	  sgAngleControl(HEAD,H_L);
	  delay_ms(400);
		sgAngleControl(HEAD,H_R);
		delay_ms(400);
		sgAngleControl(HEAD,H_L);
		delay_ms(400);
		sgAngleControl(HEAD,H_R);
		delay_ms(400);
		sgAngleControl(HEAD,H_MID);
		#endif
		
		#ifdef _LED_CONTROL_
		led_light(2);
		#endif
		
		flag = 1;
	 }	
	while(1==PES_H)  speedAdjustment(0,0);	
	while(0==PES_H)  speedAdjustment(0,0);	
	while(1==PES_H)  
	{
		flag=0;
		return 1;
	}
  return 0;
}

/*

* 函数介绍：下起点处理方法(利用底下光电开关+检测挡板)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：下完平台才巡线
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Platform_1 ()
{
	static findLine save;
	static u8 flag=0;
	if(flag == 0&&1==BlockHandleMethod_Baffle())
	{
		//u3_printf("Baffle+NFL");
		save = glHello_control.linkInform.findLineWays;
		glHello_control.linkInform.findLineWays =NFL;
		flag = 1;
	}
	else if(1==flag&&1==PES_Platform)
	{
		//u3_printf("slow");
		glHello_control.linkInform.findLineWays = FL_DownPlatform; 
		findLineFlag = 0;
		flag=2;
	}
	else if(2==flag&&0==PES_Platform)  flag=3;
	else if(1==PES_Platform && 3==flag)
	{
		//u3_printf("finish");
		glHello_control.linkInform.findLineWays = save; 
		findLineFlag = 0;
		flag = 0;
		return 1;
	}
		return 0;
}
/**********************************************起点挡板*****************************************************/

/************************************************定时********************************************************/
/*

* 函数介绍：定时(复杂节点处理方法)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_TIME()
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		gl_time=0;
		flag=1;
	}
	if(gl_time > 50)
	{	
		Time3(STOP); //关闭定时器
		gl_time = 0;
//		speedAdjustment(0,0);
//		delay_ms(500);
		flag=0;
		return 1;
	}
		
	return 0;

}

/*

* 函数介绍：定时(用于2-5减速板)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_TIME_1()
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		gl_time=0;
		flag=1;
	}
	if(gl_time > 200)
	{	
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag=0;
		return 1;
	}
		
	return 0;

}

/*

* 函数介绍：定时(用于26-27减速板)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_TIME_2()
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		gl_time=0;
		flag=1;
	}
	if(1==flag && gl_time > 200)
	{	
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag=2;
	}
	if(2==flag && 0==PES_Platform) 
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		flag=3;
	}
	if(3==flag &&1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays=FL_upPeak;
		findLineFlag = 0;
		flag=4;
	}
	if(4==flag && 0==PES_Platform) flag=5;
	if(5==flag && 1==PES_Platform) 
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		flag=0;
		return 1;
	}
		
	return 0;

}

/*

* 函数介绍：定时(备用)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_TIME_44_43()
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		gl_time=0;
		flag=1;
	}
	if(gl_time > 20)
	{	
		led1_flash();
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag=0;
		return 1;
	}
		
	return 0;

}
/************************************************定时********************************************************/

/**************************************************梯形景点**************************************************/
/*

* 函数介绍：01梯形景点处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Trapezoid_1()
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START);					 //打开定时器
		gl_time=0;
		flag = 1;
	}
	
	if(1==flag && gl_time>30)
	{
		flag = 2;
		gl_time = 0;
	}
	
	else if(2 == flag)
	{
		glHello_control.linkInform.findLineWays = FL_quickest; 
		findLineFlag = 0;
		flag = 3;
	}
	else if(3==flag && gl_time>S_TIME_6_8)  //加速时间
	{
		glHello_control.linkInform.findLineWays = FL_slow;
	  findLineFlag = 0;
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag = 4;
	}
	else if(4==flag && 0==PES_H)
	{
		glHello_control.linkInform.findLineWays = FL_stop;
	  findLineFlag = 0;
		flag = 0;
		return 1;	
	}
	return 0;
}
	

/*

* 函数介绍：02梯形景点处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Trapezoid_2(void)
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		gl_time=0;
		flag=1;
	}
	if(1==flag && gl_time>20)
	{
		flag = 2;
		gl_time = 0;
	}
	
	else if(2 == flag)
	{
		glHello_control.linkInform.findLineWays = FL_quickest; 
		findLineFlag = 0;
		flag = 3;	

	}
	else if(3==flag && gl_time>S_TIME_10_11)
	{
		glHello_control.linkInform.findLineWays = FL_slow;
	  findLineFlag = 0;
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag = 4;
	}
	else if(4==flag && 0==PES_H)
	{
		glHello_control.linkInform.findLineWays = FL_stop;
	  findLineFlag = 0;
		flag = 0;
		return 1;	
	}
	return 0;
}


/*

* 函数介绍：05、06、07、08梯形景点处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Trapezoid_3()
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		flag=1;
		gl_time=0;
	}
	if(gl_time > 50)
	{	
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag=0;
		return 1;
	}		
	return 0;
}

/**************************************************梯形景点**************************************************/

/*****************************************************斜坡***************************************************/

/*

* 函数介绍：检测是否通过斜坡（翻滚角）
* 输入参数：无
* 输出参数：无
* 返回值  ：翻滚角
* 其他		：
* 作者    ：@断忆

*/
float CrossingTILT_ROLL()
{
	float temp;
	u8 i;
	 #ifdef _NEW_MPU6050_
	   MPU6050_Pose_usart();
	#else
	for(i=0;i<50;i++)	
		MPU6050_Pose();
	#endif				//更新欧拉角
	temp=glPitch;
	return temp;
}

/*
* 函数介绍：右转倾斜路面路障处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@林| @陈

*/

u8 BlockHandleMethod_GO_Tilt_R()
{
	static u8 flag=0,flag1=0;
	if(0==flag && 0==PES_Platform)  
	{
		if(0==flag1)
		{
			Time3(START);
			gl_time=0;
			flag1=1;
		}
		if(gl_time>30 &&1==flag1)
		{
			
			Time3(STOP);
			gl_time=0;
			flag=1;
			flag1=0;
		}
	}
	else if(1==flag && 1==PES_Platform)
	{	
		speedAdjustment(2000,1950);
		delay_ms(280);
		flag=2;
	}
	else if(2==flag && 0==PES_Platform)
	{
		speedAdjustment(0,0);
		delay_ms(50);
		rotAngle_UR(80);
		speedAdjustment(2000,1950);
		delay_ms(450);
		speedAdjustment(0,0);
		flag=3;
	}	
	else if(3==flag && 0==PES_Platform)
	{
		glHello_control.linkInform.findLineWays = FL_slow;
		findLineFlag = 0;
		flag=0;
		return 1;
	}
	return 0;
}
//	static u8 flag;
//	if(0==flag && 0==PES_Platform)  flag=1;
//	else if(1==flag && 1==PES_Platform)
//	{	
//		speedAdjustment(2000,2000);
//		delay_ms(280);
//		flag=2;
//	}
//	else if(2==flag && 0==PES_Platform)
//	{
//		speedAdjustment(0,0);
//		delay_ms(50);
//		rotAngle_UR(80);
//		speedAdjustment(2000,2000);
//		delay_ms(450);
//		speedAdjustment(0,0);
//		flag=3;
//	}	
//	else if(3==flag && 0==PES_Platform)
//	{
//		glHello_control.linkInform.findLineWays = FL_slow;
//		findLineFlag = 0;
//		flag=0;
//		return 1;
//	}
//	return 0;


/*
* 函数介绍：左转倾斜路面路障处理方法(前往)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@林| @陈

*/
u8 BlockHandleMethod_GO_Tilt_L()
{
//	static u8 flag,flag1=0;
//	if(0==flag && 0==PES_Platform)  
//	{
//		if(0==flag1)
//		{
//			Time3(START);
//			gl_time=0;
//			flag1=1;
//		}
//		if(gl_time>30 &&1==flag1)
//		{
//			
//			Time3(STOP);
//			gl_time=0;
//			flag=1;
//			flag1=0;
//		}
//	}
//	else if(1==flag && 1==PES_Platform)
//	{	
//		speedAdjustment(2000,1950);
//		delay_ms(260);
//		flag=2;
//	}
//	else if(2==flag && 0==PES_Platform)
//	{
//		speedAdjustment(0,0);
//		delay_ms(50);
//		rotAngle_UL(90);
//		speedAdjustment(2000,2000);
//		delay_ms(450);
//		speedAdjustment(0,0);
//		flag=3;
//	}	
//	else if(3==flag && 0==PES_Platform)
//	{
//		glHello_control.linkInform.findLineWays = FL_default;
//		findLineFlag = 0;
//		flag=0;
//		return 1;
//	}
//	return 0;
	static u8 flag,flag1=0;
	if(0==flag && 0==PES_Platform)  
	{
		if(0==flag1)
		{
			Time3(START);
			gl_time=0;
			flag1=1;
		}
		if(gl_time>30 &&1==flag1)
		{
			
			Time3(STOP);
			gl_time=0;
			flag=1;
			flag1=0;
		}
	}
	else if(1==flag && 1==PES_Platform)
	{		
    Time3(START);
		gl_time=0;
		glHello_control.linkInform.findLineWays = FL_angle;
		findLineFlag = 0;
		angle_flag = 0;
		flag=2;
	}
	else if(2==flag && gl_time>12)
	{
		Time3(STOP);
		rotAngle_UL(80);
		speedAdjustment(2000,2000);
		delay_ms(450);
		speedAdjustment(0,0);
		glHello_control.linkInform.findLineWays = FL_default;
		findLineFlag = 0;
		flag=0;
		return 1;
	}	
	return 0;
}
/*
* 函数介绍：倾斜路面路障处理方法（回）
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@林| @陈

*/

u8 BlockHandleMethod_BACK_TILT_R()
{
  static u8 flag=0;
	if(0==flag && 0==PES_Platform)
	{		
		flag=1;
		Time3(START);
		gl_time = 0 ;
	}
	else if(1==flag && 1==PES_Platform && gl_time > 30)
	{
		Time3(STOP);
		gl_time = 0 ;
		speedAdjustment(2000,1950);
		delay_ms(580);
		//rotAngle_Right(70);
		rotAngle_UR(80);
		flag=0;
		return 1;
	}
 
	return 0;
}


/*
* 函数介绍：左拐倾斜路面路障处理方法（回）
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：将巡线方法切换成过桥的巡线
* 作者    ：@林| @陈

*/

u8 BlockHandleMethod_BACK_TILT_L()
{

  static u8 flag=0;
	if(0==flag && 0==PES_Platform)  flag=1;
	else if(1==flag && 1==PES_Platform)
	{
		speedAdjustment(2000,1950);
		delay_ms(600);
		//rotAngle_Right(70);
		rotAngle_UL(90);
		flag = 0 ;
		return 1;
	}
 
	return 0;
}

/*
* 函数介绍：穿过整个斜坡
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@林| @陈

*/
u8 BlockHandleMethod_Crossing_All_TILT()
{
//	if(1 == PES_Platform)
//	{
//		speedAdjustment(2000,2000);
//		delay_ms(1000);
//		delay_ms(400);
//		return 1;
//	}
//		return 0;
//	static u8 flag;
//	if(0==flag && 0==PES_Platform)  flag=1;
//	else if(1==flag && 1==PES_Platform)
//	{	
////		speedAdjustment(0,0);
////		delay_ms(500);
//		speedAdjustment(2000,2000);
//		delay_ms(550);
//		flag=2;
//	}
//	else if(2==flag && 0==PES_Platform)
//	{
//		speedAdjustment(2000,2000);
//		delay_ms(1000);
//		flag=0;
//		return 1;
//	}
//	return 0;

	static u8 flag;
	if(0==flag && 0==PES_Platform)  
	{
    flag = 1;
	}     	
	else if(1==flag && 1==PES_Platform)
	{	
		Time3(START);	//打开定时器
		gl_time=0;
//		led0_flash();
//		Time3(STOP); 
		glHello_control.linkInform.findLineWays = FL_angle;
		findLineFlag = 0;
		angle_flag = 0;
 		flag = 2;
		
	}
	else if(2==flag && gl_time>120)
	{
//		led1_flash();
		glHello_control.linkInform.findLineWays = FL_slow;
		findLineFlag = 0; 
		Time3(STOP); //关闭定时器

//		speedAdjustment(0,0);
//		while(1);

		flag=0;
		
		return 1;
	}
	return 0;
}
/*************************************************珠峰**********************************************************/
/*

* 函数介绍：上珠峰
* 输入参数：无
* 输出参数：无
* 返回值  ：1(检测到)0（未检测到）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Peak()
{
	static u8 flag=0;
	//static findLine save;
	if(0==flag && 0==PES_Platform)
	{
	//	save=glHello_control.linkInform.findLineWays;
		flag=1;
	}
	if(1==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays=FL_upPeak;
		findLineFlag = 0;
		flag=2;
	}
	
  if(2==flag && 0==PES_Platform) flag=3;
	if(3==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays=NFL;
		findLineFlag = 0;
		flag=4;
	}
	if(4==flag && 0==PES_Platform) flag=5;
	if(5==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays=FL_upPeak;
		findLineFlag = 0;
		flag=6;
	}
	if(6==flag && 0==PES_Platform) flag=7;
	if(7==flag && 1==PES_Platform)
	{
		glHello_control.linkInform.findLineWays = NFL;
		findLineFlag = 0;
		flag=0;
		return 1;
	}
	return 0;
	
	
}
/*
* 函数介绍：下珠峰方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_downPlatform()
{
	static findLine save;
	static u8 flag=0;
	
	if(flag == 0)
	{
		speedAdjustment(0,0);
		delay_ms(200);
	//	DangerFlag=1;            //将危险信号标志位置为1
		Time3(START);
		gl_time=0;
		save = glHello_control.linkInform.findLineWays;
		glHello_control.linkInform.findLineWays =NFL;
		flag = 1;
	}
	else if(1==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = FL_downPeak; 
		findLineFlag = 0;
		flag=2;
	}
	else if(2==flag&&0==PES_Platform)  flag=3;
	else if(1==PES_Platform && 3==flag)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = NFL; 
		flag = 4;

	}
	else if(4==flag && 0==PES_Platform) flag=5;
	else if(5==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = FL_downPeak; 
		findLineFlag = 0;
		flag=6;
	}
	else if(6==flag && 0==PES_Platform)	flag=7;
	else if(7==flag && 1==PES_Platform)
	{
		glHello_control.linkInform.findLineWays=save;
		findLineFlag = 0;
		flag=0;
		return 1;
	}
	else if(gl_time>600)
	{
		if(1==danger24_23())
		{
			Time3(STOP); //关闭定时器
			gl_time = 0;
		}
	}
		return 0;


}

//***************************************************减速板****************************************//
/*

* 函数介绍：过减速板1(用底下光电开关)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(检测到)0（未检测到）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_S_BOARD_1()
{
	static findLine save;
	static u8 flag=0;
	if(0==flag)
	{
		save = glHello_control.linkInform.findLineWays;
		flag = 1;
	}
	else if(1==flag&&1==PES_Platform) 
	{
		glHello_control.linkInform.findLineWays =FL_slowest;
		findLineFlag = 0;
//		speedAdjustment(0,0);
//		delay_ms(500);
		Time3(START);
		gl_time=0;
		flag=2;
	}
	else if(2==flag&&gl_time>150)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays =FL_slow;
		findLineFlag = 0;
		Time3(STOP);
		gl_time=0;
		flag=0;
		return 1;
	}
	return 0;
}

/*

* 函数介绍：过减速板2(用底下光电开关)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(检测到)0（未检测到）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_S_BOARD_2()
{
//	static findLine save;
	static u8 flag=0;
	if(0==flag)
	{
	//	save = glHello_control.linkInform.findLineWays;
		flag = 1;
	}
	if(1==flag&&0==PES_Platform) flag=2;
	if(2==flag&&1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays =FL_slow;
		findLineFlag = 0;
		Time3(START);
		gl_time=0;
		flag = 3;
	}
	if(3==flag&&gl_time>150)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays =FL_default;
		findLineFlag = 0;
		Time3(STOP);
		gl_time=0;
		flag=0;
		return 1;
	}
	return 0;
}

/*

* 函数介绍：过双重减速板(用底下光电开关)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(检测到)0（未检测到）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_S_BOARD_Double()
{
	static findLine save;
	static u8 flag=0;
	if(0==flag)
	{
		save = glHello_control.linkInform.findLineWays;
		flag = 1;
	}
	else if(1==flag&&1==PES_Platform) 
	{
		glHello_control.linkInform.findLineWays =FL_slowest;
		findLineFlag = 0;
//		speedAdjustment(0,0);
//		delay_ms(500);
		Time3(START);
		gl_time=0;
		flag=2;
	}
	else if(2==flag&&gl_time>280)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays =save;
		findLineFlag = 0;
		Time3(STOP);
		gl_time=0;
		flag=0;
		return 1;
	}
	return 0;
}






/*

* 函数介绍：从26到27(用底下光电开关)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(检测到)0（未检测到）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_26_27()
{
	static findLine save;
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START);
		gl_time = 0;
		save = glHello_control.linkInform.findLineWays;
		flag = 1;
	}
	if(1==flag&&0==PES_Platform) flag=2;
	if(2==flag && 1==PES_Platform && gl_time > 30)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		Time3(STOP);
		gl_time = 0;
		glHello_control.linkInform.findLineWays =FL_slowest;
		findLineFlag = 0;
		Time3(START);
		gl_time=0;
		flag = 3;
	}
	if(3==flag && gl_time>150)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
//		led0_flash();
		glHello_control.linkInform.findLineWays =FL_slowest;
		findLineFlag = 0;
		Time3(STOP);
		gl_time=0;
		flag=4;
	}
	if(4==flag && 0==PES_Platform) flag=5;
	if(5==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = FL_upPeak;
		findLineFlag = 0;
		flag=6;
	}
	if(6==flag && 0==PES_Platform) flag=7;
	if(7==flag && 1==PES_Platform) 
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		flag=0;
		return 1;
	}
	return 0;
}
/*
* 函数介绍：仅用在43-44这个地方，右边传感器找点
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@陈hzihaio

*/
u8 BlockHandleMethod_PESR(void)
	{
//		static u8 flag=0;
//	if(0 == flag)
//	{
//		pes_R=0;
//	//	pesRSwitch(START);//开中断
//		//glHello_control.linkInform.findLineWays = FL_stop;
//		flag = 1;
//	}
//	if(1==pes_R && 1==flag)
//	{	
//	//	pesRSwitch(STOP);//关中断
//		//speedAdjustment(0,0);
//		pes_R=0;
//		flag = 0;	
//		return 1;
//	}
//		
//	return 0;
		if(1==PES_R)	return 1;
		return 0;
}






