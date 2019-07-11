#include "pid.h"
#include <string.h>
#include "myconfig.h"


/*

* 函数介绍：旋转位置式PID计算
* 输入参数：p（PID调节器参数）err（误差值）
* 输出参数：
* 返回值  ：

*/
int positionPIDCalc_rotAngle(PIDTypeDef *p,int err)
{
	int derror,error;
	int out;
	error = err;													//偏差
	p->sumerror += error;									//积分
	derror = p->lastError - p->prevError;	//当前微分
	p->prevError = p->lastError;					//更新error[-1]的值
	p->lastError = error;									//更新error[-2]的值
	out = 	p->kp * error								//比例项
				+	p->ki * p->sumerror					//积分项
				+ p->kd * derror			;				//微分项
	
	out=limit(out,-p->limit,p->limit);
	
	return(out);
					
					
}


/*

* 函数介绍：位置式PID计算
* 输入参数：p（PID调节器参数）nextVaule（采样值）
* 输出参数：
* 返回值  ：

*/
int positionPIDCalc(PIDTypeDef *p,int nextVaule)
{
	int derror,error;
	int out;
	error = p->setVaule - nextVaule;			//偏差
	p->sumerror += error;									//积分
	derror = p->lastError - p->prevError;	//当前微分
	p->prevError = p->lastError;					//更新error[-1]的值
	p->lastError = error;									//更新error[-2]的值
	out = 	p->kp * error								//比例项
				+	p->ki * p->sumerror					//积分项
				+ p->kd * derror			;				//微分项
	
	out=limit(out,-p->limit,p->limit);
	
	return(out);
					
					
}

/*

* 函数介绍：增量式PID计算
* 输入参数：p（PID调节器参数）nextVaule（采样值）
* 输出参数：
* 返回值  ：

*/
int incrementalPIDcalc(PIDTypeDef *p,int nextVaule)
{
	int error;
	int ep,ei,ed;
	int out;
	error = p->setVaule - nextVaule;				//偏差
	ep = error - p->lastError;
	ei = error; 
	ed = error - 2*p->lastError + p->prevError;
	
	p->prevError = p->lastError;					//更新error[-1]的值
	p->lastError = error;									//更新error[-2]的值
	
	out = 	p->kp * ep				//比例项
				+	p->ki * ei				//积分项
				+ p->kd * ed	;			//微分项
	
	out=limit(out,-p->limit,p->limit);
	
	return(out);
						
			
}

///*

//* 函数介绍：对PID结构体清零
//* 输入参数：p（PID调节器参数）nextVaule（采样值）
//* 输出参数：
//* 返回值  ：

//*/
//static void PID_Reset(PIDTypeDef *p)
//{
//	memset(p,0,sizeof(PIDTypeDef));

//}

/*

* 函数介绍：对PID调节器参数进行设置
* 输入参数：pidRegulator(待设置的PID调节器),setVaule(期望值),limit(对输出的值进行限定),kp(比例系数),ki(积分系数),kd(微分系数)
* 输出参数：
* 返回值  ：
* 其他		：例如limit = 100则代表输出值的范围在+-100之间，意味着左右两轮的PWM相差不能超过1000
*/
void PID_Init(PIDTypeDef *pidRegulator,int setVaule,int limit,int kp,int ki,int kd)
{
	memset(pidRegulator,0,sizeof(PIDTypeDef));//对PID结构体清零
	
	pidRegulator->setVaule = setVaule;
	pidRegulator->limit = limit;
	pidRegulator->kp = kp;
	pidRegulator->ki = ki;
	pidRegulator->kd = kd;

}



