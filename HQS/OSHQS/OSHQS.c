
#include "OSHQS.h"

static TaskBackFunc     OSHQSInfoFunc[taskHQSQty] = { 0 };  //任务函数列表
static OSHQSevent_m     OSHQSInfoEvent[taskHQSQty] = { 0 };  //任务事件列表
static OSHQSInfoTask_t  InfoTask[taskHQSQty] = {0};
static uint32           TaskCyc[taskHQSQty] = {0};

void OsHQSInit(void)
{
	int i;
	for (i = 0; i<taskHQSQty; i++)
	{
		*(OSHQSInfoFunc + i)  = NULL;
		*(OSHQSInfoEvent + i) = OSNotHQS_Event;
		*(TaskCyc + i)        = 0;
		
	}
}


void OsHQSTaskCreate(uint32 TaskID, TaskBackFunc taskFunc, uint32 cyc)
{
	*(OSHQSInfoFunc + TaskID) = taskFunc;
	*(TaskCyc + TaskID)       = cyc;
	(InfoTask + TaskID) ->cyc = cyc;

}



//任务事件设置
void OsHQSSetEvent(uint32 taskID, OSHQSevent_m event)
{
	*(OSHQSInfoEvent + taskID) = event;
}



void OsHQSleep(UseSleepBackFunc  backFunc)
{
	void * backFuncPre;
  if(backFunc)
  {
	  backFunc(backFuncPre);
  }
}


void OsHQSCycUp(void)
{
	uint32 i;
	for (i = 0; i < taskHQSQty; i++)
	{
		if (*(TaskCyc + i))
		{
			(*(TaskCyc + i))--;
		}
		else
		{
			if ((InfoTask + i)->cyc)
			{
				*(TaskCyc + i) = (InfoTask + i)->cyc;
				OsHQSSetEvent(i, OSTimHQS_Event);
			}
		}
	}
}



void OsHQSRun(void)
{ 
	static uint32 taskId = 0;
	static uint32 test = 0;
	for (;;)
	{
		if (*(OSHQSInfoEvent + taskId))
		{
			OSHQSInfoFunc[taskId]();
			*(OSHQSInfoEvent + taskId) = OSNotHQS_Event;
		}
		taskId++;
		if (taskId == taskHQSQty)
		{
			taskId = 0;
			//空闲 、 休眠 
		}

		test++;
		if (test >= 0x00000F00)
		{
			test = 0;
			OsHQSCycUp();
		}
	}
   
}






