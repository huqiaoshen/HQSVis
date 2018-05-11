/**
******************************************************************************
* @file
* @author  HQS ������
* @version V1.0.0
* @date    2018/02/26
* @brief   RTCHAL ʱ��
******************************************************************************
* @brief
*
*
*
*/
/* Includes ------------------------------------------------------------------*/

#ifndef _RTCHAL_H_
#define _RTCHAL_H_
#include "HQS_typedef.h"
#include "stm32f10x.h"

/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�
;˵    ���� 
;ʹ����Դ��
;��    �ڣ�
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2018.02.26
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void RTCHALIint(void);

void RTCHLSetCounter(uint32 count);

uint32  RTCHLGetCounter(void);




#endif


