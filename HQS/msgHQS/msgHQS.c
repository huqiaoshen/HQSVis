
#include "msgHQS.h"

msgQueueInfoHQS_t * msgQueueInfoHQSCreate(FillModeHQS_m fillMode, uint8 fluidic, FluidicModeHQS_m fluidicMode)
{
	msgQueueInfoHQS_t * msgQueueAdd;
	msgQueueAdd = HQSmemPithyMalloc(sizeof(msgQueueInfoHQS_t));
	if (msgQueueAdd == NULL) //�ڴ����ʧ��
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
	msgPackHQS_t *msgPackDel; //Ҫɾ������ַ

	msgPackHQS_t * prev ; //��һ��
	msgPackHQS_t * pres ; //��ǰ

	uint8 count;

	if(dataAdd == NULL)
	{
		err = Msg_Err_QueueName;
		return err;
	}

	if (msgQueueName == NULL)
	{
		HQSmemPithyFree(dataAdd); //ɾ����Ϣ������
		err = Msg_Err_QueueName;
		return err;
	}

	msgPack = HQSmemPithyMalloc(sizeof(msgPackHQS_t));

	if (msgPack == NULL)
	{
		HQSmemPithyFree(dataAdd); //ɾ����Ϣ������
		err = Msg_Err_msgPackmem;
		return  err; //�ռ䲻��
	}

	msgPack->msgDataAdd = dataAdd;
	msgPack->next = NULL;
	msgPack ->dataSize = dataSize;


	if ((msgQueueName->fluidicCount) >= (msgQueueName->fluidic)) //�ﵽ �ж�������
	{
		switch (msgQueueName->fluidicMode)
		{
		case FLU_FIFO_RENOUNCE:
			msgPackDel = (msgPackHQS_t *)(msgQueueName->hdr); //����ȥ���İ�
			msgQueueName->hdr = ((msgPackHQS_t *)(msgQueueName->hdr))->next; //
			((msgPackHQS_t *)(msgQueueName->end))->next = msgPack; //ԭ���ж�δ�� ָ��˰�
			msgQueueName->end = msgPack; //�ж�ĩβҲָ��˰�
			break;
		case  FLU_LIFO_RENOUNCE:

			 msgPackDel = (msgPackHQS_t *)(msgQueueName->end);//����ȥ���İ�
			 pres = prev = (msgPackHQS_t *)msgQueueName->hdr; 
			 count = 0;
			 //Ѱ���ж� �����ڶ��� ��Ϣ��
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
						if (count != msgQueueName->fluidicCount) //������֤HQS
						{
							err = Msg_Err_Queue;//�жӳ��� ��������
							msgPackDel = msgPack;
							while (1);
							break;
						}

						prev->next = NULL; //�����ڶ��� �������ĩβ�İ���next ΪNULL
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
		HQSmemPithyFree(msgPackDel->msgDataAdd); //�ͷ���Ϣ���ݿռ䣨�û�������memPithyHQS ����ռ䣩
		HQSmemPithyFree(msgPackDel);             //ɾ����Ϣ��

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
				if (msgQueueName->fluidicCount != 0 || msgQueueName->end != NULL) //��֤ ��ȥ��
				{
					err = Msg_Err_Queue;//�жӳ���
					while (1);
				}
				else
				{
					msgQueueName->hdr = msgQueueName->end = msgPack; //�ж�ͷβ��ָ��˰�
					
				}
			}
		}
		else
		{
			//FIFO
			if (msgQueueName->end)
			{
				((msgPackHQS_t *)(msgQueueName->end))->next = msgPack; //ԭ���жӰ� ָ��˰�
				msgQueueName->end = msgPack; //�ж�ĩβҲָ��˰�
				
			}
			else
			{
				if (msgQueueName->fluidicCount != 0 || msgQueueName->hdr != NULL) //��֤ ��ȥ��
				{
					err = Msg_Err_Queue;//�жӳ���
					while (1);
				}
				else
				{
					msgQueueName->hdr = msgQueueName->end = msgPack; //�ж�ͷβ��ָ��˰�
					
				}
			}
		}

		msgQueueName->fluidicCount += 1;

		if (err == Msg_Err_Queue)
		{
			HQSmemPithyFree(msgPack->msgDataAdd); //�ͷ���Ϣ���ݿռ䣨�û�������memPithyHQS ����ռ䣩
			HQSmemPithyFree(msgPack); //ɾ����Ϣ��
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
		msgPack = (msgPackHQS_t *)(msgQueueName->hdr); //���а����
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
			if (msgQueueName->fluidicCount == 0) //��֤ ��ȥ��
			{
				msgQueueName->end = msgQueueName->hdr = msgPackTemp; //
			}
			else
			{
				while (1);
			}
		}
		msgPack->next = NULL;//��ֹ�û��õ�
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






