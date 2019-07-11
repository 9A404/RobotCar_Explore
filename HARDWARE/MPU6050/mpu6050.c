#include "myconfig.h"
#include "mpu6050.h"
#include "myiic.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
//#include "usart.h"
#include "math.h"

static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};
float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
unsigned long sensor_timestamp;
short gyro[3], accel[3], sensors;
unsigned char more;
long quat[4];
float a[3],w[3],angle[3],T;
unsigned char Temp[11];   
u8 count = 24;
							
     
void PrintChar()
{

}  
                                  
void MPU6050_Init(void)
{
	int result=0;
	IIC_Init();
	result=mpu_init();
	if(!result)
	{	 		 
		//PrintChar("mpu initialization complete......\n ");		//mpu initialization complete	 	  

		  mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
//		if(!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))		//mpu_set_sensor
//			PrintChar("mpu_set_sensor complete ......\n");
//		else
//			PrintChar("mpu_set_sensor come across error ......\n");
			mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
//		if(!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))	//mpu_configure_fifo
//			PrintChar("mpu_configure_fifo complete ......\n");
//		else
//			PrintChar("mpu_configure_fifo come across error ......\n");
			mpu_set_sample_rate(DEFAULT_MPU_HZ);
//		if(!mpu_set_sample_rate(DEFAULT_MPU_HZ))	   	  		//mpu_set_sample_rate
//		 PrintChar("mpu_set_sample_rate complete ......\n");
//		else
//		 	PrintChar("mpu_set_sample_rate error ......\n");
			dmp_load_motion_driver_firmware();
//		if(!dmp_load_motion_driver_firmware())   	  			//dmp_load_motion_driver_firmvare
//			PrintChar("dmp_load_motion_driver_firmware complete ......\n");
//		else
//			PrintChar("dmp_load_motion_driver_firmware come across error ......\n");
			dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation));
//		if(!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation))) 	  //dmp_set_orientation
//		 	PrintChar("dmp_set_orientation complete ......\n");
//		else
//		 	PrintChar("dmp_set_orientation come across error ......\n");
			dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
												 DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
												 DMP_FEATURE_GYRO_CAL);
//		if(!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
//		    DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
//		    DMP_FEATURE_GYRO_CAL))		   	 					 //dmp_enable_feature
//		 	PrintChar("dmp_enable_feature complete ......\n");
//		else
//		 	PrintChar("dmp_enable_feature come across error ......\n");
			 dmp_set_fifo_rate(DEFAULT_MPU_HZ);
//		if(!dmp_set_fifo_rate(DEFAULT_MPU_HZ))   	 			 //dmp_set_fifo_rate
//		 	PrintChar("dmp_set_fifo_rate complete ......\n");
//		else
//		 	PrintChar("dmp_set_fifo_rate come across error ......\n");

			run_self_test();		//自检
			mpu_set_dmp_state(1);
//		if(!mpu_set_dmp_state(1))
//		 	PrintChar("mpu_set_dmp_state complete ......\n");
//		else
//		 	PrintChar("mpu_set_dmp_state come across error ......\n");
	}
}

/*

* 函数介绍：mpu6050串口版
* 输入参数：无
* 输出参数：无	
* 返回值  ：三个角度值
* 作者    ：@位胜

*/

void MPU6050_Pose_usart(void)
{
	
		u8 i=0;	
		u8 temp;
	    delay_ms(13);
	    USART_DMA_Enable(DMA1_Channel5);
	    delay_ms(14);
		
//		  for(j=0;j<66;j++)
//		   printf("%c",readBuff[j]);
         while(USART1_RX_BUF[i]!=0x55||USART1_RX_BUF[i+1]!=0x51)
		 {
		       i++;
		 }
		 temp  =  i;
		 i = 0;
                  angle[0] = ((short)(USART1_RX_BUF[temp+25]<<8| USART1_RX_BUF[temp+24]))/32768.0*180;   //X轴滚转角（x 轴）
                  angle[1] = ((short)(USART1_RX_BUF[temp+27]<<8| USART1_RX_BUF[temp+26]))/32768.0*180;   //Y轴俯仰角（y 轴）
                  angle[2] = ((short)(USART1_RX_BUF[temp+29]<<8| USART1_RX_BUF[temp+28]))/32768.0*180;   //Z轴偏航角（z 轴）  
           
		glPitch=angle[0];
		glRoll=angle[1];
		glYaw=angle[2];
		memset(USART1_RX_BUF,0,66);
		USART_DMA_Enable(DMA1_Channel5);
			//	printf("X角度：%.2f  Y角度：%.2f  Z角度：%.2f  X速度：%.2f  Y速度：%.2f  Z速度：%.2f\r\n",angle[0],angle[1],angle[2],w[0],w[1],w[2]);
 }

 
/*

* 函数介绍：mpu6050i2c版
* 输入参数：无
* 输出参数：无	
* 返回值  ：三个角度值
* 作者    ：

*/
 
void MPU6050_Pose(void)
{
	dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more);	 
	/* Gyro and accel data are written to the FIFO by the DMP in chip frame and hardware units.
	 * This behavior is convenient because it keeps the gyro and accel outputs of dmp_read_fifo and mpu_read_fifo consistent.
	**/
	/*if (sensors & INV_XYZ_GYRO )
	send_packet(PACKET_TYPE_GYRO, gyro);
	if (sensors & INV_XYZ_ACCEL)
	send_packet(PACKET_TYPE_ACCEL, accel); */
	/* Unlike gyro and accel, quaternions are written to the FIFO in the body frame, q30.
	 * The orientation is set by the scalar passed to dmp_set_orientation during initialization. 
	**/
	if(sensors & INV_WXYZ_QUAT )
	{
		q0 = quat[0] / q30;	
		q1 = quat[1] / q30;
		q2 = quat[2] / q30;
		q3 = quat[3] / q30;

		glPitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3;	// pitch
		glRoll  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3;	// roll
		glYaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	//yaw
		
	}
}
