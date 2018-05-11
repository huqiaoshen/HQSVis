#include "memPithyHQS.h"

volatile memPithyHQSHdr_t * startHdrPithy;  //内存池起始位置
volatile memPithyHQSHdr_t memPithyHQSHeap[MEMPithyHQSMaxHeap / MEMPithyHQSHdrSize];

void HQSmemPithyInit(void)
{
#if MEMPithyHQSAlignEnable //字节对齐处理
	uint8 * originalP,* alignP; 
	MEMPithyHQStyp throwSize;  //丢弃大小
	originalP =memPithyHQSHeap; //原始内存池 首地址;
	if ((HQSPointerSize_t)memPithyHQSHeap & MEMPithyHQSAlignment)
	{
		alignP = (uint8 *)((HQSPointerSize_t)((HQSPointerSize_t)memPithyHQSHeap + MEMPithyHQSAlignSize)&((HQSPointerSize_t)~MEMPithyHQSAlignment)); //对齐处理
		startHdrPithy = (memPithyHQSHdr_t *)alignP;
		throwSize = (MEMPithyHQStyp)(alignP - originalP);
	}
	else
	{
		startHdrPithy = (memPithyHQSHdr_t *)memPithyHQSHeap;
		throwSize = 0;
	}
	startHdrPithy->useSize.size = MEMPithyHQSMaxHeap - throwSize - MEMPithyHQSHdrSize * 2; //MEMPithyHQSHdrSize*2 头、尾各占一个信息存储位置
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
#if MEMPithyHQSAlignEnable  //字节对齐处理(偶数算法)
	if (sizeMalloc & MEMPithyHQSAlignment)
	{/* 调整使其字节对齐. */
		sizeMalloc += (MEMPithyHQSAlignSize - (sizeMalloc & MEMPithyHQSAlignment));
	}
#else

	//2018.1.6BUG 解决增加
	if (sizeMalloc & (MEMPithyHQSHdrSize-1)) //防止(偶数算法) （注意奇数不是该算法）
	{
		sizeMalloc += (MEMPithyHQSHdrSize - (sizeMalloc & (MEMPithyHQSHdrSize-1)));
	}



	sizeMalloc += MEMPithyHQSHdrSize;
#endif
	uint8 *hdr;
	hdr = (uint8 *)startHdrPithy;
	/*可用空间地址查找*/
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

		if (((memPithyHQSHdr_t *)hdr)->data == 0) //到底
		{
			hdr = NULL;
			break;
		}
	} while (1);
  
	/*信息块填充*/
	if (hdr != NULL)
	{
		MEMPithyHQStyp surplus = ((memPithyHQSHdr_t *)hdr)->useSize.size - sizeMalloc; //剩余空间大小
		//2018.1.6 发现BUG ，当surplus =0时 或者 小于信息块尺寸大小  填充会破会原来下一个 信息块内容
		//2018.1.6 正好全部使用该空间 ，填充下个内存池管理块会为0 （内存池缩减）
		if (surplus != 0)
		{
			memPithyHQSHdr_t *nextHdr = (memPithyHQSHdr_t *)(hdr + sizeMalloc);  //分割，下个信息块地址
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

 /*可用空间地址查找*/
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

	 if (((memPithyHQSHdr_t *)hdr)->data == 0) //到底
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
//	/*可用空间地址查找*/
//	do
//	{
//		if (((memPithyHQSHdr_t *)hdr)->useSize.use==0)
//		{
//			startHdrPithy = (memPithyHQSHdr_t *)hdr;
//			break;
//		}
//		hdr = hdr + ((memPithyHQSHdr_t *)hdr)->useSize.size;
//
//		if (((memPithyHQSHdr_t *)hdr)->data == 0) //到底
//		{
//			break;
//		}
//	} while (1);
//}




