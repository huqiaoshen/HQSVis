/**
******************************************************************************
* @file    
* @author  HQS ������
* @version V1.0.0
* @date    2017/12/14
* @brief   IOOut IO������� ��������Ӳ���޹�.
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/


#ifndef __IOOUTHQS_H
#define __IOOUTHQS_H
#include "IOOutHQS_typedef.h"
#include "IOOutHALHQS.h" 

typedef enum
{
	IOOUTHQS_MODE_ATTONITY = 0X00,        //�޸���״̬
	IOOUTHQS_MODE_ON = 0X01,              //������һ
	IOOUTHQS_MODE_OFF = 0X02,             //�أ�����
	IOOUTHQS_MODE_BLINKH = 0X04,          //��˸��������һ
	IOOUTHQS_MODE_BLINKL = 0X08,          //��˸����������
	IOOUTHQS_MODE_BLINK = 0X10,           //��˸(����ѭ��)
}IoOutHQSModel_m;


typedef struct IoOutHQSControl_t
{
	IoOutHQSModel_m     model;        //ģʽ״̬ �ο�@IoOutHQSModel_m
	uint32              period;       //��˸���ڡ�����ʱʱ��
	uint8               highRatio;    //��˸��һռ�ȣ�0-100��
	uint16              count;        //���д���
	uint32              actionTime;   //����ʱ���
									  //struct IoOutControl_t *next;    //��һ���ṹ��ָ��
}IoOutHQSControl_t;


/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void HQSIoOutIint(void);
;˵    ������ʼIOOut ,����ģʽΪ�޶���ģʽ
;ʹ����Դ��
;��    �ڣ�
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
void HQSIoOutIint(void);



/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void HQSIoOutSet(IoOutHQSCreateUse_m ioUse, IoOutHQSModel_m model, int32 delay);
;˵    ����IOģʽ����
;ʹ����Դ��
;��    �ڣ� @ioUse���û�����IO�ӿ� @IoOutHQSCreateUse_m
            @model��ִ��ģʽ �ο� @IoOutHQSModel_m ,����ģʽ ���Զ�Ϊ50%ռ�� IOOUT_MODE_BLINKH��IOOUT_MODE_BLINKL ����һ��

			@delay��ִ����ʱ��������(model Ϊ IOOUT_MODE_ON��IOOUT_MODE_OFF ������µ� ����ִ������δ�����ʱ)
			        �������ڱ�����ڵ���2 ����
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2017.05.10
;�޸�ע�ͣ�
;ע���������ģʽ�£���ʱ���������µ���ֵ()
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS	
*********************************************************/
void HQSIoOutSet(IoOutHQSCreateUse_m ioUse, IoOutHQSModel_m model, int32 delay);




/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void HQSIoOutSetBlink(IoOutHQSCreateUse_m ioUse, IoOutHQSModel_m model, int32 period, uint8 highRatio,  uint16 count);
;˵    ����IO����ģʽ����
;ʹ����Դ��
;��    �ڣ�@ioUse���û�����IO�ӿ� @IoOutHQSCreateUse_m
           @model��ִ��ģʽ �ο� @IoOutHQSModel_m����ΪIOOUT_MODE_ON ��IOOUT_MODE_OFF ����period��Ϊ��ʱִ��ʱ��
		   @period������ʱ��
		   @highRatio �� ��һ�������б��� ��0-100%��������100% ����100%
		   @count  �����д���
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
void HQSIoOutSetBlink(IoOutHQSCreateUse_m ioUse, IoOutHQSModel_m model, int32 period, uint8 highRatio,  uint16 count);





/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void HQSIoOutUpDate()
;˵    �������ݸ���ִ�к��� 
;ʹ����Դ��
;��    �ڣ�
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
void HQSIoOutUpDate();


#endif

