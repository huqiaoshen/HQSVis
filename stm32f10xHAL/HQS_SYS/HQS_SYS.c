/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究 
;函数名称：HQS_SYS.C          
;作    者：胡乔申 
;E - mail:huqiaoshen@qq.com
;时    间：201303110947
;修改注释：	
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
  未经作者同意授权 造成作者损失 承担相关法律责任
           Copyright (c) 2012-2099 snail  HQS
*********************************************************/
#include "HQS_SYS.h"
/*
；    时间单位进制
；
；	1秒=1000毫秒(ms)
；	1毫秒=1／1,000秒(s) 
；
；	1秒=1,000,000微秒(μs) 
；	1微秒=1／1,000,000秒(s)
；	 
；	1秒=1,000,000,000 纳秒(ns) 
；	1纳秒=1／1,000,000,000秒(s) 
；	
；	1秒=1,000,000,000,000 皮秒(ps) 
；	1皮秒=1／1,000,000,000,000秒(s)  
；	
；	1s  = 1000ms  
；	1ms = 1000us  
；	1us = 1000ns  
；	1ns = 1000ps 
*/

/* 
;	   频率单位进制   f=1/t(s)  Hz
;   
;	 1KHz = 1,000Hz   f=1/t(ms) KHz 
;	 1MHz = 1,000KHz  f=1/t(μs) MHz 
*/

/*******************************************************************************
;作    者：胡乔申 
; E-mail :huqiaoshen@qq.com
v1.0 : 	 #error "HQS_Err0000 测试条件编译 " 
       一：当使用 μCOS 系统：
         （1）  宏定义 HQS_USE_uCOS	  启动编译μCOS延时。
	       （2）	宏定义 HQS_uC0S_Ver  = 2、3 选则版本选错编译会报错（HQS_Err0001）。
		     （3）	编译时会自动判断 系统频率=1KHz 
		            系统频率=1KHz 通过μCOS系统函数准确延时毫秒（ms）基准；
		            系统频率≠1KHz 此时系统延时按基准的倍数余数用普通us延时。
		     （4）  微秒us 延时	 μCOS系统频率一般在 10~1000Hz 系统延 1ms~100ms
		            无法通过系统延时函数延时μm 级别的延时 只能通过普通延时进行
				        此时μCOS系统进入while死循环延时无法切换调度任务，会导致系统
				        时钟有误差；HQS提醒尽量少用。(可采用其他定时计数器来实现不影响系统时钟)
		     （5）	当 μCOS 系统还未启动运行时 延时会启动普通延时。
	    二：未运行 μCOS 系统：
		  （1） 使用SysTick进行准确延时 不占用其他资源
		  （2）	参考资料 《CortexCortex -M3 权威指南》第133页
		       
********************************************************************************/



/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究 
;函数名称：Delay_Init(void);
;使用资源：
;入    口：
;出    口：
;说    明：
;硬件接口:         
;作    者：胡乔申 
;E - mail:huqiaoshen@qq.com
;时    间：201303110947
;修改注释：
;注意事项：时钟树配置改变会导致延时，uCOS工作频率改变  	
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
  未经作者同意授权 造成作者损失 承担相关法律责任
           Copyright (c) 2012-2099 snail  HQS
*********************************************************/

#ifndef  HQS_USE_uCOS

unsigned char  Scale_us;
unsigned short Scale_ms;

void Delay_Init(void)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	  //SysTick时钟源为AHB时钟 时钟除以8
                                                          //8MHz -> 72MHz -> 9MHz = 1/9μs

  Scale_us=SystemCoreClock/8000000;						  //时间ms比例系  (Hz换算) 根据SysTick时钟配置换算  
														  //（72MHz/8MHz us）  
														  //注意：SysTick时钟配置改变 也要改变
  Scale_ms=SystemCoreClock/8000;						  //时间ms比例系  (Hz换算) 根据SysTick时钟配置换算  
														  //（72MHz/8MHz * 1000 ms）
  														  //注意：SysTick时钟配置改变 也要改变
}

#else

 #include <includes.h>
 unsigned long  Scale_us;

#if HQS_uC0S_Ver == 2 
 #if OS_TICKS_PER_SEC != 1000   //系统频率 μCOS-2

 unsigned long  Scale_ms;
  
 #endif
#endif

#if HQS_uC0S_Ver == 3 
 #if OS_CFG_TICK_RATE_HZ!= 1000 //系统频率 μCOS-3

 unsigned long  Scale_ms;
  
 #endif
#endif



void Delay_Init(void)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	  //SysTick时钟源为AHB时钟 时钟除以8
                                                          //8MHz -> 72MHz -> 9MHz = 1/9μs

  Scale_us=SystemCoreClock/8000000;						  //时间us比例系  (MHz换算) 根据SysTick时钟配置换算   			
														  //（72MHz/8MHz us）
														  //注意：SysTick时钟配置改变 也要改变
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
    #warning "HQS_Err0001: 选择μCOS版本错误或未选择 "
  #endif
 #endif 

 	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;                 //开启SYSTICK中断
  #if HQS_uC0S_Ver == 3
	SysTick->LOAD=9000000/OS_CFG_TICK_RATE_HZ;               //每1/OS_TICKS_PER_SEC 中断一次
  #else													 //注意：SysTick时钟配置改变 也要改变
	#if HQS_uC0S_Ver == 2
	 SysTick->LOAD=9000000/OS_TICKS_PER_SEC;					 //注意：SysTick时钟配置改变 也要改变
	#else 
	 #error "HQS_Err0001: 选择μCOS版本错误或未选择 "
    #endif
  #endif  
		
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	             //开启SYSTICK  

}

