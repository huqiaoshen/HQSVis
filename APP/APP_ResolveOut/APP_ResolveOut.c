#include "APP_ResolveOut.h"
#include "IOOutHQS.h"
#include <string.h>

int8 resolveIint(void)
{
	//创建消息列队
	resolveMsgQueue= msgQueueInfoHQSCreate(FLU_FIFO_FILL, 20, FLU_FIFO_RENOUNCE);
	if (resolveMsgQueue)
	{
		return 0; //成功
	}
	else
		return -1; //失败
}


//获取 处理数据地址 及长度
resolveData_t resolveGet(uint32 dataAddr)
{
	void *add;
	resolveData_t resolveData;
	add = FlashOriginalHALHQS(dataAddr);
	resolveData.len =(uint8) *((uint16*)add);
	add=(uint8*)add + 2;
	resolveData.dataAdd = (void *)add;
	return resolveData;
}


//数据比较
int resolveCompare(uint32 dataAddr ,void * buff ,uint8 buffSize)
{
	int a;
	resolveData_t resolveData;
	resolveData = resolveGet(dataAddr);

	if (buffSize != resolveData.len)
	{
		return -1; //
	}
	a = memcmp(resolveData.dataAdd, buff, buffSize);
	return a;
}

//命令保存
int8 resolveSave(uint32 dataAddr, void * buff, uint8 len)
{
	void * memData;
//	resolveData_t resolveData;
	if (len >= (ResolveOutSize << 1))
	{
		return -1;  //失败 超字节
	}
	memData = HQSmemPithyMalloc(len + 1);
	if (memData)
	{
		*(uint8*)memData = len;
		memcpy((void *)((uint8*)memData + 1), buff, len);

		//resolveData = resolveGet(dataAddr);
		if (len & 0x01)
		{
			len += 1; 
		}

		FlashEEPROMWriteHALHQS(dataAddr, (uint16*)memData, len / 2);


		HQSmemPithyFree(memData);
		return 0;   //成功
	}
	else
	{
		return -1;  //失败
	}
}


//IO执行
void resolveIOOut(void * buff, uint8 buffSize)
{
	uint8 i;
	int ok;
	IoOutHQSCreateUse_m ioUse;
	IoOutHQSModel_m ioModel;

	for (i = 0; i < 16;i++)
	{
		ok = resolveCompare(ResolveOutStart + i*ResolveOutSize, buff, buffSize);
		if (ok == 0)
		{
			ioUse    =  i / 2;
			ioModel  =  i % 2;

			HQSIoOutSet(ioUse + LED_1, ioModel + IOOUTHQS_MODE_ON, 0);
			break;
		}
	}
}


void resolveUpDate(void)
{
	void * dataMsg;
	dataMsg =msgReceive(resolveMsgQueue);
	if (dataMsg) //有数据
	{
		                        //去除数据长度得数据地址         //数据长度
		resolveIOOut((void*)((uint16 *)dataMsg + 1),(uint8) *(uint16 *)dataMsg);
		HQSmemPithyFree(dataMsg);
	}

}







