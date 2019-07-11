#ifndef __PHOTOELECTRIC_H_
#define __PHOTOELECTRIC_H_


#define PES_L  				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)
#define PES_R  				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)
#define PES_H  				GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)
#define PES_Platform  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)

void pesInit(void);


#endif














