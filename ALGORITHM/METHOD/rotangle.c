#include "rotangle.h"


/*

* 函数介绍：计算出偏航角设定值
* 输入参数：curYaw(当前偏航角) rad（转过角度差）(+)代表右转、（-）代表左转
* 输出参数：设定值
* 返回值  ：
* 作者    ：@位胜

*/
float setYaw(float curYaw,float rad)
{
	float temp;
	rad = -rad;
	if(curYaw + rad < -180)
			temp = 180+rad+(180+curYaw);
	else if(curYaw + rad > 180)
			temp = -180+rad-(180-curYaw);
	else
			temp = curYaw + rad;
//	/*右转且设定值落在正数区域(rad>0.0) && (temp>0.0)*/
//	if((temp>0)&&(rad<0))		
//		temp= temp - 360;	
//	/*左转且设定值落在负数区域*/
//	else if((temp<0) && (rad>0))  
//		temp = temp+360;
	
	return(temp);
}

/*

* 函数介绍：当前值与设定值的误差计算
* 输入参数：curYaw（当前的偏航角）setYaw（设定的偏航角）
* 输出参数：无
* 返回值  ：err(当前值与设定值的偏差)
* 其他    ：左右转的偏差计算方法不同
* 作者    ：@断忆

*/

float  errCalculation(float curYaw,float setYaw)
{
	float err;
	err = setYaw - curYaw;
	if(err>180)err = err-360; 
  else if(err<-180)err =err+360;
  
	return err;
			
}


/*

* 函数介绍：向右旋转任意角度函数（0-180）
* 输入参数：angle（旋转角度）
* 输出参数：无
* 返回值  ：无
* 其他    ：无
* 作者    ：@断忆

*/
u8 rotAngle_Right(float angle)
{
	int err,speed;
	float set;
	u8 i;
	//sgAngleControl(R_ARM,UP);//收起舵机
	speedAdjustment(0,0);
	#ifdef _NEW_MPU6050_
	MPU6050_Pose_usart();
	#else
	for(i=0;i<50;i++)	
		MPU6050_Pose();
	#endif
	set = setYaw(glYaw,angle);

	err=errCalculation(glYaw,set);
	if(err<0)err=-err;
	#ifdef _NEW_MPU6050_
	PID_Init(&glrotAnglePID,0,4000,60,0,160);																	//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
	while(err > 5)
	{
		MPU6050_Pose_usart();
		err = errCalculation(glYaw,set);
		if(err<0)err=-err;
		//speed = 4500-(3500/angle)*(angle-err);
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(speed+1000,-speed-1000);
		//u3_printf("glYaw:%0.2f err:%d\n",glYaw,err);
	}
	#else
	PID_Init(&glrotAnglePID,0,4200,60,0,160);																	//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
	while(err > 5)
	{ 
		for(i=0;i<50;i++)
		MPU6050_Pose();
		err = errCalculation(glYaw,set);
		if(err<0)err=-err;
		//speed = 4500-(3500/angle)*(angle-err);
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(speed+1000,-speed-1000);
		//u3_printf("glYaw:%0.2f err:%d\n",glYaw,err);
	}
	#endif
	speedAdjustment(0,0);
	return 1;
}


