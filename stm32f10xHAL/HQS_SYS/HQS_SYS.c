/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ� 
;�������ƣ�HQS_SYS.C          
;��    �ߣ������� 
;E - mail:huqiaoshen@qq.com
;ʱ    �䣺201303110947
;�޸�ע�ͣ�	
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
  δ������ͬ����Ȩ ���������ʧ �е���ط�������
           Copyright (c) 2012-2099 snail  HQS
*********************************************************/
#include "HQS_SYS.h"
/*
��    ʱ�䵥λ����
��
��	1��=1000����(ms)
��	1����=1��1,000��(s) 
��
��	1��=1,000,000΢��(��s) 
��	1΢��=1��1,000,000��(s)
��	 
��	1��=1,000,000,000 ����(ns) 
��	1����=1��1,000,000,000��(s) 
��	
��	1��=1,000,000,000,000 Ƥ��(ps) 
��	1Ƥ��=1��1,000,000,000,000��(s)  
��	
��	1s  = 1000ms  
��	1ms = 1000us  
��	1us = 1000ns  
��	1ns = 1000ps 
*/

/* 
;	   Ƶ�ʵ�λ����   f=1/t(s)  Hz
;   
;	 1KHz = 1,000Hz   f=1/t(ms) KHz 
;	 1MHz = 1,000KHz  f=1/t(��s) MHz 
*/

/*******************************************************************************
;��    �ߣ������� 
; E-mail :huqiaoshen@qq.com
v1.0 : 	 #error "HQS_Err0000 ������������ " 
       һ����ʹ�� ��COS ϵͳ��
         ��1��  �궨�� HQS_USE_uCOS	  ���������COS��ʱ��
	       ��2��	�궨�� HQS_uC0S_Ver  = 2��3 ѡ��汾ѡ������ᱨ����HQS_Err0001����
		     ��3��	����ʱ���Զ��ж� ϵͳƵ��=1KHz 
		            ϵͳƵ��=1KHz ͨ����COSϵͳ����׼ȷ��ʱ���루ms����׼��
		            ϵͳƵ�ʡ�1KHz ��ʱϵͳ��ʱ����׼�ı�����������ͨus��ʱ��
		     ��4��  ΢��us ��ʱ	 ��COSϵͳƵ��һ���� 10~1000Hz ϵͳ�� 1ms~100ms
		            �޷�ͨ��ϵͳ��ʱ������ʱ��m �������ʱ ֻ��ͨ����ͨ��ʱ����
				        ��ʱ��COSϵͳ����while��ѭ����ʱ�޷��л��������񣬻ᵼ��ϵͳ
				        ʱ������HQS���Ѿ������á�(�ɲ���������ʱ��������ʵ�ֲ�Ӱ��ϵͳʱ��)
		     ��5��	�� ��COS ϵͳ��δ��������ʱ ��ʱ��������ͨ��ʱ��
	    ����δ���� ��COS ϵͳ��
		  ��1�� ʹ��SysTick����׼ȷ��ʱ ��ռ��������Դ
		  ��2��	�ο����� ��CortexCortex -M3 Ȩ��ָ�ϡ���133ҳ
		       
********************************************************************************/



/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ� 
;�������ƣ�Delay_Init(void);
;ʹ����Դ��
;��    �ڣ�
;��    �ڣ�
;˵    ����
;Ӳ���ӿ�:         
;��    �ߣ������� 
;E - mail:huqiaoshen@qq.com
;ʱ    �䣺201303110947
;�޸�ע�ͣ�
;ע�����ʱ�������øı�ᵼ����ʱ��uCOS����Ƶ�ʸı�  	
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
  δ������ͬ����Ȩ ���������ʧ �е���ط�������
           Copyright (c) 2012-2099 snail  HQS
*********************************************************/

#ifndef  HQS_USE_uCOS

unsigned char  Scale_us;
unsigned short Scale_ms;

void Delay_Init(void)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	  //SysTickʱ��ԴΪAHBʱ�� ʱ�ӳ���8
                                                          //8MHz -> 72MHz -> 9MHz = 1/9��s

  Scale_us=SystemCoreClock/8000000;						  //ʱ��ms����ϵ  (Hz����) ����SysTickʱ�����û���  
														  //��72MHz/8MHz us��  
														  //ע�⣺SysTickʱ�����øı� ҲҪ�ı�
  Scale_ms=SystemCoreClock/8000;						  //ʱ��ms����ϵ  (Hz����) ����SysTickʱ�����û���  
														  //��72MHz/8MHz * 1000 ms��
  														  //ע�⣺SysTickʱ�����øı� ҲҪ�ı�
}

