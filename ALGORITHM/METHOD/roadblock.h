#ifndef _ROADBLOCK_H_
#define _ROADBLOCK_H_
#include "sys.h"
#include "myconfig.h"

u8 BlockHandleMethod_Brige(void);      //过桥处理
u8 BlockHandleMethod_DOOR(void);      //过门1处理
u8 BlockHandleMethod_DOOR_2(void);
//u8 BlockHandleMethod_DOORBack(void);   //回家过门处理
u8 BlockHandleMethod_Platform (void);	 //平台景点
u8 BlockHandleMethod_Platform_1 (void); //起点
u8 BlockHandleMethod_Peak(void); //上珠峰景点
u8 BlockHandleMethod_downPlatform(void);//下珠峰
u8 BlockHandleMethod_S_BOARD_1(void);//减速板1
u8 BlockHandleMethod_S_BOARD_2(void);//减速板2
u8 BlockHandleMethod_S_BOARD_Double(void);
u8 BlockHandleMethod_26_27(void);//26到27节点
u8 Angle_read(void);
u8 BlockHandleMethod_Seesaw(void);
u8 BlockHandleMethod_Slope(void);      //山丘
u8 BlockHandleMethod_down_27_26(void);
u8 BlockHandleMethod_S_BOARD_Double(void);


u8 BlockHandleMethod_TIME(void);			 //复杂景点
u8 BlockHandleMethod_TIME_1(void);
u8 BlockHandleMethod_TIME_2(void);
u8 BlockHandleMethod_TIME_44_43(void);
u8 BlockHandleMethod_TIME_45_46();

u8 BlockHandleMethod_Trapezoid_1(void);
u8 BlockHandleMethod_Trapezoid_2(void);	 //梯形景点
u8 BlockHandleMethod_Trapezoid_3(void);

u8 BlockHandleMethod_GO_Tilt_R(void);     //前往右转斜坡景点
u8 BlockHandleMethod_GO_Tilt_L(void);     //前往左转斜坡景点 

u8 BlockHandleMethod_BACK_TILT_R(void);   //返回右转斜坡
u8 BlockHandleMethod_BACK_TILT_L(void);		//返回左转斜坡
u8 BlockHandleMethod_Crossing_All_TILT(void); //穿过整个斜坡
u8 BlockHandleMethod_Slope (void);

u8 BlockHandleMethod_speedtime_8_6(void);  //加速时间
u8 BlockHandleMethod_speedtime_11_10(void);  //加速时间
u8 BlockHandleMethod_speedtime_7_12(void);  //加速时间
u8 BlockHandleMethod_speedtime_36_17(void);
u8 BlockHandleMethod_speedtime_17_37(void);
u8 BlockHandleMethod_speedtime_14_37(void);
u8 BlockHandleMethod_speedtime_38_37(void);
u8 BlockHandleMethod_speedtime_10_12(void);
u8 BlockHandleMethod_speedtime_6_7(void);
u8 BlockHandleMethod_speedtime_15_37(void);
u8 BlockHandleMethod_speedtime_44_37(void);
u8 BlockHandleMethod_speedtime_36_37(void);
u8 BlockHandleMethod_speedtime_14_44(void);
u8 BlockHandleMethod_PESR(void);
u8 BlockHandleMethod_speedtime_9_30(void);
u8 BlockHandleMethod_speedtime_39_30(void);
u8 BlockHandleMethod_Platform_37_15(void);
#endif



