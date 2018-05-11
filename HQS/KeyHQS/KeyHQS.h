/********************************************************
版权归HuQiaoshen 参考学习需联系作者授权 盗版必究 
;按键处理通用程序
;可处理：
;       按键下、弹起、单击、双击、多次点击
;       长按、连按
;              

;作    者：胡乔申
;时    间：2016.9.6
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
  未经同意授权 造成作者损失 承担相关法律责任
    Copyright (c) 2012-2099 HQS
*********************************************************/

#ifndef _KeyHQS_H_
#define _KeyHQS_H_
#include "HQS_typedef.h"

#define  KEYHQStyp                uint16    //一个bit代表一个按键
#define  KEYHQS_StartValue         0x00    //初始无任何按键按下值
#define  KEYHQS_TAPLongTimeOut     300     //长按超时阀值
#define  KEYHQS_TAPSeriesTimeOut   160     //连按超时阀值

//@LongSerie
typedef enum KEYHQSLongSerie_m
{
 KEYHQSSERIES_NOTLS  =(uint8)0 ,       //都不是
 KEYHQSSERIES_Serie  ,                 //连按
 KEYHQSSERIES_Long                     //长按
}KEYHQSLongSerie_m;

//@UpDown
typedef enum KEYHQSUpDown_m
{
 KEYHQSPREESS_NOT   = (uint8)0,        //无操作
 KEYHQSPREESS_UP    ,                  //弹起
 KEYHQSPREESS_DOWN                     //按下
}KEYHQSUpDown_m;

typedef struct {
	uint8               use;         //使用标志
	KEYHQStyp           value;       //键值
	KEYHQSUpDown_m      UpDown;      //按下弹起状态 @KEYHQSUpDown_m
	KEYHQSLongSerie_m   LongSerie;   //长按连按状态 @KEYHQSLongSerie_m
	uint8               Seriescount; //连续按次数	
}KeyHQSMessage_t;

volatile KeyHQSMessage_t KeyHQSMessage;


/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：HQSKeyMessage_MACRO(KeyHQSMessage)
;说    明：宏函数，调用用户自己编写函数
           当发生按键值 或 状态放生变化（参考：KeyHQSMessage_t），KeyHQSMessage_t.use 置一，使用完成用户清零
;使用资源：
;入    口：
;出    口：
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2017.05.10
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
#define HQSKeyMessage_MACRO(KeyHQSMessage)   //用户添加 key 发送消息函数



/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void HQSKeyInit(void)
;说    明：按键处理初始化
;使用资源：
;入    口：
;出    口：
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2017.05.10
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void HQSKeyInit(void);



/********************************************************
版权归作者所有 参考学习需联系作者授权 盗版必究
;函数名称：void HQSKeyUpDate(KEYHQStyp Date)
;说    明：数据分析函数
;使用资源：
;入    口：
;出    口：
;硬件接口:
;作    者：胡乔申 545044533@qq.com 13127766030
;时    间：2017.05.10
;修改注释：
;注意事项：
;版    本：V1.00
版权归作者所有   参考学习需联系作者授权    盗版必究
未经同意授权 造成作者损失 承担相关法律责任
Copyright (c) 2012-2099 HQS
*********************************************************/
void HQSKeyUpDate(KEYHQStyp Date);

#endif


