
#include "msgHQS.h"

msgQueueInfoHQS_t * msgQueueInfoHQSCreate(FillModeHQS_m fillMode, uint8 fluidic, FluidicModeHQS_m fluidicMode)
{
	msgQueueInfoHQS_t * msgQueueAdd;
	msgQueueAdd = HQSmemPithyMalloc(sizeof(msgQueueInfoHQS_t));
	if (msgQueueAdd == NULL) //内存分配失败
	{
		return msgQueueAdd;
	}
	msgQueueAdd->hdr          =  NULL;
	msgQueueAdd->end          =  NULL;
	msgQueueAdd->fillMode     = fillMode;
	msgQueueAdd->fluidic      = fluidic;
	msgQueueAdd->fluidicCount = 0;
	msgQueueAdd->fluidicMode  = fluidicMode;

	return msgQueueAdd;
}


Msg_Err_m msgSendHQS(msgQueueInfoHQS_t * msgQueueName, uint16 dataSize,void * dataAdd)
{
	Msg_Err_m err = Msg_Err_OK;
	msgPackHQS_t *msgPack;
	msgPackHQS_t *msgPackDel; //要删除包地址

	msgPackHQS_t * prev ; //上一个
	msgPackHQS_t * pres ; //当前

	uint8 count;

	if(dataAdd == NULL)
	{
		err = Msg_Err_QueueName;
		return err;
	}

	if (msgQueueName == NULL)
	{
		HQSmemPithyFree(dataAdd); //删除消息包数据
		err = Msg_Err_QueueName;
		return err;
	}

	msgPack = HQSmemPithyMalloc(sizeof(msgPackHQS_t));

	if (msgPack == NULL)
	{
		HQSmemPithyFree(dataAdd); //删除消息包数据
		err = Msg_Err_msgPackmem;
		return  err; //空间不足
	}

	msgPack->msgDataAdd = dataAdd;
	msgPack->next = NULL;
	msgPack ->dataSize = dataSize;


	if ((msgQueueName->fluidicCount) >= (msgQueueName->fluidic)) //达到 列队流控数
	{
		switch (msgQueueName->fluidicMode)
		{
		case FLU_FIFO_RENOUNCE:
			msgPackDel = (msgPackHQS_t *)(msgQueueName->hdr); //队列去除的包
			msgQueueName->hdr = ((msgPackHQS_t *)(msgQueueName->hdr))->next; //
			((msgPackHQS_t *)(msgQueueName->end))->next = msgPack; //原来列队未包 指向此包
			msgQueueName->end = msgPack; //列队末尾也指向此包
			break;
		case  FLU_LIFO_RENOUNCE:

			 msgPackDel = (msgPackHQS_t *)(msgQueueName->end);//队列去除的包
			 pres = prev = (msgPackHQS_t *)msgQueueName->hdr; 
			 count = 0;
			 //寻找列对 倒数第二的 消息包
				do
				{
					count++;
					if (pres->next != NULL)
					{
						prev = pres;
						pres = pres->next;
					}
					else
					{
						if (count != msgQueueName->fluidicCount) //数量验证HQS
						{
							err = Msg_Err_Queue;//列队出错 致命错误
							msgPackDel = msgPack;
							while (1);
							break;
						}

						prev->next = NULL; //倒数第二个 包变成最末尾的包，next 为NULL
						msgQueueName->end = prev;

						msgPack->next = msgQueueName->hdr;
						msgQueueName->hdr = msgPack;
						break;
					}

				} while (1);
			break;

		case FLU_RENOUNCE:
		
			msgPackDel = msgPack;
			err = Msg_Err_Renounce;
			break;
		default:
			break;
		}
		HQSmemPithyFree(msgPackDel->msgDataAdd); //释放消息数据空间（用户必须用memPithyHQS 申请空间）
		HQSmemPithyFree(msgPackDel);             //删除消息包

	}
	else
	{
		if (msgQueueName->fillMode == FLU_LIFO_FILL)
		{
			//LIFO
			if (msgQueueName->hdr)
			{
				msgPack->next = msgQueueName->hdr;
				msgQueueName->hdr = msgPack;
				
			}
			else
			{
				if (msgQueueName->fluidicCount != 0 || msgQueueName->end != NULL) //验证 可去除
				{
					err = Msg_Err_Queue;//列队出错
					while (1);
				}
				else
				{
					msgQueueName->hdr = msgQueueName->end = msgPack; //列队头尾都指向此包
					
				}
			}
		}
		else
		{
			//FIFO
			if (msgQueueName->end)
			{
				((msgPackHQS_t *)(msgQueueName->end))->next = msgPack; //原来列队包 指向此包
				msgQueueName->end = msgPack; //列队末尾也指向此包
				
			}
			else
			{
				if (msgQueueName->fluidicCount != 0 || msgQueueName->hdr != NULL) //验证 可去除
				{
					err = Msg_Err_Queue;//列队出错
					while (1);
				}
				else
				{
					msgQueueName->hdr = msgQueueName->end = msgPack; //列队头尾都指向此包
					
				}
			}
		}

		msgQueueName->fluidicCount += 1;

		if (err == Msg_Err_Queue)
		{
			HQSmemPithyFree(msgPack->msgDataAdd); //释放消息数据空间（用户必须用memPithyHQS 申请空间）
			HQSmemPithyFree(msgPack); //删除消息包
		}
	}
	return err;
}


void * msgReceive(msgQueueInfoHQS_t * msgQueueName)
{
	msgPackHQS_t *msgPack;
	void * dataAdd=NULL;
	msgPack = msgPakcReceive(msgQueueName);
	if (msgPack)
	{
		dataAdd = msgPack->msgDataAdd;
		HQSmemPithyFree(msgPack);
	}
	return dataAdd;
}

msgPackHQS_t * msgPakcReceive(msgQueueInfoHQS_t * msgQueueName)
{
	msgPackHQS_t * msgPack =NULL;
	msgPackHQS_t * msgPackTemp = NULL;
	if (msgQueueName->hdr == NULL)
	{
		if (msgQueueName->end == NULL)
		{
			return NULL;
		}
		else
		{
			while (1);
		}

	}
	else
	{
		msgPack = (msgPackHQS_t *)(msgQueueName->hdr); //队列剥离包
		msgQueueName->fluidicCount--;
		msgPackTemp = ((msgPackHQS_t *)(msgQueueName->hdr))->next;
		if (msgPackTemp)
		{
			if (msgQueueName->fluidicCount)
			{
				msgQueueName->hdr = msgPackTemp; //
			}
			else
			{
				while (1);
			}
		}
		else
		{
			if (msgQueueName->fluidicCount == 0) //验证 可去除
			{
				msgQueueName->end = msgQueueName->hdr = msgPackTemp; //
			}
			else
			{
				while (1);
			}
		}
		msgPack->next = NULL;//防止用户得到
		return msgPack;
	}
}

void  msgPakcDataDel(msgPackHQS_t * msgPack) 
{
	if (msgPack)
	{
		HQSmemPithyFree(msgPack->msgDataAdd);
		HQSmemPithyFree(msgPack);
	}
}







