/**
******************************************************************************
* @file
* @author  HQS ������
* @version V1.0.0
* @date    2018/01/25
* @brief   ��Ϣ���� 
******************************************************************************
* @brief
*
*
*
*/
/* Includes ------------------------------------------------------------------*/

#ifndef _msgOSHQS_H_
#define _msgOSHQS_H_
#include "HQS_typedef.h"
#include "memPithyHQS.h"
#include "OSHQS.h"

typedef uint8 msgHQS_err;


typedef enum   //���д�����ʽ
{
	Msg_Err_OK = 0x00,      //�޴���
	Msg_Err_QueueName,      //����Ϣ�ж�
	Msg_Err_msgPackmem,     //�ڴ�ռ䲻�㣬�޷�����ռ䡣
	Msg_Err_Queue,          //�жӳ����������� ���в�����ʹ�ã������� ����ϵͳ������
	Msg_Err_Renounce        //����Ϣ���Բ�������Ϣ���в�ɾ��������Ϣ�ռ�
}
Msg_Err_m;



typedef enum   //���д�����ʽ
{
	FLU_FIFO_FILL = 0x00,    //FIFO ���(�������Ƚ���ģ�����䵽���)
	FLU_LIFO_FILL,           //LIFO ���
}
FillModeHQS_m;

typedef enum   //���ش�����ʽ
{
  FLU_FIFO_RENOUNCE,     //
  FLU_LIFO_RENOUNCE,     //
  FLU_RENOUNCE           //�������˴���Ϣ 
}FluidicModeHQS_m;


typedef struct
{
	void             * hdr;
	void             * end;
	FillModeHQS_m    fillMode;           //����ģʽ
	uint8            fluidic;            //��������
	uint8            fluidicCount;       //������������
	FluidicModeHQS_m fluidicMode;
}msgQueueInfoHQS_t;



typedef struct
{
	void           * next;
	uint16          dataSize;    //���ݰ���С
	uint8           msgts;       //ʱ���
	uint8           msgPeriod;   //��������
	void            *msgDataAdd; //���ݰ���ַ
}msgPackHQS_t;



/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�msgQueueInfoHQS_t * msgQueueInfoHQSCreate(FillModeHQS_m fillMode,uint8 fluidic, FluidicModeHQS_m fluidicMode);
;˵    ����������Ϣ�ж���Ϣ
;ʹ����Դ��
;��    �ڣ�@fillMode    �ж�ģʽ FIFO   LIFO
           @fluidic     �����ж�����
		   @fluidicMode �����ж�ģʽ
;��    �ڣ�msgQueueInfoHQS_t * �жӵ�ַ
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2018.1.5
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void msgOsQueueInfoHQSCreate(uint32 TaskID,FillModeHQS_m fillMode,uint8 fluidic, FluidicModeHQS_m fluidicMode);


/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�Msg_Err_m  msgSendHQS(msgQueueInfoHQS_t * msgQueueName, void * dataAdd);
;˵    ����������Ϣ���� ����������
           ����Ϣ���а�����ǳ������Ҫר�ݵ����ݣ�ֻ�������ݵĵ�ַ��
           ��Ϣ���ݿռ����� ������� memPithyHQS��
           �����봴���������ݿռ� ���ɺͳɹ����պ� ���ͷţ�
           ����������Ϣ���ڼ䷢������ϵͳ��ɾ���������ݿռ�
;ʹ����Դ��
;��    �ڣ�@msgQueueName ������Ϣ��ַ
           @dataAdd      ���͵����ݵ�ַ��������memPithyHQS ���ɵĿռ䣩
;��    �ڣ�Msg_Err_m

;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2018.1.6
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
Msg_Err_m msgOsSendHQS(uint32 TaskID, uint16 dataSize, void * dataAdd);

/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void * msgReceive(msgQueueInfoHQS_t * msgQueueName);
;˵    ���� ֱ�ӷ�����Ϣ���ݵ�ַ���Զ�ɾ����Ϣ�� ����ɾ�����ݰ�
             ����NULL ��ʾ������
;ʹ����Դ��
;��    �ڣ�@msgQueueName ������Ϣ��ַ
;��    �ڣ�void * 
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2018.1.7
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void * msgOsReceive(uint32 TaskID);


/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�msgPackHQS_t * msgPakcReceive(msgQueueInfoHQS_t * msgQueueName);
;˵    ���� ֱ�ӷ�����Ϣ����ַ �� ��ɾ���κΰ�
            ����NULL ��ʾ������
;ʹ����Դ��
;��    �ڣ�@msgQueueName ������Ϣ��ַ
;��    �ڣ�msgPackHQS_t *
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2018.1.7
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
msgPackHQS_t * msgOsPakcReceive(uint32 TaskID);

/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void  msgPakcDataDel(msgPackHQS_t * msgPack);
;˵    ����ɾ����Ϣ�� �� ��Ϣ����  
;ʹ����Դ��
;��    �ڣ�@msgPack ������Ϣ��ַ
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2018.1.7
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void  msgOsPakcDataDel(msgPackHQS_t * msgPack);


#endif


