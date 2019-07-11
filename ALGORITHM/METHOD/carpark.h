#ifndef _CARPARK_H_
#define _CARPARK_H_
#include "sys.h"
#include "myconfig.h"

u8 parkMethod_default(void);
u8 parkMethod_pesR(void);
u8 parkMethod_stop(void);
u8 parkMethod_pesR_Delay(int time);
u8 parkMethod_pesL(void);
u8 parkMethod_pesL_Delay(int time);
u8 parkMethod_pesPlatform(void);
u8 parkMethod_Door(void);
u8 parkMethod_pesR_45(void);
u8 parkMethod_pesL_45(void);
u8 parkMethod_pesR_noline(void);
u8 parkMethod_pesL_noline(void);
u8 parkMethod_36_24(void);
u8 parkMethod_9_5(void);
u8 parkMethod_3_5(void);
u8 parkMethod_11_10(void);
u8 parkMethod_10_24(void);
u8 parkMethod_pesR_back(void);
u8 parkMethod_pesL_back(void);

#endif





