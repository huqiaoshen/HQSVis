/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究 
;HQS_SYS.H  头文件        
;作    者：胡乔申 
;E - mail:huqiaoshen@qq.com
;时    间：201303110947
;修改注释：	
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
  未经作者同意授权 造成作者损失 承担相关法律责任
           Copyright (c) 2012-2099 snail  HQS
*********************************************************/


#ifndef __HQS_SYS_H_
#define __HQS_SYS_H_
#include "stm32f10x.h"



/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究 
;函数名称：IO口位操作
;使用资源：“STM32f10x.h” 地址
;入    口：
;出    口：
;说    明：具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
;硬件接口:         
;作    者：胡乔申 
;E - mail:huqiaoshen@qq.com
;时    间：201303110947
;修改注释：	
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
  未经作者同意授权 造成作者损失 承担相关法律责任
           Copyright (c) 2012-2099 snail  HQS
*********************************************************/

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

/***********************************
函数名    :
函数原型  :
功能描述  :
输入参数  :
输出参数  :
返回值    :
先决条件  :
被调用函数:
作者      :
创建时间  :
修改时间  :
版本      :
************************************/
void Delay_Init(void);
void Delay_ms(unsigned short ms);
void Delay_us(unsigned long  us);

#endif

