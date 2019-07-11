#ifndef __MYIIC_H__
#define __MYIIC_H__
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//IIC 驱动函数	   
//修改日期:2014/3/10 
//版本：V1.0
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

   	   		   
//IO方向设置
#define SDA_IN()  {GPIOD->CRH&=0XFFFF0FFF;GPIOD->CRH|=8<<12;}
#define SDA_OUT() {GPIOD->CRH&=0XFFFF0FFF;GPIOD->CRH|=3<<12;}

//IO操作函数	 
#define IIC_SCL    PDout(12) //SCL
#define IIC_SDA    PDout(11) //SDA	 
#define READ_SDA   PDin(11)  //输入SDA 

#define true 1
#define false 0 

#define TRUE  0
#define FALSE -1

#define  I2C_Direction_Transmitter      ((uint8_t)0x00)	//写
#define  I2C_Direction_Receiver         ((uint8_t)0x01)	//读

//IIC所有操作函数
void IIC_Init(void);  //初始化IIC的IO口				 
u8 IIC_Write_Buffer(u8 addr, u8 reg, u8 len, u8 * data);
int IIC_Write(u8 addr, u8 reg, u8 len, u8* data);
u8 IIC_Read_Buffer(u8 addr, u8 reg, u8 len, u8* buf);
int IIC_Read(u8 addr, u8 reg, u8 len, u8 *buf);
u8 IIC_WriteOneByte(u8 addr, u8 reg, u8 data);
u16 IIC_GetErrorCounter(void);
  
#endif
