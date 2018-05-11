
#include  "KeyHQS.h"

typedef struct {
	uint8     use;
	KEYHQStyp value;       //��ֵ
	KEYHQStyp oldValue;    //�ϴ�ֵ
	uint8     UpDown;      //���µ���״̬
	uint8     LongSerie;   //��������״̬
	uint8     Seriescount; //����������	
}KeyStatusData_t;

typedef struct {
  uint16 SeriesTime;  //����������ʱ
  uint16 LongTime;    //������ʱ
}KeyTime_t;

volatile KeyTime_t        KeyTime;
volatile KeyStatusData_t  KeyStatusData;

void HQSKeyInit(void)
{
 KeyStatusData.use         = 0;
 KeyStatusData.value       = KEYHQS_StartValue;    //��ֵ
 KeyStatusData.oldValue    = KEYHQS_StartValue;    //�ϴ�ֵ
 KeyStatusData.UpDown      = KEYHQSPREESS_NOT;     //���µ���״̬
 KeyStatusData.LongSerie   = KEYHQSSERIES_NOTLS;   //��������״̬
 KeyStatusData.Seriescount =0;                  //����������	
 KeyTime.SeriesTime=0;	
 KeyTime.LongTime=0; 
}	

void HQSKeyUpDate(KEYHQStyp Date)
{
  if(Date!= KEYHQS_StartValue) //����	
	{
	 KeyStatusData.value  = Date;
	 if(KeyStatusData.oldValue==Date) //�ض��βɼ�
	 {
		if(KeyStatusData.UpDown == KEYHQSPREESS_DOWN) //�ϴ�Ϊ����״̬
		{
			if(KeyTime.LongTime<KEYHQS_TAPLongTimeOut)
			{
				KeyTime.LongTime++;
			}
			else
			{
			 //����	
			 if(KeyStatusData.LongSerie != KEYHQSSERIES_Long)
			 {
				 KeyStatusData.LongSerie = KEYHQSSERIES_Long;
				 KeyStatusData.use = 1;
				 //Serial_Send_String("KEYHQSSERIES_Long\n");	
				 //������Ϣ
				 KeyHQSMessage.value       = KeyStatusData.value;
				 KeyHQSMessage.UpDown      = KeyStatusData.UpDown;
				 KeyHQSMessage.LongSerie   = KeyStatusData.LongSerie;
				 KeyHQSMessage.Seriescount = KeyStatusData.Seriescount;
				 KeyHQSMessage.use         = 1;
				 HQSKeyMessage_MACRO(KeyHQSMessage);
							 
			 } 
			}				
		}
		else    //�ϴ�Ϊ����״̬
		{
			KeyStatusData.UpDown = KEYHQSPREESS_DOWN; //��Ϊ����״̬ 
			KeyStatusData.LongSerie = KEYHQSSERIES_Serie;
			KeyStatusData.Seriescount++;
			KeyTime.SeriesTime = 0;
			KeyStatusData.use = 1;
			// Serial_Send_String("KEYHQSSERIES_Serie\n");
		    //������Ϣ
			KeyHQSMessage.value       = KeyStatusData.value;
			KeyHQSMessage.UpDown      = KeyStatusData.UpDown;
			KeyHQSMessage.LongSerie   = KeyStatusData.LongSerie;
			KeyHQSMessage.Seriescount = KeyStatusData.Seriescount;
			KeyHQSMessage.use = 1;
			HQSKeyMessage_MACRO(KeyHQSMessage);
		}
	 }
	 else  //��ֵ��ͬ 
	 { 		 
		 KeyStatusData.UpDown      = KEYHQSPREESS_DOWN; //����Ϊ����״̬ 		 
		 KeyStatusData.LongSerie   = KEYHQSSERIES_NOTLS; //��������Ҳ���ǳ���
		 KeyStatusData.Seriescount = 0;
	     KeyStatusData.oldValue    = Date; 
		 KeyTime.SeriesTime        = 0;
		 KeyTime.LongTime          = 0;
		 KeyStatusData.Seriescount = 0;
	     KeyStatusData.use         = 1;
		 //Serial_Send_String("KEYHQSPREESS_DOWN\n");
		 //������Ϣ
		 KeyHQSMessage.value = KeyStatusData.value;
		 KeyHQSMessage.UpDown = KeyStatusData.UpDown;
		 KeyHQSMessage.LongSerie = KeyStatusData.LongSerie;
		 KeyHQSMessage.Seriescount = KeyStatusData.Seriescount;
		 KeyHQSMessage.use = 1;
		 HQSKeyMessage_MACRO(KeyHQSMessage);	
	 }
	}
	else
	{
	 //����
	 KeyTime.LongTime  = 0; 
	 if(KeyStatusData.UpDown != KEYHQSPREESS_NOT)
	 {
		 if(KeyTime.SeriesTime<KEYHQS_TAPSeriesTimeOut)
		 {
			 if(KeyStatusData.UpDown == KEYHQSPREESS_DOWN) //��֤����һ����Ϣ
			 {
			  KeyStatusData.UpDown    = KEYHQSPREESS_UP;
			  KeyStatusData.use  =  1;		
              //  Serial_Send_String("KEYHQSPREESS_UP\n");

			  //������Ϣ
			  KeyHQSMessage.value = KeyStatusData.value;
			  KeyHQSMessage.UpDown = KeyStatusData.UpDown;
			  KeyHQSMessage.LongSerie = KeyStatusData.LongSerie;
			  KeyHQSMessage.Seriescount = KeyStatusData.Seriescount;
			  KeyHQSMessage.use = 1;
			  HQSKeyMessage_MACRO(KeyHQSMessage);
			 }
			 KeyTime.SeriesTime++; 
		 }
		 else
		 {
			//���κβ���
			KeyStatusData.UpDown      = KEYHQSPREESS_NOT;
			KeyStatusData.LongSerie   = KEYHQSSERIES_NOTLS;
			KeyStatusData.Seriescount = 0; 
			KeyStatusData.value       = KEYHQS_StartValue;
			KeyStatusData.oldValue    = KEYHQS_StartValue;	 	
		 }	 
	   }
	}	
}

