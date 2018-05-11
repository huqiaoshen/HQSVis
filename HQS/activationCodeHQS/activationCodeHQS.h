/**
******************************************************************************
* @file
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2018/02/27
* @brief   激活码算法
******************************************************************************
* @brief
*
*
*
*/
/* Includes ------------------------------------------------------------------*/

#ifndef _activationCodeHQS_H_
#define _activationCodeHQS_H_
#include "HQS_typedef.h"
#include "TimeHQS.h"

typedef struct
{
	TimeDate_t timeDate; //时间
	uint16  count;       //次数
	bool keyCode;        //密钥错误

}activation_t;



/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：
;说    明：
;使用资源：
;入    口：
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
activation_t activationCodeAnalyze(uint8 *keyData ,uint8 *idData);



#endif


