/**
******************************************************************************
* @file
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2018/01/25
* @brief   消息队列 
******************************************************************************
* @brief
*
*
*
*/
/* Includes ------------------------------------------------------------------*/

#ifndef _msgOSHQS_H_
#define _msgOSHQS_H_
#include "HQS_typedef.h"
#include "memPithyHQS.h"
#include "OSHQS.h"

typedef uint8 msgHQS_err;


typedef enum   //队列处理方式
{
	Msg_Err_OK = 0x00,      //无错误
	Msg_Err_QueueName,      //无消息列队
	Msg_Err_msgPackmem,     //内存空间不足，无法申请空间。
	Msg_Err_Queue,          //列队出现致命错误 此列不能再使用（会引起 整个系统崩溃）
	Msg_Err_Renounce        //次消息忽略不加入消息队列并删除消数据息空间
}
Msg_Err_m;



typedef enum   //队列处理方式
{
	FLU_FIFO_FILL = 0x00,    //FIFO 填充(舍弃最先进入的，并填充到最后)
	FLU_LIFO_FILL,           //LIFO 填充
}
FillModeHQS_m;

typedef enum   //流控处理方式
{
  FLU_FIFO_RENOUNCE,     //
  FLU_LIFO_RENOUNCE,     //
  FLU_RENOUNCE           //不处理此次消息 
}FluidicModeHQS_m;


typedef struct
{
	void             * hdr;
	void             * end;
	FillModeHQS_m    fillMode;           //队列模式
	uint8            fluidic;            //流控数量
	uint8            fluidicCount;       //流控数量计数
	FluidicModeHQS_m fluidicMode;
}msgQueueInfoHQS_t;



typedef struct
{
	void           * next;
	uint16          dataSize;    //数据包大小
	uint8           msgts;       //时间戳
	uint8           msgPeriod;   //生存周期
	void            *msgDataAdd; //数据包地址
}msgPackHQS_t;



/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：msgQueueInfoHQS_t * msgQueueInfoHQSCreate(FillModeHQS_m fillMode,uint8 fluidic, FluidicModeHQS_m fluidicMode);
;说    明：创建消息列队信息
;使用资源：
;入    口：@fillMode    列队模式 FIFO   LIFO
           @fluidic     流控列队数量
		   @fluidicMode 流控列队模式
;出    口：msgQueueInfoHQS_t * 列队地址
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2018.1.5
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void msgOsQueueInfoHQSCreate(uint32 TaskID,FillModeHQS_m fillMode,uint8 fluidic, FluidicModeHQS_m fluidicMode);


/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：Msg_Err_m  msgSendHQS(msgQueueInfoHQS_t * msgQueueName, void * dataAdd);
;说    明：发送消息数据 打包放入队列
           本消息队列包采用浅拷贝需要专递的数据（只传递数据的地址）
           消息数据空间申请 必须采用 memPithyHQS，
           不参与创建传递数据空间 生成和成功接收后 的释放；
           但在生成消息包期间发生错误系统会删除传递数据空间
;使用资源：
;入    口：@msgQueueName 队列信息地址
           @dataAdd      发送的数据地址（必须是memPithyHQS 生成的空间）
;出    口：Msg_Err_m

;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2018.1.6
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
Msg_Err_m msgOsSendHQS(uint32 TaskID, uint16 dataSize, void * dataAdd);

/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void * msgReceive(msgQueueInfoHQS_t * msgQueueName);
;说    明： 直接返回消息数据地址，自动删除消息包 但不删除数据包
             返回NULL 表示无数据
;使用资源：
;入    口：@msgQueueName 队列信息地址
;出    口：void * 
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2018.1.7
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void * msgOsReceive(uint32 TaskID);


/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：msgPackHQS_t * msgPakcReceive(msgQueueInfoHQS_t * msgQueueName);
;说    明： 直接返回消息包地址 ， 不删除任何包
            返回NULL 表示无数据
;使用资源：
;入    口：@msgQueueName 队列信息地址
;出    口：msgPackHQS_t *
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2018.1.7
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
msgPackHQS_t * msgOsPakcReceive(uint32 TaskID);

/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void  msgPakcDataDel(msgPackHQS_t * msgPack);
;说    明：删除信息包 和 消息数据  
;使用资源：
;入    口：@msgPack 队列信息地址
;出    口：
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2018.1.7
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void  msgOsPakcDataDel(msgPackHQS_t * msgPack);


#endif



