#ifndef  _MY_CONFIG_H_
#define  _MY_CONFIG_H_

#include "sys.h"
#include "delay.h"
#include "timer.h"
#include "pwm.h"
#include "usart.h"
#include "pid.h"
#include "usart3.h"
#include "control.h"
#include "findline.h"
#include "roadblock.h"
#include "rotangle.h"
#include "seeknodeway.h"
#include "carpark.h"
#include "adc.h"
#include "mpu6050.h"
#include "key.h"
#include "pes.h"
#include "led.h"
#include "string.h"
#include "GUI.h"
#include "Lcd_Driver.h"
#include "myGUI.h"
#include "door.h"
#include "danger.h"
#include "speed.h"

//#define _DEBUG_
//#define _DEBUG_U3_P		//调试串口三蓝牙打印
//#define _LED_CONTROL_		//一型闪灯
#define _DJ_CONTROL_ 	//二型舵机
//#define _FINDLINE_DEBUG_//调试慢速度
#define _NEW_MPU6050_//新版陀螺仪

//加速时间

#define Door_Time 		120
#define Door_Time_2 	100

#define S_TIME_6_8 		80
#define S_TIME_8_6 		80
#define S_TIME_6_7 		70
#define S_TIME_7_12 	280
#define S_TIME_10_11 	60
#define S_TIME_11_10 	45
#define S_TIME_10_12 	90
#define S_TIME_36_37 	50
#define S_TIME_38_37 	100
#define S_TIME_14_37 	160
#define S_TIME_44_37 	250
#define S_TIME_17_37 	280
#define S_TIME_15_37 	120
#define S_TIME_36_17 	200
#define S_TIME_14_44 	110
#define S_TIME_9_30 	90
#define S_TIME_39_30 	50

#define max(a,b)			(a>b ? a:b)
#define min(a,b)			(a<b ? a:b)
#define limit(x,a,b)	(min(max(x,a) , b))	

#define NUM_OF_SENSOR 	12					//传感器个数
#define USART3_MAX_SEND_LEN 200		 // 发送缓存大小


extern unsigned short glsensor_ad_value[NUM_OF_SENSOR];       //传感器模拟量数组
extern unsigned short glsensor_dig_value;									    //传感器数字量数组
extern unsigned char 	USART3_TX_BUF[USART3_MAX_SEND_LEN];     //串口3发送缓存
extern unsigned char  USART1_RX_BUF[66];											//串口1 DMA缓存区
/********************************传感器阈值******************************************************************/
extern const unsigned short int  basic_sensorThreshold[NUM_OF_SENSOR]; //传感器阈值
extern const  u16  brige_sensorThreshold[NUM_OF_SENSOR];//过桥阈值

/*******************************常量表*******************************************************************/
extern const map_linkInforTypeDef mapInformation[][NODEFORKNUM]; //地图信息数字化表
extern const rankTypeDef rankInformation_FL[22];                   //巡线分级表

extern float glPitchbuff[2];
extern float gldif_Pitch;
extern u8 mpu6050_flag;
extern u8 U_Dswitch;                                //上下台控制开关 1代表上台，2代表下台
extern float gldYaw;																//储存偏航角PID输出
extern float glPitch,glRoll,glYaw;							  //欧拉角
extern float glsetYaw;																		//储存设定的偏航角
extern int gldSpeed;															//储存速度PID输出
extern float angle_read_temp[5];
extern float angle_read;
extern u8 findLineFlag;														//巡线方法初始化标志位
extern u8 rotAngleFlag;                         //旋转方法初始化标志位

extern u8 key0_Flag;																//按键0标志位
extern u16 gl_time;														 		 //定时器3标志
extern u8 runTimes;																//记录奔跑次数
extern float angle_read;			//记录第一个翘板转弯的角度
extern float angle_read_back;		//记录第二个翘板转弯的角度
extern float glsensor_angle;
extern  u8 angle_flag;
/********************************逻辑层控制器**************************************************/
extern PIDTypeDef glsensorPID;										//定义一个传感器PID调节器
extern PIDTypeDef glrotAnglePID;									//定义一个转角PID调节器
extern motorSpeedTypeDef glmotorSpeed;				  	//定义一个速度记录器
//extern rankTypeDef glrankInformation[50];				//定义一个分级表变量 
extern controlCenterTypeDef glHello_control;			//定义一个控制台
extern runStateTypeDef		glrunState;							//定义一个运行状态记录器

void Fun_game(void);															//
void Fun_SecondGameMethod1(void);
void Fun_SecondGameMethod2(void);
extern const u8  runMethodTable[][100];						//不过门奔跑路线表格
extern const u8  runMethodTableDoor[][100];
extern const u8  runMethodTableDoorAuto[][100]; 

extern const u8  runMethodTableDebug[][100];						//所有路线调试表格
extern u8 runMethodNum;
extern u8 runMethodNumDebug;
extern u8 runMethodNumDoor;                       //用于记录39门开的奔跑条数
extern u8 DoorFlag;                         //用于当门关切换路线的次数，即自动切换路线标志位   
extern u8 DoorFlag_2;                               //两次选择过门标志位，为了让第二轮奔跑不在寻找哪个门是开的
extern u8 runMethod[100];													//储存第一次奔跑路线
extern u8 runMethod_2[100];                       //储存第二次奔跑路线

extern u8 pes_L;																		//左边光电传感器状态
extern u8 pes_R;																		//右边光电传感器状态

extern u8 SecondGameNum1;														//一键切换第二遍路线1（保守路线）
extern u8 SecondGameNum2;														//一键切换第二遍路线2（高分路线）
//extern u8 DangerFlag;                         //危险标志位



#endif



