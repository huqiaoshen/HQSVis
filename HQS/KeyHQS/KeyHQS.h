/********************************************************
��Ȩ��HuQiaoshen �ο�ѧϰ����ϵ������Ȩ ����ؾ� 
;��������ͨ�ó���
;�ɴ�����
;       �����¡����𡢵�����˫������ε��
;       ����������
;              

;��    �ߣ�������
;ʱ    �䣺2016.9.6
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
  δ��ͬ����Ȩ ���������ʧ �е���ط�������
    Copyright (c) 2012-2099 HQS
*********************************************************/

#ifndef _KeyHQS_H_
#define _KeyHQS_H_
#include "HQS_typedef.h"

#define  KEYHQStyp                uint16    //һ��bit����һ������
#define  KEYHQS_StartValue         0x00    //��ʼ���κΰ�������ֵ
#define  KEYHQS_TAPLongTimeOut     300     //������ʱ��ֵ
#define  KEYHQS_TAPSeriesTimeOut   160     //������ʱ��ֵ

//@LongSerie
typedef enum KEYHQSLongSerie_m
{
 KEYHQSSERIES_NOTLS  =(uint8)0 ,       //������
 KEYHQSSERIES_Serie  ,                 //����
 KEYHQSSERIES_Long                     //����
}KEYHQSLongSerie_m;

//@UpDown
typedef enum KEYHQSUpDown_m
{
 KEYHQSPREESS_NOT   = (uint8)0,        //�޲���
 KEYHQSPREESS_UP    ,                  //����
 KEYHQSPREESS_DOWN                     //����
}KEYHQSUpDown_m;

typedef struct {
	uint8               use;         //ʹ�ñ�־
	KEYHQStyp           value;       //��ֵ
	KEYHQSUpDown_m      UpDown;      //���µ���״̬ @KEYHQSUpDown_m
	KEYHQSLongSerie_m   LongSerie;   //��������״̬ @KEYHQSLongSerie_m
	uint8               Seriescount; //����������	
}KeyHQSMessage_t;

volatile KeyHQSMessage_t KeyHQSMessage;


/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�HQSKeyMessage_MACRO(KeyHQSMessage)
;˵    �����꺯���������û��Լ���д����
           ����������ֵ �� ״̬�����仯���ο���KeyHQSMessage_t����KeyHQSMessage_t.use ��һ��ʹ������û�����
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
#define HQSKeyMessage_MACRO(KeyHQSMessage)   //�û����� key ������Ϣ����



/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void HQSKeyInit(void)
;˵    ��������������ʼ��
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
void HQSKeyInit(void);



/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void HQSKeyUpDate(KEYHQStyp Date)
;˵    �������ݷ�������
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
void HQSKeyUpDate(KEYHQStyp Date);

#endif

