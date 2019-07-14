#include "control.h"
#include "string.h"
#include "myconfig.h"


extern const map_linkInforTypeDef mapInformation[][NODEFORKNUM];





/*

* 函数介绍：更改控制中心状态信号
* 输入参数：p(控制中心名字)	updataState（输入状态信号）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void	updataState_Reset(controlCenterTypeDef *p,updataState state)
{
	p->update = state;
}




/*

* 函数介绍：将路段信息更新到控制中心
* 输入参数：controlp(更新的控制中心名字)p(地图规则表)
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
static void	linkInformUpdate(controlCenterTypeDef *controlp,const map_linkInforTypeDef(*p)[NODEFORKNUM])
{
		int i;
		for(i = 0;i < NODEFORKNUM;i++)
			{
				if(controlp->nextNode == (*(p+controlp->curNode)+i)->map_nextNode)
				{
					if(controlp->nnNode == (*(p+controlp->curNode)+i)->map_nnNode)
					{
						controlp->linkInform.findLineWays = (*(p+controlp->curNode)+i)->map_findLineWays;
						controlp->linkInform.typeRoadblock = (*(p+controlp->curNode)+i)->map_typeRoadblock;
						controlp->linkInform.typeSpeed = (*(p+controlp->curNode)+i)->map_typeSpeed;
						controlp->linkInform.speedTime = (*(p+controlp->curNode)+i)->map_speedTime;
						controlp->linkInform.seekways = (*(p+controlp->curNode)+i)->map_seekways;
						controlp->linkInform.parkways = (*(p+controlp->curNode)+i)->map_parkways;
						controlp->linkInform.rotateAngle = (*(p+controlp->curNode)+i)->map_rotateAngle;
						break;
					}
				}
			
			}


}

/*

* 函数介绍：控制中心初始化函数
* 输入参数：controlp(更新的控制中心名字)curNode(当前节点编号)nextNode（下一节点编号）nnNode（下下节点编号）nodeNum（路线中待跑编号的位置）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void Control_Init(controlCenterTypeDef *controlp,u8*runMethod)
{
	memset(controlp,0,sizeof(controlCenterTypeDef));//对控制中心结构体清零
	
	controlp->curNode =	runMethod[0];
	controlp->nextNode = runMethod[1];
	controlp->nnNode	 = runMethod[2];
	controlp->nodeNum	= 3;

	controlp->update	=	EIC;
	

}


/*

* 函数介绍：更新控制中心（controlCenterTypeDef结构体）的参数。注意：只有当到达新节点的时候才会更新
* 输入参数：controlp（控制中心）、nodeLength（路线节点总个数）runMethod（路线数组）p（地图规则）
* 输出参数：无
* 返回值  ：1(更新成功)0(更新失败)
* 作者    ：@断忆

*/
unsigned char control_Update(controlCenterTypeDef *controlp,u8 nodeLength,const u8 *runMethod,const map_linkInforTypeDef(*p)[NODEFORKNUM] )
{
	if(controlp->update == EIC)
	{
				
		/*找出接下来寻迹的路段并将信息更新到控制中心*/
		linkInformUpdate(controlp,p);
			
		/*更新控制中心curNode、nextNode、nnNode*/
		if(controlp->nodeNum < nodeLength)
		{
			controlp->curNode = controlp->nextNode;
			controlp->nextNode = controlp->nnNode;
			controlp->nnNode = runMethod[controlp->nodeNum];
			controlp->nodeNum++;
		}
		else
		{
			controlp->curNode = controlp->nextNode;
			controlp->nextNode = controlp->nnNode;
		}
		
				/*将控制中心的状态标志位设置成NTBE*/
		updataState_Reset(controlp,NTBE);
		
		return 1;
	}
	return 0;
}

