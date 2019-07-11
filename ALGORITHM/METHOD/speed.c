#include "speed.h"
#include "common_time.h"
/*
	*加速任务方法集合
	*作者：@袁梓聪
*/

/*

* 函数介绍：下台加速方法
* 输入参数：加速时间time
* 输出参数：
* 返回值  ：1(加速完成)0（加速还没完成）
* 其他	：
* 作者    ：@袁梓聪

*/
u8 Speed_downMethod(u16 time){
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
		flag = 5;
	}
	else if(5==flag)
	{
		Time3(START);
		gl_time=0;
		flag=6;
	}
	else if(6==flag && gl_time > 20)
	{
		gl_time=0;
		glHello_control.linkInform.findLineWays = FL_quickest;  //切换到超高速巡线
		findLineFlag = 0;
		flag = 7;
	}	
	else if(7 == flag && gl_time > time)
	{	
		Time3(STOP);
		gl_time = 0;
		glHello_control.linkInform.findLineWays = save;  //切换到缺省巡线
		findLineFlag = 0;
		flag = 0;
		return 1;
	}	
	return 0;	
	
}

/*

* 函数介绍：普通加速方法
* 输入参数：加速时间time
* 输出参数：
* 返回值  ：1(加速完成)0（加速还没完成）
* 其他	：
* 作者    ：@袁梓聪

*/
u8 Speed_commonMethod(u16 time){
	static u8 flag=0;
	if(flag==0)
	{
		Time3(START);
		gl_time=0;
		flag=1;
	}
	else if(gl_time > 30 && 1==flag)
	{
		gl_time = 0;
		glHello_control.linkInform.findLineWays = FL_quickest;
		findLineFlag = 0;
		flag=2;
	}
	else if(2==flag && gl_time > time)
	{
		Time3(STOP);
		gl_time = 0;
		glHello_control.linkInform.findLineWays = FL_slow;
		findLineFlag = 0;
		flag=0;
		return 1;
	}
	return 0;
}

/*

* 函数介绍：用于占用时间，处理复杂节点
* 输入参数：占用时间time
* 输出参数：
* 返回值  ：1(占用完成)0（占用还没完成）
* 其他	：
* 作者    ：@袁梓聪

*/
u8 Take_up_time(u16 time){
	
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		gl_time=0;
		flag=1;
	}
	if(gl_time > time)
	{	
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag=0;
		return 1;
	}
		
	return 0;
}
