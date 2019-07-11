#ifndef _ROTANGLE_H_
#define _ROTANGLE_H_
#include "sys.h"
#include "myconfig.h"

typedef enum {Left,Right}Direction;

float setYaw(float curYaw,float rad);
float  errCalculation(float curYaw,float setYaw);

u8 rotAngle_Right_F(float angle);
u8 rotAngle_Right(float angle);
u8 rotAngleMethod_R180(void);
u8 rotAngleMethod_R90(void);
u8 rotAngleMethod_R35(void);

u8 rotAngle_Left_F(float angle);
u8 rotAngle_Left(float angle);
u8 rotAngleMethod_L90(void);
u8 rotAngleMethod_L35(void);

u8 rotAngleMethod_LFL(void);
u8 rotAngleMethod_RFL(void);

u8 rotAngle_UR(float angle);
u8 rotAngle_UL(float angle);

u8 rotAngle_UR_crossroad(void);
u8 rotAngle_UL_crossroad(void);


#endif





