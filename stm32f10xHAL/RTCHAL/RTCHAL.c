
#include "RTCHAL.h"
#include "USART1.h"
#include "TimeHQS.h"


void RTCHALIint(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	NVIC_InitTypeDef NVIC_InitStruct;

	PWR_BackupAccessCmd(ENABLE); //ʹ�ܺ󱸼Ĵ�������

	/*����*/
	RCC_LSEConfig(RCC_LSE_ON);   //���ⲿ����ʱ��
//	RCC_LSICmd(ENABLE);  //�ڲ�
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)  //�ȴ����� �����жϾ����Ƿ�����
	{
		USART1_Send_String("����");
	}

	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);  //����RTCʱ��

	RCC_RTCCLKCmd(ENABLE); //ʹ�� RTC ʱ��


//	RTC_WaitForSynchro();  //�ȴ� RTC �ȴ� RTC_CNT�� RTC_ALR��RTC_PRL�Ѿ���ͬ����
//	RTC_WaitForLastTask(); //�ȴ����һ�ζ� RTC �Ĵ�����д�������


	RTC_EnterConfigMode(); // ��������

 	RTC_WaitForLastTask(); //�ȴ����һ�ζ� RTC �Ĵ�����д�������

	RTC_SetPrescaler(32767); //���� RTC 

	RTC_WaitForLastTask(); //�ȴ����һ�ζ� RTC �Ĵ�����д�������
	RTC_SetCounter(0); //���� RTC ��������ֵ
	RTC_WaitForLastTask(); //�ȴ����һ�ζ� RTC �Ĵ�����д�������
	RTC_WaitForSynchro();  //�ȴ� RTC �ȴ� RTC_CNT�� RTC_ALR��RTC_PRL�Ѿ���ͬ����

	RTC_ExitConfigMode(); //�˳�����ģʽ

	PWR_BackupAccessCmd(DISABLE); //ʹ�ܺ󱸼Ĵ�������


	 //RCT �жϷ�������
	NVIC_InitStruct.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);//�ж�����
	RTC_ITConfig(RTC_IT_SEC, ENABLE); //ʹ�� RTC ���ж�

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE);

}


void RTCHLSetCounter(uint32 count)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR |RCC_APB1Periph_BKP, ENABLE); //ʹ�� PWR �� BKP ����ʱ��
	PWR_BackupAccessCmd(ENABLE); //ʹ�� RTC �ͺ󱸼Ĵ�������
	
	
	RTC_EnterConfigMode();  // ��������
	RTC_WaitForLastTask();  //�ȴ����һ�ζ� RTC �Ĵ�����д�������
	RTC_SetCounter(count);  //���� RTC ��������ֵ
	RTC_WaitForSynchro();   //�ȴ� RTC_CNT�� RTC_ALR��RTC_PRL�Ѿ���ͬ����

	RTC_ExitConfigMode();   //�˳�����ģʽ

	RTC->CRL &= (uint16_t)~RTC_FLAG_RSF;

	PWR_BackupAccessCmd(DISABLE); //ʹ�� RTC �ͺ󱸼Ĵ�������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE); //ʹ�� PWR �� BKP ����ʱ��
}


uint32  RTCHLGetCounter(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); //ʹ�� PWR �� BKP ����ʱ��
	PWR_BackupAccessCmd(ENABLE); //ʹ�� RTC �ͺ󱸼Ĵ�������

	uint32 data = RTC_GetCounter();

	PWR_BackupAccessCmd(DISABLE); //ʹ�� RTC �ͺ󱸼Ĵ�������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE); //ʹ�� PWR �� BKP ����ʱ��

	return data;
	
}



void RTC_IRQHandler(void)
{
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET) //�����ж�
	{
	     //����ʱ��
		//USART1_Send_String("1");
		TimeHQSGetDateTime();
	}
	if (RTC_GetITStatus(RTC_IT_ALR) != RESET) //�����ж�
	{
		

	}
	if (RTC_GetITStatus(RTC_IT_OW) != RESET) //����ж�
	{


	}
	RTC_ClearITPendingBit(RTC_IT_SEC | RTC_IT_OW | RTC_IT_OW); //�������ж�

}