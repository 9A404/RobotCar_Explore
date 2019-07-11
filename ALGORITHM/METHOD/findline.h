#ifndef _FINDLINE_H_
#define _FINDLINE_H_
#include "sys.h"
#include "myconfig.h"

void flMethod_default(void);    //默认巡线方法   3300
void flMethod_middle(void);    //中速巡线方法    4500
void flMethod_brige(void);			//过桥巡线
void flMethod_brige_up(void);   //上桥斜坡时的巡线方法
void flMethod_brige_down(void); //上桥斜坡时的巡线方法
void flMethod_slow(void);				//慢速巡线
void flMethod_slowest(void);				//慢速巡线
void flMethod_UpPlatform(void);//上平台巡线
void flMethod_DownPlatform(void);//下平台巡线
void flMethod_quick(void);      //快速巡线        5500
void flMethod_stop(void);				//停车巡线
void flMethod_quickest(void);   //超快速巡线       6800
void flMethod_upPeak(void);     //上珠峰巡线
void flMethod_downPeak(void);   //下珠峰巡线
void flMethod_left(void);       //偏左巡线
void flMethod_right(void);      //偏右巡线
void flMethod_node(void);      //圆边巡线方法
void flMethod_43_44(void);      //圆边巡线方法
void flMethod_16_44(void);      //圆边巡线方法
void flMethod_circular(void);      //圆边巡线方法
void flMethod_NFL(void);        //循角度方法
void flMethod_NFL_slow(void);        //循角度方法
#endif