/*

* 函数介绍：根据控制台起始路段初始化运行状态
* 输入参数：runState(运行状态记录器的地址) controlp（控制台的地址）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/	
void runStateInit(runStateTypeDef *runState,const controlCenterTypeDef *controlp)
{
		runState->F_LineState = NTBE;					//需要执行	
		runState->F_RoadBlockState = (controlp->linkInform.typeRoadblock==FREE)?EIC:NTBE; //没有路障的时候就（执行完成），有路障就（需要执行）
    runState->speedState = STANDBY;			//待命状态等待路障来触发
		runState->seekNodeState = STANDBY;		//待命状态等待路障来触发
		runState->carParkState = STANDBY;			//待命状态等待“找点处于EIC”触发
		runState->RotangleState = STANDBY;		//待命状态等待“停车处于EIC”触发
}	
	
	
	
	
	
/*

* 函数介绍：根据控制台判断是否来到新的路段，然后重新设置运行状态
* 输入参数：runState(运行状态记录器的地址) controlp（控制台的地址）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/

void runStateReset(runStateTypeDef *runState,const controlCenterTypeDef *controlp)
{
		runState->F_LineState = ((controlp->curNode==controlp->nextNode)&&(controlp->nextNode==controlp->nnNode))?EIC:NTBE;						//需要执行		
		runState->F_RoadBlockState = (controlp->linkInform.typeRoadblock==FREE)?EIC:NTBE; //没有路障的时候就（执行完成），有路障就（需要执行）
    runState->speedState = STANDBY;			//待命状态等待路障来触发
		runState->seekNodeState = STANDBY;	//待命状态等待路障来触发
		runState->carParkState = STANDBY;//待命状态等待“找点处于EIC”触发
		runState->RotangleState = STANDBY;//待命状态等待“停车处于EIC”触发

}


/*

* 函数介绍：重置奔跑路线
* 输入参数：runMethod(储存被替换奔跑路线) runMethod_2（存储替换的奔跑的路线）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void runMethodReset(u8 runMethod[],const u8 runMethod_2[])
{
	u8 i=0;
	/*数组清零*/
	while(runMethod[i]!= 0)
	{
		runMethod[i]= 0;
		i++;
	}
	/*更新路线*/
	i=0;
	while(runMethod_2[i] != 0)
	{
		runMethod[i] = runMethod_2[i];
		i++;
	}
	
}


/*

* 函数介绍：从奔跑路线表格中选择奔跑路线
* 输入参数：runMethod(储存被替换奔跑路线) runMethodNum(第几条路线)runMethodTab（路线表）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void runMethodUpdate(u8 runMethod[],u8 runMethodNum, const u8 runMethodTab[][100])
{
	u8 i=0;
	/*数组清零*/
	while(runMethod[i]!= 0)
	{
		runMethod[i]= 0;
		i++;
	}
	/*更新路线*/
	i=0;
	while(runMethodTab[runMethodNum][i] != 0)
	{
		runMethod[i] = runMethodTab[runMethodNum][i];
		i++;
	}
	
}









/*

* 函数介绍：巡线任务
* 输入参数：controlp（控制台的地址） runState(运行状态记录器的地址)
* 输出参数：无
* 返回值  ：无
* 其他		：根据控制台的路段信息的巡线方法执行相应方法,根据运行状态决定是否运行
* 作者    ：@断忆

*/
void findLine_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState)
{
		
		if(runState->F_LineState == NTBE)
		{
			switch(controlp->linkInform.findLineWays)
			{
				case FL_default: 	 flMethod_default();break;
				case FL_node: 	 	 flMethod_node();break;
				case FL_43_44: 	 	 flMethod_43_44();break;
				case FL_16_44: 	 	 flMethod_16_44();break;
				case FL_circular:  flMethod_circular();break;
				case FL_middle: 	 flMethod_middle();break;
				case FL_brige: 	 	 flMethod_brige();break;
				case FL_brigeup:   flMethod_brige_up();break;
				case FL_brigedown: flMethod_brige_down();break;
				case FL_slow:			 flMethod_slow();break;
				case FL_slowest:			 flMethod_slowest();break;
				case FL_UpPlatform:	flMethod_UpPlatform();break;
				case FL_DownPlatform:	flMethod_DownPlatform();break;
				case FL_quick:		 flMethod_quick();break;
				case FL_stop :		 flMethod_stop();break;
				case FL_quickest	:flMethod_quickest();	break;
				case FL_upPeak		:flMethod_upPeak();break;
				case FL_downPeak	:flMethod_downPeak();break;
				case FL_left			:flMethod_left();break;
				case FL_Right			:flMethod_right();break;
				case NFL: 			 speedAdjustment(1690,1800);break;
				case FL_angle:   flMethod_NFL();break;
				case FL_angle_slow:  flMethod_NFL_slow();break;
				case NFL_slow:   speedAdjustment(1300,1320);break;
				case BACK_NFL:   speedAdjustment(-1500,-1500);break;
				default:  break;
			}
		}
		else if(runState->F_LineState == EIC)
		{
				
				if(3 == runTimes)
				{
//					delay_ms(1000);
//					delay_ms(1000);
					runTimes = 1;
					speedAdjustment(0,0);  //停车
				}
				
				else if(4 == runTimes)
				{
					speedAdjustment(0,0);  //停车
					runTimes = 5;
					Gui_DrawFont_GBK16(0,80,RED,WHITE,"Finish");
					while(1)
					{
						/*当有按键按下就跳出*/
						keyFlag = keyScan(0);
						if(keyFlag==KEY4_ESC)
						{
							keyFlag = 0;
							Gui_DrawFont_GBK16(0,100,RED,WHITE,"ESC_Again");
							break;
						}
					}
				}	
		}
	
	
}



