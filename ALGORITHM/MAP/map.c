#include "control.h"
#include "myconfig.h"

/*通过一个表示出地图  巡线方法 路障类型  加速方法  加速时间 找节点方法 停车方法 车头旋转角度*/

const map_linkInforTypeDef mapInformation[][NODEFORKNUM]={
/*节点*/	{	{0,0,},			},//没有用到	

/*1节点*/	{	{2,1,FL_brige,FREE,NOSPEED,0,SEEK_default,PARK_default,HN_Rotate},{2,3,FL_default,PLATFORM_1,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},	\
						{2,5,FL_default,PLATFORM_1,NOSPEED,0,SEEK_default,NOTPARK,rot_LFL},	
					},	

/*2节点*/	{	{1,2,FL_slow,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_default,HL_180_F},{3,4,FL_slow,BRIGE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},	\
						{5,9,FL_default,S_BOARD_1,NOSPEED,0,SEEK_default,PARK_pesL,HL_120},{5,6,FL_default,S_BOARD_1,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},	
					},		

/*3节点*/	{	{2,1,FL_brige,FREE,NOSPEED,0,SEEK_default,PARK_default,HN_Rotate},{4,3,FL_default,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HL_180_F},	\
						{5,9,FL_slow,SLOPE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},{5,6,FL_slow,SLOPE,NOSPEED,0,SEEK_default,PARK_pesR_200,HR_135},	
					},		
	
/*4节点*/	{	{3,5,FL_default,PLATFORM,NOSPEED,0,SEEK_default,NOTPARK,rot_RFL},	
					},

/*5节点*/	{	{2,1,FL_slow,S_BOARD_1,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate},{6,7,FL_default,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},	\
						{6,8,FL_default,FREE,NOSPEED,0,SEEK_default,NOTPARK,rot_RFL},{9,10,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},	\
						{6,42,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL_45,HL_90},{6,14,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL_200,HL_90},
					},      

/*6节点*/	{	{7,6,FL_default,FREE,COMMON_SPEED,50,SEEK_PesPlatform,PARK_PesPlatform,HL_180_F},{8,6,FL_default,FREE,COMMON_SPEED,60,SEEK_Collision,NOTPARK,HL_180_F},	\
						{14,15,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_90},{5,2,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,rot_LFL},	\
						{7,12,FL_default,FREE,COMMON_SPEED,50,SEEK_PesPlatform,PARK_PesPlatform,HL_180_F},{14,16,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},\
						{42,14,FL_slow,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},{14,35,FL_default,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},	\
						{14,17,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},
					},                 

						
/*7节点*/	{	{12,11,FL_default,PLATFORM,COMMON_SPEED,320,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},{6,14,FL_default,PLATFORM,NOSPEED,0,SEEK_default,PARK_pesR,HR_90},	\
						{12,10,FL_slow,PLATFORM,COMMON_SPEED,320,SEEK_PesPlatform,PARK_PesPlatform,HL_180_F},{6,42,FL_default,PLATFORM,NOSPEED,0,SEEK4,PARK_pesR,HR_90},\
					},
	
/*8节点*/ {	{6,7,FL_slow,FREE,COMMON_SPEED,80,SEEK_default,PARK_pesR_250,HR_145},
					},

/*9节点*/	{	{10,12,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},{10,11,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,rot_LFL},	\
						{5,6,FL_default,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},{39,15,FL_slow,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},	\
						{5,2,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesR_200,HR_135_F},{39,9,FL_slow,FREE,NOSPEED,0,SEEK_Collision,PARK_Door,HL_180}, \
						{40,13,FL_slow,FREE,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},{40,9,FL_slow,FREE,NOSPEED,0,SEEK_Collision,PARK_Door,HL_180},	\
						{13,14,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},{15,30,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},	\
						{39,30,FL_slow,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},{6,41,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_135},	\
						{30,31,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HR_90},
					},

/*10节点*/{	{12,10,FL_default,PLATFORM,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HL_180_F},{9,5,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},	\
						{9,40,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_45},{9,39,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},	\
						{9,15,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},{9,13,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_45},	\
						{11,10,FL_default,FREE,COMMON_SPEED,50,SEEK_Collision,NOTPARK,HL_180_F},{9,30,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},	\
						
					},         

/*11节点*/{	{10,9,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HR_35},{10,12,FL_slow,FREE,NOSPEED,0,SEEK_default,PARK_pesL_250,HL_120},	\
						
					},

/*12节点*/{	{10,9,FL_default,PLATFORM,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},{10,11,FL_default,PLATFORM,NOSPEED,0,SEEK_default,PARK_pesL,HR_145},	\
						
					},

/*13节点*/{	{14,35,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL_45,HL_45},{9,5,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_135}, \
						{14,17,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL_45,HR_45},{40,9,FL_default,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},	\
					},

/*14节点*/{	{15,9,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_90},{37,36,FL_default,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HL_180},	\
						{16,17,FL_quick,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},{44,16,FL_default,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},	\
						{35,36,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},{42,6,FL_default,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},	\
						{44,43,FL_middle,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},{6,5,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HR_90},	\
						{34,30,FL_default,FREE,NOSPEED,0,SEEK_DIGL,PARK_pesL_No,HL_90},{17,18,FL_default,FREE,COMMON_SPEED,80,SEEK_DIGL,PARK_pesL_No,HL_90},	
						
					},	

/*15节点*/{	{9,5,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_90},{39,9,FL_default,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},	\
						{31,32,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},	
					},

/*16节点*/{	{17,18,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},{44,45,FL_default,FREE,NOSPEED,0,SEEK_SeeSaw,NOTPARK,HN_Rotate},	\
						
					},
	
/*17节点*/{	{18,20,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},{18,19,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90}, \
            {14,34,FL_default,FREE,COMMON_SPEED,80,SEEK_DIGR,PARK_pesR,HR_90},{43,44,FL_default,FREE,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate}, \
						{43,16,FL_slow,ANGLE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
					},

/*18节点*/{	{20,21,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},{19,18,FL_slow,FREE,NOSPEED,0,SEEK_Collision,NOTPARK,HN_Rotate},	\
            {17,43,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},{17,14,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},	\
						{17,37,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},
					},

/*19节点*/{	{18,17,BACK_NFL,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HL_90},
					},

/*20节点*/{	{21,22,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},{18,17,},	\
					},

/*21节点*/{	{22,23,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesR,HR_145},
					},

/*22节点*/{	{23,24,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesR,HR_135},{21,20,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},
					},

/*23节点*/{	{24,23,FL_default,Peak,NOSPEED,0,NOTSEEK,PARK_PesPlatform,HL_180_F},{25,26,FL_slow,ALL_TILT,NOSPEED,0,SEEK4,PARK_pesR,HR_90},\
						{22,21,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_145},
					},
	
/*24节点*/{	{23,25,FL_default,DOWNPLATFORM,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},{23,22,FL_downPeak,DOWNPLATFORM,NOSPEED,0,SEEK_default,PARK_pesL,HL_135},
						
					},

/*25节点*/{	{26,27,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},{28,50,FL_slow,SLOPE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},	\

					},

/*26节点*/{	{27,26,FL_default,S_BOARD_26_27,NOSPEED,0,NOTSEEK,PARK_PesPlatform,HR_180_F},{25,28,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},
					},

/*27节点*/{	{26,25,FL_default,DOWN27_26,NOSPEED,0,SEEK4,PARK_pesR,HR_90},		\
					
					},

/*28节点*/{	{25,26,FL_slow,SLOPE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},	{50,49,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_35},  \
           },

/*29节点*/{	{36,37,},	},

/*30节点*/{	{34,35,FL_slow,S_BOARD_DOUBLE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},{50,28,FL_slow,SLOPE,NOSPEED,0,SEEK_DIGR,PARK_pesR_No,HR_90},	\
					},

/*31节点*/{	{32,31,FL_slow,FREE,NOSPEED,0,SEEK_Collision,NOTPARK,HN_Rotate},{30,34,FL_slow,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HR_90},	\
						
					},

/*32节点*/{	{31,30,BACK_NFL,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HL_90},
					},

/*33节点*/{	{33,33,},
					},

/*34节点*/{	{35,36,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},{30,50,FL_slow,S_BOARD_DOUBLE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},	\
					},

/*35节点*/{	{36,35,FL_slow,FREE,NOSPEED,0,SEEK_Collision,NOTPARK,HN_Rotate},{14,37,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesL,HR_90},	\
						{14,42,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},{14,17,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_90},	\
						{14,16,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},{14,44,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_90},	\
						{14,6,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},	
					},

/*36节点*/{	{35,14,BACK_NFL,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HR_90},{35,34,BACK_NFL,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HL_90},	\
						
					},

						
/*37节点*/{	{15,9,FL_quickest,Platform_37_15,NOSPEED,0,SEEK4,PARK_pesL,HR_90},{49,15,FL_default,PLATFORM,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},	\
					},

/*38节点*/{	{33,23,}
					},

/*39节点*/	{ {15,31,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate}, {9,5,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_90}, \
							{9,40,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_145},
						},

/*40节点*/  {	{13,14,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},{9,6,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_135},	\
							{9,5,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_135},
						},

/*41节点*/  { {13,15,},
						},

/*42节点*/  {	{14,35,FL_default,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},{14,37,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_90},	\
							{6,5,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HR_90},{14,44,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},	\
						},

/*43节点*/  {	{44,14,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},{16,44,FL_slow,FREE,NOSPEED,0,NOTSEEK,NOTPARK,rot_LFL},	\
							{17,18,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},{44,37,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},	\
						  {37,36,FL_slow,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HL_180},
						},

/*44节点*/  {	{14,38,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},{45,46,FL_slow,SEESAW,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},	\
							{37,36,FL_quickest,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HL_180},{43,17,FL_node,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},	\
						},

/*45节点*/  {	{46,47,FL_circular,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},
						},

/*46节点*/  {	{47,46,FL_default,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HR_180_F},	{43,16,FL_circular,BRIGE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},	\
							{43,44,FL_circular,BRIGE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},{43,37,FL_circular,BRIGE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},
						},

/*47节点*/  {	{46,43,FL_slow,PLATFORM,NOSPEED,0,SEEK_default,PARK_pesL,HL_105},
						},

/*48节点*/  {	{46,43,FL_slow,PLATFORM,NOSPEED,0,SEEK_default,PARK_pesL,HL_105},
						},

/*49节点*/  {	{37,49,FL_default,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HL_180_F},{15,9,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HR_90},
						},

/*50节点*/  {	{28,25,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},{49,37,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_120},
						},




};

