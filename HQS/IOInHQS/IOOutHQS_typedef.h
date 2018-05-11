/**
******************************************************************************
* @file    IOOutHQS_typedef.h
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2017/12/14
* @brief   IOOut IO输出控制 软件层与HAL硬件层 接口.
******************************************************************************
* @brief
*
* 
*
*
*
* 
*/
#ifndef __IOOUTHQS_TYP_H
#define __IOOUTHQS_TYP_H
/* Includes ------------------------------------------------------------------*/
#include "HQS_typedef.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//用户定义ION名称
typedef enum
{
	/*用户定义区*/
	RUN_LED_R,    //运行指示灯 红
	RUN_LED_G,    //运行指示灯 绿
	LED_1,        //
	LED_2,        //
	LED_3,        //
	LED_4,        //
	LED_5,        //
	LED_6,        //
	LED_7,        //
	LED_8,        //

	/*用户定义结束*/
	IOOUT_END_MAX
}IoOutHQSCreateUse_m;



//1使用自带  0使用用户自己函数 返回（uint32）
#define HQSIOOUT_CLOCK 1

#if     HQSIOOUT_CLOCK == 0
#define HQSIoOutGetClock_MACRO()   //用户添加 获得当前系统时钟
#endif



//@ HQSIOOUTlevel_H  HQSIOOUTlevel_L
#define HQSIOOUTlevel_H   1   //开 置一
#define HQSI0OUTlevel_L   0   //关 置零


/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：HQSIoOutContrl_MACRO(ioUse,level)
;说    明：宏函数，进行底层IO 操作，用户自己编写调用
;使用资源：
;入    口：@ioUse：用户定义IO接口 @IoOutHQSCreateUse_m
;          @level：IO电平状态 参考 @HQSIOOUTlevel_H  HQSIOOUTlevel_L
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
#define HQSIoOutContrl_MACRO(ioUse,level) HQSHALIoOutContrl(ioUse,level)//IO控制函数 用户自己添加


#endif


