#ifndef _MYGUI_H_
#define _MYGUI_H_

#include "myconfig.h"

#define  GUI_NUM 30

extern u8 keyFlag;


typedef struct{
	
	u8 curIndex;				// 当前界面索引
	u8 downIndex;				// 向下按键需要跳转的索引
	u8 upIndex;					// 向上按键需要跳转的索引
	u8 enterIndex;			// 确认按键需要跳转的索引
	u8 escIndex;				// 返回按键需要跳转的索引
//	excState state;     //执行状态 
	void (*function)(); // 当前索引执行函数的入口地址
		
}myGUIIndexTypeDef;

void bootDisplay(void);
void displayOperation(void);
void displayControl(controlCenterTypeDef *controlp);



#endif











