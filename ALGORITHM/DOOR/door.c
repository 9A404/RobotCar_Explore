#include "door.h"
#include "myconfig.h"

/*

* 函数介绍：第二轮自动重置奔跑路线，如果第一轮奔跑路线为过门并且第二轮奔跑路线中存在大于或者等于39的节点则表明第二轮路线过门
* 输入参数：runMethod_2（第二轮奔跑的路线）
* 输出参数：无
* 返回值  ：无
* 作者    ：@陈

*/
u8 runMethodDoorSecondCheck(u8 runMethod[],const u8 runMethod_2[])
{
	u8 i=0;
	while(runMethod[i]!=0)
	{
		if(runMethod_2[i]>=39) break;
		else i++;
	}
	i=0;
	while(runMethod_2[i]!= 0)
	{
		if(runMethod_2[i]>=39) return 1;
		else i++;
	}
	return 0;
}
/*

* 函数介绍：第二轮自动重置奔跑路线
* 输入参数：runMethod_2（在屏幕中选择的第二轮过门路线  DoorFlag(门开标志位，记录那个门处于开启状态    runMethodTableDoorAuto(过门路线表))）
* 输出参数：无
* 返回值  ：无
* 作者    ：@陈

*/
void runMethodResetDoorSecond(u8 runMethod_2[],u8 doorflag,const u8 runMethodTableDoorAuto[][100])
{
	u8 i=0;
	
	/*数组清零*/
	while(runMethod_2[i]!= 0)
	{
		runMethod_2[i]= 0;
		i++;
	}
	/*更新路线*/
	i=0;
	while(runMethodTableDoorAuto[doorflag+3][i] != 0)
	{
		runMethod_2[i] = runMethodTableDoorAuto[doorflag+3][i];
		i++;
	}
	
}
	

	
	
	
	
	
	

