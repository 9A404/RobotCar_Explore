函数书写版式：
/*

* 函数介绍：
* 输入参数：
* 输出参数：
* 返回值  ：
* 作者    ：@断忆

*/

函数书写：函数传参数尽量在函数入口进行传入，杜绝直接在函数内部使用全局变量（保证函数的独立性）

全局变量：
储存传感器的值（模拟量）：glsensor_ad_value[NUM_OF_SENSOR];
储存传感器的值（数字量）：glsensor_dig_value

1、TIM4已经作为PWM生成
2、ADC与DMA实现说明：
ADC:独立模式：指ADC1和ADC2独立工作。
扫描：指从设置的通道依次采集数据一次，比如：开通了CH1 CH2 CH9，那么从1到2到9，就完成了扫  描。
连续：第一轮扫描结束后，会从头扫，进行第二次扫描，第三次。。。。。。直到该期间 CONT 被清零或者ADC结束采集数据。 
每次每个通道采样结束都会产生：EOC( END OF CONVENSION)，通知（过程复杂）DMA进行数据搬运。
所以查询EOC是可以的！不需要控制DMA，你也可以查询DMA的标志位：比如传输完成标志。就能使用数据了

3、使用TIM2定传感器的采样时间进行控制，设计系统的采样时间为20ms

4、 PWM.c中的void incrementalSpeedOut(motorSpeedTypeDef *p,int dSpeed)函数要与pid.c中的float incrementalPIDcalc(PIDTypeDef *p,float nextVaule)的函数配套使用
	PWM.c中的void positionSpeedOut(int leftSpeed,int rightSpeed,int dSpeed)函数要与pid.c中的float positionPIDcalc(PIDTypeDef *p,float nextVaule)的函数配套使用

5、mpu6050有三种获取欧拉角（姿态解算）方法：
	①四元素（利用mpu6050的DMP得到）然后利用公式获得pitch（俯仰角）roll（滚转角）yaw（偏航角）
	②卡尔曼滤波
	③一阶互补滤波
	

6、AD转化口对应引脚：
	AD0：PA0
	AD1：PA1
	AD2：PA2
	AD3：PA3
	AD4：PA4
	AD5：PA5
	AD6：PA6
	AD7：PA7
	AD8：PB0
	AD9：PB1
	AD10：PC0
	AD11：PC1
	AD12：PC2
	AD13：PC3
	AD14：PC4
	AD15：PC5

7、串口3：
	TX：PB10
	RX：PB11

8、串口1：
	TX：PA9
	RX：PA10

9、系统中断优先级分组抢占2：响应2		

10、左轮： PB8 PB9  右轮：PB6 PB7

11、用定时器5控制mpu6050采样时间 采样时间10ms




12、const char *p" (也可以写成 ``char const *p") 声明了一个指向字符常量的指针, 因此不能改变它所指向的字符; ``char * const p" 声明一个指向 (可变)  字符的指针常量, 就是说, 你不能修改指针。

13、KEY0--PD0、KEY1--PC12、KEY2--PC13、KEY3--PC11、KEY4--PC10  

14、光电传感器-->检测到为低电平

15、光电传感器：黑线（信号线）蓝色（GND）棕色（vcc）

左边：PC2 右边：PC3 前面：PE7 前下：PC4


16、
	Image2LCD取模选项设置
	水平扫描
	16位
	不包含图像头数据
	自左至右
	自顶至底
	低位在前


17、	/*软件复位，只需要调用这两句话就能实现*/
		__set_FAULTMASK(1);  // 关闭所有中端
		NVIC_SystemReset();  // 复位


18、TIME_2用在26到27节点

/*
始动电压：900-900
1000--1040
2000--2080
2500--2640
2800--2920
3000--3180
3500--3740
4000--4250





*/
*****************
巡线 PD结合有奇效*
*****************


while（1）	
{
	(控制台)->巡线->判断路障->找点->停车->转弯->(等待控制台信号)
}

程序思路：
一个控制台（）、一个运行状态（）五个任务（）

每个路段执行的任务：巡线--路障处理--找点--停车--转弯

任务的执行根据运行状态依次运行，当所有任务完成后将更新控制台的数据以及重置运行状态






盲走基本直线：
			speedAdjustment(2090,2000);
			speedAdjustment(1365,1300);
			speedAdjustment(-1300,-1315);
			
			
			
