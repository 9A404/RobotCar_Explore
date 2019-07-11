#include "myconfig.h"


/*全局变量*/
const u16  basic_sensorThreshold[NUM_OF_SENSOR] = {3800,3800,3800,3800 ,3800,3800,3800,3800,3800,3800,3800,3800 };
const u16  brige_sensorThreshold[NUM_OF_SENSOR] = {900,900,900,900,900,900,900,900,900,900,900,900 };



/*****************************************************奔跑路线****************************************************************************************/
/*不过门路线*/
const u8 runMethodTable[][100]=
{
///*保守路线0 不过桥267*2=534	*/{1,2,5,6,8,6,7,12,10,11,10,9,5,2,1,2},				
/*保守路线1  过桥	282*2=564	*/{1,2,3,4,3,5,9,10,11,10,12,10,9,5,6,8,6,7,6,5,2,1,2},	
///*高分路线2 不过桥484*2=968	*/{1,2,5,6,8,6,7,12,10,11,10,24,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,37,36,24,10,9,5,2,1,2},			
/*高分路线3	 过桥 499*2=998	*/{1,2,3,4,3,5,6,8,6,7,12,10,11,10,24,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,37,36,24,10,9,5,2,1,2},
/*高分路线4	不拿圆510*2=1020*/{1,2,3,4,3,5,6,8,6,7,12,10,11,10,24,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,17,18,19,18,17,37,36,24,10,9,5,2,1,2},
///*高分路线5	 全部 550*2=1100*/{1,2,3,4,3,5,6,8,6,7,12,10,11,10,24,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,17,18,19,18,17,43,16,44,45,46,47,46,43,37,36,24,10,9,5,2,1,2},
};
/*过门前路线同时也是如果39门开走的路线*/
const u8 runMethodTableDoor[][100]=
{
/* 0 */	{1,2,3,4,3,5,6,8,6,7,12,10,11,10,9,39,15,31,32,31,30,34,35,36,35,14,17,18,19,18,17,14,34,30,50,28,25,26,27,26,25,28,50,49,37,49,15,9,5,2,1,2},//过桥
///* 1 */	{1,2,3,4,3,5,6,8,6,7,12,10,11,10,9,39,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,16,17,18,19,18,17,37,36,15,9,5,2,1,2},//过桥
};
/*过门后路线*/
const u8 runMethodTableDoorAuto[][100]=
{
/* 0 	39号门关*/	{39,9,40,13,14,17,18,19,18,17,37,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,13,9,5,2,1,2},        			//第一遍路线如果40门开走这条路线
/* 1 	40号门关*/	{40,9,5,6,14,17,18,19,18,17,37,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,6,5,2,1,2},         				//第一遍路线如果41门开就这条路线
/* 2 	42号门关*/	{6,}, 
/* 3 	开39号门*/	{1,2,3,4,3,5,6,8,6,7,12,10,11,10,9,39,15,31,32,31,30,34,35,36,35,14,17,18,19,18,17,14,34,30,50,28,25,26,27,26,25,28,50,49,37,49,15,9,5,2,1,2},
/* 4 	开40号门*/	{1,2,3,4,3,5,6,8,6,7,12,10,11,10,9,13,14,17,18,19,18,17,37,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,13,9,5,2,1,2},	//第二遍路线更新走的路线（不用检测门的开启）
/* 5 	开42号门*/	{1,2,3,4,3,5,6,8,6,7,12,10,11,10,9,5,6,14,17,18,19,18,17,37,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,6,5,2,1,2}, 
};

/*调试路线表格*/
const u8  runMethodTableDebug[][100]=
{
  {1,2,3,4,3,5,6,8,6,7,12,10,11,10,9,39,15,31,32,31,30,34,35,36,35,14,17,18,19,18,17,14,34,30,50,28,25,26,27,26,25,28,50,49,37,49,15,9,5,2,1,2},
	{1,2,5,6,8,6,7,12,10,11,10,9,39,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,16,17,18,19,18,17,37,36,15,9,5,2,1,2},//不过桥，去19
	{1,2,3,4,3,5,6,8,6,7,12,10,11,10,9,39,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,17,18,19,18,17,37,36,15,9,5,2,1,2},
    
};
u8 runMethod[100]=	{1,2,5,9};							//保守奔跑的路线:方案二
u8 runMethod_2[100]={1,2,5,9};  						//保守奔跑的路线:方案二
/***********************************************************************************************************************************************/

