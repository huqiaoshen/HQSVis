/**
******************************************************************************
* @file    USART2.h
* @author  HQS 胡乔申
* @version V1.0.0
* @date    2017/12/15
* @brief  STM32F1 USART2 串行通信接口
******************************************************************************
* @brief
*1：USART2  GPIO选择；
*   通过 USART2_GPIO_DENFIN 配置 USART2_GPIO_A、USART2_GPIO_D；切换USART2 在不同引脚
*2：USART2 RS485发送接受 IO控制切换
*   USART2_RS485_TRHAL 1使用 0不用
*   USART2_RS485_TRHAL == 1 添加对应控制IO
*   #define RS_485_RX_USART2EN() 	GPIO_ResetBits(GPIOD , GPIO_Pin_7)	//接收使能
*   #define RS_485_TX_USART2EN() 	GPIO_SetBits(GPIOD , GPIO_Pin_7)  	//发送使能  
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
 USART2  GPIO选择
 USART2_GPIO_A  选择 PA2 PA3
 USART2_GPIO_D  选择 PD5 PD6
******************************************************************************/
#define   USART2_GPIO_A     0
#define   USART2_GPIO_D     1
//用户配置
#define   USART2_GPIO_DENFIN  USART2_GPIO_D


/*****************************************************************************
USART2  RS485 接收发送硬件切换
USART2_RS485_TRHAL  1  使用硬件
USART2_RS485_TRHAL  0  不用硬件
******************************************************************************/
#define USART2_RS485_TRHAL  0

#if  USART2_RS485_TRHAL == 1
#define RS_485_RX_USART2EN() 	GPIO_ResetBits(GPIOD , GPIO_Pin_7)	//接收使能
#define RS_485_TX_USART2EN() 	GPIO_SetBits(GPIOD , GPIO_Pin_7)  	//发送使能
#endif

void USART2_Init(unsigned int bound);

void USART2_Send_Data(unsigned char *send_buff,unsigned int length);

void USART2_Send_String(unsigned char *string);

#endif
