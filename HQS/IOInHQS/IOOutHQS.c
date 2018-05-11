#include "IOOutHQS.h"

IoOutHQSCreateUse_m IoOutCreateUseMAX = IOOUT_END_MAX;
IoOutHQSControl_t   IoOutControl[IOOUT_END_MAX];


#if  HQSIOOUT_CLOCK
#define HQSIoOutGetClock_MACRO()  HQSIoOutGetClock()
volatile uint32 IoOutClock=0;
uint32 HQSIoOutGetClock(void)
{
	return IoOutClock;
}

void HQSIoOutClockUpDate(void)
{
	IoOutClock++;
}
#endif



void HQSIoOutIint(void)
{
   int16  i;
   for (i=0;i<IoOutCreateUseMAX; i++)
   {
	   (IoOutControl + i)->model = IOOUTHQS_MODE_ATTONITY;
   }
}


void HQSIoOutSet(IoOutHQSCreateUse_m ioUse, IoOutHQSModel_m model, int32 delay)
{
	switch (model)
	{
	case IOOUTHQS_MODE_ON:
	case IOOUTHQS_MODE_OFF:
		if (delay)  //延时
		{
			(IoOutControl + ioUse)->actionTime = HQSIoOutGetClock_MACRO()+delay; //动作时间点 =当前时间 + 延时时间
			(IoOutControl + ioUse)->model = model;
		}
		else //无延时
		{
			if (model==IOOUTHQS_MODE_ON)
			{
				//调用IO控制函数  置一
				HQSIoOutContrl_MACRO(ioUse, HQSIOOUTlevel_H);
			}
			else
			{
				////调用IO控制函数 置零
				HQSIoOutContrl_MACRO(ioUse, HQSI0OUTlevel_L);
			}
			(IoOutControl + ioUse)->model = IOOUTHQS_MODE_ATTONITY;
		}

		break;
	case IOOUTHQS_MODE_BLINKH:
	case IOOUTHQS_MODE_BLINKL:
	case IOOUTHQS_MODE_BLINK:
		if (delay>1)  //周期时间 至少有两个周期
		{
			(IoOutControl + ioUse)->actionTime= HQSIoOutGetClock_MACRO();  //获得当前时间，直接 由Updata 更新时间；
			(IoOutControl + ioUse)->period    =  delay;
			(IoOutControl + ioUse)->highRatio =  50;
			(IoOutControl + ioUse)->count     =  1;
			(IoOutControl + ioUse)->model     =  model;
            (IoOutControl + ioUse)->model |= IOOUTHQS_MODE_ON;
		}
		else //无周期
		{
			(IoOutControl + ioUse)->model = IOOUTHQS_MODE_ATTONITY;
		}
	default:
		break;
	}
}

void HQSIoOutSetBlink(IoOutHQSCreateUse_m ioUse, IoOutHQSModel_m model, int32 period, uint8 highRatio, uint16 count)
{
	if (model & IOOUTHQS_MODE_ON || model & IOOUTHQS_MODE_OFF)
	{
		HQSIoOutSet(ioUse, model, period);
	}
	else
	{
		if (highRatio >= 100 || highRatio == 0)
		{
			if (highRatio == 0)
			{
				HQSIoOutSet(ioUse, IOOUTHQS_MODE_OFF, 0);
			}
			else
				HQSIoOutSet(ioUse, IOOUTHQS_MODE_ON, 0);
		}
		else
		{
			if (period < 2 || period*highRatio / 100 == 0 || period*(100 - highRatio) / 100 == 0)
			{
				if (model&IOOUTHQS_MODE_BLINKH)
				{
					HQSIoOutSet(ioUse, IOOUTHQS_MODE_ON, 0);
				}
				if (model&IOOUTHQS_MODE_BLINKL)
				{
					HQSIoOutSet(ioUse, IOOUTHQS_MODE_OFF, 0);
				}
				(IoOutControl + ioUse)->model = IOOUTHQS_MODE_ATTONITY;
			}
			else
			{
				(IoOutControl + ioUse)->period    = period;
				(IoOutControl + ioUse)->highRatio = highRatio;
				(IoOutControl + ioUse)->count     = count;
				(IoOutControl + ioUse)->model     = model;
				(IoOutControl + ioUse)->model     |= IOOUTHQS_MODE_ON;
				if (count == 0)
				{
					if (model&IOOUTHQS_MODE_BLINKH)
					{
						HQSIoOutSet(ioUse, IOOUTHQS_MODE_ON, 0);
					}
					if (model&IOOUTHQS_MODE_BLINKL)
					{
						HQSIoOutSet(ioUse, IOOUTHQS_MODE_OFF, 0);
					}
				}
				(IoOutControl + ioUse)->actionTime = HQSIoOutGetClock_MACRO();
			}
		}
	}
}


