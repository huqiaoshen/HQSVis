
#include "BKPHAL.h"



void BKPHALWirte(uint16 BKP_DR,uint16 data)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE); //ʹ�ܺ󱸼Ĵ�������
	BKP_WriteBackupRegister(BKP_DR, data);
	PWR_BackupAccessCmd(DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE);
}



uint16 BKPHALRead(uint16 BKP_DR )
{
	uint16 data=0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE); //ʹ�ܺ󱸼Ĵ�������
	data = BKP_ReadBackupRegister(BKP_DR);
	PWR_BackupAccessCmd(DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE);
	return data;

}