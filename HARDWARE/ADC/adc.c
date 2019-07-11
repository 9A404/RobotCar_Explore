#include "adc.h"
#include "myconfig.h"
#include "string.h"


/*

* 函数介绍：adc用到的GPIO初始化成模拟输入模式
* 输入参数：无
* 输出参数：无
* 返回值  ：无

*/
static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE );	//PA、PB、PC时钟使能
	/*配置PA*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	/*配置PB*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	/*配置PC*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1  | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}

/*

* 函数介绍：配置adc1控制器的通道规则
* 输入参数：无
* 输出参数：无
* 返回值  ：无

*/
static void ADC_Multichannel_Config(void)
{
	ADC_InitTypeDef   ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 	//使能ADC1时钟
	
	/*配置ADC分频系数&复位*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//设置ADC分频因子6 ；72M/6=12,ADC最大时间不能超过14M
	ADC_DeInit(ADC1);  								//复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;										//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;													//模数转换工作在扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;										//模数转换不工作在连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;								//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = NUM_OF_SENSOR;										//顺序进行规则转换的ADC通道的数目
	
	ADC_Init(ADC1, &ADC_InitStructure);																		//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

	/*s设置制定ADC规则通道，设置它们的转化顺序和采样时间*/
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0  , 1 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1  , 2 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2  , 3 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3  , 4 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4  , 5 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5  , 6 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6  , 7 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7  , 8 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8  , 9 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_9  ,10 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10 ,11 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11 ,12 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12 ,13 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13 ,14 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14 ,15 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_15 ,16 , ADC_SampleTime_239Cycles5);
	
	/*开启ADC的DMA支持*/
	ADC_DMACmd(ADC1,ENABLE);
	
	/*ADC使能&校准*/
	ADC_Cmd(ADC1, ENABLE);											//使能指定的ADC1
	ADC_ResetCalibration(ADC1);									//使能复位校准  
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	ADC_StartCalibration(ADC1);	 								//开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	 	//等待校准结束
}

/*

* 函数介绍：初始化DMA1的通道1
* 输入参数：无
* 输出参数：无
* 返回值  ：无

*/
static void ADC_DMA_Config(void)
{
	DMA_InitTypeDef   DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);			//DMA1时钟使能

	/*配置DMA通道*/  
    DMA_DeInit(DMA1_Channel1);																					//将DMA的通道1寄存器重设为缺省值    
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;	//外设地址     
    DMA_InitStructure.DMA_MemoryBaseAddr =(u32)glsensor_ad_value;  		//DMA内存基地址  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  							//dma传输方向  
    DMA_InitStructure.DMA_BufferSize = NUM_OF_SENSOR;  								//DMA通道的DMA缓存的大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//设置DMA的内存递增模式   
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据字长   
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //内存数据字长   
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  									//工作在循环缓存模式   
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;								//设置DMA的优先级别     
    DMA_InitStructure.DMA_Mode = DMA_M2M_Disable;      								//非内存到内存传输
		
		DMA_Init(DMA1_Channel1,&DMA_InitStructure);                      //根据DMA_InitStructure中指定的参数初始化通道

}

/*

* 函数介绍：启动DMA通道1
* 输入参数：无
* 输出参数：无
* 返回值  ：无

*/
static void DMA_Start()
{
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

/*

* 函数介绍：adc的dma初始化
* 输入参数：无
* 输出参数：无
* 返回值  ：无

*/
void ADC_DMA_Init(void)
{
	ADC_GPIO_Config();
	ADC_Multichannel_Config();
	ADC_DMA_Config();
	DMA_Start();
}

/*

* 函数介绍：进行一次adc转化
* 输入参数：无
* 输出参数：无
* 返回值  ：无

*/
void ADC_ConvertOnce(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);												//关闭DMA
	DMA_SetCurrDataCounter(DMA1_Channel1,NUM_OF_SENSOR );//设置DMA通道以及缓存大小
	DMA_Cmd(DMA1_Channel1,ENABLE);											//打开DMA
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

/*

* 函数介绍：检测采样是否完成
* 输入参数：无
* 输出参数：无
* 返回值  ：1（完成），0（没有）

*/
unsigned char sampingStatus(void)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC1)!=RESET) //查看DMA1通道1是否完成传输
	{
		DMA_ClearFlag(DMA1_FLAG_TC1|DMA1_FLAG_HT1|DMA1_FLAG_GL1);             //清除DMA1通道1完成标志
		return 1;
	}
	
	return 0;
}