u16 glsensor_ad_value[NUM_OF_SENSOR];				//储存模拟量
u16 glsensor_dig_value;											//储存转化后的数字量
u8 	USART3_TX_BUF[USART3_MAX_SEND_LEN];			//串口3 DMA缓存区

PIDTypeDef glsensorPID;											//定义一个传感器PID调节器
PIDTypeDef glrotAnglePID;										//定义一个转角PID调节器
motorSpeedTypeDef glmotorSpeed;							//定义一个速度记录器
controlCenterTypeDef glHello_control;				//定义一个控制台
runStateTypeDef		glrunState;								//定义一个运行状态记录器
//rankTypeDef glrankInformation[50];				//定义一个分级表变量 

u8 angle_flag=0;                         		//巡线角度标志
float glsensor_angle;
int gldSpeed;															 	//储存速度PID输出
float gldYaw=0;														 	//储存偏航角PID输出
u8 findLineFlag=0;											   	//巡线方法初始化标志位
u8 rotAngleFlag=0;                         	//旋转方法初始化标志位
float glPitch,glRoll,glYaw;							   	//存储mpu6050读出的欧拉角
float glsetYaw;                            	//储存设定的偏航角

float angle_read_temp[5];
float angle_read;

float glPitchbuff[2];											 	//俯仰角缓存区
float gldif_Pitch;                         	//前后两次之差	  
u8 mpu6050_flag=0;												 	//标志上下台
u8 U_Dswitch;                             	//上下台控制开关 1代表上台，2代表下台
u8  USART1_RX_BUF[66];											//串口1 DMA缓存区
u16 gl_time=0;														 	//定时器3标志
u8 runTimes=0;															//记录奔跑次数
u8 DoorFlag=0;                        			//记录门开标志位
u8 DoorFlag_2=0;

u8 runMethodNumDebug;                       //记录调试路线条数
u8 runMethodNum;                            //记录不过门奔跑路线条数
u8 runMethodNumDoor;                        //记录过门奔跑路线条数

u8 pes_L=0;																	//左边光电传感器状态
u8 pes_R=0;																	//右边光电传感器状态

u8 SecondGameNum1 = 0;											//一键切换第二遍路线1（保守路线）
u8 SecondGameNum2 = 1;											//一键切换第二遍路线2（高分路线）
/*

* 函数介绍：比赛
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆（修改@ 陈）

*/
void Fun_game(void)
{
	Lcd_Clear(WHITE);//清屏
	Gui_DrawFont_GBK16(0,0,BLUE,WHITE,"比赛:");
	#ifndef _NEW_MPU6050_
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"MPU6050_Init...");
	MPU6050_Init();		        //MPU6050初始化
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"               ");
	#endif
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"Start");
	/*重新初始化*/
	runTimes = 0;						//记录奔跑次数
	gl_time=0;							//定时器3标志
	mpu6050_flag=0;					//标志上下台
	findLineFlag=0;					//巡线方法初始化标志位
	
	while(1)
	{
		keyFlag = keyScan(0);
		
		/*当有按键按下就跳出*/
		if(keyFlag==KEY0_UP || keyFlag==KEY4_ESC)
		{
			speedAdjustment(0,0);
			Time3(STOP);     //关闭定时器
			mpu6050_samping(STOP); //关闭mpu6050采样
			/*软件复位*/
			__set_FAULTMASK(1);  // 关闭所有中断
			NVIC_SystemReset();  // 复位
		} 
		
		if(0 == runTimes)
			{
				Gui_DrawFont_GBK16(0,40,BLUE,WHITE,"First round...");
				runTimes=3;																		//保证跑一次只初始化
				/*****软件逻辑层初始化部分*****/
				Control_Init(&glHello_control,runMethod);     //初始化控制台
				runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
			}
		if(1 == runTimes)
			{
				Gui_DrawFont_GBK16(0,60,BLUE,WHITE,"Second round...");
				runTimes=4;																		//保证跑一次只初始化
				if(1==DoorFlag)
					runMethodResetDoorSecond(runMethod_2,DoorFlag_2,runMethodTableDoorAuto);//根据开启的那号门更新数组runMethodTableDoorAuto中对应的编号路线到runMethod_2（注意是从3开始）
				runMethodReset(runMethod,runMethod_2);				//更新路线
				/*****软件逻辑层初始化部分*****/
				Control_Init(&glHello_control,runMethod);     //初始化控制台
				runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
			}
			/*跑完一个路段才更新一次*/
		 if(control_Update(&glHello_control,strlen((const char*)runMethod),runMethod,mapInformation))//当检测到节点后就会更新控制台的数据//sizeof(runMethod)/sizeof(runMethod[0])
			{
				//u3_printf("Control_Update\r\n");
				runStateReset(&glrunState,&glHello_control);//重置运行状态
				findLineFlag=0;
			}
				/*采样完成一次就进行一次处理*/
		if(sampingStatus() == 1) 
			{	
				findLine_Task(&glHello_control,&glrunState);        	 // 巡线任务
				roadBlocksHandle_Task(&glHello_control,&glrunState);	 // 障碍处理任务
        speed_Task(&glHello_control,&glrunState);				//加速任务
				carPark_Task(&glHello_control, &glrunState);       		 // 停车任务
				seekNode_Task(&glHello_control,&glrunState);      		 // 找点任务				
			}
		rotAngle_Task(&glHello_control,&glrunState);           // 转弯任务	
	}
}
/*

* 函数介绍：比赛（一键确定比赛路线）
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@ 陈

*/

