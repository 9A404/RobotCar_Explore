#include "carpark.h"

/*

* 函数介绍：默认停车方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_default()
{
	delay_ms(520);
	return 1;	
}


/*

* 函数介绍：左边光电传感器停车方法(带反转减速)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesL_back()
{
	static u8 flag=0;
	if(flag ==0)
	{
		/*反转加速刹车*/
		speedAdjustment(-3500,-3500);
		delay_ms(20);
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_L && 1==flag)
	{	
		/*停车*/
		speedAdjustment(-2000,-2000);
		delay_ms(40);
		speedAdjustment(0,0);
		flag = 0;
		delay_ms(40);		
		//delay_ms(1000);
		//delay_ms(1000);
		return 1;
	}
	
	return 0;	
}


/*

* 函数介绍：右边光电传感器停车方法（带反转减速）
* 输入参数：
* 输出参数：
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesR_back()
{
	static u8 flag=0;
	if(flag ==0)
	{	
		/*反转加速刹车*/
		speedAdjustment(-3500,-3500);
		delay_ms(20);
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_R && 1==flag)
	{
		/*停车*/
		speedAdjustment(-3500,-3500); 
		delay_ms(15);
		speedAdjustment(0,0);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}







/*
* 函数介绍：左边光电传感器停车方法(不反转减速)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesL()
{
	static u8 flag=0;
	if(flag ==0)
	{
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_L && 1==flag)
	{	
//		speedAdjustment(-2000,-2000); 
//		delay_ms(15);
		
		flag = 0;
			
		return 1;
	}
	
	return 0;	
}




/*

* 函数介绍：右边光电传感器停车方法(不反转减速)
* 输入参数：
* 输出参数：
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesR()
{
	static u8 flag=0;
	if(flag ==0)
	{	
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_R && 1==flag)
	{
//		speedAdjustment(-2000,-2000); 
//		delay_ms(15);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}

/*

* 函数介绍：
* 输入参数：
* 输出参数：
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_stop()
{
		speedAdjustment(-2000,-2000);
		delay_ms(10);
		return 1 ;
}



/*

* 函数介绍：左边光电传感器延时停车方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/
u8 parkMethod_pesL_Delay(int time)
{
	static u8 flag=0;
	if(flag ==0)
	{
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_L && 1==flag)
	{	
//		speedAdjustment(-2000,-2000); 
//		delay_ms(15);
		speedAdjustment(1200,1200); 
		delay_ms(time);
		speedAdjustment(0,0);
		flag = 0;
			
		return 1;
	}
	
	return 0;	
}

/*

* 函数介绍：右边光电传器延时停车方法
* 输入参数：
* 输出参数：
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/
u8 parkMethod_pesR_Delay(int time)
{
	static u8 flag=0;
	if(flag ==0)
	{	
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_R && 1==flag)
	{
		speedAdjustment(1200,1200); 
		delay_ms(time);
		speedAdjustment(0,0);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}



/*

* 函数介绍：门停车方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_Door()
{
	speedAdjustment(0,0);
//	delay_ms(270);
	return 1;	
}



/*

* 函数介绍：平台停车方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesPlatform()
{
	static u8 flag=0;
	if(0==flag)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = NFL;
		flag=1;
	}
	if(1==flag&&0==PES_H)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = NFL_slow;
		flag=2;
	}
	if(2==flag&&1==Collision)
	{
		flag=3;
	}
	else if(3==flag)
	{
		speedAdjustment(-1400,-1400);
		delay_ms(200);
		speedAdjustment(0,0);
		#ifdef _DJ_CONTROL_ //条件编译
			sgAngleControl(L_ARM,L_UP);
			delay_ms(200);
			sgAngleControl(L_ARM,L_DOWN);
			sgAngleControl(R_ARM,R_UP);
			delay_ms(200);
			sgAngleControl(R_ARM,R_DOWN);
			delay_ms(200);
		#endif
		#ifdef _LED_CONTROL_ //条件编译
			led_light(2);
		#endif
		flag=0;
		return 1;
	}
	return 0;

}
/*

* 函数介绍：左边光电传感器45度停车方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesL_45()
{
	static u8 flag=0;
	if(flag ==0)
	{
		/*反转加速刹车*/
		speedAdjustment(-3500,-3500);
		delay_ms(20);
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_L && 1==flag)
	{	
		/*停车*/
		speedAdjustment(2000,2000);
		delay_ms(150);
		speedAdjustment(0,0);
		flag = 0;
		delay_ms(40);		
		//delay_ms(1000);
		//delay_ms(1000);
		return 1;
	}
	
	return 0;	
}
/*

* 函数介绍：右边光电传感器45度停车方法
* 输入参数：
* 输出参数：
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesR_45()
{
	static u8 flag=0;
	if(flag ==0)
	{	
		/*反转加速刹车*/
		speedAdjustment(-3500,-3500);
		delay_ms(20);
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_R && 1==flag)
	{
		/*停车*/
		speedAdjustment(2000,2000);
		delay_ms(150);
		speedAdjustment(0,0);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}
/*

* 函数介绍：右边光电传感器前面没有线停车方法
* 输入参数：
* 输出参数：
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesR_noline()
{
	static u8 flag=0;
	if(flag ==0)
	{	
//		/*反转加速刹车*/
//		speedAdjustment(-3500,-3500);
//		delay_ms(20);
		speedAdjustment(1800,1800);
		flag = 1;
	}
	if(0==PES_R && 1==flag)
	{
		/*停车*/
		speedAdjustment(-3500,-3500); 
		delay_ms(15);
//		speedAdjustment(0,0);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}
/*

* 函数介绍：左边光电传感器前面没有线停车方法
* 输入参数：
* 输出参数：
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesL_noline()
{
	static u8 flag=0;
	if(flag ==0)
	{	
//		/*反转加速刹车*/
//		speedAdjustment(-3500,-3500);
//		delay_ms(20);
		speedAdjustment(1800,1800);
		flag = 1;
	}
	if(0==PES_L && 1==flag)
	{
		/*停车*/
		speedAdjustment(-3500,-3500); 
		delay_ms(15);
//		speedAdjustment(0,0);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}





