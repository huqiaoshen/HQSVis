/**
******************************************************************************
* @file
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2018/01/17
* @brief   事件驱动类型轮换执行OS系统
******************************************************************************
* @brief

*
*
*
*/
/* Includes ------------------------------------------------------------------*/

#ifndef _OSHQS_H_
#define _OSHQS_H_
#include "HQS_typedef.h"
#include "memPithyHQS.h"


#define taskHQSQty   2 //任务数量

typedef void (*TaskBackFunc)(void);
typedef void (*UseSleepBackFunc)(void *); //用户睡眠函数


typedef enum
{
	OSNotHQS_Event = 0x0000,  //无  事件
	OSMgsHQS_Event = 0x0001,  //消息事件
	OSTimHQS_Event = 0x0002,  //定时事件
}
OSHQSevent_m;



typedef struct _OSHQSTask_t
{
	uint32       cyc;             //循环周期  ；0 为消息事件驱动
	uint32       runtime;         //任务执行消耗时间
	uint32       sts;             //任务执行开始时间戳
	uint32       ets;             //任务执行结束时间戳
}OSHQSInfoTask_t;



void OsHQSInit(void);

//系统节拍调用
void OsHQSCycUp(void);

                        //id            任务函数               周期
void OsHQSTaskCreate(uint32 TaskID, TaskBackFunc taskFunc,  uint32 cyc);


void OsHQSSetEvent(uint32 taskID, OSHQSevent_m event);


void OsHQSleep(UseSleepBackFunc  backFunc);


void OsHQSRun(void);



#endif