/*

* 函数介绍：传感器模拟量转化为数字量
* 输入参数：sourceAnalog(需要转化成数字量的模拟值)，thresholdAnalog（模拟量阈值）
* 输出参数：无
* 返回值  ：12个传感器对应的数字量
* 其他    ：返回的数字量格式为右对齐，高字节的高四位没用上 0000 1010 1010 1010   
*/
u16 sensorAD(u16 *sourceAnalog,const u16 *thresholdAnalog )
{
	int i=0;
	u16 temp=0;
	for(i=0;i<NUM_OF_SENSOR;i++)
	{
		temp=temp<<1;
		
		if(sourceAnalog[i] > thresholdAnalog[i])
			temp|=0x0001;
		else
			temp&=(~0x01);
	}

	return temp;

}

/*
* 函数介绍:卡角度跑法，角度分级
* 输入参数：当前角度
* 输出参数：
* 返回值  ：根据规则计算后的等级
* 其他  ：根据角度来调整
*/
int rotangle_run(float angle)
{
	int temp=18;
	static int save=18;//保存当前值，以便下次使用
  static float angle_temp[19]={-12.6,-11.2,-9.8,-8.4,-7.0,-5.6,-4.2,-2.8,-1.4,0,1.4,2.8,4.2,5.6,7.0,8.4,9.8,11.2,12.6};

	if(angle_temp[0]>=angle ) temp = 38;
	else if(  angle_temp[0] < angle && angle<=angle_temp[1])temp=36;
	else if(  angle_temp[1] <angle && angle<=angle_temp[2])temp=34;
	else if(  angle_temp[2] <angle && angle<=angle_temp[3])temp=32;
	else if(  angle_temp[3] <angle && angle<=angle_temp[4])temp=30;
	else if(  angle_temp[4] <angle && angle<=angle_temp[5])temp=28;
	else if(  angle_temp[5] <angle && angle<=angle_temp[6])temp=26;
	else if(  angle_temp[6] <angle && angle<=angle_temp[7])temp=24;
	else if(  angle_temp[7] <angle && angle<=angle_temp[8])temp=22;
	else if(  angle_temp[8] <angle && angle<=angle_temp[9])temp=20;
	else if(  angle_temp[9] <angle && angle <=angle_temp[10])temp=18;
	else if(  angle_temp[10]<angle&& angle <=angle_temp[11])temp=16;
	else if(  angle_temp[11] <angle&& angle<=angle_temp[12])temp=14;
	else if(  angle_temp[12] <angle&& angle<=angle_temp[13])temp=12;
	else if(  angle_temp[13] <angle&& angle<=angle_temp[14])temp=10;
	else if(  angle_temp[14] <angle&& angle <=angle_temp[15])temp=8;
	else if(  angle_temp[15] <angle&& angle <=angle_temp[16])temp=6;
	else if(  angle_temp[16] <angle&& angle<=angle_temp[17])temp=4;
	else if(  angle_temp[17] <angle&& angle<=angle_temp[18])temp=2;
	else if( angle_temp[18]<angle)  temp=0;  
	save = temp;
	//u3_printf("%.2f %.2f %.2f \n",angle,angle_temp[0],angle_temp[17]);
	return temp;
}

/*

* 函数介绍：传感器数字量划分等级
* 输入参数：digitalValue（传感器的数字量）
* 输出参数：
* 返回值  ：根据规则计算后的等级
* 其他    ：根据传感器来调整数值   

*/
int sensorDigitalRank(u16 digitalValue)
{
	int temp;
	static int save=20;//保存当前值，以便下次使用
	switch(digitalValue)
	{
		case 0x800: temp=0;break;     // 1000 0000 0000
		case 0xC00: temp=2;break;			// 1100 0000 0000
		case 0xE00: temp=4;break;			// 1110 0000 0000
		case 0x600: temp=6;break;     // 0110 0000 0000
		case 0x700: temp=8;break;     // 0111 0000 0000
		case 0x300: temp=10;break;    // 0011 0000 0000
		case 0x380: temp=12;break;    // 0011 1000 0000
		case 0x180: temp=14;break;    // 0001 1000 0000
		case 0x1C0: temp=16;break;    // 0001 1100 0000
		case 0x0C0: temp=18;break;    // 0000 1100 0000 
		
		case 0x0E0: temp=19;break;    // 0000 1110 0000 中间
		case 0x060: temp=20;break;    // 0000 0110 0000 中间
		case 0x070: temp=21;break;    // 0000 0111 0000 中间
		
		case 0x030: temp=22;break;    // 0000 0011 0000 
		case 0x038: temp=24;break;    // 0000 0011 1000
		case 0x018: temp=26;break;    // 0000 0001 1000
		case 0x01C: temp=28;break;    // 0000 0001 1100
		case 0x00C: temp=30;break;    // 0000 0000 1100
		case 0x00E: temp=32;break;    // 0000 0000 1110
		case 0x006: temp=34;break;    // 0000 0000 0110
		case 0x007: temp=36;break;    // 0000 0000 0111
		case 0x003: temp=38;break;    // 0000 0000 0011
		case 0x001: temp=40;break;    // 0000 0000 0001
		default   : temp = save; break;//读到其他值的时候采用上次的值
	}
		save = temp;
	return temp;
}


