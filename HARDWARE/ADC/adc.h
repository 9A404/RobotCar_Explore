#ifndef _ADC_H
#define _ADC_H

#include "sys.h"

/*分级记录表*/
typedef	struct{

	u16 digitalValue;    //数字量
	int	proportion  ;    //数字量对应的份额
}rankTypeDef;

	
void ADC_DMA_Init(void);
void ADC_ConvertOnce(void);
unsigned char sampingStatus(void);
unsigned short int sensorAD(u16 *sourceAnalog,const u16 *thresholdAnalog );
int sensorDigitalRank(u16 digitalValue);
int sensorDigitalRank_Brige(u16 digitalValue);
int sensorDigitalRank_Brige_Up(u16 digitalValue);
int sensorDigitalRank_Brige_Down(u16 digitalValue);
int rotangle_run(float angle);
int sensorDigitalRank_Peak(u16 digitalValue);

int sensorDigitalRank_HR90(u16 digitalValue);

//void tableExchang(rankTypeDef *rankInformationp,const rankTypeDef *refp);
//void rankInformationInit(void);


#endif
