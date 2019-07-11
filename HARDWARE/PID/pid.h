#ifndef _PID_H_
#define _PID_H_

#include "sys.h"

/*PID调节器*/
typedef struct{
	
	int setVaule; 	//设定目标
	int kp;        //比例常数
	int ki;   			//积分常数
	int kd;				//微分常数
	
	int lastError;	//Error[-1]
	int prevError;	//Error[-2]
	int sumerror;	//误差累加
	
	int limit;		//限制值
	
}PIDTypeDef;

void PID_Init(PIDTypeDef *pidRegulator,int setVaule,int limit,int kp,int ki,int kd);
int incrementalPIDcalc(PIDTypeDef *p,int nextVaule);	//增量式PID
int positionPIDCalc(PIDTypeDef *p,int nextVaule);			//位置式PID
int positionPIDCalc_rotAngle(PIDTypeDef *p,int err);  // 旋转用的位置式PID

#endif