#else

 #include <includes.h>
 unsigned long  Scale_us;

#if HQS_uC0S_Ver == 2 
 #if OS_TICKS_PER_SEC != 1000   //ϵͳƵ�� ��COS-2

 unsigned long  Scale_ms;
  
 #endif
#endif

#if HQS_uC0S_Ver == 3 
 #if OS_CFG_TICK_RATE_HZ!= 1000 //ϵͳƵ�� ��COS-3

 unsigned long  Scale_ms;
  
 #endif
#endif



void Delay_Init(void)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	  //SysTickʱ��ԴΪAHBʱ�� ʱ�ӳ���8
                                                          //8MHz -> 72MHz -> 9MHz = 1/9��s

  Scale_us=SystemCoreClock/8000000;						  //ʱ��us����ϵ  (MHz����) ����SysTickʱ�����û���   			
														  //��72MHz/8MHz us��
														  //ע�⣺SysTickʱ�����øı� ҲҪ�ı�
 #if HQS_uC0S_Ver == 2
   #if OS_TICKS_PER_SEC != 1000
   //Scale_us=*1000000/OS_TICKS_PER_SEC;				   //MHz(*1000000)-> Hz
   Scale_ms=1000000000*Scale_us/OS_TICKS_PER_SEC;		   // ms=1/KHz   Hz(*1000)->KHz

   #endif
 #else

  #if HQS_uC0S_Ver == 3
   #if OS_CFG_TICK_RATE_HZ != 1000
   //Scale_us=*1000000/OS_CFG_TICK_RATE_HZ;				   //MHz(*1000000)-> Hz
   Scale_ms=1000000000*Scale_us/OS_CFG_TICK_RATE_HZ;	   //ms=1/KHz   Hz(*1000)->KHz   
   #endif
  #else
//	  #message "fuck"
    #warning "HQS_Err0001: ѡ���COS�汾�����δѡ�� "
  #endif
 #endif 

 	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;                 //����SYSTICK�ж�
  #if HQS_uC0S_Ver == 3
	SysTick->LOAD=9000000/OS_CFG_TICK_RATE_HZ;               //ÿ1/OS_TICKS_PER_SEC �ж�һ��
  #else													 //ע�⣺SysTickʱ�����øı� ҲҪ�ı�
	#if HQS_uC0S_Ver == 2
	 SysTick->LOAD=9000000/OS_TICKS_PER_SEC;					 //ע�⣺SysTickʱ�����øı� ҲҪ�ı�
	#else 
	 #error "HQS_Err0001: ѡ���COS�汾�����δѡ�� "
    #endif
  #endif  
		
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	             //����SYSTICK  

}

#endif


#ifndef  HQS_USE_uCOS
/********************************************************
��Ȩ���������� �ο�ѧϰ����ϵ������Ȩ ����ؾ� 
;�������ƣ�Delay_us(unsigned long  us)
;ʹ����Դ��
;��    �ڣ�
;��    �ڣ�
;˵    ����
;Ӳ���ӿ�:         
;��    �ߣ������� 
;E - mail:huqiaoshen@qq.com
;ʱ    �䣺201303110947
;�޸�ע�ͣ�
;ע��������뱣֤ us<=��2^24��/Scale_us�����򽫵�����ʱ�䲻׼ȷ��(SysTick->LOADΪ24bit)
;��    ����V1.00
��Ȩ����������   �ο�ѧϰ����ϵ������Ȩ    ����ؾ�
  δ������ͬ����Ȩ ���������ʧ �е���ط�������
           Copyright (c) 2012-2099 snail  HQS
*********************************************************/
void Delay_us(unsigned long  us)
{
	unsigned long temp;
		    	 
	SysTick->LOAD=us*Scale_us;                         //ʱ�����   (SysTick->LOADΪ24bit)	  		 
	SysTick->VAL=0x00;                                 //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;           //��ʼ����	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));                 //�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;           //�رռ�����

	SysTick->VAL =0X00;                                //��ռ�����	  
}



void Delay_ms(unsigned short ms)
{
 	unsigned long temp;		   
	SysTick->LOAD=(unsigned long)ms*Scale_ms;         //ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;                               //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));                 //�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;           //�رռ�����
	SysTick->VAL =0X00;                                //��ռ�����	  
}
#else
 	   
