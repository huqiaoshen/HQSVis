
#ifndef _UART5_h
#define _UART5_h

#include "stm32f10x.h"

void UART5_Init(unsigned int bound);

void UART5_Send_Data(unsigned char *send_buff,unsigned int length);

void UART5_Send_String(unsigned char *string);

#endif
