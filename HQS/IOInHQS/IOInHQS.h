/**
******************************************************************************
* @file    
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2017/12/14
* @brief   IOOut IO输出控制 软件层与硬件无关.
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/
#ifndef __IOOUTHQS_H
#define __IOOUTHQS_H
#include "HQS_typedef.h"

typedef enum
{
	/*用户定义区*/
	IOIN00 = 0x00,
	IOIN01 ,
	IOIN02 ,
	IOIN03 ,
	IOIN04 ,
	IOIN05 ,
	IOIN06 ,
	IOIN08,
	/*用户定义结束*/
	IOIN_END_MAX
}IoInHQSCreateName_m;

typedef enum
{
	IOINHQS_LEVEL_Not = 0X00,    //无
	IOINHQS_LEVEL_Low,           //低电平
	IOINHQS_LEVEL_High           //高电平
	           
}IoInHQSLevel_m;

typedef enum
{
	IOINHQS_TR_Not  = 0x00,      //无
	IOINHQS_TR_Rising ,          //上升沿
	IOINHQS_TR_Trailing          //下降沿
}IoInHQSTrigger_m;


typedef enum
{
	IOINHQS_MODE_Poll = 0x00,      //轮查
	IOINHQS_MODE_PRisingCount,     //轮查上升沿计数
	IOINHQS_MODE_PTrailingCount,   //轮查下降沿计数
	IOINHQS_MODE_Interrupt,        //中断查询
	IOINHQS_MODE_IRisingCount,     //中断上升沿计数
	IOINHQS_MODE_ITrailingCount,   //中断下降沿计数
	IOINHQS_MODE_MUCRisingCount,   //MUC上升沿计数
	IOINHQS_MODE_MUCTrailingCount, //MUC下升沿计数
	IOINHQS_MODE_MUCRTCount        //MUC上下沿都计数
}IoInHQSMode_m;


typedef struct IoInHQSData_t
{
	uint32 risingTimeStamp;     // 上升沿时间戳
	uint32 trailingTimeStamp;   // 下降沿时间戳
	uint32 dataCount;  //计数器
}IoInHQSData_t;

typedef struct IoInHQS_t
{
	IoInHQSLevel_m     level;    //电平
	IoInHQSTrigger_m   trigger;  //触发
	IoInHQSMode_m      mode;     //模式
	IoInHQSData_t      Data;     //数据
}IoInHQS_t;


IoInHQS_t IoInControl[IOIN_END_MAX];

//触发消息
void HQSIoInTriggerMessage(void);

//设置模式
void HQSIoInSetMode();


void HQSIoInChangeHAL(IoInHQS_t IOName)

//获取数据
IoInHQS_t HQSIoInGetData(IoInHQS_t IOName);


/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void HQSIoOutIint(void);
;说    明：初始IOOut ,动作模式为无动作模式
;使用资源：
;入    口：
;出    口：
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2017.05.10
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void HQSIoInIint(void);



/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：
;说    明：
;使用资源：
;入    口： 
;出    口：
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2017.05.10
;修改注释：
;注意事项：开关模式下，延时参数是最新调用值()
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS	
*********************************************************/
void HQSIoInGetHL();







/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void HQSIoOutUpDate()
;说    明：数据更新执行函数 
;使用资源：
;入    口：
;出    口：
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2017.05.10
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void HQSIoInUpDate();


#endif


