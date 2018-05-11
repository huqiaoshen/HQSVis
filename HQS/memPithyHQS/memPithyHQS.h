/**
******************************************************************************
* @file
* @author  HQS ������
* @version V1.0.0
* @date    2017/05/28
* @brief   ����С�ڴ�������� ������ 0x7FFF���ֽ�
******************************************************************************
* @brief
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/

#ifndef _memPithyHQS_H_
#define _memPithyHQS_H_
#include "HQS_typedef.h"

#define MEMPithyHQSAlignEnable  0     //ʹ�ܶ���ģʽ  1ʹ��  0��ʹ��


#define MEMPithyHQSMaxHeap      10240  //�Ѵ�С���ֽڣ�----  ������0X7FFF���ֽ� 31Kb

#define MEMPithyHQStyp          uint16 //���߹����ڴ� ��С����  use:1(ʹ�ñ�־) | len:15���ߴ��С��
#define MEMPithyHQSUse          0x8000 //���߹����ڴ� ��С����  use:1(ʹ�ñ�־) 

//ע����С������
typedef struct
{
	MEMPithyHQStyp size : 15; //@ �ռ��С  �����ֽڣ�
	MEMPithyHQStyp use : 1;   //@ MEMPithyHQSUse
}memPithyHQSSU_t;  //����ռ� ʹ�ñ�־

typedef union
{
#if MEMPithyHQSAlignEnable
	HQSDataAlign_t   align;
#endif
	MEMPithyHQStyp   data;
	memPithyHQSSU_t  useSize;
}memPithyHQSHdr_t;              //��Ϣ�� �ṹ��

#define MEMPithyHQSHdrSize     sizeof(memPithyHQSHdr_t)    //��Ϣ���С��
#define MEMPithyHQSBottomSize  ((MEMPithyHQSMaxHeap / MEMPithyHQSHdrSize)-1)  //�ڴ����� ������

#define MEMPithyHQSAlignSize   sizeof(HQSDataAlign_t)      //�ڴ����ߴ�
#define MEMPithyHQSAlignment   (MEMPithyHQSAlignSize-1)    //����У׼



/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void HQSmemPithyInit(void);
;˵    �����ѿռ��ʼ��
;ʹ����Դ��
;��    �ڣ�
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2017.5.28
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void HQSmemPithyInit(void);


/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void * HQSmemPithyMalloc(MEMPithyHQStyp sizeMalloc);
;˵    �����ѿռ�����
;ʹ����Դ��
;��    �ڣ�@sizeMalloc ����Ѵ�С����λ���ֽڣ�
;��    �ڣ�@void *  ��������ѵ�ַ ������NULL Ϊʧ��
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2017.5.28
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void * HQSmemPithyMalloc(MEMPithyHQStyp sizeMalloc);


/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�void HQSmemPithyFree(void *freeP);
;˵    �����ѿռ��ͷ�
;ʹ����Դ��
;��    �ڣ�@ *freeP Ҫ�ͷſռ��ַ
;��    �ڣ�
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2017.5.28
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
void HQSmemPithyFree(void *freeP);


/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ�
;�������ƣ�MEMPithyHQStyp HQSmemPithySize(void * dataAdd);
;˵    �����ѿռ��С
;ʹ����Դ��
;��    �ڣ�@ *dataAdd �ռ��ַ
;��    �ڣ�MEMPithyHQStyp �ռ䳤��
;Ӳ���ӿ�:
;��    �ߣ������� 545044533@qq.com 13127766030
;ʱ    �䣺2017.5.28
;�޸�ע�ͣ�
;ע�����
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
δ��ͬ����Ȩ ���������ʧ �е���ط�������
Copyright (c) 2012-2099 HQS
*********************************************************/
//MEMPithyHQStyp HQSmemPithySize(void * dataAdd);
#endif


