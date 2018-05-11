
#include "RTCHAL.h"
#include "USART1.h"
#include "TimeHQS.h"


void RTCHALIint(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	NVIC_InitTypeDef NVIC_InitStruct;

	PWR_BackupAccessCmd(ENABLE); //使能后备寄存器访问

	/*晶振*/
	RCC_LSEConfig(RCC_LSE_ON);   //打开外部低速时钟
//	RCC_LSICmd(ENABLE);  //内部
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)  //等待低速 可以判断晶振是否正常
	{
		USART1_Send_String("晶振");
	}

	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);  //设置RTC时钟

	RCC_RTCCLKCmd(ENABLE); //使能 RTC 时钟


//	RTC_WaitForSynchro();  //等待 RTC 等待 RTC_CNT、 RTC_ALR或RTC_PRL已经被同步。
//	RTC_WaitForLastTask(); //等待最近一次对 RTC 寄存器的写操作完成


	RTC_EnterConfigMode(); // 允许配置

 	RTC_WaitForLastTask(); //等待最近一次对 RTC 寄存器的写操作完成

	RTC_SetPrescaler(32767); //设置 RTC 

	RTC_WaitForLastTask(); //等待最近一次对 RTC 寄存器的写操作完成
	RTC_SetCounter(0); //设置 RTC 计数器的值
	RTC_WaitForLastTask(); //等待最近一次对 RTC 寄存器的写操作完成
	RTC_WaitForSynchro();  //等待 RTC 等待 RTC_CNT、 RTC_ALR或RTC_PRL已经被同步。

	RTC_ExitConfigMode(); //退出配置模式

	PWR_BackupAccessCmd(DISABLE); //使能后备寄存器访问


	 //RCT 中断分组设置
	NVIC_InitStruct.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);//中断配置
	RTC_ITConfig(RTC_IT_SEC, ENABLE); //使能 RTC 秒中断

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE);

}


void RTCHLSetCounter(uint32 count)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR |RCC_APB1Periph_BKP, ENABLE); //使能 PWR 和 BKP 外设时钟
	PWR_BackupAccessCmd(ENABLE); //使能 RTC 和后备寄存器访问
	
	
	RTC_EnterConfigMode();  // 允许配置
	RTC_WaitForLastTask();  //等待最近一次对 RTC 寄存器的写操作完成
	RTC_SetCounter(count);  //设置 RTC 计数器的值
	RTC_WaitForSynchro();   //等待 RTC_CNT、 RTC_ALR或RTC_PRL已经被同步。

	RTC_ExitConfigMode();   //退出配置模式

	RTC->CRL &= (uint16_t)~RTC_FLAG_RSF;

	PWR_BackupAccessCmd(DISABLE); //使能 RTC 和后备寄存器访问
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE); //使能 PWR 和 BKP 外设时钟
}


uint32  RTCHLGetCounter(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); //使能 PWR 和 BKP 外设时钟
	PWR_BackupAccessCmd(ENABLE); //使能 RTC 和后备寄存器访问

	uint32 data = RTC_GetCounter();

	PWR_BackupAccessCmd(DISABLE); //使能 RTC 和后备寄存器访问
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE); //使能 PWR 和 BKP 外设时钟

	return data;
	
}



void RTC_IRQHandler(void)
{
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET) //秒钟中断
	{
	     //更新时间
		//USART1_Send_String("1");
		TimeHQSGetDateTime();
	}
	if (RTC_GetITStatus(RTC_IT_ALR) != RESET) //闹钟中断
	{
		

	}
	if (RTC_GetITStatus(RTC_IT_OW) != RESET) //溢出中断
	{


	}
	RTC_ClearITPendingBit(RTC_IT_SEC | RTC_IT_OW | RTC_IT_OW); //清闹钟中断

}