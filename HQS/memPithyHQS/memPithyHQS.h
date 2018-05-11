/**
******************************************************************************
* @file
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2017/05/28
* @brief   精简小内存管理程序 最大管理 0x7FFF个字节
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/

#ifndef _memPithyHQS_H_
#define _memPithyHQS_H_
#include "HQS_typedef.h"

#define MEMPithyHQSAlignEnable  0     //使能对齐模式  1使能  0不使用


#define MEMPithyHQSMaxHeap      10240  //堆大小（字节）----  最大管理0X7FFF个字节 31Kb

#define MEMPithyHQStyp          uint16 //更具管理内存 大小调整  use:1(使用标志) | len:15（尺寸大小）
#define MEMPithyHQSUse          0x8000 //更具管理内存 大小调整  use:1(使用标志) 

//注意大端小端问题
typedef struct
{
	MEMPithyHQStyp size : 15; //@ 空间大小  ；（字节）
	MEMPithyHQStyp use : 1;   //@ MEMPithyHQSUse
}memPithyHQSSU_t;  //分配空间 使用标志

typedef union
{
#if MEMPithyHQSAlignEnable
	HQSDataAlign_t   align;
#endif
	MEMPithyHQStyp   data;
	memPithyHQSSU_t  useSize;
}memPithyHQSHdr_t;              //信息块 结构体

#define MEMPithyHQSHdrSize     sizeof(memPithyHQSHdr_t)    //信息块大小，
#define MEMPithyHQSBottomSize  ((MEMPithyHQSMaxHeap / MEMPithyHQSHdrSize)-1)  //内存池最低 数组标记

#define MEMPithyHQSAlignSize   sizeof(HQSDataAlign_t)      //内存对齐尺寸
#define MEMPithyHQSAlignment   (MEMPithyHQSAlignSize-1)    //对齐校准



/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void HQSmemPithyInit(void);
;说    明：堆空间初始化
;使用资源：
;入    口：
;出    口：
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2017.5.28
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void HQSmemPithyInit(void);


/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void * HQSmemPithyMalloc(MEMPithyHQStyp sizeMalloc);
;说    明：堆空间申请
;使用资源：
;入    口：@sizeMalloc 申请堆大小（单位：字节）
;出    口：@void *  返回申请堆地址 ，返回NULL 为失败
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2017.5.28
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void * HQSmemPithyMalloc(MEMPithyHQStyp sizeMalloc);


/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void HQSmemPithyFree(void *freeP);
;说    明：堆空间释放
;使用资源：
;入    口：@ *freeP 要释放空间地址
;出    口：
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2017.5.28
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void HQSmemPithyFree(void *freeP);


/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：MEMPithyHQStyp HQSmemPithySize(void * dataAdd);
;说    明：堆空间大小
;使用资源：
;入    口：@ *dataAdd 空间地址
;出    口：MEMPithyHQStyp 空间长度
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2017.5.28
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
//MEMPithyHQStyp HQSmemPithySize(void * dataAdd);
#endif



