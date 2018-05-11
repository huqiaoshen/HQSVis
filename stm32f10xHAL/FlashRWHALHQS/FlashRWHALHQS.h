/**
******************************************************************************
* @file
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2018/01/04
* @brief   STM32小中大容量设备 FLASH  读写程序
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/
#ifndef _FlashRWHALHQS_H_
#define _FlashRWHALHQS_H_


#include "HQS_typedef.h"
#include "stm32f10x.h"
#include "stm32f10x_flash.h"

#define PAGE_AMOUNT  4  //4K 分配空间大小

/* STM32小中大容量设备 FLASH 单页大小设置 ------------------------------*/
/* Define the STM32F10Xxx Flash page size depending on the used STM32 device */
#if defined (STM32F10X_LD) || defined (STM32F10X_MD) 
  #define PAGE_SIZE  (uint16_t)0x400  /* Page size = 1KByte */
#elif defined (STM32F10X_HD) || defined (STM32F10X_CL)
  #define PAGE_SIZE  (uint16_t)0x800  /* Page size = 2KByte */
#endif


/* EEPROM 在 Flash起始地址 */
#define EEPROM_START_ADDRESS    ((uint32_t)0x0803F000) /* EEPROM emulation start address:
                                                          after 256KByte of used Flash memory */

/* 存储页起始和结束地址 */
#define PAGE_BASE_ADDRESS      ((uint32_t)(EEPROM_START_ADDRESS + 0x000))
#define PAGE_END_ADDRESS       ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE*PAGE_AMOUNT - 1)))

/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void FlashEEPROMReadHALHQS(uint32 DataAddr,uint16 *readBuffer,uint16 length);
;说    明：相对地址读取数据，DataAddr 从0开始并非flash的真实地址，用户可设置EEPROM_START_ADDRESS 
            flash的真实地址
    
;使用资源：
;入    口：@DataAddr     存储地址
           @readBuffer   数据指针
		   @length       数据长度
;出    口：
;硬件接口:
;作    者：胡乔申
;时    间：2018.01.04
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void FlashEEPROMReadHALHQS(uint32 DataAddr,uint16 *readBuffer,uint16 length);


/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void FlashEEPROMWriteHALHQS(uint32 DataAddr,uint16 *writeBuffer,uint16 length);
;说    明：相对地址写入flash；相对地址读取数据，DataAddr 从0开始并非flash的真实地址，用户可设置EEPROM_START_ADDRESS 
            flash的真实地址
;使用资源：
;入    口：@DataAddr     存储地址
           @readBuffer   保存数据指针
		   @length       数据长度
;出    口：
;硬件接口:
;作    者：胡乔申
;时    间：2018.01.04
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void FlashEEPROMWriteHALHQS(uint32 DataAddr,uint16 *writeBuffer,uint16 length);








//获取实际地址
void * FlashOriginalHALHQS(uint32 DataAddr);



#endif