/*

* 函数介绍：向左旋转任意角度函数（0-180）
* 输入参数：angle（旋转角度）
* 输出参数：无
* 返回值  ：无
* 其他    ：无
* 作者    ：@断忆

*/
u8 rotAngle_Left(float angle)
{
	int err,speed;
	float set;
	u8 i;
	//sgAngleControl(R_ARM,UP);//收起舵机
	speedAdjustment(0,0);
	#ifdef _NEW_MPU6050_
	MPU6050_Pose_usart();
	#else
	for(i=0;i<50;i++)	
		MPU6050_Pose();
	#endif
	set = setYaw(glYaw,-angle);
	
	err=errCalculation(glYaw,set);
	if(err<0)err=-err;
	
    #ifdef _NEW_MPU6050_
	PID_Init(&glrotAnglePID,0,4000,60,0,160);																	//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
	while(err > 5)
	{
		MPU6050_Pose_usart();
		err = errCalculation(glYaw,set);
		if(err<0)err=-err;
		//speed = 4500-(3500/angle)*(angle-err);
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(-speed-1000,speed+1000);
		//u3_printf("glYaw:%0.2f err:%d\n",glYaw,err);
	}
	#else
	PID_Init(&glrotAnglePID,0,4200,60,0,160);																	//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
	while(err > 5)
	{ 
		for(i=0;i<50;i++)
		MPU6050_Pose();
		err = errCalculation(glYaw,set);
		if(err<0)err=-err;
		//speed = 4500-(3500/angle)*(angle-err);
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(speed+1000,-speed-1000);
		//u3_printf("glYaw:%0.2f err:%d\n",glYaw,err);
	}
	#endif
	speedAdjustment(0,0);
	return 1;
}
/*

* 函数介绍：向右旋转任意角度函数（0-180）
* 输入参数：angle（旋转角度）
* 输出参数：无
* 返回值  ：无
* 其他    ：无
* 作者    ：@断忆

*/
u8 rotAngle_Right_F(float angle)
{
	int err,speed;
	float set;
	u8 i;
	//sgAngleControl(R_ARM,UP);//收起舵机
	speedAdjustment(0,0);
	#ifdef _NEW_MPU6050_
	MPU6050_Pose_usart();
	#else
	for(i=0;i<50;i++)	
		MPU6050_Pose();
	#endif
	set = setYaw(glYaw,angle);

	err=errCalculation(glYaw,set);
	if(err<0)err=-err;
	#ifdef _NEW_MPU6050_
	PID_Init(&glrotAnglePID,0,4700,60,0,160);																	//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
	while(err > 5)
	{
		MPU6050_Pose_usart();
		err = errCalculation(glYaw,set);
		if(err<0)err=-err;
		//speed = 4500-(3500/angle)*(angle-err);
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(speed+1200,-speed-1200);
		//u3_printf("glYaw:%0.2f err:%d\n",glYaw,err);
	}
	#else
	PID_Init(&glrotAnglePID,0,4200,60,0,160);																	//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
	while(err > 5)
	{ 
		for(i=0;i<50;i++)
		MPU6050_Pose();
		err = errCalculation(glYaw,set);
		if(err<0)err=-err;
		//speed = 4500-(3500/angle)*(angle-err);
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(speed+1000,-speed-1000);
		//u3_printf("glYaw:%0.2f err:%d\n",glYaw,err);
	}
	#endif
	speedAdjustment(0,0);
	return 1;
}


/*

* 函数介绍：向左旋转任意角度函数（0-180）
* 输入参数：angle（旋转角度）
* 输出参数：无
* 返回值  ：无
* 其他    ：无
* 作者    ：@断忆

*/
u8 rotAngle_Left_F(float angle)
{
	int err,speed;
	float set;
	u8 i;
	//sgAngleControl(R_ARM,UP);//收起舵机
	speedAdjustment(0,0);
	#ifdef _NEW_MPU6050_
	MPU6050_Pose_usart();
	#else
	for(i=0;i<50;i++)	
		MPU6050_Pose();
	#endif
	set = setYaw(glYaw,-angle);
	
	err=errCalculation(glYaw,set);
	if(err<0)err=-err;
	
    #ifdef _NEW_MPU6050_
	PID_Init(&glrotAnglePID,0,4700,60,0,160);																	//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
	while(err > 5)
	{
		MPU6050_Pose_usart();
		err = errCalculation(glYaw,set);
		if(err<0)err=-err;
		//speed = 4500-(3500/angle)*(angle-err);
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(-speed-1200,speed+1200);
		//u3_printf("glYaw:%0.2f err:%d\n",glYaw,err);
	}
	#else
	PID_Init(&glrotAnglePID,0,4200,60,0,160);																	//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
	while(err > 5)
	{ 
		for(i=0;i<50;i++)
		MPU6050_Pose();
		err = errCalculation(glYaw,set);
		if(err<0)err=-err;
		//speed = 4500-(3500/angle)*(angle-err);
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(speed+1000,-speed-1000);
		//u3_printf("glYaw:%0.2f err:%d\n",glYaw,err);
	}
	#endif
	speedAdjustment(0,0);
	return 1;
}
/*

* 函数介绍：向右拐35角度
* 输出参数：无
* 返回值  ：无
* 其他    ：无
* 作者    ：@断忆

*/
u8 rotAngleMethod_R35()
{
	speedAdjustment(2000,-2000);
	delay_ms(210);
	speedAdjustment(0,0);
	return 1;

}

