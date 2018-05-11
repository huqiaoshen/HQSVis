/**
******************************************************************************
* @file    USART2.h
* @author  HQS ������
* @version V1.0.0
* @date    2017/12/15
* @brief  STM32F1 USART2 ����ͨ�Žӿ�
******************************************************************************
* @brief
*1��USART2  GPIOѡ��
*   ͨ�� USART2_GPIO_DENFIN ���� USART2_GPIO_A��USART2_GPIO_D���л�USART2 �ڲ�ͬ����
*2��USART2 RS485���ͽ��� IO�����л�
*   USART2_RS485_TRHAL 1ʹ�� 0����
*   USART2_RS485_TRHAL == 1 ���Ӷ�Ӧ����IO
*   #define RS_485_RX_USART2EN() 	GPIO_ResetBits(GPIOD , GPIO_Pin_7)	//����ʹ��
*   #define RS_485_TX_USART2EN() 	GPIO_SetBits(GPIOD , GPIO_Pin_7)  	//����ʹ��  
*
*
*
*
*/
/* Includes ------------------------------------------------------------------*/
#ifndef _USART2_h
#define _USART2_h

#include "stm32f10x.h"

/*****************************************************************************
 USART2  GPIOѡ��
 USART2_GPIO_A  ѡ�� PA2 PA3
 USART2_GPIO_D  ѡ�� PD5 PD6
******************************************************************************/
#define   USART2_GPIO_A     0
#define   USART2_GPIO_D     1
//�û�����
#define   USART2_GPIO_DENFIN  USART2_GPIO_D


/*****************************************************************************
USART2  RS485 ���շ���Ӳ���л�
USART2_RS485_TRHAL  1  ʹ��Ӳ��
USART2_RS485_TRHAL  0  ����Ӳ��
******************************************************************************/
#define USART2_RS485_TRHAL  0

#if  USART2_RS485_TRHAL == 1
#define RS_485_RX_USART2EN() 	GPIO_ResetBits(GPIOD , GPIO_Pin_7)	//����ʹ��
#define RS_485_TX_USART2EN() 	GPIO_SetBits(GPIOD , GPIO_Pin_7)  	//����ʹ��
#endif

void USART2_Init(unsigned int bound);

void USART2_Send_Data(unsigned char *send_buff,unsigned int length);

void USART2_Send_String(unsigned char *string);

#endif