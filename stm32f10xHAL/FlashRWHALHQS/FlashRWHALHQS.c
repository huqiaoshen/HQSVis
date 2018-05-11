
#include "FlashRWHALHQS.h"


uint16 FlashEEPROMBuffer[PAGE_SIZE / 2]; //零时存放数据

void FlashEEPROMReadOriginalHALHQS(uint32 DataAddr, uint16 *readBuffer, uint16 length);

void FlashEEPROMReadHALHQS(uint32 DataAddr,uint16 *readBuffer,uint16 length)
{
	uint16 i;
	DataAddr=DataAddr*2+EEPROM_START_ADDRESS;
	for(i=0;i<length;i++)
	{
	 *(readBuffer+i)=*(volatile uint16*)DataAddr;    //2个字节.
	 DataAddr+=2;                                    //偏移2个字节.	
	}
}

//获取实际地址
void * FlashOriginalHALHQS(uint32 DataAddr)
{
	DataAddr = DataAddr * 2 + EEPROM_START_ADDRESS;
	return (void*)DataAddr;
}

void FlashEEPROMWriteHALHQS(uint32 DataAddr,uint16 *writeBuffer,uint16 length)
{
 uint16   i;
 uint32   PageAddrHead;       //本页头地址
 uint16   pageSpareLength;    //页剩余空间大小	
 uint16 * FlashEEPROMBuffeP;  //要修改缓存存储起始地址 

 //转化为flash直接地址
 DataAddr=DataAddr*2+EEPROM_START_ADDRESS;
	
 if( DataAddr < EEPROM_START_ADDRESS || DataAddr>PAGE_END_ADDRESS)
	 return;//地址超界
 if(DataAddr+length>PAGE_END_ADDRESS)
	 return; //存储数据超界


 
 //找到存储页的首地址
 PageAddrHead=EEPROM_START_ADDRESS + PAGE_SIZE *((DataAddr-EEPROM_START_ADDRESS)/PAGE_SIZE);

 //剩余空间大小
 pageSpareLength  = (PageAddrHead+PAGE_SIZE - DataAddr)/2;
  
// //缓存替换起始位置
// buffei=(DataAddr-PageAddrHead)>>1;
 
 //要修改缓存存储起始地址
 FlashEEPROMBuffeP=FlashEEPROMBuffer+((DataAddr-PageAddrHead)/2);
 
 
 FLASH_Unlock();//解锁
 
 while(1)
 {
	 //原来flash数据，读入零时缓存
	 FlashEEPROMReadOriginalHALHQS(PageAddrHead,FlashEEPROMBuffer,PAGE_SIZE/2);
	 
	 //修改要存储的存储 
	 for(i=0;i<pageSpareLength;i++)
	 {
		*(FlashEEPROMBuffeP+i)=  *(writeBuffer+i);
	 }
	 
	 //擦除该页
		FLASH_ErasePage(PageAddrHead);
	 
	 //写入
		for(i=0;i<PAGE_SIZE/2;i++)
		{
			FLASH_ProgramHalfWord(PageAddrHead+i*2,*(FlashEEPROMBuffer+i));
		}  
	 
	 if(pageSpareLength >= length)
	 { 
		//存储完成退出循环
		 return;
	 }
	 else
	 { 	 
		 //该页完全写完,进入下个完整页
 
		 //要存储剩余数据大小
		 length=length-pageSpareLength; 
		
		 //需存储地址到未存数据首地址
		 writeBuffer = writeBuffer+pageSpareLength;	
		
		 //新页起始头地址
		 PageAddrHead=PageAddrHead+PAGE_SIZE;
		 //新页的空间大小
		 pageSpareLength=PAGE_SIZE/2;

		 //防止剩余数据小于 导致页数据全部修改  20180104 发现BUG 修复
		 if (pageSpareLength > length)
		 {
			 pageSpareLength = length;
		 }
		 //20180104  BUG    END

		 //要修改缓存存储起始地址,直接从第一个缓存开始	 
		 FlashEEPROMBuffeP=FlashEEPROMBuffer;
	 }
 }
 	
 FLASH_Lock();//上锁 
 	//存储完成
  return;
}


//直接地址读取
void FlashEEPROMReadOriginalHALHQS(uint32 DataAddr, uint16 *readBuffer, uint16 length)
{
	uint16 i;
	//DataAddr=DataAddr*2+EEPROM_START_ADDRESS;
	for (i = 0; i<length; i++)
	{
		*(readBuffer + i) = *(volatile uint16*)DataAddr;    //2个字节.
		DataAddr += 2;                                    //偏移2个字节.	
	}
}