void Fun_SecondGameMethod1(void)
{
	Lcd_Clear(WHITE);//清屏
	Gui_DrawFont_GBK16(0,0,BLUE,WHITE,"比赛:");
	#ifndef _NEW_MPU6050_
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"MPU6050_Init...");
	MPU6050_Init();		        //MPU6050初始化
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"               ");
	#endif
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"Start");
	/*重新初始化*/
	runTimes = 0;						//记录奔跑次数
	gl_time=0;							//定时器3标志
	mpu6050_flag=0;					//标志上下台
	findLineFlag=0;					//巡线方法初始化标志位
	
	while(1)
	{
		keyFlag = keyScan(0);
		
		/*当有按键按下就跳出*/
		if(keyFlag==KEY0_UP || keyFlag==KEY4_ESC)
		{
			speedAdjustment(0,0);
			Time3(STOP);     //关闭定时器
			mpu6050_samping(STOP); //关闭mpu6050采样
			/*软件复位*/
			__set_FAULTMASK(1);  // 关闭所有中断
			NVIC_SystemReset();  // 复位
		} 
		
		if(0 == runTimes)
			{
				Gui_DrawFont_GBK16(0,40,BLUE,WHITE,"Second round...");
				runTimes=4;																		//保证跑一次只初始化
				runMethodUpdate(runMethod,SecondGameNum1,runMethodTable);
				/*****软件逻辑层初始化部分*****/
				Control_Init(&glHello_control,runMethod);     //初始化控制台
				runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
			}
			/*跑完一个路段才更新一次*/
		 if(control_Update(&glHello_control,strlen((const char*)runMethod),runMethod,mapInformation))//当检测到节点后就会更新控制台的数据//sizeof(runMethod)/sizeof(runMethod[0])
			{
				//u3_printf("Control_Update\r\n");
				runStateReset(&glrunState,&glHello_control);//重置运行状态
				findLineFlag=0;
			}
				/*采样完成一次就进行一次处理*/
		if(sampingStatus() == 1) 
			{	
				findLine_Task(&glHello_control,&glrunState);        	 // 巡线任务
				roadBlocksHandle_Task(&glHello_control,&glrunState);	 // 障碍处理任务
        speed_Task(&glHello_control,&glrunState);				//加速任务
				carPark_Task(&glHello_control, &glrunState);       		 // 停车任务
				seekNode_Task(&glHello_control,&glrunState);      		 // 找点任务				
			}
		rotAngle_Task(&glHello_control,&glrunState);           // 转弯任务	
	}
}
/*

* 函数介绍：比赛（一键确定比赛路线）
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@ 陈

*/