/*

* 函数介绍：过桥传感器数字量划分等级
* 输入参数：digitalValue（传感器的数字量）
* 输出参数：
* 返回值  ：根据规则计算后的等级
* 其他    ：根据传感器来调整数值   

*/
int sensorDigitalRank_Brige(u16 digitalValue)
{
	int temp;
	static int save=14;//保存当前值，以便下次使用
	switch(digitalValue)
	{
		case 0xff:  temp=0;break;			// 000011111111
	  case 0x8ff: temp=1;break;			// 100011111111
		case 0x87f: temp=3;break;			// 100001111111
		case 0xc7f: temp=5;break;			// 110001111111
		
		case 0xc3f: temp=7;break;     // 110000111111
		case 0xe3f: temp=10;break;    // 111000111111
		case 0xe1f: temp=12;break;    // 111000011111
		case 0xf0f: temp=14;break;    // 111100001111	中间
		case 0xf87: temp=16;break;		// 111110000111
		case 0xfc7: temp=18;break;    // 111111000111
		case 0xfc3: temp=21;break;    // 111111000011
		
		case 0xfe3: temp=23;break;    // 111111100011
		case 0xfe1: temp=25;break;		// 111111100001
		case 0xff1: temp=27;break;		// 111111110001
		case 0xff0: temp=28;break;		// 111111110000
		default   : temp = save; break;//读到其他值的时候采用上次的值
	}
	
	save = temp;
	return temp;
}

/*

* 函数介绍：上桥传感器数字量划分等级
* 输入参数：digitalValue（传感器的数字量）
* 输出参数：
* 返回值  ：根据规则计算后的等级
* 其他    ：根据传感器来调整数值   

*/
int sensorDigitalRank_Brige_Up(u16 digitalValue)
{
	int temp;
	static int save=14;//保存当前值，以便下次使用
	switch(digitalValue)
	{
		case 0xff:  temp=0;break;			// 000011111111
	  case 0x8ff: temp=1;break;			// 100011111111
		case 0x87f: temp=3;break;			// 100001111111
		case 0xc7f: temp=5;break;			// 110001111111
		
		case 0xc3f: temp=7;break;     // 110000111111
		case 0xe3f: temp=10;break;    // 111000111111
		case 0xe1f: temp=12;break;    // 111000011111
		case 0xf0f: temp=14;break;    // 111100001111	中间
		case 0xf87: temp=16;break;		// 111110000111
		case 0xfc7: temp=18;break;    // 111111000111
		case 0xfc3: temp=21;break;    // 111111000011
		
		case 0xfe3: temp=23;break;    // 111111100011
		case 0xfe1: temp=25;break;		// 111111100001
		case 0xff1: temp=27;break;		// 111111110001
		case 0xff0: temp=28;break;		// 111111110000
		default   : temp = save; break;//读到其他值的时候采用上次的值
	}
	
	save = temp;
	return temp;
}

