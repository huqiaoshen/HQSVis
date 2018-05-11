/**
******************************************************************************
* @file
* @author  HQS ������
* @version V1.0.0
* @date    2018/01/04
* @brief   STM32С�д������豸 FLASH  ��д����
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

#define PAGE_AMOUNT  4  //4K ����ռ��С

/* STM32С�д������豸 FLASH ��ҳ��С���� ------------------------------*/
/* Define the STM32F10Xxx Flash page size depending on the used STM32 device */
#if defined (STM32F10X_LD) || defined (STM32F10X_MD) 
  #define PAGE_SIZE  (uint16_t)0x400  /* Page size = 1KByte */
#elif defined (STM32F10X_HD) || defined (STM32F10X_CL)
  #define PAGE_SIZE  (uint16_t)0x800  /* Page size = 2KByte */
#endif


/* EEPROM �� Flash��ʼ��ַ */
#define EEPROM_START_ADDRESS    ((uint32_t)0x0803F000) /* EEPROM emulation start address:
                                                          after 256KByte of used Flash memory */

/* �洢ҳ��ʼ�ͽ�����ַ */
#define PAGE_BASE_ADDRESS      ((uint32_t)(EEPROM_START_ADDRESS + 0x000))
#define PAGE_END_ADDRESS       ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE*PAGE_AMOUNT - 1)))

/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void FlashEEPROMReadHALHQS(uint32 DataAddr,uint16 *readBuffer,uint16 length);
;˵    ������Ե�ַ��ȡ���ݣ�DataAddr ��0��ʼ����flash����ʵ��ַ���û�������EEPROM_START_ADDRESS 
            flash����ʵ��ַ
    
;ʹ����Դ��
;��    �ڣ�@DataAddr     �洢��ַ
           @readBuffer   ����ָ��
		   @length       ���ݳ���
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ�������
;ʱ    �䣺2018.01.04
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void FlashEEPROMReadHALHQS(uint32 DataAddr,uint16 *readBuffer,uint16 length);


/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void FlashEEPROMWriteHALHQS(uint32 DataAddr,uint16 *writeBuffer,uint16 length);
;˵    ������Ե�ַд��flash����Ե�ַ��ȡ���ݣ�DataAddr ��0��ʼ����flash����ʵ��ַ���û�������EEPROM_START_ADDRESS 
            flash����ʵ��ַ
;ʹ����Դ��
;��    �ڣ�@DataAddr     �洢��ַ
           @readBuffer   ��������ָ��
		   @length       ���ݳ���
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ�������
;ʱ    �䣺2018.01.04
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void FlashEEPROMWriteHALHQS(uint32 DataAddr,uint16 *writeBuffer,uint16 length);








//��ȡʵ�ʵ�ַ
void * FlashOriginalHALHQS(uint32 DataAddr);



#endif