void Fun_SecondGameMethod2(void)
{
	Lcd_Clear(WHITE);//清屏
	Gui_DrawFont_GBK16(0,0,BLUE,WHITE,"比赛:");
	#ifndef _NEW_MPU6050_
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"MPU6050_Init...");
	MPU6050_Init();		        //MPU6050初始化
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"               ");
	#endif
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"Start");
	/*重新初始化*/
	runTimes = 0;						//记录奔跑次数
	gl_time=0;							//定时器3标志
	mpu6050_flag=0;					//标志上下台
	findLineFlag=0;					//巡线方法初始化标志位
	
	while(1)
	{
		keyFlag = keyScan(0);
		
		/*当有按键按下就跳出*/
		if(keyFlag==KEY0_UP || keyFlag==KEY4_ESC)
		{
			speedAdjustment(0,0);
			Time3(STOP);     //关闭定时器
			mpu6050_samping(STOP); //关闭mpu6050采样
			/*软件复位*/
			__set_FAULTMASK(1);  // 关闭所有中断
			NVIC_SystemReset();  // 复位
		} 
		
		if(0 == runTimes)
			{
				Gui_DrawFont_GBK16(0,40,BLUE,WHITE,"Second round...");
				runTimes=4;																		//保证跑一次只初始化
				runMethodUpdate(runMethod,SecondGameNum2,runMethodTable);
				/*****软件逻辑层初始化部分*****/
				Control_Init(&glHello_control,runMethod);     //初始化控制台
				runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
			}
			/*跑完一个路段才更新一次*/
		 if(control_Update(&glHello_control,strlen((const char*)runMethod),runMethod,mapInformation))//当检测到节点后就会更新控制台的数据//sizeof(runMethod)/sizeof(runMethod[0])
			{
				//u3_printf("Control_Update\r\n");
				runStateReset(&glrunState,&glHello_control);//重置运行状态
				findLineFlag=0;
			}
				/*采样完成一次就进行一次处理*/
		if(sampingStatus() == 1) 
			{	
				findLine_Task(&glHello_control,&glrunState);        	 // 巡线任务
				roadBlocksHandle_Task(&glHello_control,&glrunState);	 // 障碍处理任务
				carPark_Task(&glHello_control, &glrunState);       		 // 停车任务
        speed_Task(&glHello_control,&glrunState);				//加速任务
				seekNode_Task(&glHello_control,&glrunState);      		 // 找点任务				
			}
		rotAngle_Task(&glHello_control,&glrunState);           // 转弯任务	
	}
}
/*********************************************************************************************************************/
int main(void)
{	
		/************硬件初始化部分*****************************************************************************/	
	  NVIC_Configuration();				//系统中断优先级分组抢占2：响应2	
		delay_init();	    	  		//延时函数初始化	
		Lcd_Init();             //TFT屏幕显示初始化
		bootDisplay();					//开机界面
		ADC_DMA_Init();        	//ADC&DMA初始化
		sampingTime_Init(150);	//采样周期为15ms对应的值为150 
//		mpu6050_sampingTime_Init(80);//mpu6050采样周期8ms
		TIM3_Config(100-1,7200-1); // 定时器3定时周期为10ms
		motor_PWM_Init();       //PWM初始化
		uart_init(115200);			//串口1初始化	
//		usart3_init(115200);			//串口DMA初始化函数		
		sg_PWM_Init();					//舵机初始化
		keyInit();							//按键初始化
	  pesInit();							//光电传感器初始化
		ledInit();							//led初始化
		//buzzerInit();         //蜂鸣器初始化
		
		runMethodNum=sizeof(runMethodTable)/sizeof(runMethodTable[0]);
		runMethodNumDoor=sizeof(runMethodTableDoor)/sizeof(runMethodTableDoor[0]);
		runMethodNumDebug=sizeof(runMethodTableDebug)/sizeof(runMethodTableDebug[0]);
		
		while(1)
		{
			displayOperation();
////			speedAdjustment(2080,2200);
		}
		
}

 



