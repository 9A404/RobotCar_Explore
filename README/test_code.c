/*************本文件的代码均为测试用图*****************/

/*2017-7-10*/
/*测试舵机用图：
				sgAngleControl(HEAD,L_90);
				delay_ms(500);
				sgAngleControl(HEAD,R_90);
				delay_ms(500);
*/

/*

if(sampingStatus() == 1)
			{
				//array_u3printf(glsensor_ad_value);//串口3输出模拟量
				//arrayPrintf(glsensor_ad_value,12); //串口1输出模拟量
				glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  //将模拟量转化成数字量
				//u3_printf("%d\r\n",sensorDigitalRank(glsensor_dig_value));
				u3_printf("%d \r\n",glsensor_dig_value);//串口3输出数字量
				//sensorBit_u3printf(glsensor_dig_value);//串口3按位输出数字量
				
				//sensorBitPrintf(glsensor_dig_value);	//串口1按位输出数字量																										//将数字量按位输出

				//dSpeed=incrementalPIDcalc(&sensorPID,sensorDigitalRank(glsensor_dig_value));//增量式PID输出
				dSpeed=positionPIDCalc(&sensorPID,sensorDigitalRank(glsensor_dig_value));   //位置式PID输出
				//printf("dSpedd:%d \r\n ",dSpeed);
				//printf("%f  ",sensorPID.setVaule);
				//printf("%f  ",sensorPID.kp);
				 //incrementalSpeedOut(&motorSpeed,dSpeed);	//在当前的速度上叠加速度
				 positionSpeedOut(motorSpeed.leftSpeed,motorSpeed.rightSpeed,dSpeed);
				 //u3_printf(" %d ds:%d left:%d right:%d \r\n",sensorDigitalRank(glsensor_dig_value),dSpeed,motorSpeed.leftSpeed,motorSpeed.rightSpeed);
				//u3_printf("ds:%d\r\n",dSpeed);
				//printf("left:%d \r\n",motorSpeed.leftSpeed);
				//printf("right:%d \r\n",motorSpeed.rightSpeed);
				
				//printf("digital:%d ",glsensor_dig_value );
				//printf("\r\n");
			}
*/








