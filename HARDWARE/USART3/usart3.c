#include "usart3.h"	
#include "sys.h"
#include "stdarg.h"
#include "string.h"
#include "stdio.h"
#include "myconfig.h"

char *findLinep[]={"FL_default","FL_brige","FL_brigeup","FL_brigedown","FL_slow","FL_quick","FL_stop","FL_quickest","FL_upPeak","FL_downPeak","FL_left","FL_Right","rot_RFL","NFL","BACK_NFL"};

char *typeRoadblockp[]={"FREE","BRIGE","DOOR","S_BOARD_1","S_BOARD_2","S_BOARD_26_27","SEESAW","GO_TILT_R","GO_TILT_L","BACK_TILT_R","BACK_TILT_L","SLOPE",\
												"PLATFORM","PLATFORM_1","Peak","TRAPEZOID_1","TRAPEZOID_2","TRAPEZOID_3",\
												"TIME","TIME_1","TIME_2","TIME_3","SPEEDTIME_1","SPEEDTIME_2","SPEEDTIE_36_17","SPEEDTIME_17_37","DOWNPLATFORM","ALL_TILT","DOWN27_26"};

char *seekNodeWayp[]={"SEEK_PESL","SEEK_PESR","SEEK3","SEEK4","SEEK_default","NOTSEEK","SEEK_PesPlatform","SEEK_Collision"};

char *carParkp[]={"NOTPARK","PARK1","PARK_pesR","PARK_def","PARK_pesL","PARK_PesPlatform"};

char *carRotAnglep[]={"HL_180","HL_145","HL_135","HL_90","HL_60","HL_45","HL_35","HN_Rotate",\
											"HR_35","HR_45","HR_60","HR_90","HR_110","HR_135","HR_145","HR_180","rot_LFL","rot_RFL","rot_UL","rot_UR","Sensor_L90","Sensor_R90"};

char *updataStatep[]={"NTBE","EIC","STANDBY"};

//u8 uartData;

/*

* 函数介绍：串口3的DMA规则设置
* 输入参数：(DMA_CHx)DMA通道CHx	(cpar)外设地址	(cmar)存储器地址
* 输出参数：
* 返回值  ：
* 作者    ：@断忆

*/

void USART3_DMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar)
{
	DMA_InitTypeDef DMA_InitStructure;
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
    DMA_DeInit(DMA_CHx);   															//将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  	//DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  			//DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = 0;  							//DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  									//内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  	//数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 					//数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  													//工作在正常缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 									//DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  													//DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure);  																//根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器	
}

/*

* 函数介绍：DMA1的各通道配置,这里的传输形式是固定的,这点要根据不同的情况来修改,从存储器->外设模式/8位数据宽度/存储器增量模式
* 输入参数：(DMA_CHx)DMA通道CHx	(cpar)外设地址	(cmar)存储器地址
* 输出参数：
* 返回值  ：
* 作者    ：@断忆

*/
void USART_DMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar)
{
	DMA_InitTypeDef DMA_InitStructure;
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
  DMA_DeInit(DMA_CHx);   															//将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  	//DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  			//DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = 66;  							//DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  									//内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  	//数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 					//数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  													//工作在正常缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; 									//DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  													//DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure);  																//根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器	
}

/*串口3中断服务程序*/
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART3_RX_BUF[USART3_REC_LEN];     //接收缓冲,最大USART3_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART3_RX_STA=0;       //接收状态标记	  

//初始化IO 串口3 
//bound:波特率
void usart3_init(u32 bound)
{
    /*GPIO端口设置*/
		 /*GPIO端口设置*/
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		/*使能USART3*/
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	
		/*使能USART1，GPIOB时钟*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
		/*复位串口3*/
		USART_DeInit(USART3);  
		/*USART3_TX   PB10*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB10
    /*USART1_RX	  PB11*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB11
   /*Usart3 NVIC 配置*/
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级1
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
   /*USART3 初始化设置*/
		USART_InitStructure.USART_BaudRate = bound;																				//一般设置为9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;												//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;													//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;															//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;								//收发模式

    USART_Init(USART3, &USART_InitStructure); 			//初始化串口
		
		/*使能串口3的DMA发送*/
		USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);  	
		/*DMA1通道3,外设为串口3,存储器为USART3_TX_BUF*/
		USART_DMA_Config(DMA1_Channel5,(u32)&USART1->DR,(u32)USART3_TX_BUF);
    
		/*使能串口3的DMA发送*/
		USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);  	
		/*DMA1通道3,外设为串口3,存储器为USART3_TX_BUF*/
		USART3_DMA_Config(DMA1_Channel2,(u32)&USART3->DR,(u32)USART3_TX_BUF);

}
#if EN_USART3_RX   //如果使能了接收
void USART3_IRQHandler(void)                	//串口1中断服务程序
	{
	//u8 Res;
#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
				if(USART3->DR == 1)
				{
					speedAdjustment(0,0);
					while(1);
				}
				
		
				
     } 
#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntExit();  											 
#endif
} 
#endif	




/*

* 函数介绍：开启一次串口1DMA传输
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者   :@位胜

*/
void USART_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{
	/*库函数版本*/
		//	DMA_Cmd(DMA_CHx, DISABLE ); 				 //关闭 指示的通道        
		//	DMA_SetCurrDataCounter(DMA_CHx,len);//DMA通道的DMA缓存的大小	
		//	DMA_Cmd(DMA_CHx, ENABLE);           //开启DMA传输
	/*寄存器版本*/
				DMA_CHx->CCR&=~(1<<0);//关闭DMA传输
				DMA_CHx->CNDTR=66;   //DMA1,传输数据量 
				DMA_CHx->CCR|=1<<0;   //开启DMA传输
}	  		