/*

* 函数介绍：路障解决任务
* 输入参数：runStateconst(运行状态记录器) controlp（控制台）
* 输出参数：无
* 返回值  ：无
* 其他		：根据控制台的路段信息的路障类型判断出路障并执行处理方法，
* 作者    ：@断忆|@陈

*/
void roadBlocksHandle_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState) //识别到路障后，执行路障处理函数，处理完后将"F_RoadBlockState"标志成执行完成
{
	if((runState->F_RoadBlockState==NTBE) && (runState->F_LineState != EIC))
	{
		switch(controlp->linkInform.typeRoadblock)
		{
			case FREE :											
									{		runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("FREE_EIC\r\n");
											#endif
									}break; 
			case BRIGE:if(1 == BlockHandleMethod_Brige())
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("BRIGE_EIC\r\n");
											#endif
									}break; 
			case DOOR	:if(1 == BlockHandleMethod_DOOR())
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("DOOR_EIC\r\n");
											#endif
									}break; 
			case DOOR2	:if(1 == BlockHandleMethod_DOOR_2())
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("DOOR_EIC\r\n");
											#endif
									}break; 
			case S_BOARD_1:	if(1==BlockHandleMethod_S_BOARD_1())	
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("S_BOARD_1_EIC\r\n");
											#endif
									}break; 
			case S_BOARD_2:	if(1==BlockHandleMethod_S_BOARD_2())						
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("S_BOARD_2_EIC\r\n");
											#endif
									}break; 
			case S_BOARD_26_27:	if(1==BlockHandleMethod_26_27())					
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("S_BOARD_26_27_EIC\r\n");
											#endif
									}break; 
									
			case S_BOARD_DOUBLE:	if(1==BlockHandleMethod_S_BOARD_Double())					
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("S_BOARD_DOUBLE_EIC\r\n");
											#endif
									}break; 
		
			case GO_TILT_R: if(1 == BlockHandleMethod_GO_Tilt_R())							
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("GO_TILT_R_EIC\r\n");
											#endif
									}break; 
			case GO_TILT_L: if(1 == BlockHandleMethod_GO_Tilt_L())								
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("GO_TILT_L_EIC\r\n");
											#endif
									}break; 
			case BACK_TILT_R:if(1 == BlockHandleMethod_BACK_TILT_R())						
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("BACK_TILT_R_EIC\r\n");
											#endif
									}break; 
			case BACK_TILT_L:if(1 == BlockHandleMethod_BACK_TILT_L())					
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("BACK_TILT_L_EIC\r\n");
											#endif
									}break; 
			case ALL_TILT   :if(1 == BlockHandleMethod_Crossing_All_TILT())					
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("ALL_TILT_EIC\r\n");
											#endif
									}break; 
			
			case SLOPE :if(1 == BlockHandleMethod_Slope ())
										{
											runState->F_RoadBlockState = EIC;
											#ifdef BlueTooth_Debug
												u3_printf("SLOPE_EIC\r\n");
											#endif
										}break;
			
			case PLATFORM:if(1 == BlockHandleMethod_Platform ())							
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("PLATFORM_EIC\r\n");
											#endif
									}break; 
			case PLATFORM_1:if(1 == BlockHandleMethod_Platform_1 ())							
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("PLATFORM_1_EIC\r\n");
											#endif
									}break; 
			case Peak:if(1 == BlockHandleMethod_Peak())					
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("Peak_EIC\r\n");
											#endif
									}break; 
			case DOWNPLATFORM:if(1 ==  BlockHandleMethod_downPlatform())							
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("DOWNPLATFORM_EIC\r\n");
											#endif
									}break; 
			case DOWN27_26   :if(1 == BlockHandleMethod_down_27_26())						
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("DOWN27_26_EIC\r\n");
											#endif
									}break; 
			
			case TRAPEZOID_1:if(1 == BlockHandleMethod_Trapezoid_1())						
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("TRAPEZOID_1_EIC\r\n");
											#endif
									}break; 
			case TRAPEZOID_2:if(1 == BlockHandleMethod_Trapezoid_2())				
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("TRAPEZOID_2_EIC\r\n");
											#endif
									}break; 
			case TRAPEZOID_3:if(1 == BlockHandleMethod_Trapezoid_3())								
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("TRAPEZOID_3_EIC\r\n");
											#endif
									}break; 
			
			case TIME				:if(1 == BlockHandleMethod_TIME ())							
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("TIME_EIC\r\n");
											#endif
									}break; 
			case TIME_1			:if(1 == BlockHandleMethod_TIME_1 ())								
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("TIME_1_EIC\r\n");
											#endif
									}break; 
			case TIME_2			:if(1 == BlockHandleMethod_TIME_2 ())		 								
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("TIME_2_EIC\r\n");
											#endif
									}break; 
		
			case SEESAW:	if(1==BlockHandleMethod_Seesaw())
										{
											runState->F_RoadBlockState = EIC;
											#ifdef _DEBUG_U3_P
												u3_printf("SEESAW_EIC\r\n");
											#endif
										}break;
			
			case Block_PESR:if(1 == BlockHandleMethod_PESR())
									{
											runState->F_RoadBlockState = EIC;												
											#ifdef _DEBUG_
											led1_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("SPEEDTIME_44_37\r\n");
											#endif
									}break;

			case ANGLE:if(1 == Angle_read())										
							{		runState->F_RoadBlockState = EIC;												
									#ifdef _DEBUG_
									led1_flash();
									#endif
									#ifdef _DEBUG_U3_P
									u3_printf("Angle_read_EIC\r\n");
									#endif
									}break; 
			case Platform_37_15:		
										if(1 == BlockHandleMethod_Platform_37_15())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
			case TIME_45_46:if(1 == BlockHandleMethod_TIME_45_46 ())		 
								{
									runState->F_RoadBlockState = EIC;
									#ifdef BlueTooth_Debug
										u3_printf("TIME_EIC_3\r\n");
									#endif
								}break;
			default:  			break;
		}
	}
	
}
/*

* 函数介绍：加速任务
* 输入参数：runStateconst(运行状态记录器) controlp（控制台）
* 输出参数：无
* 返回值  ：无
* 其他	  ：根据控制台的路段信息的找点方法执行相应方法
* 作者    ：@袁梓聪

*/
void speed_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState){

	if(runState->speedState == NTBE){
		
		switch(controlp->linkInform.typeSpeed){
			
			case DOWN_SPEED:
              if(1 == Speed_downMethod(controlp->linkInform.speedTime))
							{
								runState->speedState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_PESL_EIC\r\n");
								#endif
								
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
			case COMMON_SPEED:
              if(1 == Speed_commonMethod(controlp->linkInform.speedTime))
							{
								runState->speedState=EIC;
                
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_PESL_EIC\r\n");
								#endif
								
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
			case NOSPEED:
              if(1)
							{
								runState->speedState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_PESL_EIC\r\n");
								#endif
								
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
			case TME:
              if(1 == Take_up_time(controlp->linkInform.speedTime))
							{
								runState->speedState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_PESL_EIC\r\n");
								#endif
								
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
      default:break;
		}
			
	}
	else if(runState->speedState == STANDBY)
	{
		if(runState->F_RoadBlockState == EIC)
			runState->speedState = NTBE;	
	}

}

/*

* 函数介绍：找点任务
* 输入参数：runStateconst(运行状态记录器) controlp（控制台）
* 输出参数：无
* 返回值  ：无
* 其他	  ：根据控制台的路段信息的找点方法执行相应方法
* 作者    ：@断忆|@陈

*/
void seekNode_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState)
{
	if(runState->seekNodeState == NTBE)
	{
    
		switch(controlp->linkInform.seekways)
		{
			case SEEK_PESL:
											if(1 == seekNodeMethod_pesL())
											{
												runState->seekNodeState=EIC;
												#ifdef _DEBUG_
												led0_flash();
												#endif
												#ifdef _DEBUG_U3_P
												u3_printf("Seek_pesL_EIC\r\n");
												#endif
											}
											break;
			case SEEK_PESR:
											if(1 == seekNodeMethod_pesR())
											{
												runState->seekNodeState=EIC;

												#ifdef _DEBUG_
												led0_flash();
												#endif
												#ifdef _DEBUG_U3_P
												u3_printf("Seek_pesR_EIC\r\n");
												#endif
												
											}
											break;
			case SEEK3:
										if(1 == seekNodeMethod_4())
										{
											runState->seekNodeState=EIC;

											#ifdef _DEBUG_
											led0_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("Seek3_EIC\r\n");
											#endif

										}
										break;
			case SEEK4:
										if(1 == seekNodeMethod_10())
										{
											runState->seekNodeState=EIC;

											#ifdef _DEBUG_
											led0_flash();
											#endif
											#ifdef _DEBUG_U3_P
											u3_printf("Seek4_EIC\r\n");
											#endif
											
										}
										break;
			case SEEK_default:
												if(1 == seekNodeMethod_default())
												{
													runState->seekNodeState=EIC;

													#ifdef _DEBUG_
													led0_flash();
													#endif
													#ifdef _DEBUG_U3_P
													u3_printf("SEEK_default\r\n");
													#endif
													
												}
												break;
//			case SEEK_8_6:
//												if(1 == seekNodeMethod_8_6())
//												{
//													runState->seekNodeState=EIC;

//													#ifdef _DEBUG_
//													led0_flash();
//													#endif
//													#ifdef _DEBUG_U3_P
//													u3_printf("SEEK_8_6\r\n");
//													#endif
//													
//												}
//												break;
			case NOTSEEK:
											if(1)
											{
												runState->seekNodeState=EIC;

												#ifdef _DEBUG_
												led0_flash();
												#endif
												#ifdef _DEBUG_U3_P
												u3_printf("NOTSEEK\r\n");
												#endif
												
											}
											break;
			case SEEK_PesPlatform:
                       
											if(1==seekNodeMethod_pesPlatform())
											{
												runState->seekNodeState=EIC;
												#ifdef _DEBUG_
												led0_flash();
												#endif
												#ifdef _DEBUG_U3_P
												u3_printf("SEEK_PesPlatform\r\n");
												#endif
												
											}
											break;
			case SEEK_Collision:
											if(1==seekNodeMethod_Collision())
											{
												runState->seekNodeState=EIC;
												
												#ifdef _DEBUG_
												led0_flash();
												#endif
												#ifdef _DEBUG_U3_P
												u3_printf("SEEK_Collision\r\n");
												#endif
												
											}break;
											
			case SEEK_SeeSaw:if(1==seekNodeMethod_SeeSaw_2019())
												{
												runState->seekNodeState=EIC;
												#ifdef _DEBUG_
												led0_flash();
												#endif
												#ifdef _DEBUG_U3_P
												u3_printf("SEEK_SeeSaw\r\n");
												#endif
											}break;
       case SEEK_DIGR:if(1 == seekNodeMethod_digR())
												{
//												speedAdjustment(0,0);
//												while(1);
												runState->seekNodeState=EIC;
												#ifdef _DEBUG_
												led0_flash();
												#endif
												#ifdef _DEBUG_U3_P
												u3_printf("SEEK_DIGR\r\n");
												#endif
											}break;
       case SEEK_DIGL:if(1 == seekNodeMethod_digL())
												{
												runState->seekNodeState=EIC;
												#ifdef _DEBUG_
												led0_flash();
												#endif
												#ifdef _DEBUG_U3_P
												u3_printf("SEEK_DIGL\r\n");
												#endif
											}break;
			 case SEEK_SeeSaw_back:if(1==seekNodeMethod_SeeSaw_back())
								       {
								      	runState->seekNodeState=EIC;
								      	#ifdef BlueTooth_Debug
									    	u3_printf("SEEK_SeeSaw\r\n");
								      	#endif
										
								      	#ifdef LED_Debug
									    	led_flash();
								       	#endif
						          	}break;								
											
											
			default: 		break;
		
		}
	
	}
	else if(runState->seekNodeState == STANDBY)
		{
			if(runState->speedState == EIC)
				runState->seekNodeState = NTBE;	
		}
	
}







/*

* 函数介绍：停车任务
* 输入参数：runStateconst(运行状态记录器) controlp（控制台）
* 输出参数：无
* 返回值  ：无
* 其他		：根据控制台的路段信息的停车方法执行相应方法
* 作者    ：@断忆|@陈

*/
void carPark_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState)
{
	if(runState->carParkState == NTBE)
	{
		switch(controlp->linkInform.parkways)
			{
				case NOTPARK:
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("NOTPARK_EIC\r\n");
											#endif
										}break;
				case PARK1:		
										if(1)
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK1_EIC\r\n");
											#endif
										}break;
				case PARK_pesR:		
										if(1 == parkMethod_pesR())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_pesR_200:		
										if(1 == parkMethod_pesR_Delay(200))
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_pesR_250:		
										if(1 == parkMethod_pesR_Delay(250))
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_pesR_300:		
										if(1 == parkMethod_pesR_Delay(300))
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_pesR_350:		
										if(1 == parkMethod_pesR_Delay(350))
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_pesR_400:		
										if(1 == parkMethod_pesR_Delay(400))
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_default:
										if(1 == parkMethod_default())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_default_EIC\r\n");
											#endif
										}break;
				case PARK_pesL:		
										if(1 == parkMethod_pesL())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesL_EIC\r\n");
											#endif
										}break;
				case PARK_pesL_200:		
										if(1 == parkMethod_pesL_Delay(200))
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_pesL_250:		
										if(1 == parkMethod_pesL_Delay(250))
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_pesL_300:		
										if(1 == parkMethod_pesL_Delay(300))
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_pesL_350:		
										if(1 == parkMethod_pesL_Delay(350))
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_pesL_400:		
										if(1 == parkMethod_pesL_Delay(400))
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_EIC\r\n");
											#endif
										}break;
				case PARK_PesPlatform:		
										if(1==parkMethod_pesPlatform())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_PesPlatform_EIC\r\n");
											#endif
										}break;
				case PARK_Door:		
										if(1==parkMethod_Door())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_Door_EIC\r\n");
											#endif
										}break;
				case PARK_pesR_45:		
										if(1 == parkMethod_pesR_45())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_45_EIC\r\n");
											#endif
										}break;
				case PARK_pesL_45:		
										if(1 == parkMethod_pesL_45())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesL_45_EIC\r\n");
											#endif
										}break;
				case PARK_pesR_No:		
										if(1 == parkMethod_pesR_noline())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_45_EIC\r\n");
											#endif
										}break;
				case PARK_pesL_No:		
										if(1 == parkMethod_pesL_noline())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesL_45_EIC\r\n");
											#endif
										}break;
				case PARK_pesR_back:		
										if(1 == parkMethod_pesR_back())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesR_45_EIC\r\n");
											#endif
										}break;
				case PARK_pesL_back:		
										if(1 == parkMethod_pesL_back())
										{
											runState->carParkState = EIC;
											#ifdef _DEBUG_U3_P
											u3_printf("PARK_pesL_45_EIC\r\n");
											#endif
										}break;						
				default:break;
			}
	
	}
	else if(runState->carParkState == STANDBY)
		{
			if(runState->seekNodeState == EIC)
				runState->carParkState=NTBE;	
		}
}

