#ifndef __IOOUTHALHQS_H
#define __IOOUTHALHQS_H

#include "stm32f10x.h"
#include "IOOutHQS_typedef.h"

void HQSHALIoOutIint(void);

/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void HQSIoOutSetBlink(IoOutCreateUse_m ioUse, IoOutModel_m model,uint16 count, int32 period, uint8 highRatio);
;˵    ����IO����ģʽ����
;ʹ����Դ��
;��    �ڣ�
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ�������
;ʱ    �䣺2017.05.10
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/

void HQSHALIoOutContrl(IoOutHQSCreateUse_m ioUse, uint8 level);



#endif