void Delay_us(unsigned long us)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;

	u32 reload=SysTick->LOAD;	                       //LOAD��ֵ (��������0����װֵ)	    	 
	ticks=us*Scale_us; 			                       //��Ҫ�Ľ�����
		  		 
	tcnt=0;
	told=SysTick->VAL;        	                       //�ս���ʱ�ļ�����ֵ����ǰ������ֵ��
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;              //����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			 else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)  
			  break;                                   //ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	} 									    
}



//��ʱnms
//nms:Ҫ��ʱ��ms��
void Delay_ms(unsigned short ms)
{	
   #if HQS_uC0S_Ver == 3
    OS_ERR err;
   #endif

#if HQS_uC0S_Ver == 2
 					   //OSʱ��!=1ms ��׼
   if(OSRunning)                                       //���os�Ѿ�����	    
	{
    #if OS_TICKS_PER_SEC != 1000	  
	  OSTimeDly(ms/Scale_ms);                          //ucos��ʱ		
	  ms%=Scale_ms;
	  if(ms!=0)   
	  Delay_us((unsigned long)(ms*1000));	               //��ͨ��ʽ��ʱ,��ʱucos�޷���������.
	  #else											   //OSʱ��=1ms ��׼
	  OSTimeDly(ms);
	}
    #endif
 
#else 
 #if HQS_uC0S_Ver == 3
    
    if(OSRunning)                                      //���os�Ѿ�������	    
	{
	 #if OS_CFG_TICK_RATE_HZ!= 1000 					   //OSʱ��!=1ms ��׼
	  OSTimeDly(ms/Scale_ms,OS_OPT_TIME_DLY,&err);     //ucos��ʱ		
	  ms%=Scale_ms;
	  if(ms!=0)   
	  Delay_us((unsigned long)(ms*1000));	           //��ͨ��ʽ��ʱ,��ʱucos�޷���������.

	 #else											   //OSʱ��=1ms ��׼
	  OSTimeDly(ms,OS_OPT_TIME_DLY,&err);
	 #endif
	}
	 
 #else
  #error "HQS_Err0001: ѡ���COS�汾�����δѡ�� "
 #endif
#endif
	else
	 Delay_us((unsigned long)(ms*1000));	 	                             
}

#endif




void SysTick_Handler(void)	  // SysTick �жϴ��� 
{
  #ifdef HQS_USE_uCOS     //��������	 ����uCOSϵͳ ����				   
	
	OSIntEnter();		      //�����ж�
  OSTimeTick();         //����os��ʱ�ӷ������               
  OSIntExit();          //���������л����ж�
	  
  #endif
}

/**************************************
��ͬ������ ��printf ����֧��


/**************************************/
#define HQS_STM32_PRINTF       1          //1֧��  0��֧��
#define HQS_STM32_PRINTF_RORT  USART1     //��Ӧstm32����


#if HQS_STM32_PRINTF == 1 
#include <stdio.h>
#include <stm32f10x_usart.h>
#if defined(__GNUC__)
#include <sys/stat.h>
int _fstat(int fd, struct stat *pStat)
{
	pStat->st_mode = S_IFCHR;
	return 0;
}

int _write(int fd, char *pBuffer, int size)
{
	for (int i = 0; i < size; i++)
	{
		while (!(HQS_STM32_PRINTF_RORT->SR & USART_SR_TXE))
		{
		}
		USART_SendData(HQS_STM32_PRINTF_RORT, pBuffer[i]);
	}
	return size;
}

int _isatty(int fd)
{
	return 1;
}



int _read(int fd, char *pBuffer, int size)
{
	for (int i = 0; i < size; i++)
	{
		while ((HQS_STM32_PRINTF_RORT->SR & USART_SR_RXNE) == 0)
		{
		}

		pBuffer[i] = USART_ReceiveData(HQS_STM32_PRINTF_RORT);
	}
	return size;
}

caddr_t _sbrk(int increment)
{
	extern char end asm("end");
	register char *pStack asm("sp");

	static char *s_pHeapEnd;

	if (!s_pHeapEnd)
		s_pHeapEnd = &end;

	if (s_pHeapEnd + increment > pStack)
		return (caddr_t)-1;

	char *pOldHeapEnd = s_pHeapEnd;
	s_pHeapEnd += increment;
	return (caddr_t)pOldHeapEnd;
}
#elif defined (__CC_ARM)
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE
{
	int handle;

};
FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x)
{
	x = x;
}
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{
	while (USART_GetFlagStatus(HQS_STM32_PRINTF_RORT, USART_FLAG_TC) == RESET);
	USART_SendData(HQS_STM32_PRINTF_RORT, (uint8_t)ch);
	return ch;
}


#endif
#endif