/*

* 函数介绍：转弯任务
* 输入参数：runStateconst(运行状态记录器) controlp（控制台）
* 输出参数：无
* 返回值  ：无
* 其他		：根据控制台的路段信息的转弯方法执行相应方法
* 作者    ：@断忆|@陈

*/
void rotAngle_Task(controlCenterTypeDef *controlp,runStateTypeDef *runState)
{
	if(runState->RotangleState == NTBE)
	{
		switch(controlp->linkInform.rotateAngle)
		{
			case HN_Rotate:
									if(1)
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HN_Rotate_EIC\r\n ");
										#endif
									}break;
			case HR_35:	
									if(1 == rotAngleMethod_R35())
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_35_EIC\r\n ");
										#endif
									}break;
			case HR_45:	if(1 == rotAngle_Right(45)) 
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_45_EIC\r\n ");
										#endif
									}break;
			case HR_60: if(1 == rotAngle_Right(65))	
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_60_EIC\r\n ");
										#endif
									}break;
			case HR_80 :if(1 == rotAngle_Right(80))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_80_EIC\r\n ");
										#endif
									}break;
			case HR_90 :if(1 == rotAngle_Right(90))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_90_EIC\r\n ");
										#endif
									}break;
			case HR_110:if(1 == rotAngle_Right(110))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_110_EIC\r\n ");
										#endif
									}break;
			case HR_120:if(1 == rotAngle_Right(120))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_120_EIC\r\n ");
										#endif
									}break;
			case HR_135:if(1 ==	rotAngle_Right(135))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_135_EIC\r\n ");
										#endif
									}break;
			case HR_135_F:if(1 ==	rotAngle_Right_F(135))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_135_EIC\r\n ");
										#endif
									}break;
			case HR_120_F:if(1 ==	rotAngle_Right_F(120))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_135_EIC\r\n ");
										#endif
									}break;
			case HR_145:if(1 == rotAngle_Right(150))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_145_EIC\r\n ");
										#endif
									}break;
			case HR_150:if(1 == rotAngle_Right(150))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_180_EIC\r\n ");
										#endif
									}break;
			case HR_160:if(1 == rotAngle_Right(160))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_180_EIC\r\n ");
										#endif
									}break;
			case HR_170:if(1 == rotAngle_Right(170))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_180_EIC\r\n ");
										#endif
									}break;
			case HR_180:if(1 == rotAngle_Right(180))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_180_EIC\r\n ");
										#endif
									}break;
			case HR_180_F:if(1 == rotAngle_Right_F(180))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HR_180_EIC\r\n ");
										#endif
									}break;
	    case rot_RFL:if(1 == rotAngleMethod_RFL())
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("rot_RFL_EIC\r\n ");
										#endif
									}break;
			case rot_UR :if(1 == rotAngle_UR(70))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("rot_UR_EIC\r\n ");
										#endif
									}break;
			
			case HL_35 :if(1 == rotAngle_Left(35))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_35_EIC\r\n ");
										#endif
									}break;
			case HL_45 :if(1 == rotAngle_Left(45))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_45_EIC\r\n ");
										#endif
									}break;
			case HL_60 :if(1 == rotAngle_Left(60))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_60_EIC\r\n ");
										#endif
									}break;
			case HL_80 :if(1 == rotAngle_Left(80))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_80_EIC\r\n ");
										#endif
									}break;
			case HL_90 :if(1 == rotAngle_Left(90))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_90_EIC\r\n ");
										#endif
									}break;
			case HL_105 :if(1 == rotAngle_Left(105))
							{
											runState->RotangleState=EIC;
											runState->F_LineState=EIC;
											updataState_Reset(controlp,EIC);
											#ifdef BlueTooth_Debug
												u3_printf("HL_110_EIC\n\n");
											#endif
										}break;
			case HL_110 :if(1 == rotAngle_Left(110))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_110_EIC\r\n ");
										#endif
									}break;
			case HL_120 :if(1 == rotAngle_Left(120))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_120_EIC\r\n ");
										#endif
									}break;
			case HL_135:if(1 == rotAngle_Left(135))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_135_EIC\r\n ");
										#endif
									}break;
			case HL_145:if(1 == rotAngle_Left(145))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_145_EIC\r\n ");
										#endif
									}break;
			case HL_180:if(1 == rotAngle_Left(180))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_180_EIC\r\n ");
										#endif
									}break;
			case HL_180_F:if(1 == rotAngle_Left_F(180))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
                                      
										#ifdef _DEBUG_U3_P
										u3_printf("HL_180_EIC\r\n ");
										#endif
									}break;
			case HL_185:if(1 == rotAngle_Left(185))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("HL_185_EIC\r\n ");
										#endif
									}break;
			case rot_LFL:if(1 == rotAngleMethod_LFL())
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("rot_LFL_EIC\r\n ");
										#endif
									}break;
			case rot_UL :if(1 == rotAngle_UL(80))
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("rot_UL_EIC\r\n ");
										#endif
									}break;
			case Sensor_L90:if(1==rotAngle_UL_crossroad()) 
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("Sensor_L90_EIC\r\n ");
										#endif
									}break;
			case Sensor_R90:if(1==rotAngle_UR_crossroad()) 
									{
										runState->RotangleState=EIC;
										runState->F_LineState=EIC;
										updataState_Reset(controlp,EIC);
										#ifdef _DEBUG_U3_P
										u3_printf("Sensor_R90_EIC\r\n ");
										#endif
									}break;
			default    :break;	
		}
	}
	else if(runState->RotangleState == STANDBY)
	{
		if(runState->carParkState == EIC)
			runState->RotangleState=NTBE;
	}
}










	
	


