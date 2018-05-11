#ifndef __IOOUTHALHQS_H
#define __IOOUTHALHQS_H

#include "stm32f10x.h"
#include "IOOutHQS_typedef.h"

void HQSHALIoOutIint(void);

/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void HQSIoOutSetBlink(IoOutCreateUse_m ioUse, IoOutModel_m model,uint16 count, int32 period, uint8 highRatio);
;说    明：IO闪动模式设置
;使用资源：
;入    口：
;出    口：
;硬件接口:
;作    者：胡乔申
;时    间：2017.05.10
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/

void HQSHALIoOutContrl(IoOutHQSCreateUse_m ioUse, uint8 level);



#endif