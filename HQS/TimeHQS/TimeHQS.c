#include "TimeHQS.h"

//月份天数表
const u8 MonDayT[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


//闰年判断
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


//时间设置
void TimeHQSSetDateTime(uint16 year, uint8	month, uint8	day, uint8	hour, uint8	min, uint8	sec)
{

	uint32 secCount = 0;
	uint16 yearMemory;
	uint8  STMyear  = (uint8)year; //0-127年 通过STM32F1 RTC计数

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
	//保存 年份
	yearMemory = year & (~0x007F);
}

//获得时间日期
TimeDate_t TimeHQSGetDateTime(void)
{
	TimeDate_t timeDate;

	static uint16 dayRunRTC = 0;

	uint32 secCount = 0;	
	//获得 RTC 秒计数
	secCount = RTCHLGetCounter();

	uint32 daySecTmp;
	uint16 yearTmp;
	uint16 yearMemory;


	//等到运行的天数
	 daySecTmp = secCount / DAYSec;

	//超过一天 更新年月
	if (dayRunRTC != daySecTmp)
	{
		dayRunRTC = daySecTmp;


		//获取年数据
		yearMemory = 2000;

		//运行年统计
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

		//年数据
		timeDate.year = yearTmp + yearMemory;

		int8 momTmp=0;
		//获得月 、日
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

		//月数据
		timeDate.month = momTmp    + 1;
		//日数据
		timeDate.day   = daySecTmp + 1;
		



		if (yearTmp > 127) //运行时间已经超过 127 年
		{
			//计数器重新 设置 从0 开始设置标志

			//等到一天剩下的秒数
			daySecTmp = secCount % DAYSec;
			//小时
			timeDate.hour = daySecTmp / 3600;
			//分钟
			timeDate.min = (daySecTmp % 3600) / 60;
			//秒
			timeDate.sec = (daySecTmp % 3600) % 60;

			TimeHQSSetDateTime(timeDate.year, timeDate.month, timeDate.day, timeDate.hour, timeDate.min, timeDate.sec);

			return timeDate;
		}
	}

	//等到一天剩下的秒数
	daySecTmp = secCount % DAYSec;
	//小时
	timeDate.hour = daySecTmp / 3600;
	//分钟
	timeDate.min = (daySecTmp % 3600) / 60;
	//秒
	timeDate.sec = (daySecTmp % 3600) % 60;

	return timeDate;

}







