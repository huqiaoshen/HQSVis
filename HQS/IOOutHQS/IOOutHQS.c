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
		if (delay)  //��ʱ
		{
			(IoOutControl + ioUse)->actionTime = HQSIoOutGetClock_MACRO()+delay; //����ʱ��� =��ǰʱ�� + ��ʱʱ��
			(IoOutControl + ioUse)->model = model;
		}
		else //����ʱ
		{
			if (model==IOOUTHQS_MODE_ON)
			{
				//����IO���ƺ���  ��һ
				HQSIoOutContrl_MACRO(ioUse, HQSIOOUTlevel_H);
			}
			else
			{
				////����IO���ƺ��� ����
				HQSIoOutContrl_MACRO(ioUse, HQSI0OUTlevel_L);
			}
			(IoOutControl + ioUse)->model = IOOUTHQS_MODE_ATTONITY;
		}

		break;
	case IOOUTHQS_MODE_BLINKH:
	case IOOUTHQS_MODE_BLINKL:
	case IOOUTHQS_MODE_BLINK:
		if (delay>1)  //����ʱ�� ��������������
		{
			(IoOutControl + ioUse)->actionTime= HQSIoOutGetClock_MACRO();  //��õ�ǰʱ�䣬ֱ�� ��Updata ����ʱ�䣻
			(IoOutControl + ioUse)->period    =  delay;
			(IoOutControl + ioUse)->highRatio =  50;
			(IoOutControl + ioUse)->count     =  1;
			(IoOutControl + ioUse)->model     =  model;
            (IoOutControl + ioUse)->model |= IOOUTHQS_MODE_ON;
		}
		else //������
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
	  if ((IoOutControl + i)->model) //�ж�����ִ��
	  {
		  if ((IoOutControl + i)->actionTime == HQSIoOutGetClock_MACRO()) //���ﶯ��ʱ���
		  {
			  if (((IoOutControl + i)->model) & (IOOUTHQS_MODE_BLINKH | IOOUTHQS_MODE_BLINKL | IOOUTHQS_MODE_BLINK))  //��˸
			  {  
				  if (((IoOutControl + i)->model) & IOOUTHQS_MODE_ON)
				  {
					  if ((((IoOutControl + i)->model) & IOOUTHQS_MODE_BLINK)!= IOOUTHQS_MODE_BLINK) //����ѭ����˸
					  {
						  if ((IoOutControl + i)->count == 0) //��˸�������
						  {
							  if(((IoOutControl + i)->model & IOOUTHQS_MODE_BLINKH) == IOOUTHQS_MODE_BLINKH)
							  {
								  //����IO���ƺ��� IO��һ
								  HQSIoOutContrl_MACRO(i, HQSIOOUTlevel_H);
								  (IoOutControl + i)->model = IOOUTHQS_MODE_ATTONITY; //�޶���ִ��
							  }
							  else
							  {
								  //����IO���ƺ��� IO����
								   HQSIoOutContrl_MACRO(i, HQSI0OUTlevel_L);
								  (IoOutControl + i)->model = IOOUTHQS_MODE_ATTONITY;//�޶���ִ��
							  }
						  }
						  else
						  {
							   HQSIoOutContrl_MACRO(i, HQSIOOUTlevel_H);
							  (IoOutControl + i)->count--; //���õ��ʺ���Ҫ
							  (IoOutControl + i)->model ^= IOOUTHQS_MODE_ON;
							  (IoOutControl + i)->model |= IOOUTHQS_MODE_OFF;  //����������ģʽ
						  }
					  }	
					  else
					  {
						  //����IO���ƺ��� ���δ�����һ
						  HQSIoOutContrl_MACRO(i, HQSIOOUTlevel_H);
						  (IoOutControl + i)->model ^= IOOUTHQS_MODE_ON;
						  (IoOutControl + i)->model |= IOOUTHQS_MODE_OFF;  //����������ģʽ
					  }
					  (IoOutControl + i)->actionTime = HQSIoOutGetClock_MACRO() + ((IoOutControl + i)->period) * ((IoOutControl + i)->highRatio) / 100;//����������ʱ���
				  }
				  else
				  {
					  if (((IoOutControl + i)->model) & IOOUTHQS_MODE_OFF)
					  {
						  //����IO���ƺ��� ���δ�������
						  HQSIoOutContrl_MACRO(i, HQSI0OUTlevel_L);
						  (IoOutControl + i)->actionTime = HQSIoOutGetClock_MACRO() + ((IoOutControl + i)->period) * ((100 - (IoOutControl + i)->highRatio)) / 100; //����������ʱ���
						  (IoOutControl + i)->model ^= IOOUTHQS_MODE_OFF;
						  (IoOutControl + i)->model |= IOOUTHQS_MODE_ON; //������IO���� ģʽ

					  }
				  }
			  }
			  else
			  {
				  if (((IoOutControl + i)->model) & IOOUTHQS_MODE_ON)
				  {
					  //����IO���ƺ��� ��һ
					  HQSIoOutContrl_MACRO(i, HQSIOOUTlevel_H);
					  (IoOutControl + i)->model = IOOUTHQS_MODE_ATTONITY;
				  }
				  if (((IoOutControl + i)->model) & IOOUTHQS_MODE_OFF)
				  {
					  //����IO���ƺ��� ����
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








