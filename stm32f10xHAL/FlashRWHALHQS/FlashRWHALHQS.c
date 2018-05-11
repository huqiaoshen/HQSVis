
#include "FlashRWHALHQS.h"


uint16 FlashEEPROMBuffer[PAGE_SIZE / 2]; //��ʱ�������

void FlashEEPROMReadOriginalHALHQS(uint32 DataAddr, uint16 *readBuffer, uint16 length);

void FlashEEPROMReadHALHQS(uint32 DataAddr,uint16 *readBuffer,uint16 length)
{
	uint16 i;
	DataAddr=DataAddr*2+EEPROM_START_ADDRESS;
	for(i=0;i<length;i++)
	{
	 *(readBuffer+i)=*(volatile uint16*)DataAddr;    //2���ֽ�.
	 DataAddr+=2;                                    //ƫ��2���ֽ�.	
	}
}

//��ȡʵ�ʵ�ַ
void * FlashOriginalHALHQS(uint32 DataAddr)
{
	DataAddr = DataAddr * 2 + EEPROM_START_ADDRESS;
	return (void*)DataAddr;
}

void FlashEEPROMWriteHALHQS(uint32 DataAddr,uint16 *writeBuffer,uint16 length)
{
 uint16   i;
 uint32   PageAddrHead;       //��ҳͷ��ַ
 uint16   pageSpareLength;    //ҳʣ��ռ��С	
 uint16 * FlashEEPROMBuffeP;  //Ҫ�޸Ļ���洢��ʼ��ַ 

 //ת��Ϊflashֱ�ӵ�ַ
 DataAddr=DataAddr*2+EEPROM_START_ADDRESS;
	
 if( DataAddr < EEPROM_START_ADDRESS || DataAddr>PAGE_END_ADDRESS)
	 return;//��ַ����
 if(DataAddr+length>PAGE_END_ADDRESS)
	 return; //�洢���ݳ���


 
 //�ҵ��洢ҳ���׵�ַ
 PageAddrHead=EEPROM_START_ADDRESS + PAGE_SIZE *((DataAddr-EEPROM_START_ADDRESS)/PAGE_SIZE);

 //ʣ��ռ��С
 pageSpareLength  = (PageAddrHead+PAGE_SIZE - DataAddr)/2;
  
// //�����滻��ʼλ��
// buffei=(DataAddr-PageAddrHead)>>1;
 
 //Ҫ�޸Ļ���洢��ʼ��ַ
 FlashEEPROMBuffeP=FlashEEPROMBuffer+((DataAddr-PageAddrHead)/2);
 
 
 FLASH_Unlock();//����
 
 while(1)
 {
	 //ԭ��flash���ݣ�������ʱ����
	 FlashEEPROMReadOriginalHALHQS(PageAddrHead,FlashEEPROMBuffer,PAGE_SIZE/2);
	 
	 //�޸�Ҫ�洢�Ĵ洢 
	 for(i=0;i<pageSpareLength;i++)
	 {
		*(FlashEEPROMBuffeP+i)=  *(writeBuffer+i);
	 }
	 
	 //������ҳ
		FLASH_ErasePage(PageAddrHead);
	 
	 //д��
		for(i=0;i<PAGE_SIZE/2;i++)
		{
			FLASH_ProgramHalfWord(PageAddrHead+i*2,*(FlashEEPROMBuffer+i));
		}  
	 
	 if(pageSpareLength >= length)
	 { 
		//�洢����˳�ѭ��
		 return;
	 }
	 else
	 { 	 
		 //��ҳ��ȫд��,�����¸�����ҳ
 
		 //Ҫ�洢ʣ�����ݴ�С
		 length=length-pageSpareLength; 
		
		 //��洢��ַ��δ�������׵�ַ
		 writeBuffer = writeBuffer+pageSpareLength;	
		
		 //��ҳ��ʼͷ��ַ
		 PageAddrHead=PageAddrHead+PAGE_SIZE;
		 //��ҳ�Ŀռ��С
		 pageSpareLength=PAGE_SIZE/2;

		 //��ֹʣ������С�� ����ҳ����ȫ���޸�  20180104 ����BUG �޸�
		 if (pageSpareLength > length)
		 {
			 pageSpareLength = length;
		 }
		 //20180104  BUG    END

		 //Ҫ�޸Ļ���洢��ʼ��ַ,ֱ�Ӵӵ�һ�����濪ʼ	 
		 FlashEEPROMBuffeP=FlashEEPROMBuffer;
	 }
 }
 	
 FLASH_Lock();//���� 
 	//�洢���
  return;
}


//ֱ�ӵ�ַ��ȡ
void FlashEEPROMReadOriginalHALHQS(uint32 DataAddr, uint16 *readBuffer, uint16 length)
{
	uint16 i;
	//DataAddr=DataAddr*2+EEPROM_START_ADDRESS;
	for (i = 0; i<length; i++)
	{
		*(readBuffer + i) = *(volatile uint16*)DataAddr;    //2���ֽ�.
		DataAddr += 2;                                    //ƫ��2���ֽ�.	
	}
}





