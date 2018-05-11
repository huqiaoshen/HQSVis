/**
******************************************************************************
* @file    IOOutHQS_typedef.h
* @author  HQS ������
* @version V1.0.0
* @date    2017/12/14
* @brief   IOOut IO������� ��������HALӲ���� �ӿ�.
******************************************************************************
* @brief
*
* 
*
*
*
* 
*/
#ifndef __IOOUTHQS_TYP_H
#define __IOOUTHQS_TYP_H
/* Includes ------------------------------------------------------------------*/
#include "HQS_typedef.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//�û�����ION����
typedef enum
{
	/*�û�������*/
	RUN_LED_R,    //����ָʾ�� ��
	RUN_LED_G,    //����ָʾ�� ��
	LED_1,        //
	LED_2,        //
	LED_3,        //
	LED_4,        //
	LED_5,        //
	LED_6,        //
	LED_7,        //
	LED_8,        //

	/*�û��������*/
	IOOUT_END_MAX
}IoOutHQSCreateUse_m;



//1ʹ���Դ�  0ʹ���û��Լ����� ���أ�uint32��
#define HQSIOOUT_CLOCK 1

#if     HQSIOOUT_CLOCK == 0
#define HQSIoOutGetClock_MACRO()   //�û����� ��õ�ǰϵͳʱ��
#endif



//@ HQSIOOUTlevel_H  HQSIOOUTlevel_L
#define HQSIOOUTlevel_H   1   //�� ��һ
#define HQSI0OUTlevel_L   0   //�� ����


/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�HQSIoOutContrl_MACRO(ioUse,level)
;˵    �����꺯�������еײ�IO �������û��Լ���д����
;ʹ����Դ��
;��    �ڣ�@ioUse���û�����IO�ӿ� @IoOutHQSCreateUse_m
;          @level��IO��ƽ״̬ �ο� @HQSIOOUTlevel_H  HQSIOOUTlevel_L
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2017.05.10
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
#define HQSIoOutContrl_MACRO(ioUse,level) HQSHALIoOutContrl(ioUse,level)//IO���ƺ��� �û��Լ�����


#endif