/*

* 函数介绍：开启一串口3DMA传输
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void USART3_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u8 len)
{
	/*库函数版本*/
		//	DMA_Cmd(DMA_CHx, DISABLE ); 				 //关闭 指示的通道        
		//	DMA_SetCurrDataCounter(DMA_CHx,len);//DMA通道的DMA缓存的大小	
		//	DMA_Cmd(DMA_CHx, ENABLE);           //开启DMA传输
	/*寄存器版本*/
				DMA_CHx->CCR&=~(1<<0);//关闭DMA传输
				DMA_CHx->CNDTR=len;   //DMA1,传输数据量 
				DMA_CHx->CCR|=1<<0;   //开启DMA传输
}	 

/*

* 函数介绍：串口3,printf 函数
* 输入参数：无
* 输出参数：无
* 返回值  ：无
*	其他		：确保一次发送数据不超过USART2_MAX_SEND_LEN字节
* 作者    ：@断忆

*/
void u3_printf(char* fmt,...)  
{  
	va_list ap;
	va_start(ap,fmt);
	while(DMA1_Channel2->CNDTR!=0);					//等待通道2传输完成才更新缓存区
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);  
		USART_DMA_Enable(DMA1_Channel3); 	//通过dma发送出去
	
}

/*

* 函数介绍：通过串口3将传感器模拟量全部打印
* 输入参数：（sourceArray）数组储存首地址
* 输出参数：无
* 返回值  ：无
*	其他		：无
* 作者    ：@断忆

*/
void array_u3printf(const unsigned short int *sourceArray)
{
	u3_printf("%d %d %d %d %d %d %d %d %d %d %d %d\r\n",
						sourceArray[0],sourceArray[1],sourceArray[2],sourceArray[3],sourceArray[4],sourceArray[5],
						sourceArray[6],sourceArray[7],sourceArray[8],sourceArray[9],sourceArray[10],sourceArray[11]);
}

/*

* 函数介绍：计算数字量中1个数
* 输入参数：digital（待计算的数字量）
* 输出参数：无
* 返回值  ：1的个数
* 作者    ：@断忆

*/
u8 calculateNum(u16 digital)
{
	u8 i;
	u8 temp=0;
	for(i=0;i<NUM_OF_SENSOR;i++)
	{
		if(digital & (1<<i) )
			temp++;
	}
	return temp;
}


///*

//* 函数介绍：通过串口3将传感器数字量打印出来
//* 输入参数：（value）数字量
//* 输出参数：无
//* 返回值  ：无
//*	其他		：无
//* 作者    ：@断忆(value&0x40)>>6

//*/
//void sensorBit_u3printf(const unsigned short int value)
//{
//	unsigned short int temp = 0x0800;
//	u3_printf("Digital:%d%d%d%d %d%d%d%d %d%d%d%d %x %d\r\n",(value&temp)>>11,(value&(temp>>1))>>10,(value&(temp>>2))>>9,(value&(temp>>3))>>8,(value&(temp>>4))>>7,
//	(value&(temp>>5))>>6,(value&(temp>>6))>>5,(value&(temp>>7))>>4,(value&(temp>>8))>>3,(value&(temp>>9))>>2,(value&(temp>>10))>>1,value&1,value,calculateNum(value));

//}	

///*

//* 函数介绍：通过串口3将控制台信息打印出来
//* 输入参数：controlp（控制台地址）
//* 输出参数：无
//* 返回值  ：无
//*	其他		：无
//* 作者    ：@断忆

//*/
//void controlCenter_u3printf(const u8 *runMethod ,const controlCenterTypeDef *controlp)
//{
//	static char i=0;
//	u3_printf("LD:%d-%d\ncurNode:%d  nextNode:%d  nnNode:%d \n updataState:%s\n findLineWays:%s\n typeRoadblock:%s\n seekways:%s\n parkways:%s\n rotateAngle:%s\n",
//	*(runMethod+i),
//	*(runMethod+i+1),
//	controlp->curNode,controlp->nextNode,controlp->nnNode,
//	updataStatep[controlp->update],
//	findLinep[controlp->linkInform.findLineWays],
//	typeRoadblockp[controlp->linkInform.typeRoadblock],
//	seekNodeWayp[controlp->linkInform.seekways],
//	carParkp[controlp->linkInform.parkways],
//	carRotAnglep[controlp->linkInform.rotateAngle]
//	);
//	i++;
//	
//}	

///*

//* 函数介绍：通过串口3将运行状态打印出来
//* 输入参数：runState（运行状态记录器状态）
//* 输出参数：无
//* 返回值  ：无
//*	其他		：无
//* 作者    ：@断忆

//*/
//void runState_u3printf(runStateTypeDef *runState)
//{
//	u3_printf("findLine:%s\n fB:%s\n seekNode:%s\n carpark:%s\n rotangle:%s\n",
//	updataStatep[runState->F_LineState],
//	updataStatep[runState->F_RoadBlockState],
//	updataStatep[runState->seekNodeState],
//	updataStatep[runState->carParkState],
//	updataStatep[runState->RotangleState]
//	);
//}	





