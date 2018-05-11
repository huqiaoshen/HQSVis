#include "memPithyHQS.h"

volatile memPithyHQSHdr_t * startHdrPithy;  //�ڴ����ʼλ��
volatile memPithyHQSHdr_t memPithyHQSHeap[MEMPithyHQSMaxHeap / MEMPithyHQSHdrSize];

void HQSmemPithyInit(void)
{
#if MEMPithyHQSAlignEnable //�ֽڶ��봦��
	uint8 * originalP,* alignP; 
	MEMPithyHQStyp throwSize;  //������С
	originalP =memPithyHQSHeap; //ԭʼ�ڴ�� �׵�ַ;
	if ((HQSPointerSize_t)memPithyHQSHeap & MEMPithyHQSAlignment)
	{
		alignP = (uint8 *)((HQSPointerSize_t)((HQSPointerSize_t)memPithyHQSHeap + MEMPithyHQSAlignSize)&((HQSPointerSize_t)~MEMPithyHQSAlignment)); //���봦��
		startHdrPithy = (memPithyHQSHdr_t *)alignP;
		throwSize = (MEMPithyHQStyp)(alignP - originalP);
	}
	else
	{
		startHdrPithy = (memPithyHQSHdr_t *)memPithyHQSHeap;
		throwSize = 0;
	}
	startHdrPithy->useSize.size = MEMPithyHQSMaxHeap - throwSize - MEMPithyHQSHdrSize * 2; //MEMPithyHQSHdrSize*2 ͷ��β��ռһ����Ϣ�洢λ��
#else
	startHdrPithy = memPithyHQSHeap;
	startHdrPithy->useSize.size = MEMPithyHQSMaxHeap - MEMPithyHQSHdrSize*2;
#endif 
	(memPithyHQSHeap+ MEMPithyHQSBottomSize)->data = 0;
}


void * HQSmemPithyMalloc(MEMPithyHQStyp sizeMalloc)
{
	if (sizeMalloc == 0)
	{
		return NULL;
	}
#if MEMPithyHQSAlignEnable  //�ֽڶ��봦��(ż���㷨)
	if (sizeMalloc & MEMPithyHQSAlignment)
	{/* ����ʹ���ֽڶ���. */
		sizeMalloc += (MEMPithyHQSAlignSize - (sizeMalloc & MEMPithyHQSAlignment));
	}
#else

	//2018.1.6BUG �������
	if (sizeMalloc & (MEMPithyHQSHdrSize-1)) //��ֹ(ż���㷨) ��ע���������Ǹ��㷨��
	{
		sizeMalloc += (MEMPithyHQSHdrSize - (sizeMalloc & (MEMPithyHQSHdrSize-1)));
	}



	sizeMalloc += MEMPithyHQSHdrSize;
#endif
	uint8 *hdr;
	hdr = (uint8 *)startHdrPithy;
	/*���ÿռ��ַ����*/
	do
	{
		if (((memPithyHQSHdr_t *)hdr)->useSize.use == 0)
		{
			if(((memPithyHQSHdr_t *)hdr)->useSize.size >= sizeMalloc)
			{
			 break;
		    }
		}
		hdr = hdr + ((memPithyHQSHdr_t *)hdr)->useSize.size;

		if (((memPithyHQSHdr_t *)hdr)->data == 0) //����
		{
			hdr = NULL;
			break;
		}
	} while (1);
  
	/*��Ϣ�����*/
	if (hdr != NULL)
	{
		MEMPithyHQStyp surplus = ((memPithyHQSHdr_t *)hdr)->useSize.size - sizeMalloc; //ʣ��ռ��С
		//2018.1.6 ����BUG ����surplus =0ʱ ���� С����Ϣ��ߴ��С  �����ƻ�ԭ����һ�� ��Ϣ������
		//2018.1.6 ����ȫ��ʹ�øÿռ� ������¸��ڴ�ع������Ϊ0 ���ڴ��������
		if (surplus != 0)
		{
			memPithyHQSHdr_t *nextHdr = (memPithyHQSHdr_t *)(hdr + sizeMalloc);  //�ָ�¸���Ϣ���ַ
			nextHdr->data = surplus;
		}

		((memPithyHQSHdr_t *)hdr)->data = (MEMPithyHQSUse| sizeMalloc);
		hdr = hdr + MEMPithyHQSHdrSize; 

	}
	return hdr;

}

void HQSmemPithyFree(void *freeP)
{
  uint8 *hdr, *prev;
  static uint8 seek = 0;

  if (freeP == NULL)
  {
	  return;
  }
  hdr = (uint8 *)startHdrPithy;
 ((memPithyHQSHdr_t *)((HQSPointerSize_t)freeP - MEMPithyHQSHdrSize))->useSize.use = 0;

 /*���ÿռ��ַ����*/
 do
 {
	 if (((memPithyHQSHdr_t *)hdr)->useSize.use)
	 {
		 seek = 0;
	 }
	 else
	 {
		 if (seek)
		 {
			 ((memPithyHQSHdr_t *)prev)->useSize.size += ((memPithyHQSHdr_t *)hdr)->useSize.size;
		 }
		 else
		 {
			 seek = 1;
			 prev = hdr;
		 }
	 }
	 hdr = hdr + ((memPithyHQSHdr_t *)hdr)->useSize.size;

	 if (((memPithyHQSHdr_t *)hdr)->data == 0) //����
	 {
		 break;
	 }
 } while (1);
}

//MEMPithyHQStyp HQSmemPithySize(void * dataAdd)
//{
//	return ((memPithyHQSHdr_t *)((HQSPointerSize_t)dataAdd - MEMPithyHQSHdrSize))->useSize.size-MEMPithyHQSHdrSize;
//}
//void HQSmemPithyFasten(void)
//{
//	uint8 *hdr;
//	hdr = (uint8 *)startHdrPithy;
//
//	/*���ÿռ��ַ����*/
//	do
//	{
//		if (((memPithyHQSHdr_t *)hdr)->useSize.use==0)
//		{
//			startHdrPithy = (memPithyHQSHdr_t *)hdr;
//			break;
//		}
//		hdr = hdr + ((memPithyHQSHdr_t *)hdr)->useSize.size;
//
//		if (((memPithyHQSHdr_t *)hdr)->data == 0) //����
//		{
//			break;
//		}
//	} while (1);
//}