void HQSIoOutUpDate(void)
{
	int16 i;
	for (i = 0; i<IoOutCreateUseMAX; i++)
	{
	  if ((IoOutControl + i)->model) //有动作需执行
	  {
		  if ((IoOutControl + i)->actionTime == HQSIoOutGetClock_MACRO()) //到达动作时间点
		  {
			  if (((IoOutControl + i)->model) & (IOOUTHQS_MODE_BLINKH | IOOUTHQS_MODE_BLINKL | IOOUTHQS_MODE_BLINK))  //闪烁
			  {  
				  if (((IoOutControl + i)->model) & IOOUTHQS_MODE_ON)
				  {
					  if ((((IoOutControl + i)->model) & IOOUTHQS_MODE_BLINK)!= IOOUTHQS_MODE_BLINK) //不是循环闪烁
					  {
						  if ((IoOutControl + i)->count == 0) //闪烁次数完成
						  {
							  if(((IoOutControl + i)->model & IOOUTHQS_MODE_BLINKH) == IOOUTHQS_MODE_BLINKH)
							  {
								  //调用IO控制函数 IO置一
								  HQSIoOutContrl_MACRO(i, HQSIOOUTlevel_H);
								  (IoOutControl + i)->model = IOOUTHQS_MODE_ATTONITY; //无动作执行
							  }
							  else
							  {
								  //调用IO控制函数 IO置零
								   HQSIoOutContrl_MACRO(i, HQSI0OUTlevel_L);
								  (IoOutControl + i)->model = IOOUTHQS_MODE_ATTONITY;//无动作执行
							  }
						  }
						  else
						  {
							   HQSIoOutContrl_MACRO(i, HQSIOOUTlevel_H);
							  (IoOutControl + i)->count--; //设置的适合需要
							  (IoOutControl + i)->model ^= IOOUTHQS_MODE_ON;
							  (IoOutControl + i)->model |= IOOUTHQS_MODE_OFF;  //接下来动作模式
						  }
					  }	
					  else
					  {
						  //调用IO控制函数 本次处理置一
						  HQSIoOutContrl_MACRO(i, HQSIOOUTlevel_H);
						  (IoOutControl + i)->model ^= IOOUTHQS_MODE_ON;
						  (IoOutControl + i)->model |= IOOUTHQS_MODE_OFF;  //接下来动作模式
					  }
					  (IoOutControl + i)->actionTime = HQSIoOutGetClock_MACRO() + ((IoOutControl + i)->period) * ((IoOutControl + i)->highRatio) / 100;//接下来动作时间点
				  }
				  else
				  {
					  if (((IoOutControl + i)->model) & IOOUTHQS_MODE_OFF)
					  {
						  //调用IO控制函数 本次处理置零
						  HQSIoOutContrl_MACRO(i, HQSI0OUTlevel_L);
						  (IoOutControl + i)->actionTime = HQSIoOutGetClock_MACRO() + ((IoOutControl + i)->period) * ((100 - (IoOutControl + i)->highRatio)) / 100; //接下来动作时间点
						  (IoOutControl + i)->model ^= IOOUTHQS_MODE_OFF;
						  (IoOutControl + i)->model |= IOOUTHQS_MODE_ON; //接下来IO动作 模式

					  }
				  }
			  }
			  else
			  {
				  if (((IoOutControl + i)->model) & IOOUTHQS_MODE_ON)
				  {
					  //调用IO控制函数 置一
					  HQSIoOutContrl_MACRO(i, HQSIOOUTlevel_H);
					  (IoOutControl + i)->model = IOOUTHQS_MODE_ATTONITY;
				  }
				  if (((IoOutControl + i)->model) & IOOUTHQS_MODE_OFF)
				  {
					  //调用IO控制函数 置零
					  HQSIoOutContrl_MACRO(i, HQSI0OUTlevel_L);
					  (IoOutControl + i)->model = IOOUTHQS_MODE_ATTONITY;
				  }
			  }
		  }
	  }
	}
#if  HQSIOOUT_CLOCK
	HQSIoOutClockUpDate();
#endif
}









