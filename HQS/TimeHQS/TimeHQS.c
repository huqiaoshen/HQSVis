#include "TimeHQS.h"

//�·�������
const u8 MonDayT[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


//�����ж�
bool TimeHQSisLeapYear(uint16 year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return TRUE;
			else
				return FALSE;
		}
		else return TRUE;
	}
	else return FALSE;
}


//ʱ������
void TimeHQSSetDateTime(uint16 year, uint8	month, uint8	day, uint8	hour, uint8	min, uint8	sec)
{

	uint32 secCount = 0;
	uint16 yearMemory;
	uint8  STMyear  = (uint8)year; //0-127�� ͨ��STM32F1 RTC����

	while (STMyear)
	{
		if (TimeHQSisLeapYear(year))
		{
			secCount += YEARSecLeap;
		}
		else
		{
			secCount += YEARSecNonleap;
		}
		STMyear--;
	}

	month -= 1;
	for (int8 i = 0; i<month; i++)
	{
		secCount += (u32)MonDayT[i] * DAYSec;
		if ((TimeHQSisLeapYear(year)) && i== 1)
		  secCount += DAYSec;
	}
	secCount += (u32)(day - 1) * DAYSec;
	secCount += (u32)hour * HOURSec;
	secCount += (u32)min  * MINSec;
	secCount += sec;
	RTCHLSetCounter(secCount);
	//���� ���
	yearMemory = year & (~0x007F);
}

//���ʱ������
TimeDate_t TimeHQSGetDateTime(void)
{
	TimeDate_t timeDate;

	static uint16 dayRunRTC = 0;

	uint32 secCount = 0;	
	//��� RTC �����
	secCount = RTCHLGetCounter();

	uint32 daySecTmp;
	uint16 yearTmp;
	uint16 yearMemory;


	//�ȵ����е�����
	 daySecTmp = secCount / DAYSec;

	//����һ�� ��������
	if (dayRunRTC != daySecTmp)
	{
		dayRunRTC = daySecTmp;


		//��ȡ������
		yearMemory = 2000;

		//������ͳ��
		while (daySecTmp >= 365)
		{
			if (TimeHQSisLeapYear(yearMemory + yearTmp))
			{
				if (daySecTmp >= 366)
					daySecTmp -= 366;
				else
				{
					yearTmp++;
					break;
				}
			}
			else
			{
				daySecTmp -= 365;
				yearTmp++;
			}
		}

		//������
		timeDate.year = yearTmp + yearMemory;

		int8 momTmp=0;
		//����� ����
		while (daySecTmp >= 28)
		{
			if (TimeHQSisLeapYear(timeDate.year) && momTmp == 1)
			{
				if (daySecTmp >= 29)
				    daySecTmp -= 29;
				else
					break;
			}
			else
			{
				if (daySecTmp  >= MonDayT[momTmp])
					daySecTmp -= MonDayT[momTmp];
				else 
					break;
			}
			momTmp++;
		}

		//������
		timeDate.month = momTmp    + 1;
		//������
		timeDate.day   = daySecTmp + 1;
		



		if (yearTmp > 127) //����ʱ���Ѿ����� 127 ��
		{
			//���������� ���� ��0 ��ʼ���ñ�־

			//�ȵ�һ��ʣ�µ�����
			daySecTmp = secCount % DAYSec;
			//Сʱ
			timeDate.hour = daySecTmp / 3600;
			//����
			timeDate.min = (daySecTmp % 3600) / 60;
			//��
			timeDate.sec = (daySecTmp % 3600) % 60;

			TimeHQSSetDateTime(timeDate.year, timeDate.month, timeDate.day, timeDate.hour, timeDate.min, timeDate.sec);

			return timeDate;
		}
	}

	//�ȵ�һ��ʣ�µ�����
	daySecTmp = secCount % DAYSec;
	//Сʱ
	timeDate.hour = daySecTmp / 3600;
	//����
	timeDate.min = (daySecTmp % 3600) / 60;
	//��
	timeDate.sec = (daySecTmp % 3600) % 60;

	return timeDate;

}






