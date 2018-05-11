
#ifndef _USART1_h
#define _USART1_h

#include "stm32f10x.h"

void USART1_Init(unsigned int bound);

void USART1_Send_Data(unsigned char *send_buff,unsigned int length);

void USART1_Send_String(unsigned char *string);

#endif