/*

* 函数介绍：下桥传感器数字量划分等级
* 输入参数：digitalValue（传感器的数字量）
* 输出参数：
* 返回值  ：根据规则计算后的等级
* 其他    ：根据传感器来调整数值   

*/
int sensorDigitalRank_Brige_Down(u16 digitalValue)
{
	int temp;
	static int save=14;//保存当前值，以便下次使用
	switch(digitalValue)
	{
		case 0xff:  temp=0;break;			// 000011111111
	  case 0x8ff: temp=1;break;			// 100011111111
		case 0x87f: temp=3;break;			// 100001111111
		case 0xc7f: temp=5;break;			// 110001111111
		
		case 0xc3f: temp=7;break;     // 110000111111
		case 0xe3f: temp=10;break;    // 111000111111
		case 0xe1f: temp=12;break;    // 111000011111
		case 0xf0f: temp=14;break;    // 111100001111	中间
		case 0xf87: temp=16;break;		// 111110000111
		case 0xfc7: temp=18;break;    // 111111000111
		case 0xfc3: temp=21;break;    // 111111000011
		
		case 0xfe3: temp=23;break;    // 111111100011
		case 0xfe1: temp=25;break;		// 111111100001
		case 0xff1: temp=27;break;		// 111111110001
		case 0xff0: temp=28;break;		// 111111110000
		default   : temp = save; break;//读到其他值的时候采用上次的值
	}
	
	save = temp;
	return temp;
}

/*

* 函数介绍：上珠峰传感器数字量划分等级
* 输入参数：digitalValue（传感器的数字量）
* 输出参数：
* 返回值  ：根据规则计算后的等级
* 其他    ：根据传感器来调整数值   

*/
int sensorDigitalRank_Peak(u16 digitalValue)
{
	int temp;
	static int save=16;//保存当前值，以便下次使用
	switch(digitalValue)
	{
		case 0xe00: temp=0;break;     // 111000000000
		case 0x600: temp=2;break;			// 011000000000
		case 0x700: temp=4;break;			// 011100000000
		case 0x300: temp=6;break;     // 001100000000
		
		case 0x380: temp=8;break;     // 001110000000
		case 0x180: temp=10;break;    // 000110000000
		case 0x1c0: temp=12;break;    // 000111000000
		case 0x0c0: temp=14;break;    // 000011000000
		
		case 0x0e0: temp=16;break;    // 000011100000
		case 0x060: temp=16;break;    // 000001100000	中间 
		case 0x070: temp=16;break;    // 000001110000
		
		case 0x030: temp=18;break;    // 000000110000
		case 0x038: temp=20;break;    // 000000111000
		case 0x018: temp=22;break;    // 000000011000
		case 0x01c: temp=24;break;    // 000000011100
		
		case 0x00c: temp=26;break;    // 000000001100
		case 0x00e: temp=28;break;    // 000000001110
		case 0x006: temp=30;break;    // 000000000110
		case 0x007: temp=32;break;    // 000000000111
		
		default   : temp = save; break;//读到其他值的时候采用上次的值
	}
		save = temp;
	return temp;
}

/*

* 函数介绍：右转90传感器数字量划分等级
* 输入参数：digitalValue（传感器的数字量）
* 输出参数：
* 返回值  ：根据规则计算后的等级
* 其他    ：根据传感器来调整数值   

*/
int sensorDigitalRank_HR90(u16 digitalValue)
{
	int temp;
	static int save=22;//保存当前值，以便下次使用
	switch(digitalValue)
	{
		case 0x800: temp=-6;break;     // 1000 0000 0000
		case 0xC00: temp=-4;break;			// 1100 0000 0000
		case 0xE00: temp=-2;break;			// 1110 0000 0000
		case 0x600: temp=0;break;     // 0110 0000 0000
		case 0x700: temp=2;break;     // 0111 0000 0000
		case 0x300: temp=4;break;    // 0011 0000 0000
		case 0x380: temp=6;break;    // 0011 1000 0000
		case 0x180: temp=8;break;    // 0001 1000 0000
		case 0x1C0: temp=10;break;    // 0001 1100 0000
		case 0x0C0: temp=12;break;    // 0000 1100 0000  
		case 0x0E0: temp=14;break;    // 0000 1110 0000 中间
		case 0x060: temp=22;break;    // 0000 0110 0000 中间
		case 0x030: temp=30;break;    // 0000 0011 0000
		case 0x038: temp=32;break;    // 0000 0011 1000
		case 0x018: temp=34;break;    // 0000 0001 1000
		case 0x01C: temp=36;break;    // 0000 0001 1100
		case 0x00C: temp=38;break;    // 0000 0000 1100
		case 0x00E: temp=40;break;    // 0000 0000 1110
		case 0x006: temp=42;break;    // 0000 0000 0110
		case 0x007: temp=44;break;    // 0000 0000 0111
		case 0x003: temp=46;break;    // 0000 0000 0011
		case 0x001: temp=48;break;    // 0000 0000 0001
	
		default   : temp = save; break;//读到其他值的时候采用上次的值
	}
	save = temp;
	return temp;
}

















