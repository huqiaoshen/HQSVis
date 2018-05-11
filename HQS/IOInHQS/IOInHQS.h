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
#include "HQS_typedef.h"

typedef enum
{
	/*�û�������*/
	IOIN00 = 0x00,
	IOIN01 ,
	IOIN02 ,
	IOIN03 ,
	IOIN04 ,
	IOIN05 ,
	IOIN06 ,
	IOIN08,
	/*�û��������*/
	IOIN_END_MAX
}IoInHQSCreateName_m;

typedef enum
{
	IOINHQS_LEVEL_Not = 0X00,    //��
	IOINHQS_LEVEL_Low,           //�͵�ƽ
	IOINHQS_LEVEL_High           //�ߵ�ƽ
	           
}IoInHQSLevel_m;

typedef enum
{
	IOINHQS_TR_Not  = 0x00,      //��
	IOINHQS_TR_Rising ,          //������
	IOINHQS_TR_Trailing          //�½���
}IoInHQSTrigger_m;


typedef enum
{
	IOINHQS_MODE_Poll = 0x00,      //�ֲ�
	IOINHQS_MODE_PRisingCount,     //�ֲ������ؼ���
	IOINHQS_MODE_PTrailingCount,   //�ֲ��½��ؼ���
	IOINHQS_MODE_Interrupt,        //�жϲ�ѯ
	IOINHQS_MODE_IRisingCount,     //�ж������ؼ���
	IOINHQS_MODE_ITrailingCount,   //�ж��½��ؼ���
	IOINHQS_MODE_MUCRisingCount,   //MUC�����ؼ���
	IOINHQS_MODE_MUCTrailingCount, //MUC�����ؼ���
	IOINHQS_MODE_MUCRTCount        //MUC�����ض�����
}IoInHQSMode_m;


typedef struct IoInHQSData_t
{
	uint32 risingTimeStamp;     // ������ʱ���
	uint32 trailingTimeStamp;   // �½���ʱ���
	uint32 dataCount;  //������
}IoInHQSData_t;

typedef struct IoInHQS_t
{
	IoInHQSLevel_m     level;    //��ƽ
	IoInHQSTrigger_m   trigger;  //����
	IoInHQSMode_m      mode;     //ģʽ
	IoInHQSData_t      Data;     //����
}IoInHQS_t;


IoInHQS_t IoInControl[IOIN_END_MAX];

//������Ϣ
void HQSIoInTriggerMessage(void);

//����ģʽ
void HQSIoInSetMode();


void HQSIoInChangeHAL(IoInHQS_t IOName)

//��ȡ����
IoInHQS_t HQSIoInGetData(IoInHQS_t IOName);


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
void HQSIoInIint(void);



/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�
;˵    ����
;ʹ����Դ��
;��    �ڣ� 
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
void HQSIoInGetHL();







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
void HQSIoInUpDate();


#endif