#endif


#ifndef  HQS_USE_uCOS
/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究 
;函数名称：Delay_us(unsigned long  us)
;使用资源：
;入    口：
;出    口：
;说    明：
;硬件接口:         
;作    者：胡乔申 
;E - mail:huqiaoshen@qq.com
;时    间：201303110947
;修改注释：
;注意事项：必须保证 us<=（2^24）/Scale_us，否则将导致延时间不准确。(SysTick->LOAD为24bit)
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
  未经作者同意授权 造成作者损失 承担相关法律责任
           Copyright (c) 2012-2099 snail  HQS
*********************************************************/
void Delay_us(unsigned long  us)
{
	unsigned long temp;
		    	 
	SysTick->LOAD=us*Scale_us;                         //时间加载   (SysTick->LOAD为24bit)	  		 
	SysTick->VAL=0x00;                                 //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;           //开始倒数	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));                 //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;           //关闭计数器

	SysTick->VAL =0X00;                                //清空计数器	  
}



void Delay_ms(unsigned short ms)
{
 	unsigned long temp;		   
	SysTick->LOAD=(unsigned long)ms*Scale_ms;         //时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;                               //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));                 //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;           //关闭计数器
	SysTick->VAL =0X00;                                //清空计数器	  
}
#else
 	   
void Delay_us(unsigned long us)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;

	u32 reload=SysTick->LOAD;	                       //LOAD的值 (计数器到0后重装值)	    	 
	ticks=us*Scale_us; 			                       //需要的节拍数
		  		 
	tcnt=0;
	told=SysTick->VAL;        	                       //刚进入时的计数器值（当前计数器值）
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;              //这里注意一下SYSTICK是一个递减的计数器就可以了.
			 else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)  
			  break;                                   //时间超过/等于要延迟的时间,则退出.
		}  
	} 									    
}



//延时nms
//nms:要延时的ms数
void Delay_ms(unsigned short ms)
{	
   #if HQS_uC0S_Ver == 3
    OS_ERR err;
   #endif

#if HQS_uC0S_Ver == 2
 					   //OS时钟!=1ms 基准
   if(OSRunning)                                       //如果os已经运行	    
	{
    #if OS_TICKS_PER_SEC != 1000	  
	  OSTimeDly(ms/Scale_ms);                          //ucos延时		
	  ms%=Scale_ms;
	  if(ms!=0)   
	  Delay_us((unsigned long)(ms*1000));	               //普通方式延时,此时ucos无法启动调度.
	  #else											   //OS时钟=1ms 基准
	  OSTimeDly(ms);
	}
    #endif
 
#else 
 #if HQS_uC0S_Ver == 3
    
    if(OSRunning)                                      //如果os已经在跑了	    
	{
	 #if OS_CFG_TICK_RATE_HZ!= 1000 					   //OS时钟!=1ms 基准
	  OSTimeDly(ms/Scale_ms,OS_OPT_TIME_DLY,&err);     //ucos延时		
	  ms%=Scale_ms;
	  if(ms!=0)   
	  Delay_us((unsigned long)(ms*1000));	           //普通方式延时,此时ucos无法启动调度.

	 #else											   //OS时钟=1ms 基准
	  OSTimeDly(ms,OS_OPT_TIME_DLY,&err);
	 #endif
	}
	 
 #else
  #error "HQS_Err0001: 选择μCOS版本错误或未选择 "
 #endif
#endif
	else
	 Delay_us((unsigned long)(ms*1000));	 	                             
}

#endif




void SysTick_Handler(void)	  // SysTick 中断处理 
{
  #ifdef HQS_USE_uCOS     //条件编译	 启动uCOS系统 编译				   
	
	OSIntEnter();		      //进入中断
  OSTimeTick();         //调用os的时钟服务程序               
  OSIntExit();          //触发任务切换软中断
	  
  #endif
}

/**************************************
不同编译器 对printf 函数支持


/**************************************/
#define HQS_STM32_PRINTF       1          //1支持  0不支持
#define HQS_STM32_PRINTF_RORT  USART1     //对应stm32串口


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
//标准库需要的支持函数                 
struct __FILE
{
	int handle;

};
FILE __stdout;
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x)
{
	x = x;
}
//重定义fputc函数 
int fputc(int ch, FILE *f)
{
	while (USART_GetFlagStatus(HQS_STM32_PRINTF_RORT, USART_FLAG_TC) == RESET);
	USART_SendData(HQS_STM32_PRINTF_RORT, (uint8_t)ch);
	return ch;
}


#endif
#endif

