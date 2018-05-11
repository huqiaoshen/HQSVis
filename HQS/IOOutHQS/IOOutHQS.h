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
#include "IOOutHQS_typedef.h"
#include "IOOutHALHQS.h" 

typedef enum
{
	IOOUTHQS_MODE_ATTONITY = 0X00,        //无更新状态
	IOOUTHQS_MODE_ON = 0X01,              //开，置一
	IOOUTHQS_MODE_OFF = 0X02,             //关，置零
	IOOUTHQS_MODE_BLINKH = 0X04,          //闪烁，结束置一
	IOOUTHQS_MODE_BLINKL = 0X08,          //闪烁，结束置零
	IOOUTHQS_MODE_BLINK = 0X10,           //闪烁(无限循环)
}IoOutHQSModel_m;


typedef struct IoOutHQSControl_t
{
	IoOutHQSModel_m     model;        //模式状态 参考@IoOutHQSModel_m
	uint32              period;       //闪烁周期、关延时时间
	uint8               highRatio;    //闪烁置一占比（0-100）
	uint16              count;        //运行次数
	uint32              actionTime;   //动作时间点
									  //struct IoOutControl_t *next;    //下一个结构体指针
}IoOutHQSControl_t;


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
void HQSIoOutIint(void);



/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void HQSIoOutSet(IoOutHQSCreateUse_m ioUse, IoOutHQSModel_m model, int32 delay);
;说    明：IO模式设置
;使用资源：
;入    口： @ioUse：用户定义IO接口 @IoOutHQSCreateUse_m
            @model：执行模式 参考 @IoOutHQSModel_m ,闪动模式 都自动为50%占比 IOOUT_MODE_BLINKH、IOOUT_MODE_BLINKL 运行一次

			@delay：执行延时或者周期(model 为 IOOUT_MODE_ON、IOOUT_MODE_OFF 填充最新的 不会执行所有未完的延时)
			        闪动周期必须大于等于2 （）
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
void HQSIoOutSet(IoOutHQSCreateUse_m ioUse, IoOutHQSModel_m model, int32 delay);




/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void HQSIoOutSetBlink(IoOutHQSCreateUse_m ioUse, IoOutHQSModel_m model, int32 period, uint8 highRatio,  uint16 count);
;说    明：IO闪动模式设置
;使用资源：
;入    口：@ioUse：用户定义IO接口 @IoOutHQSCreateUse_m
           @model：执行模式 参考 @IoOutHQSModel_m；当为IOOUT_MODE_ON 、IOOUT_MODE_OFF 周期period则为延时执行时间
		   @period：周期时间
		   @highRatio ： 置一在周期中比例 （0-100%），超过100% 按照100%
		   @count  ：运行次数
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
void HQSIoOutSetBlink(IoOutHQSCreateUse_m ioUse, IoOutHQSModel_m model, int32 period, uint8 highRatio,  uint16 count);





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
void HQSIoOutUpDate();


#endif


