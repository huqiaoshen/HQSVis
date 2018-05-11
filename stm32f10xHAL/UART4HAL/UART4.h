
#ifndef _UART4_h
#define _UART4_h

#include "stm32f10x.h"

void UART4_Init(unsigned int bound);

void UART4_Send_Data(unsigned char *send_buff,unsigned int length);

void UART4_Send_String(unsigned char *string);

#endif
