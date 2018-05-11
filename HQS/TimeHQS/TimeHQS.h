/**
******************************************************************************
* @file
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2018/02/27
* @brief   时钟
******************************************************************************
* @brief
*
*
*
*/
/* Includes ------------------------------------------------------------------*/

#ifndef _TimeHQS_H_
#define _TimeHQS_H_
#include "HQS_typedef.h"


#include "RTCHAL.h"
#include "FlashRWHALHQS.h"


#define  YEARSecNonleap  31536000  //平年 年总秒
#define  YEARSecLeap     31622400  //润年 年总秒
#define  DAYSec          86400     //天总秒数
#define  HOURSec         3600
#define  MINSec          60

typedef struct
{
	uint16  year;  //年
	uint8	month; //月
	uint8	day;   //日
	uint8	hour;  //时
	uint8	min;   //分
	uint8	sec;   //秒
}TimeDate_t;



/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void TimeHQSSetDateTime(uint16 year, uint8 month, uint8 day, uint8 hour, uint8 min, uint8 sec);
;说    明：时间设置
;使用资源：
;入    口：uint16 year,  年
           uint8 month,  月
		   uint8 day,    日
		   uint8 hour,   时
		   uint8 min,    分
		   uint8 sec     秒
;出    口：
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2018.03.01
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void TimeHQSSetDateTime(uint16 year, uint8	month, uint8	day, uint8	hour, uint8	min, uint8	sec);


/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：TimeDate_t TimeHQSGetDateTime(void);
;说    明：获得日期时间
;使用资源：
;入    口：
;出    口：@TimeDate_t
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2018.03.01
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
TimeDate_t TimeHQSGetDateTime(void);



#endif