/*

* 函数介绍：向右拐90角度
* 输出参数：无
* 返回值  ：无
* 其他    ：此转弯需在十字路口才能转
* 作者    ：@断忆

*/
u8 rotAngleMethod_R90()
{
	static u8 flag=0;
	static u8 times=0;
	int rank;
	if(1==sampingStatus())
	{
		glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  		//与阈值比较后将模拟量转化成数字量
		if(flag!=2 && flag!=3)
		{
			speedAdjustment(4000,-4000);
		}
		if((0x000==glsensor_dig_value)&&(flag==0))
		{
			flag=1; 
		}
	  if((flag==1)&&(calculateNum(glsensor_dig_value)!=0))
		{
			flag=2;
		}
	  if(2 == flag|3 == flag)
		{
			if(2 == flag)
			{
				PID_Init(&glsensorPID,22,8000,500,0,0);																					//对速度PID的参数进行初始化设置
				speedRec_Init(&glmotorSpeed,0,0);
				flag = 3;
			}
			rank=sensorDigitalRank_HR90(glsensor_dig_value);		//分级
			gldSpeed=positionPIDCalc(&glsensorPID,rank);   			//速度位置式PID输出
			positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度
		//sensorBit_u3printf(glsensor_dig_value);//串口3按位输出数字量
		//u3_printf("ds:%d  ",gldSpeed);//串口3输出数字量
		if(rank==22)
		{
			times++;
			if(times>2)
			{
				flag=0;
				times=0;
				speedAdjustment(0,0);
				return 1;
			}
		}
			
		}
	}
	return 0;
}


/*

* 函数介绍：左拐巡线
* 输出参数：无
* 返回值  ：无
* 其他    ：
* 作者    ：@断忆

*/
u8 rotAngleMethod_LFL()
{
	static u8 flag=0;
	if(((glsensor_dig_value&0x200)||(glsensor_dig_value&0x800)||(glsensor_dig_value&0x400)) && (0==flag))
		flag=1;
	
	if(flag==1)
	{
		glHello_control.linkInform.findLineWays =FL_left; 
		findLineFlag = 0;
		flag=2;
	}
	if((2==flag) && (glsensor_dig_value&0x001))
	{
		flag = 3;
		
	}
	if(3==flag && 0==(glsensor_dig_value&0x001))
	{
		flag = 0;
		return 1;
	}
	
	return 0;
}

/*

* 函数介绍：右拐巡线
* 输出参数：无
* 返回值  ：无
* 其他    ：
* 作者    ：@断忆

*/
u8 rotAngleMethod_RFL()
{
	static u8 flag=0;
	if((glsensor_dig_value&0x002) && (0==flag))
		flag=1;
	if(flag==1)
	{
		glHello_control.linkInform.findLineWays =FL_Right; 
		findLineFlag = 0;
		flag=2;
	}
	if((2==flag) && (glsensor_dig_value&0xf00))
	{
		flag = 3;
		
	}
	if(3==flag && 0==(glsensor_dig_value&0xf00))
	{
		flag = 0;
		return 1;
	}
	
	return 0;
}



