/**************************************************************************************************
  Filename:       HQS_typedef.h


  V1.01


  Copyright 2006-2007 HQS. All rights reserved.
**************************************************************************************************/


#ifndef _HQS_TYPES_H__
#define _HQS_TYPES_H__


/* ------------------------------------------------------------------------------------------------
 *                                               Types
 * ------------------------------------------------------------------------------------------------
 */
typedef signed   char         int8;   //1�ֽ�|-128~127
typedef unsigned char         uint8;  //1�ֽ�| 0~255

typedef signed   short int   int16;   //2�ֽ�|-32768~32767
typedef unsigned short int   uint16;  //2�ֽ�|0~65535

typedef signed   int         int32;   //4�ֽ�|-2147483648~2147483647
typedef unsigned int         uint32;  //4�ֽ�|0~4294967295

typedef signed   long long int   int64;    //8�ֽ�|
typedef long long unsigned int  uint64;    //8�ֽ�|

typedef unsigned  char   bool;

typedef  uint64 HQSDataAlign_t; //���ݶ��� ,��ͨ������ �����С��ͬ

#define ____HQSPSIZE_____  4   //ϵͳָ���С
#if ____HQSPSIZE_____ == 1
typedef  uint8  HQSPointerSize_t;
#endif //____HQSPSIZE_____ == 1

#if ____HQSPSIZE_____ == 2
typedef  uint16  HQSPointerSize_t;
#endif //____HQSPSIZE_____ == 2

#if ____HQSPSIZE_____ == 4
typedef  uint32  HQSPointerSize_t;
#endif //____HQSPSIZE_____ == 4

#if ____HQSPSIZE_____ == 8
typedef  uint64  HQSPointerSize_t;
#endif //____HQSPSIZE_____ == 8


/* ------------------------------------------------------------------------------------------------
 *                                        Standard Defines
 * ------------------------------------------------------------------------------------------------
 */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif


/**************************************************************************************************
 */
#endif

