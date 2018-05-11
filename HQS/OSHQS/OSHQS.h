/**
******************************************************************************
* @file
* @author  HQS ������
* @version V1.0.0
* @date    2018/01/17
* @brief   �¼����������ֻ�ִ��OSϵͳ
******************************************************************************
* @brief

*
*
*
*/
/* Includes ------------------------------------------------------------------*/

#ifndef _OSHQS_H_
#define _OSHQS_H_
#include "HQS_typedef.h"
#include "memPithyHQS.h"


#define taskHQSQty   2 //��������

typedef void (*TaskBackFunc)(void);
typedef void (*UseSleepBackFunc)(void *); //�û�˯�ߺ���


typedef enum
{
	OSNotHQS_Event = 0x0000,  //��  �¼�
	OSMgsHQS_Event = 0x0001,  //��Ϣ�¼�
	OSTimHQS_Event = 0x0002,  //��ʱ�¼�
}
OSHQSevent_m;



typedef struct _OSHQSTask_t
{
	uint32       cyc;             //ѭ������  ��0 Ϊ��Ϣ�¼�����
	uint32       runtime;         //����ִ������ʱ��
	uint32       sts;             //����ִ�п�ʼʱ���
	uint32       ets;             //����ִ�н���ʱ���
}OSHQSInfoTask_t;



void OsHQSInit(void);

//ϵͳ���ĵ���
void OsHQSCycUp(void);

                        //id            ������               ����
void OsHQSTaskCreate(uint32 TaskID, TaskBackFunc taskFunc,  uint32 cyc);


void OsHQSSetEvent(uint32 taskID, OSHQSevent_m event);


void OsHQSleep(UseSleepBackFunc  backFunc);


void OsHQSRun(void);



#endif


