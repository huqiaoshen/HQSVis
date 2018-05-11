
#include  "KeyHQS.h"

typedef struct {
	uint8     use;
	KEYHQStyp value;       //键值
	KEYHQStyp oldValue;    //上次值
	uint8     UpDown;      //按下弹起状态
	uint8     LongSerie;   //长按连按状态
	uint8     Seriescount; //连续按次数	
}KeyStatusData_t;

typedef struct {
  uint16 SeriesTime;  //连续按键计时
  uint16 LongTime;    //长按计时
}KeyTime_t;

volatile KeyTime_t        KeyTime;
volatile KeyStatusData_t  KeyStatusData;

void HQSKeyInit(void)
{
 KeyStatusData.use         = 0;
 KeyStatusData.value       = KEYHQS_StartValue;    //键值
 KeyStatusData.oldValue    = KEYHQS_StartValue;    //上次值
 KeyStatusData.UpDown      = KEYHQSPREESS_NOT;     //按下弹起状态
 KeyStatusData.LongSerie   = KEYHQSSERIES_NOTLS;   //长按连按状态
 KeyStatusData.Seriescount =0;                  //连续按次数	
 KeyTime.SeriesTime=0;	
 KeyTime.LongTime=0; 
}	

void HQSKeyUpDate(KEYHQStyp Date)
{
  if(Date!= KEYHQS_StartValue) //按下	
	{
	 KeyStatusData.value  = Date;
	 if(KeyStatusData.oldValue==Date) //地二次采集
	 {
		if(KeyStatusData.UpDown == KEYHQSPREESS_DOWN) //上次为按下状态
		{
			if(KeyTime.LongTime<KEYHQS_TAPLongTimeOut)
			{
				KeyTime.LongTime++;
			}
			else
			{
			 //长按	
			 if(KeyStatusData.LongSerie != KEYHQSSERIES_Long)
			 {
				 KeyStatusData.LongSerie = KEYHQSSERIES_Long;
				 KeyStatusData.use = 1;
				 //Serial_Send_String("KEYHQSSERIES_Long\n");	
				 //发送消息
				 KeyHQSMessage.value       = KeyStatusData.value;
				 KeyHQSMessage.UpDown      = KeyStatusData.UpDown;
				 KeyHQSMessage.LongSerie   = KeyStatusData.LongSerie;
				 KeyHQSMessage.Seriescount = KeyStatusData.Seriescount;
				 KeyHQSMessage.use         = 1;
				 HQSKeyMessage_MACRO(KeyHQSMessage);
							 
			 } 
			}				
		}
		else    //上次为弹起状态
		{
			KeyStatusData.UpDown = KEYHQSPREESS_DOWN; //设为按下状态 
			KeyStatusData.LongSerie = KEYHQSSERIES_Serie;
			KeyStatusData.Seriescount++;
			KeyTime.SeriesTime = 0;
			KeyStatusData.use = 1;
			// Serial_Send_String("KEYHQSSERIES_Serie\n");
		    //发送消息
			KeyHQSMessage.value       = KeyStatusData.value;
			KeyHQSMessage.UpDown      = KeyStatusData.UpDown;
			KeyHQSMessage.LongSerie   = KeyStatusData.LongSerie;
			KeyHQSMessage.Seriescount = KeyStatusData.Seriescount;
			KeyHQSMessage.use = 1;
			HQSKeyMessage_MACRO(KeyHQSMessage);
		}
	 }
	 else  //键值不同 
	 { 		 
		 KeyStatusData.UpDown      = KEYHQSPREESS_DOWN; //设置为按下状态 		 
		 KeyStatusData.LongSerie   = KEYHQSSERIES_NOTLS; //不是连按也不是长按
		 KeyStatusData.Seriescount = 0;
	     KeyStatusData.oldValue    = Date; 
		 KeyTime.SeriesTime        = 0;
		 KeyTime.LongTime          = 0;
		 KeyStatusData.Seriescount = 0;
	     KeyStatusData.use         = 1;
		 //Serial_Send_String("KEYHQSPREESS_DOWN\n");
		 //发送消息
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
	 //弹起
	 KeyTime.LongTime  = 0; 
	 if(KeyStatusData.UpDown != KEYHQSPREESS_NOT)
	 {
		 if(KeyTime.SeriesTime<KEYHQS_TAPSeriesTimeOut)
		 {
			 if(KeyStatusData.UpDown == KEYHQSPREESS_DOWN) //保证发送一次消息
			 {
			  KeyStatusData.UpDown    = KEYHQSPREESS_UP;
			  KeyStatusData.use  =  1;		
              //  Serial_Send_String("KEYHQSPREESS_UP\n");

			  //发送消息
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
			//无任何操作
			KeyStatusData.UpDown      = KEYHQSPREESS_NOT;
			KeyStatusData.LongSerie   = KEYHQSSERIES_NOTLS;
			KeyStatusData.Seriescount = 0; 
			KeyStatusData.value       = KEYHQS_StartValue;
			KeyStatusData.oldValue    = KEYHQS_StartValue;	 	
		 }	 
	   }
	}	
}


