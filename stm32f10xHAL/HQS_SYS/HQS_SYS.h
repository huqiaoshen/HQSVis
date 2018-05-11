/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ� 
;HQS_SYS.H  ͷ�ļ�        
;��    �ߣ������� 
;E - mail:huqiaoshen@qq.com
;ʱ    �䣺201303110947
;�޸�ע�ͣ�	
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
  δ������ͬ����Ȩ ���������ʧ �е���ط�������
           Copyright (c) 2012-2099 snail  HQS
*********************************************************/


#ifndef __HQS_SYS_H_
#define __HQS_SYS_H_
#include "stm32f10x.h"



/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ� 
;�������ƣ�IO��λ����
;ʹ����Դ����STM32f10x.h�� ��ַ
;��    �ڣ�
;��    �ڣ�
;˵    ��������ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
;Ӳ���ӿ�:         
;��    �ߣ������� 
;E - mail:huqiaoshen@qq.com
;ʱ    �䣺201303110947
;�޸�ע�ͣ�	
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
  δ������ͬ����Ȩ ���������ʧ �е���ط�������
           Copyright (c) 2012-2099 snail  HQS
*********************************************************/

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO�ڵ�ַӳ��
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
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

/***********************************
������    :
����ԭ��  :
��������  :
�������  :
�������  :
����ֵ    :
�Ⱦ�����  :
�����ú���:
����      :
����ʱ��  :
�޸�ʱ��  :
�汾      :
************************************/
void Delay_Init(void);
void Delay_ms(unsigned short ms);
void Delay_us(unsigned long  us);

#endif