/*

* 函数介绍：向右单边旋转任意角度函数（0-180）
* 输入参数：angle（旋转角度）
* 输出参数：无
* 返回值  ：无
* 其他    ：无
* 作者    ：@断忆

*/
u8 rotAngle_UR(float angle)
{
	int err,speed;
	float set;
	u8 i;
	//speedAdjustment(0,0);
    #ifdef _NEW_MPU6050_
	   MPU6050_Pose_usart();
	#else
	for(i=0;i<50;i++)	
		MPU6050_Pose();
	#endif
	set = setYaw(glYaw,angle);

	err=errCalculation(glYaw,set);
	if(err<0)err=-err;
	
	PID_Init(&glrotAnglePID,0,4000,0,0,0);																	//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
	while(err > 2)
	{
    #ifdef _NEW_MPU6050_
	    MPU6050_Pose_usart();
	#else
	for(i=0;i<50;i++)	
		MPU6050_Pose();
	#endif
		err = errCalculation(glYaw,set);
		if(err<0)err=-err;
		
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(speed+2500,0);
		
	}
	
	return 1;
}


/*

* 函数介绍：向左单边旋转任意角度函数（0-180）
* 输入参数：angle（旋转角度）
* 输出参数：无
* 返回值  ：无
* 其他    ：无
* 作者    ：@断忆

*/
u8 rotAngle_UL(float angle)
{
	int err,speed;
	float set;
	u8 i;
	//speedAdjustment(-1000,-1000);
    #ifdef _NEW_MPU6050_
	   MPU6050_Pose_usart();
	#else
	for(i=0;i<50;i++)	
		MPU6050_Pose();
	#endif
	set = setYaw(glYaw,-angle);
	
	err=errCalculation(glYaw,set);
	if(err<0)err=-err;
	
	PID_Init(&glrotAnglePID,0,3500,0,0,0);//对转弯PID的参数进行初始化设置，旋转PID直接传误差值

	while(err>5)
	{
    #ifdef _NEW_MPU6050_
			MPU6050_Pose_usart();
		#else
			for(i=0;i<50;i++)	
			MPU6050_Pose();
		#endif
			err = errCalculation(glYaw,set);
		if(err<0)err=-err;
		
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(0,speed+2500);
		
	}
	
	return 1;
}
/*

* 函数介绍：右旋转函数（单边刹车版_常规十字路口）
* 输入参数：angle（旋转角度）
* 输出参数：无
* 返回值  ：无
* 其他    ：无
* 作者    ：位胜

*/
u8 rotAngle_UR_crossroad()
{
	  static u8 flag;
    speedAdjustment(2800,-1800);
	   
	  if((glsensor_dig_value&0x040||glsensor_dig_value&0x020) && flag == 0)
		{
      speedAdjustment(2800,-1800);
		}
		else 
			flag=1;
			
//	   delay_ms(140);
	   if((glsensor_dig_value&0x020||glsensor_dig_value&0x040||glsensor_dig_value&0x010)&&flag == 1)
		 { 
//			 speedAdjustment(0,0);
			 flag = 0;
			 return 1;
		 }
			 
     return 0;
}

/*

* 函数介绍：左旋转函数（单边刹车版_常规十字路口）
* 输入参数：angle（旋转角度）
* 输出参数：无
* 返回值  ：无
* 其他    ：无
* 作者    ：位胜

*/
u8 rotAngle_UL_crossroad()
{
	   static u8 flag;
     speedAdjustment(-1800,2800);
	   
	  if((glsensor_dig_value&0x010||glsensor_dig_value&0x040)&&flag == 0)
		{
      speedAdjustment(-1800,2800);
		}
		else flag=1;
			
//	   delay_ms(140);
	   if((glsensor_dig_value&0x020||glsensor_dig_value&0x040||glsensor_dig_value&0x010)&&flag == 1)
		 { 
//			 speedAdjustment(0,0);
			 flag = 0;
			 return 1;
		}
			 
     return 0;
}


/*********************************************左转函数*********************************************************/
/*

* 函数介绍：向左拐35角度
* 输出参数：无
* 返回值  ：无
* 其他    ：无
* 作者    ：@断忆

*/
u8 rotAngleMethod_L35()
{
	speedAdjustment(-2000,2000);
	delay_ms(210);
	speedAdjustment(0,0);
	return 1;

}


