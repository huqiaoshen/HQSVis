/**
******************************************************************************
* @file
* @author  HQS ������
* @version V1.0.0
* @date    2018/02/27
* @brief   ʱ��
******************************************************************************
* @brief
*
*
*
*/
/* Includes ------------------------------------------------------------------*/

#ifndef _TimeHQS_H_
#define _TimeHQS_H_
#include "HQS_typedef.h"


#include "RTCHAL.h"
#include "FlashRWHALHQS.h"


#define  YEARSecNonleap  31536000  //ƽ�� ������
#define  YEARSecLeap     31622400  //���� ������
#define  DAYSec          86400     //��������
#define  HOURSec         3600
#define  MINSec          60

typedef struct
{
	uint16  year;  //��
	uint8	month; //��
	uint8	day;   //��
	uint8	hour;  //ʱ
	uint8	min;   //��
	uint8	sec;   //��
}TimeDate_t;



/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void TimeHQSSetDateTime(uint16 year, uint8 month, uint8 day, uint8 hour, uint8 min, uint8 sec);
;˵    ����ʱ������
;ʹ����Դ��
;��    �ڣ�uint16 year,  ��
           uint8 month,  ��
		   uint8 day,    ��
		   uint8 hour,   ʱ
		   uint8 min,    ��
		   uint8 sec     ��
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2018.03.01
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void TimeHQSSetDateTime(uint16 year, uint8	month, uint8	day, uint8	hour, uint8	min, uint8	sec);


/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�TimeDate_t TimeHQSGetDateTime(void);
;˵    �����������ʱ��
;ʹ����Դ��
;��    �ڣ�
;��    �ڣ�@TimeDate_t
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2018.03.01
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
TimeDate_t TimeHQSGetDateTime(void);



#endif

